#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoItem {
    char cep[100];
    char estado[100];
    char cidade[100];
    char endereco[100];
    // chave vai ser usado para ordenar a arvore
    // o conteudo dela vai ser os 5 primeiros digitos do cep 
    int chave;
} tipoItem;

typedef struct tipoNo {
    tipoItem item;
    struct tipoNo *esq;
    struct tipoNo *dir;
} tipoNo;

typedef tipoNo *tipoArvore;

tipoArvore* inicializaArvore();
int alturaArvore (tipoArvore *raiz);
void antecessor (tipoNo *q, tipoNo *r);
void retira (tipoArvore *raiz, int x);
void mostraArvorePosOrdem (tipoArvore *raiz);
int insereArvore (tipoArvore *raiz, tipoItem item);
tipoItem pesquisaArvore (tipoArvore *raiz, int chave);
void leituraArquivo(tipoArvore *arvore, char *nomeArquivo);
