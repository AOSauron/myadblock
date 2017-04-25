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

bool contains(char URL[]){
	int i;
	for(i=0;i<sizeList;i++){
		if(strstr(URL, MyAdList[i])!=NULL){
			//printf("Token bloquant : %s\n", MyAdList[i]);
			return true;
		}
	}
	return false;
}

void iniListe(){
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i=0;

    	fp = fopen("src/MyAdListLight", "r");
    	if (fp == NULL)
		exit(EXIT_FAILURE);
	
	// on compte le nb de ligne
	while ((read = getline(&line, &len, fp)) != -1) {
		i++;
	}
	
	// on initialise easyListe
	MyAdList = malloc(i*sizeof(char*));
	sizeList=i; 

	// on se remet le debut du fichier
	fseek(fp, 0, SEEK_SET);

	i=0;
	while ((read = getline(&line, &len, fp)) != -1) {
		MyAdList[i]=malloc(read*sizeof(char));
		strncpy(MyAdList[i],line,read-1);
		i++;	
	}
    	fclose(fp);
}
/*
void iniListe(){
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i=0;
	int j=0;
	int k=0;
	int l=0;

    	fp = fopen("src/MyAdList", "r");
    	if (fp == NULL)
		exit(EXIT_FAILURE);
	
	// on compte le nb de ligne
	while ((read = getline(&line, &len, fp)) != -1) {
		if(line[0] != '!'){
			if(line[0]=='@' && line[1]== '@'){
				i++;
			}	
			else if(line[0]=='|' && line[1]== '|'){
				j++;
			}	
			else if(line[0]=='|' && line[read-1]== '|'){
				k++;
			}
			else{
				l++;
			}
		}
	}

	// on initialise easyListe
	exceptListe = malloc(i*sizeof(char*));
	BlockingByDomainName = malloc(j*sizeof(char*));
	BlockingExactAddress = malloc(k*sizeof(char*));
	BlockingByAddressParts = malloc(l*sizeof(char*));

	// on se remet le debut du fichier
	fseek(fp, 0, SEEK_SET);

	i=0;
	j=0;
	k=0;
	l=0;
	while ((read = getline(&line, &len, fp)) != -1) {
		// on enleve les coms'
		if(line[0] != '!'){
			if(line[0]=='@' && line[1]== '@'){
				exceptListe[i]=malloc(read*sizeof(char));
				strncpy(exceptListe[i],line+2,read-3);
				i++;
			}	
			else if(line[0]=='|' && line[1]== '|'){
				BlockingByDomainName[j]=malloc(read*sizeof(char));
				strncpy(BlockingByDomainName[j],line+2,read-3);
				j++;
			}	
			else if(line[0]=='|' && line[read-1]== '|'){
				BlockingExactAddress[k]=malloc(read*sizeof(char));
				strncpy(BlockingExactAddress[k],line,read-1);
				k++;
			}
			else if(line[0]!='\n'){
				BlockingByAddressParts[l]=malloc(read*sizeof(char));
				strncpy(BlockingByAddressParts[l],line,read-1);
				l++;
			}
		}	
	}
    	fclose(fp);
	
	
}*/
