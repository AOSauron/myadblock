#include "sockets.h"
#include "messages.h"
#include "util.h"

// pour telecom-> pourquoi ça marche pas???


int main(int argc, char *argv[]){
	iniListe();

	// declarations
	int server[2];
	int tab_ecoute_clients[FD_SETSIZE];
	int tab_ecoute_servers[FD_SETSIZE];
	int maxfdp1;
	int nbfd;
	int i;
	fd_set rset;
	fd_set pset;
	

	// il faut renseigner le port
	if(argc != 2){
		printf("usage : servecho numero_port_serveur\n");
		exit(1);
	}

	
	// on créé le serveur sur le port demandé
	newServer(&server,argv[1]);
 

	// on initialise les descripteurs et on commence l'ecoute
	FD_ZERO(&pset);
	FD_ZERO(&rset);
	FD_SET(server[0], &rset);
	FD_SET(server[1], &rset);

	//mis à jour du plus grand fd
	maxfdp1 = server[0] +1;
	maxfdp1 = MaJ_maxFD(server[1],maxfdp1);
	
	
	// initialisations
	nbfd = 0;
	i = 0;
	for (i=0;i<FD_SETSIZE;i++){
		tab_ecoute_clients[i] = -1;
		tab_ecoute_servers[i] = -1;
	}
	


	printf("\nMyAddBlock est bien lancé.\n\n");

	for(;;){

		//initialisation des fd_set puis SELECT
		pset=rset;
		nbfd=select(maxfdp1,&pset,NULL,NULL,NULL);
		if (nbfd==-1) {
			perror("Erreur dans le select");
			exit(1);
		}
		
		
		// si connexion client, on créé une socket de dialogue client et on la met dans une place libre du tableau
		if( FD_ISSET(server[0], &pset) || FD_ISSET(server[1], &pset) ){

			i = placelibre(tab_ecoute_clients);
			
			// si c'est en ipv4
			if( FD_ISSET(server[0], &pset) ){
				tab_ecoute_clients[i] = newCommunicationSock(server[0]);
			}
			
			// si c'est en ipv6 
			if( FD_ISSET(server[1], &pset) ){	
				tab_ecoute_clients[i] = newCommunicationSock(server[1]);
			}
			
			// mises à jour variables
			FD_SET(tab_ecoute_clients[i], &rset);
			maxfdp1 = MaJ_maxFD(tab_ecoute_clients[i],maxfdp1);
			nbfd--;
		}

		
		i=0;
		//Parcour des tableau des clients et serveurs connectés
		while((nbfd>0)&&(i<FD_SETSIZE)){
			
			// on regarde si on a une réponse du serveur
			if(tab_ecoute_servers[i] >= 0 && FD_ISSET(tab_ecoute_servers[i], &pset)){
				messageDuServeur(tab_ecoute_servers, tab_ecoute_clients,i,&rset);
				nbfd--;
			}
			// on regarde si on a une requete du client
			if(tab_ecoute_clients[i] >= 0 && FD_ISSET(tab_ecoute_clients[i], &pset)){
				maxfdp1 = messageDuClient(tab_ecoute_clients,tab_ecoute_servers,i,maxfdp1,&rset);
				nbfd--;
			}

			i++;
		}
	}

	close(server[0]);
	close(server[1]);

	return 0;
}


