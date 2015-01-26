#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>


int creerServeur(){

	int socket_serveur ;
	struct sockaddr_in saddr ;


	const char * message = " Notre super serveur marche \n " ;


	socket_serveur = socket( AF_INET , SOCK_STREAM , 0);
	if ( socket_serveur == -1)
	{
	perror ( " socket_serveur " );
	}

	addr.sin_family = AF_INET ;   		/* Socket ipv4 */
	saddr.sin_port = htons (8000); 		/* Port d ’ écoute */
	saddr.sin_addr.s_addr = INADDR_ANY ;

	if(bind(socket_serveur, (struct sockaddr *) &saddr,sizeof(saddr))==-1){
		perror ( " bind socker_serveur " );
	}

	if (listen(socket_serveur, 10) == -1){
		perror("listen socket_serveur");
	/*traitement d'erreur*/
	}

	


	/* traitement de l ’ erreur */

}
	/* Utilisation de la socket serveur */

}
