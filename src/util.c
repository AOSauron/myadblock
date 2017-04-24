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
				exceptListe[i]=malloc((read+1)*sizeof(char));
				strcpy(exceptListe[i],line);
				i++;
			}	
			else if(line[0]=='|' && line[1]== '|'){
				BlockingByDomainName[j]=malloc((read+1)*sizeof(char));
				strcpy(BlockingByDomainName[j],line);
				j++;
			}	
			else if(line[0]=='|' && line[read-1]== '|'){
				BlockingExactAddress[k]=malloc((read+1)*sizeof(char));
				strcpy(BlockingExactAddress[k],line);
				k++;
			}
			else{
				printf("coucou41 %s\n",line);
				BlockingByAddressParts[l]=malloc((read+1)*sizeof(char));
				strcpy(BlockingByAddressParts[l],line);
				l++;
			}
		}	
	}
	
    	fclose(fp);
	
}
