#include <stdio.h>
#include <stdlib.h>

// estrutura da arvore
typedef struct no {
    int chave;
    int altura;
    struct no *esq;
    struct no *dir;
} No;

// ponteiro raiz
typedef No *arvoreAVL;

No *procuraMenor(No *atual); // implementada
arvoreAVL *criaArvoreAVL(); // implementada
int liberaArvoreAVL(arvoreAVL *raiz);  // implementada
void liberaNo(No *no); // implementada
void eliminaMenores(arvoreAVL *raiz, int v); // implementada
int insereArvoreAVL(arvoreAVL *raiz, int chave); // implementada
int removeArvoreAVL(arvoreAVL *raiz, int chave); // implementada
int buscaArvoreAVL(arvoreAVL *raiz, int chave); // implementada
int alturaArvoreAVL(arvoreAVL *raiz); // implementada
int avlSimilar(arvoreAVL *raiz1, arvoreAVL *raiz2); // implementada
void mostrapreOrdem(arvoreAVL *raiz); // implementada 
// funções usadas para a manipulação da arvore
int alturaNo(No *no); // implementada
int fatorBalanceamentoNo(No *no); // implementada
int maior(int x, int y); // implementada
void rotacaoLL(arvoreAVL *raiz);
void rotacaoRR(arvoreAVL *raiz);
void rotacaoLR(arvoreAVL *raiz);
void rotacaoRL(arvoreAVL *raiz); // todas implementadas
