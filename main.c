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

void wormholeSearch (FILE *inputFile, FILE *outputFile, int numGalaxies, int numWormholes);
int BellmanFord (Wormhole *list, int numGalaxies, int numWormholes, int matrix[][numWormholes]);
void relax(Wormhole *u, Wormhole *v, int w);

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
	FILE *outputFile = fopen("log_output.txt", "w");

	for(i=0; i<sets; i++){  // Para todos os conjuntos
		int galaxies, wormholes;
		fscanf(inputFile, "%d %d\n", &galaxies, &wormholes);  // Le o numero de galaxias e o numero de buracos de minhoca
		wormholeSearch(inputFile, outputFile, galaxies, wormholes);
	}

	fclose(inputFile);
	fclose(outputFile);
}

void wormholeSearch (FILE *inputFile, FILE *outputFile, int numGalaxies, int numWormholes){
	int matrix[numGalaxies][numWormholes]; //Matriz de adjacência
	Wormhole vertices[numGalaxies]; //Lista de vertices do grafo
	int i, j, src = INT_MAX, possible;
	int aux1, aux2, aux3;  // Auxiliares para leitura do arquivo

	for(i=0; i<numGalaxies; i++){         //
		for(j=0; j<numWormholes; j++){    //  Matriz tbm iniciada com INT_MAX
			matrix[i][j] = INT_MAX;        //  para identificar as posições não usadas
		}                                 //
	}                                     //

	//Starta a matriz de adjacência com os devidos custos
	for(i=0; i<numWormholes; i++){
		fscanf(inputFile, "%d %d %d\n", &aux1, &aux2, &aux3);
		matrix[aux1][aux2] = aux3;
		if(aux1 < src)
			src = aux1;
	}

	//Starta a distancia de cada vertice com infinito e predecessor nulo
	for(i = 0; i < numGalaxies; i++){
		vertices[i].distance = INT_MAX; // Seta todos os vertices com infinito
		vertices[i].pred = NULL;
	}
	vertices[src].distance = 0; // Vertice inicial recebe 0

	possible = BellmanFord(vertices, numGalaxies, numWormholes, matrix);

	if(possible){
		fprintf(outputFile, "possivel\n");
	}
	else{
		fprintf(outputFile, "impossivel\n");
	}

}

int BellmanFord (Wormhole *list, int numGalaxies, int numWormholes, int matrix[][numWormholes]){
	int i, j, k;

	//Pra cada vertice - vertice(inicial) -> percorre cada aresta
	for(k = 0; k < numGalaxies - 1; k++){
		for (i = 0; i < numGalaxies; i++) {
			for (j = 0; j < numWormholes; j++) {
				if(matrix[i][j] != INT_MAX)
					relax(&list[i], &list[j], matrix[i][j]);
			}
		}
	}

	for (i = 0; i < numGalaxies; i++) {
		for (i = 0; i < numWormholes; i++) {
			if (matrix[i][j] != INT_MAX && list[i].distance + matrix[i][j] < list[j].distance) {
				return 0;
			}
		}
	}

	return 1;
}

void relax(Wormhole *u, Wormhole *v, int w){
	if (u->distance + w < v->distance) {
		v->distance = u->distance + w;
		v->pred = u;
	}

}
