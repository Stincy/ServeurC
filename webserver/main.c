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


	creer_serveur(8000);

	printf ( " Need an advice ? \n " );
	return 0;
}
