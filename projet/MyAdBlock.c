#include "sockets.h"
#include "messages.h"
#include "util.h"

// pour telecom-> pourquoi ça marche pas???
// parfois : Erreur dans getaddrinfo de socket d'envoi: Success


int main(int argc, char *argv[]){
	
	// declarations
	struct addrinfo *result;
	int tab_clients[FD_SETSIZE];
	int tab_servers[FD_SETSIZE];
	int ipv4;
	int ipv6;
	int maxfdp1;
	int nbfd;
	int i;
	fd_set rset;
	fd_set pset;
	

	// initialisations
	nbfd = 0;
	i = 0;
	for (i=0;i<FD_SETSIZE;i++){
		tab_clients[i] = -1;
		tab_servers[i] = -1;
	}

	// il faut renseigner le port
	if(argc != 2){
		printf("usage : servecho numero_port_serveur\n");
		exit(1);
	}
	
	// on créé le serveur sur le port demandé
	result = NULL;
	newServer(&result,argv[1]);
	
	// on créé la socket d'écoute sur ipv4 et ipv6
	ipv4 = newEcouteSocket(result);
	ipv6 = newEcouteSocket(result->ai_next);

	// on initialise les descripteurs et on commence l'ecoute
	FD_ZERO(&pset);
	FD_ZERO(&rset);
	maxfdp1 = enEcoute(ipv4,ipv6,&rset);

	// plus besoin de cette structure
	freeaddrinfo(result);
	
	
	
	
	printf("MyAddBlock est bien lancé.\n");

	for(;;){
		//initialisation des fd_set puis SELECT
		pset=rset;
		nbfd=select(maxfdp1,&pset,NULL,NULL,NULL);
		if (nbfd==-1) {
			perror("Erreur dans le select");
			exit(1);
		}
		
		// si connexion client, on créé une socket de dialogue client et on la met dans une place libre du tableau
		if( FD_ISSET(ipv4, &pset) || FD_ISSET(ipv6, &pset) ){
			
			printf("\n ( nouveau client )\n\n");
			i = placelibre(tab_clients);
			
			// si c'est en ipv4
			if( FD_ISSET(ipv4, &pset) ){	
				tab_clients[i] = newClient(ipv4,&rset);
			}
			
			// si c'est en ipv6 
			if( FD_ISSET(ipv6, &pset) ){	
				tab_clients[i] = newClient(ipv6,&rset);
			}

			maxfdp1 = MaJ_maxFD(tab_clients[i],maxfdp1);
			nbfd--;
		}

		
		i=0;
		//Parcour des tableau des clients et serveurs connectés
		while((nbfd>0)&&(i<FD_SETSIZE)){
			
			// on regarde si on a une réponse du serveur
			if(tab_servers[i] >= 0 && FD_ISSET(tab_servers[i], &pset)){
				printf("\n---------------------------- message serveur ---------------------\n");
				messageServeur(tab_servers, tab_clients,i,&rset);
				printf("\n\n\n\n");
				nbfd--;
			}

			// on regarde si on a une requete du client
			if(tab_clients[i] >= 0 && FD_ISSET(tab_clients[i], &pset)){
				printf("\n---------------------------- message client ----------------------\n");
				maxfdp1 = messageClient(tab_clients,tab_servers,i,maxfdp1,&rset);
				printf("\n\n\n\n");
				nbfd--;
			}

			i++;
		}
	}

	close(ipv4);
	close(ipv6);

	return 0;
}


