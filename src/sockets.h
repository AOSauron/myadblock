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


// renvoie les fd ipv4 et ipv6 du serveur
void newServer(int (*server)[2],const char *serv_port);

// renvoie le fd d'une nouvelle socket d'écoute
int newCommunicationSock(int serverSocket);

// renvoie le fd d'une nouvelle socket d'envoi au serveur web
int newClient(char *host, char* port);

// renvoie le fd du client selon sa famille (ipv4/ipv6)
int try_with_family(char *host, char *serv, int family);

#endif
