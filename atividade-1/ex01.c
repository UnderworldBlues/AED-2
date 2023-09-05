#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

#define N 8

int main (void)
{
    // inicializando a seed do gerador de numeros
    srand(time(NULL));
    // contador
    int i; 
    // ponteiro para a alocação  
    int *V;

    // alocando o vetor
    V = (int *)malloc(N*sizeof(int));   // não sabia se era pra alocar o vetor com 10.000 posições ou 8, então deixei 8 akakakaka

    for(i=0; i<N; i++)
        V[i] = rand()%100;

    printf("vetor desordenado:\n");
    for(i=0; i<N; i++)
        printf("%d ", V[i]);

    // ordenando o vetor    
    bubbleSort(V,8);

    printf("\nvetor ordenado:\n");
    for(i=0; i<N; i++)
        printf("%d ", V[i]);

    printf("\n");

    // liberando o vetor
    free(V);
    V = NULL;

    return 0;
}