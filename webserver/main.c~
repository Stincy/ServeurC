#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"

int main(int argc , char **argv){

	/* Arnold Robbins in the LJ of February ’95 , describing RCS */
	if ( argc > 1 && strcmp ( argv [1] , " - advice " ) == 0) {
		printf("don't panic \n");
	return 42;
	}
	int socket_serveur;
	socket_serveur = creer_serveur(8000);


	while(1){

		initialiser_signaux();
		connectionClient(socket_serveur);
	}
	return 0;
}
