#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_PORT 2250

int main(void) {

	int serverSocket;
	if((serverSocket = socket(PF_INET,SOCK_DGRAM,0)) < 0) {
		perror("error socket");
		exit(1);
	}

	struct sockaddr_in serv_addr;
	char recbuf[1000];

	memset (&serv_addr, 0, sizeof(serv_addr) );
	serv_addr.sin_family = AF_INET ;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_PORT);

	if (bind(serverSocket,(struct sockaddr *)&serv_addr, sizeof(serv_addr) ) <0) {
 		perror ("servecho: erreur bind\n");
		exit (1);
	}

	/*
	if (listen(serverSocket,SOMAXCONN) <0) {
		perror ("servecho: erreur listen\n");
		exit (1);
		} */

       while (recvfrom(serverSocket, recbuf, sizeof(recbuf), 0 , NULL , 0) > 0) {
	  printf("Données reçues : %s\n",recbuf);
       }

       printf("fin\n");
	
	
	/*
	int dialogSocket;
	int clilen;
	struct sockaddr_in cli_addr;

	clilen = sizeof(cli_addr);
	dialogSocket = accept(serverSocket,(struct sockaddr *)&cli_addr,(socklen_t *)&clilen);

	if (dialogSocket < 0) {
		perror("servecho : erreur accep\n");
		exit(1);
		} */

	return 0;
}
