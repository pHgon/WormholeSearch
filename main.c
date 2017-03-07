// Trabalho Pratico 2 - Algoritmo e Estrutura de Dados II - 09/03/2017
// Autores - Paulo Henrik Goncalves & Gilberto Kreisler

#include <stdio.h>

void main (int argc,char *argv[]){
	if(argc == 1){
		printf("\nERROR: No argument received .. Program closed!\n");
		exit(-1);
	}

	FILE *inputFile  = fopen (argv[2], "r");
}