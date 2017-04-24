#ifndef __UTIL__
#define __UTIL__

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h> 
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

char** MyAdList;
int sizeList;

// recherche d'une place libre dans le tableau
int placelibre(int tab_clients[]);

bool contains(char URL[]);

// renvoie la mise à jour de maxfdp1 quand on a un nouveau Fd
int MaJ_maxFD(int fd,int maxfdp1);

void iniListe();
#endif
