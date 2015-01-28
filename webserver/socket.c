#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "socket.h"


int creer_serveur(int port){

	int socket_serveur;
	int socket_client;
	struct sockaddr_in saddr;
	const char *message_bienvenue = "Bonjour, bienvenue sur notre serveur\n";


	/*const char * message = " Notre super serveur marche \n ";*/


	socket_serveur = socket( AF_INET , SOCK_STREAM , 0);
	if ( socket_serveur == -1)
	{
	perror ( " socket_serveur " );
	}

	saddr.sin_family = AF_INET ;   			/* Socket ipv4 */
	saddr.sin_port = htons (port); 			/* Port d ’ écoute */
	saddr.sin_addr.s_addr = INADDR_ANY;

	if(bind(socket_serveur, (struct sockaddr *) &saddr,sizeof(saddr))==-1){
		perror ( " bind socker_serveur " );
	}

	if (listen(socket_serveur, 10) == -1){ 		/*traitement d'erreur*/
		perror("listen socket_serveur");
	}

	/* socket client */
	socket_client = accept(socket_serveur, NULL, NULL);
	if (socket_client == -1)			/* traitement d'erreur*/
	{
		perror("accept");	
	}
	/* On peut maintenant dialoguer avec le client */
	
	write(socket_client, message_bienvenue, strlen(message_bienvenue));

}
	  
