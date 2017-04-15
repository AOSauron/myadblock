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

// extrait le hostname de la requete dans "fromClient" et le met dans "host"
void getHost(char fromClient[], char host[]){
	int i=0;
	int j=0;

	//On passe le type de requete et le http://
	while(fromClient[i] != '/'){
		i++;
	}
	// on saute le 2eme '/'
	i=i+2;

	//On récupère le nom jusqu'au prochain '/'
	while(fromClient[i] != '/'){
		host[j] = fromClient[i];
		i++;
		j++;
	}
	host[j]='\0';
	//printf("host: %s\n",host);
}


// retourne le fd du serveur
void messageServeur(int tab_servers[], int tab_clients[],int i,fd_set* rset){
	char fromServer[MAXLINE];
	memset(fromServer, 0, MAXLINE);
	int recept = recv(tab_servers[i], fromServer, MAXLINE, 0);
	
	//On vérifie qu'il n'y ait pas eu d'erreur dans la lecture
	if(recept < 0){
		perror("Erreur dans la lecture de la reponse");
		close(tab_servers[i]);
		exit(5);
	}
	//on ferme le fd, on l'enleve sur rset et on remet le fd à -1
	else if(recept == 0){
		close(tab_servers[i]);
		FD_CLR(tab_servers[i], rset);
		tab_servers[i] = -1;
		printf("La connexion avec le serveur web a été fermée\n");
	}
	//on envoie la reponse
	else{
		printf("%s", fromServer);
		send(tab_clients[i], fromServer, recept, 0);
	}
}

// retourne le fd du client
int messageClient(int tab_clients[],int tab_servers[],int i,int maxFD,fd_set* rset){
	char fromClient[MAXLINE];
	char typeRequete[MAXTYPE];
	char host[MAXHOST];
	int maxfdp1 = maxFD;

	memset(fromClient, 0, MAXLINE);
	int recept = recv(tab_clients[i], fromClient, MAXLINE, 0);

	//On vérifie qu'il n'y ait pas eu d'erreur dans la lecture
	if(recept < 0){
		perror("Erreur dans la lecture de la requête");
		close(tab_clients[i]);
		exit(5);
	}
	//on ferme le fd, on l'enleve sur rset et on remet le fd à -1
	else if(recept == 0) { 
		close(tab_clients[i]);
		FD_CLR(tab_clients[i], rset);
		tab_clients[i] = -1;
		printf("La connexion avec le client a été fermée\n");
	}
	else{
		//on recupere le type de requete
		getTypeRequete(fromClient, typeRequete);

		//On regarde les requêtes GET
		if(strcmp(typeRequete, "GET") == 0){

			// On cree une socket serveur au même l'indice i que sa sockets client correspondante
			// On recupère au passage le hostname du client
			printf("\n( nouveau serveur )\n\n");
			getHost(fromClient,host);
			tab_servers[i] = newEnvoiSocket(host, rset);
			maxfdp1 = MaJ_maxFD(tab_servers[i],maxfdp1);

			// On envoie la requête au serveur
			send(tab_servers[i], fromClient, recept, 0);

		}
		//si la requête est CLOSE on ferme le fd, on l'enleve sur rset et on remet le fd à -1
		else if(strcmp(typeRequete, "CLOSE")){
			close(tab_clients[i]);
			FD_CLR(tab_clients[i], rset);
			tab_clients[i] = -1;
			printf("La connexion avec le client a été fermée\n");
		}
		
		printf("%s", fromClient);
		
	}
	return maxfdp1;
}



