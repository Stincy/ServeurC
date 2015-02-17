#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include "socket.h"


int creer_serveur(int port){
	
	int socket_serveur;
	struct sockaddr_in saddr;


	socket_serveur = socket( AF_INET , SOCK_STREAM , 0);
	if ( socket_serveur == -1)
	{
	perror ( " socket_serveur " );
	}

	saddr.sin_family = AF_INET ;   		/* Socket ipv4 */
	saddr.sin_port = htons(port); 		/* Port d ’ écoute */
	saddr.sin_family = AF_INET ;   			/* Socket ipv4 */
	saddr.sin_port = htons(port); 			/* Port d ’ écoute */
	saddr.sin_addr.s_addr = INADDR_ANY;

	int optval = 1;
	if ( setsockopt( socket_serveur , SOL_SOCKET , SO_REUSEADDR , &optval , sizeof(int)) == -1){
		perror ( " Can not set SO_REUSEADDR option " );
	}

	if(bind(socket_serveur, (struct sockaddr *) &saddr,sizeof(saddr))==-1){
		perror ( " bind socker_serveur " );
	}

	if (listen(socket_serveur, 10) == -1){ 		/*traitement d'erreur*/
		perror("listen socket_serveur");
	}

	return socket_serveur;

}



void connectionClient(int socket_serveur){
	

	#define SIZE_BUFF 2048
	char buff[SIZE_BUFF];
	int nbClient = 1;
	int socket_client = accept(socket_serveur, NULL, NULL);	
	const char *message_bienvenue = "Bonjour, bienvenue sur notre serveur\n";

	if (socket_client == -1){
		perror("accept");
	}else{
		
		int pid = fork();
		
		if (pid == 0){
			printf("%s \n" ,message_bienvenue );
			FILE *fclient = fdopen(socket_client, "w+");
			while(fgets(buff , SIZE_BUFF, fclient)!=NULL){
				fprintf(fclient, "Bravo vous etes le %d client \n", nbClient );
				nbClient += 1;
				decoupageGET(buff);
			}
			fclose(fclient) ;
		 	exit(0);
		}
			//pere

	}
	
	/* On peut maintenant dialoguer avec le client */
	
	write(socket_client, message_bienvenue, strlen(message_bienvenue));


}

void decoupageGET(char * str){

	#define size_t = 7	

	const char s[2] = " ";
	char *token;
	//int nbMot = 0;

	printf("%s\n", str);

	/* get the first token */
	token = strtok(str, s);
	printf("TOKEN1 : %s\n", token);

	if(strcmp(token,"GET") == 0 && strlen(token)==3){
		while( token != NULL ){
			token = strtok(NULL, s);
			printf("TOKEN : %s\n", token);
		}
	}

	if (strncmp(token[2], "HTTP/1.", size_t) == 0){
		if (strrchr(token[2], '0') == 0 || strrchr(token[2], '1') == 0){
			printf("ouai ouai ouai \n");
		}
	}

}

void initialiser_signaux(void){
	if ( signal( SIGPIPE , SIG_IGN ) == SIG_ERR ){
		perror("accept");
	}

	struct sigaction sa ;
	sa.sa_handler = traitement_signal;
	sigemptyset (&sa.sa_mask );
	sa.sa_flags = SA_RESTART;
	if ( sigaction( SIGCHLD, &sa, NULL ) == -1)
	{
		perror ( " sigaction(SIGCHLD) " );
	}
}

void traitement_signal (int sig )
{
	printf ( " Signal %d reçu \n " , sig );
}
	  
