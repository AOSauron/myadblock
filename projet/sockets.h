#ifndef __SOCKETS__
#define __SOCKETS__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h> 
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

// initialise les inforamtions du serveur
void newServer(struct addrinfo** result, const char *serv_port);

// renvoie le fd d'une nouvelle socket d'écoute
int newEcouteSocket(struct addrinfo *result);

//renvoie le plus grand des 2 Fd
int enEcoute(int ipv4,int ipv6,fd_set* rset);

// renvoie le fd d'une nouvelle socket d'écoute
int newClient(int serverSocket, fd_set* rset);

// renvoie le fd d'une nouvelle socket d'envoi
int newEnvoiSocket(char* hostname, fd_set* rset);

#endif
