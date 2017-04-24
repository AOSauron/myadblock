#ifndef __UTIL__
#define __UTIL__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h> 
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

char** BlockingByAddressParts;
char** BlockingByDomainName;
char** BlockingExactAddress;
char** exceptListe;

// recherche d'une place libre dans le tableau
int placelibre(int tab_clients[]);

// renvoie la mise à jour de maxfdp1 quand on a un nouveau Fd
int MaJ_maxFD(int fd,int maxfdp1);

void iniListe();
#endif
