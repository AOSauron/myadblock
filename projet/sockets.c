#include "sockets.h"
#include "util.h"

// initialise les inforamtions du serveur
void newServer(struct addrinfo** result, const char *serv_port){
	struct addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC; /* Allow IPv4 or IPv6 */
	hints.ai_socktype=SOCK_STREAM; /* Dialogue socket */
	hints.ai_flags=AI_PASSIVE; /* For wildcard IP address */
	hints.ai_protocol=0; /* Any protocol */
	hints.ai_canonname = NULL;
    	hints.ai_addr = NULL;
   	hints.ai_next = NULL;
  
	//  getaddrinfo() retourne dans "result" la liste des structures possibles avec les données mises dans "hints"
	// le 1er result est avec AF_INET(ipv4) le suivant (result-> ai_next) est avec AF_INET6(ipv6)
	if (getaddrinfo(NULL,serv_port,&hints,result)!=0){
	   	perror ("Erreur dans getaddrinfo du proxy");
		exit (1);
	}
}

// renvoie le fd d'une nouvelle socket d'écoute
int newEcouteSocket(struct addrinfo *result){
	int ecouteSocket;
	
	// Ouvrir une socket (socket STREAM)
	if( (ecouteSocket=socket(result->ai_family, result->ai_socktype, result->ai_protocol)) < 0) { 
		perror ("erreur socket");
		exit (2);
	}
	

	// Permet le multi-usage de l'adresse(Enlève le message "Address already in use")
	unsigned int ok = 1;
	if(setsockopt(ecouteSocket, SOL_SOCKET, SO_REUSEPORT, &ok, sizeof(ok)) < 0){
		perror ("erreur options socket");
		exit(2);
	}

	// Lie la socket à l'adresse 
	if (bind(ecouteSocket,result->ai_addr, result->ai_addrlen) <0) {
		perror ("servecho: erreur bind");
		exit (1);
	}

	return ecouteSocket;
}

//renvoie le plus grand des 2 Fd
int enEcoute(int ipv4,int ipv6,fd_set* rset){
	
	// Paramétrer le nombre de connexion "pending" pour ipv4
	if(listen(ipv4, SOMAXCONN) <0) {
		perror ("servecho: erreur listen ipv4");
		exit (1);
	}

	// Paramétrer le nombre de connexion "pending" pour ipv4
	if(listen(ipv6, SOMAXCONN) <0) {
		perror ("servecho: erreur listen ipv6");
		exit (1);
	}

	//initialisation descripteurs
	FD_SET(ipv4, rset);
	FD_SET(ipv6, rset);

	//mis à jour du plus grand fd
	int maxfdp1 = ipv4 +1;
	maxfdp1 = MaJ_maxFD(ipv6,maxfdp1);

	return maxfdp1;
}

// renvoie le fd d'une nouvelle socket d'écoute
int newClient(int serverSocket, fd_set* rset){
	struct sockaddr_in cli_addr;
	int clilen = sizeof(cli_addr);
	int clientSocket = accept(serverSocket,(struct sockaddr *)&cli_addr,(socklen_t *)&clilen);

	if(clientSocket < 0) {
		perror("erreur création socket client");
		exit (1);
	}

	// On ajoute le nouveau client à rset
	FD_SET(clientSocket, rset);

	return clientSocket;
}

// renvoie le fd d'une nouvelle socket d'envoi
int newEnvoiSocket(char* hostname, fd_set* rset){
	struct addrinfo *result;
	struct addrinfo hints;
	int envoiSocket;

	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC; /* Allow IPv4 or IPv6 */
	hints.ai_socktype=SOCK_STREAM; /* Dialogue socket */
	hints.ai_flags=0; 
	hints.ai_protocol=0; /* Any protocol */
	
	//get addrinfo
	if(getaddrinfo(hostname, "80", &hints, &result)){
		perror ("Erreur dans getaddrinfo de socket d'envoi");
		exit (1);
	}

	// Ouvrir une socket (socket STREAM)
	if ((envoiSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) <0) {
		perror("Erreur dans l'ouverture dans la socket");
		exit (2);
	}

	// Permet le multi-usage de l'adresse(Enlève le message "Address already in use")
	unsigned int ok = 1;
	if(setsockopt(envoiSocket, SOL_SOCKET, SO_REUSEPORT, &ok, sizeof(ok)) < 0){
		perror ("erreur options socket");
		exit(2);
	}

	// se connect au server
	if(connect (envoiSocket, result->ai_addr, result->ai_addrlen)  < 0){
		perror ("Problème connect pour la socket de discution avec serveur web");
		exit(1);
	}
	
	//plus besoin de la structure
	freeaddrinfo(result);
	
	// On ajoute le nouveau client à rset
	FD_SET(envoiSocket, rset);

	return envoiSocket;
}
