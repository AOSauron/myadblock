#include "sockets.h"
#include "messages.h"
#include "util.h"


// extrait le type de la requete dans "fromClient" et le met dans "typeRequete"
void getTypeRequete(char fromClient[], char typeRequete[]){
	int i = 0;
	while(fromClient[i] != ' ' && i < MAXTYPE){
		typeRequete[i] = fromClient[i];
		i++;
	}
	typeRequete[i] = '\0';
}

void getHost(char fromClient[], char host[]){
	int i=0;
	int j=0;
	char hostSearch[7] = "";

	//On passe jusqu'à ce qu'on arrive à "Host: "
	while(strcmp(hostSearch,"Host: ")!=0){
		for(j=0;j<6;j++){
			hostSearch[j] = fromClient[i+j];
		}
		hostSearch[6]='\0';
		i++;
	}
	
	// on saute le 2eme '/'
	i=i+5;
	j=0;
	//On récupère le nom jusqu'au prochain '/'
	while(fromClient[i] != '\n'){
		host[j] = fromClient[i];
		i++;
		j++;
	}
	host[j-1]='\0';
}

void getURL(char fromClient[], char host[]){
	int i=0;
	int j=0;
	char hostSearch[8] = "";
	
	//On passe jusqu'à ce qu'on arrive à "Host: "
	while(strcmp(hostSearch,"http://")!=0){
		
		for(j=0;j<7;j++){
			hostSearch[j] = fromClient[i+j];
		}
		hostSearch[7]='\0';
		i++;
	}
	
	// on saute le 2eme '/'
	i--;
	j=0;
	//On récupère le nom jusqu'au prochain '/'
	while(fromClient[i] != ' '){
		host[j] = fromClient[i];
		i++;
		j++;
	}
	host[j]='\0';
}

// retourne le fd du serveur
void messageDuServeur(int tab_servers[], int tab_clients[],int i,fd_set* rset){

	char fromServer[MAXLINE];
	memset(fromServer, 0, MAXLINE);
	int recept = recv(tab_servers[i], fromServer, MAXLINE, 0);

	//si erreur ou fermeture : on ferme le fd, on l'enleve sur rset et on remet le fd à -1
	if(recept <= 0){
		close(tab_servers[i]);
		FD_CLR(tab_servers[i], rset);
		tab_servers[i] = -1;
		//printf("La connexion avec le serveur %d a été fermée ",i);
	}
	//on envoie la reponse
	else{
		//printf("%s", fromServer);

		if(send(tab_clients[i], fromServer, recept, 0)==-1){
			perror("Erreur dans l'envoi de la reponse du serveur");
		}
	}

}

// retourne le fd du client
int messageDuClient(int tab_clients[],int tab_servers[],int i,int maxFD,fd_set* rset){
	
	char fromClient[MAXLINE];
	char typeRequete[MAXTYPE];
	char host[MAXHOST];
	char URL[MAXURL];
	int maxfdp1 = maxFD;

	memset(fromClient, 0, MAXLINE);
	int recept = recv(tab_clients[i], fromClient, MAXLINE, 0);

	//si erreur ou fermeture : on ferme le fd, on l'enleve sur rset et on remet le fd à -1
	if(recept <= 0){
		close(tab_clients[i]);
		FD_CLR(tab_clients[i], rset);
		tab_clients[i] = -1;
		//printf("La connexion avec le client %d a été fermée",i);
	}
	else{
		//on recupere le type de requete
		getTypeRequete(fromClient, typeRequete);

		//On regarde les requêtes GET
		if(strcmp(typeRequete, "GET") == 0){
			
			// On recupère le hostname du client
			getHost(fromClient,host);
	
			getURL(fromClient,URL);

			//if((strcmp(host, "www.01net.com") == 0) ){
			if(contains(URL)==false){
				// On cree une socket serveur au même l'indice i que sa sockets client correspondante
				tab_servers[i] = newClient(host);
	
				// On envoie la requête au serveur
				if(send(tab_servers[i], fromClient, recept, 0)==-1){
					perror("Erreur dans la requete");
				}
			
				//Mise à jour variables
				FD_SET(tab_servers[i], rset);
				maxfdp1 = MaJ_maxFD(tab_servers[i],maxfdp1);
			}
			// si c'est une pub
			else{
				printf(" bloqué :");
				char buf[1024] = "HTTP/1.0 200 OK \n";
    				send(tab_clients[i], buf, strlen(buf), 0);
				close(tab_clients[i]);
				FD_CLR(tab_clients[i], rset);
				tab_clients[i] = -1;
			}

			printf(" %s  %s\n",typeRequete, host);
		}
		//si la requête est autre que GET on ferme le fd, on l'enleve sur rset et on remet le fd à -1
		else {
			close(tab_clients[i]);
			FD_CLR(tab_clients[i], rset);
			tab_clients[i] = -1;
			//printf("La connexion avec le client %d a été fermée\n",i);
		}
		
		//printf("%s", fromClient);
	}
	return maxfdp1;
}

