#include "util.h"

//recherche d'une place libre dans le tableau
int placelibre(int tab_clients[]){
	int i = 0;
	while((i<FD_SETSIZE)&&tab_clients[i]>=0){
		i++;
	}
	if(i == FD_SETSIZE){
		perror("Nombre maximal de clients atteints");
		exit(3);
	}
	return i;
}

// renvoie la mise à jour de maxfdp1 quand on a un nouveau Fd
int MaJ_maxFD(int fd,int maxfdp1){
	int maxFD = maxfdp1;
	if(fd >= maxFD){
		maxFD=fd+1;
	}
	return maxFD;
}
