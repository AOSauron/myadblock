#include "sockets.h"
#include "util.h"

// initialise les inforamtions du serveur
void newServer(int (*server)[2],const char *serv_port){
	int sock[2], ecode, num_sock = 0, on = 1;
	struct addrinfo *res, *rres, hints;

	// use getaddrinfo to get information about the server sockets we may create
	memset(&hints, 0, sizeof hints) ;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;

	ecode = getaddrinfo(NULL, serv_port, &hints, &rres);
	if (ecode) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ecode));
		exit(1);
	}

	// for each of these possible server sockets
	for (res = rres; res; res = res->ai_next) {
		sock[num_sock] = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sock[num_sock] < 0) {
			perror("socket() error");
			continue;
		}

		// set the SO_REUSEADDR option
		// (this will avoid EADDRINUSE errors if we restart the server too quickly)
		setsockopt(sock[num_sock], SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

		if (res->ai_family == AF_INET6) {
			setsockopt(sock[num_sock], IPPROTO_IPV6, IPV6_V6ONLY, (char *)&on, sizeof(on));
		}

		// bind the socket
		if (bind(sock[num_sock], res->ai_addr, res->ai_addrlen) < 0) {
			perror("bind() error");
			exit(1);
		}

		listen(sock[num_sock], SOMAXCONN);
		
		//on passe au server
		(*server)[num_sock]= sock[num_sock];

		num_sock++;
	}

	// free memory
	freeaddrinfo(rres);
}


// renvoie le fd d'une nouvelle socket d'écoute
int newCommunicationSock(int serverSocket){
	
	struct sockaddr_in cli_addr;
	int clilen = sizeof(cli_addr);
	int clientSocket = accept(serverSocket,(struct sockaddr *)&cli_addr,(socklen_t *)&clilen);

	if(clientSocket < 0) {
		perror("erreur création socket client");
		exit (1);
	}

	return clientSocket;
}

// renvoie le fd d'une nouvelle socket d'envoi au serveur web
int newClient(char *host, char* port){

	// try to connect to the server using IPv4
	int sock = try_with_family(host, port, AF_INET);

	if(sock == -1){
		// try to connect to the server using IPv6
		sock = try_with_family(host, port, AF_INET6);
		if(sock == -1){
			perror ("Problème création client");
			exit(1);	
		}
	}	

	return sock;
}

// renvoie le fd du client selon sa famille (ipv4/ipv6)
int try_with_family(char *host, char *serv, int family){
	int sock, ecode, on = 1;
	struct addrinfo *res;
	struct addrinfo hints = {
		0,
		0,
		SOCK_STREAM,
		0,
		0,
		NULL,
		NULL,
		NULL
	};

	// get an available server address for the given family
	hints.ai_family = family;
	
	ecode = getaddrinfo(host, serv, &hints, &res);
	if (ecode) {
		fprintf(stderr, "getaddrinfo() error: %s\n", gai_strerror(ecode));
		return -1;
	}

	// create a socket
	if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
		freeaddrinfo(res);
		perror("socket() error");
		return -1;
	}

	// Options
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	if (family == AF_INET6) {
		setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&on, sizeof(on));
	}

	// connect
	if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
		close(sock);
		freeaddrinfo(res);
		perror("connect() error");
		return -1;
	}
	
	// free memory
	freeaddrinfo(res);

	return sock;
}
