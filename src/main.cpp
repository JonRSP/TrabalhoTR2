#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Servidor.hpp"

#define PORTA_DEFAULT 8228

int main(int argc, char * const argv[]){

	long porta;
	if (argc != 1){
		if(argc !=3){
			printf("Digite: ./aracne -p <porta> \n");
			exit(EXIT_FAILURE);
		}else if(strcmp(argv[1], "-p") != 0){
			printf("Digite: -p <porta> \n");
			exit(EXIT_FAILURE);
		}
		porta = strtol(argv[2], nullptr, 10);
	}else
	{
		porta = PORTA_DEFAULT;
	}
	if(porta < 1024 || porta > 65535){
		printf("A porta deve estar entre 1024 e 65535 \n");
		exit(EXIT_FAILURE);
	}
	Servidor servidor((int)porta);
	servidor.Inicia();
	return 0;

}
