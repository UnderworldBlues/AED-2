#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <string.h>

int arvoreVazia(tipoArvore arvore) {
    return (arvore == NULL);
}

tipoArvore* inicializaArvore() {
  // aloca memoria para um tipoArvore e inicializa com NULL
  tipoArvore *arvore = (tipoArvore*) malloc(sizeof(tipoArvore));
  *arvore = NULL;
  return arvore;
}

void central(tipoArvore arvore) {
  if (!arvoreVazia(arvore)) {
    central(arvore->esq);
    printf("%s\n", arvore->chave.cep);
    central(arvore->dir);
  }
}

void pesquisaArvore(tipoApontador no, tipoApontador retorno, char *chave) {

  if (strcmp(chave, no->chave.cep) == 0) 
  {
    *retorno = no;
  } 
  else 
  {
    if (strcmp(chave, no->chave.cep) < 0) {
      pesquisaArvore(no->esq, retorno, chave);
    } 
    else {
      pesquisaArvore(no->dir, retorno, chave);
    }

  }
}

void insereArvore(tipoApontador no, tipoChave item){
  // se a arvore estiver vazia, o novo no sera a raiz
  if (no == NULL) 
  {
    // aloca a memoria e preenche os valores do novo no
    tipoApontador *aux = (tipoApontador*) malloc(sizeof(tipoApontador));
    (*aux)->chave = item;
    (*aux)->esq = NULL;
    (*aux)->dir = NULL;
    no = aux;

  } 
  else
  {
    // se o novo no for menor que o no atual, vai para a esquerda
    if (strcmp(item.cep, no->chave.cep) < 0) {
      insereArvore(no->esq, item);
    }
    else
    {
      // se o novo no for maior que o no atual, vai para a direita
      insereArvore(no->dir, item);
    }
  }
}

void antecessor(tipoApontador q, tipoApontador *r){
  if((*r)->dir != NULL){
    antecessor(q, &(*r)->dir);
    return;
  }
  q->chave = (*r)->chave;
  q = *r;
  *r = (*r)->esq;
  free(q);
}

void removeArvore(tipoArvore arvore, tipoChave chave){
  if(arvoreVazia(arvore)){
    printf("Arvore vazia\n");
    return;
  }

  tipoApontador *retorno;
  // procura o item na arvore
  pesquisaArvore(arvore, retorno, chave.cep);
  // se o item nao for encontrado, a funcao retorna a chamada
  if(retorno == NULL){
    printf("item nao encontrado na arvore\n");
    return;
  }

  // se o item for encontrado, verifica se ele eh uma folha
  if((*retorno)->esq == NULL && (*retorno)->dir == NULL){
    free(*retorno);
    *retorno = NULL;
  }
  // se o item tiver apenas um filho, o no eh removido e o filho assume seu lugar
  else if((*retorno)->esq == NULL){
    tipoApontador *aux = *retorno;
    *retorno = (*retorno)->dir;
    free(aux);
  }
  else if((*retorno)->dir == NULL){
    tipoApontador *aux = *retorno;
    *retorno = (*retorno)->esq;
    free(aux);
  }
  // se o item tiver dois filhos, o antecessor eh removido e o atual assume seu lugar
  else{
    tipoApontador *aux = *retorno;
    antecessor((*retorno)->esq, &aux);
    (*retorno)->chave = (*aux)->chave;
    removeArvore((*retorno)->esq, (*aux)->chave);
  }

}

// outras funções
int lerArquivo(tipoApontador *Dicionario, char *nomeArquivo) {
    char linha[100];

    tipoChave c;
  
    // char c[100]; // cep
    // char e[100]; // estado
    // char cid[100]; // cidade
    // char end[100]; // endereço
  
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro!, arquivo nao aberto");
        return 0;
    }

    int contador = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

      if (sscanf(linha, "%19[^;];%2[^;];%99[^;];%99[^\n]", c.cep, c.endereco, c.cidade, c.endereco) == 4) {
        insereArvore(Dicionario, c);
      }

      contador ++;
    }

    fclose(arquivo);
    return contador;
}