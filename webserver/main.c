#include <stdio.h>
#include <stdlib.h>
#include "socket.h"

int main (){

	while(1){
		creer_serveur(8000);
		printf("main ok"); 
	}

	return 0;
}
