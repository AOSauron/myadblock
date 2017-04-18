#ifndef __MESSAGES__
#define __MESSAGES__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h> 
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

#define MAXLINE 5000
#define SERV_PORT 7777
#define MAXTYPE 50
#define MAXHOST 100

// extrait le type de la requete dans "fromClient" et le met dans "typeRequete"
void getTypeRequete(char fromClient[], char typeRequete[]);

// extrait le hostname de la requete dans "fromClient" et le met dans "host"
void getHost(char fromClient[], char host[]);

// retourne le fd du serveur
void messageDuServeur(int tab_servers[], int tab_clients[],int i,fd_set* rset);

// retourne le fd du client
int messageDuClient(int tab_clients[],int tab_servers[],int i,int maxFD,fd_set* rset);

#endif
