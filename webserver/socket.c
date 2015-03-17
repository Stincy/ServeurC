#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include "socket.h"

int nbClient = 0;
int status ;

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
	int socket_client = accept(socket_serveur, NULL, NULL);	
	const char *message_bienvenue = "Bonjour, bienvenue sur notre serveur\n";
	char *erreur;
	nbClient += 1;
	printf("Bravo vous etes le %d client \n", nbClient );

	if (socket_client == -1){
		perror("accept");
	}else{
		
		//int pid = fork();
		//if (pid == 0){
			FILE *fclient = fdopen(socket_client, "w+");
	//		fflush(fclient);
			while(fgets(buff , SIZE_BUFF, fclient)!=NULL){
				if (buff[0] == '\0') {
					printf("ligne vide\n");				
				} else {
					printf("ligne non vide: %s\n,", buff);	
					status = decoupageGET(buff);
					printf("code d'erreur du decoupage: %d\n", status);
					if (status == 0) {
						erreur = "HTTP/1.1 400 Bad request\nConnection: close\nContent-length: 17\n";
						write(socket_client, erreur, strlen(erreur));
						int x = fprintf(fclient, "%d%s\r\n", (int)strlen(erreur), erreur);
						printf("%d  %d\r\n%s", x, (int)strlen(erreur), erreur);
						//traitement
					} else if (status == 3) {
						erreur ="HTTP/1.1 200 OK\nContent-length: ";
						write(socket_client, message_bienvenue, strlen(message_bienvenue));
					}
				}
			}
			fflush(fclient);
			fclose(fclient) ;
			printf("fin du client %d\n", nbClient);
		 	/*exit(0);
		} else {
			//pere
			
		}*/

	}
	
	/* On peut maintenant dialoguer avec le client */
	
	//write(socket_client, message_bienvenue, strlen(message_bienvenue));


}

int decoupageGET(char * str){

	#define size_t = 7	

	//const char s[2] = " ";

	char *token;
	char *substr;
	char *tr = malloc(strlen(str)); 
	
	strcpy(tr, str);
	printf("%s\n", str);

	/* get the first token */
	token = strtok(str, " ");
	printf("TOKEN1 : %s\n", token);

	if(strcmp(token,"GET") == 0 ){
			substr = strstr(tr, "\r\n");
			if (substr != NULL) {
				substr = strstr(tr, "1.1");
				if (substr != NULL ){
					printf("terminaison bonne \n");
					free(tr);
					return 3;
				}
				substr = strstr(tr, "1.0");
				if (substr != NULL) {
					printf("terminaison bonne \n");
					free(tr);
					return 3;
				}
				free(tr);
				return 2;
			}
		free(tr);
		return 1;
	}
	free(tr);
	return 0;
}

/*enum http_method {
	HTTP_GET ,
	HTTP_UNSUPPORTED ,
};

typedef struct {
	enum http_method method ;
	int major_version ;
	int minor_version ;
	char * url ;
} http_request ;

char * fgets_or_exit( char *buffer, int size, FILE *stream ){

}

int parse_http_request(const char *request_line, http_request *request){
	return 0;
}*/

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
	  
