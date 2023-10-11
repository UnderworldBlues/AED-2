#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cep 
{
    char cep[100];
    char estado[100];
    char cidade[100];
    char endereco[100];
} CEP;

int lerArquivo(CEP *ceps, char *nomeArquivo);
void trocar(CEP *a, CEP *b);
void quickSort(CEP *ceps, int inicio, int fim);
int buscaBinaria(CEP *ceps, char *alvo, int inicio, int fim);