// Trabalho Pratico 2 - Algoritmo e Estrutura de Dados II - 09/03/2017
// Autores - Paulo Henrik Goncalves & Gilberto Kreisler

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Node{
	int cost; 
	struct Node *pred; // Predecessor    
}; typedef struct Node Wormhole;

void wormholeSearch (FILE *inputFile, int numGalaxies, int numWormholes);
//void BellmanFord (Wormhole *matrix, int numGalaxies, int numWormholes, int src);

void main (int argc,char *argv[]){
	if(argc == 1){
		printf("\nERROR: No argument received .. Program closed!\n");
		exit(-1);
	}

	FILE *inputFile  = fopen (argv[1], "r");
	if (inputFile == NULL){
		printf("ERROR: Failed to open File .. Program closed!\n");
		exit(-1);
	}

	int i, sets;
	fscanf(inputFile, "%d\n", &sets);  // Le o numero de conjuntos que serao avaliados

	for(i=0; i<sets; i++){  // Para todos os conjuntos
		int galaxies, wormholes; 
		fscanf(inputFile, "%d %d\n", &galaxies, &wormholes);  // Le o numero de galaxias e o numero de buracos de minhoca
		wormholeSearch(inputFile, galaxies, wormholes);
	}
}

void wormholeSearch (FILE *inputFile, int numGalaxies, int numWormholes){
	Wormhole matrix[numGalaxies][numWormholes];
	int i, j, src = INT_MAX;
	int aux1, aux2, aux3;  // Auxiliares para leitura do arquivo

	for(i=0; i<numGalaxies; i++){         //
		for(j=0; j<numWormholes; j++){    //  NAO SEI AO CERTO SE ESTE TRECHO E NECESSARIO
			matrix[i][j].cost = 0;        //  A MATRIZ JA INICIA ZERADA?
		}                                 //  
	}                                     //

	for(i=0; i<numWormholes; i++){
		fscanf(inputFile, "%d %d %d\n", &aux1, &aux2, &aux3);
		matrix[aux1][aux2].cost = aux3;
		if(aux1<src)
			src=aux1;
	}

	// BELLMAN FORD ALGORITHM //////////////////////////////////////////////////////////////////////

	int dist[numGalaxies];  // Vetor de Distancias
	for(i=0; i<numGalaxies; i++){
		dist[i] = INT_MAX; // Seta todos os vertices com infinito
	}
	dist[src] = 0; // Vertice inicial recebe 0

	

	
}

/*void BellmanFord (Wormhole *matrix, int numGalaxies, int numWormholes, int src){
	int i,j;

	for(i=0; i<numGalaxies; i++){         
		for(j=0; j<numWormholes; j++){    
			printf("%5d ", matrix[i][j].cost);
		} 
		printf("\n");                                  
	}
	printf("\n");
}*/
