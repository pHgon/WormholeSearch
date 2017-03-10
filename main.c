// Trabalho Pratico 2 - Algoritmo e Estrutura de Dados II - 09/03/2017
// Autores - Paulo Henrik Goncalves & Gilberto Kreisler

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Node{
	int distance;
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
	int matrix[numGalaxies][numWormholes]; //Matriz de adjacência
	int vertices[numGalaxies]; //Lista de vertices do grafo
	int i, j, src = INT_MAX;
	int aux1, aux2, aux3;  // Auxiliares para leitura do arquivo

	for(i=0; i<numGalaxies; i++){         //
		for(j=0; j<numWormholes; j++){    //  NAO SEI AO CERTO SE ESTE TRECHO E NECESSARIO
			matrix[i][j] = 0;        //  A MATRIZ JA INICIA ZERADA?
		}                                 //
	}                                     //

	//Starta a matriz de adjacência com os devidos custos
	for(i=0; i<numWormholes; i++){
		fscanf(inputFile, "%d %d %d\n", &aux1, &aux2, &aux3);
		matrix[aux1][aux2] = aux3;
		if(aux1<src)
			src=aux1;
	}

	// BELLMAN FORD ALGORITHM //////////////////////////////////////////////////////////////////////

	//Starta a distancia de cada vertice com infinito e predecessor nulo
	for(i = 0; i < numGalaxies; i++){
		vertices[i].dist = INT_MAX; // Seta todos os vertices com infinito
		vertices[i]->pred = NULL;
	}
	vertices[src].dist = 0; // Vertice inicial recebe 0

	BellmanFord(vertices, matrix, numGalaxies, numWormholes,src);


}

void BellmanFord (Wormhole *list, int matrix[][numWormholes], int numGalaxies, int numWormholes, int src){
	int i,j;

	for(i=0; i<numGalaxies; i++){
		for(j=0; j<numWormholes; j++){
			printf("%5d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//Acho que aqui deveria ser um for triplo
	//Pra cada vertice - vertice(inicial) -> percorre cada aresta
	for (i = 0; i < numGalaxies; i++) {
		for (j = 0; j < numWormholes; j++) {
			if (matrix[i][j] != 0)
				relax(list[i], list[j], matrix[i][j]);
		}
	}

	for (i = 0; i < numGalaxies; i++) {
		for (i = 0; i < numWormholes; i++) {
			if (matrix[i][j] != 0 && list[i].dist + matrix[i][j] < list[j].dist) {
				//CICLO NEGATIVO - POSSIVEL
			}
		}
	}

	//IMPOSSIVEL
}

void relax(Wormhole u, Wormhole v, int w){
	if (u.dist + w < v.dist) {
		v.dist = u.dist + w;
		v->pred = u;
	}

}
