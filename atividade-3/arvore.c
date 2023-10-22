#include "arvore.h"

tipoArvore* inicializaArvore() 
{
    tipoArvore *raiz = (tipoArvore*) malloc(sizeof(tipoArvore));
    if (raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

int alturaArvore(tipoArvore *raiz){
    if (raiz == NULL) {
        printf("erro, a raiz nao existe\n");
        return -1;
    }
    if (*raiz == NULL) {
        return 0;
    }
    int altEsq = alturaArvore(&((*raiz)->esq));
    int altDir = alturaArvore(&((*raiz)->dir));
    if (altEsq > altDir) {
        return (altEsq + 1);
    } else {
        return (altDir + 1);
    }

}
void mostraArvorePosOrdem(tipoArvore *raiz)
{
    if (raiz == NULL) {
        return;
    }
    if (*raiz != NULL) {
        mostraArvorePosOrdem(&((*raiz)->esq));
        mostraArvorePosOrdem(&((*raiz)->dir));
        printf("[%s;%s;%s;%s]\n", (*raiz)->item.cep, (*raiz)->item.estado, (*raiz)->item.cidade, (*raiz)->item.endereco);
    }
}

// preferi fazer iterativa pq tava tendo uns problemas com recursao
int insereArvore(tipoArvore *raiz, tipoItem item)
{
    // conferindo se o ponteiro eh valido
    if (raiz == NULL) {
        printf("erro, a raiz nao existe\n");
        return 0;
    }

    tipoNo *novo;
    novo = (tipoNo*) malloc(sizeof(tipoNo));
    if (novo == NULL) {
        return 0;
    }
    novo->item = item;
    novo->dir = NULL;
    novo->esq = NULL;

    // caso nao tenha nenhum elemento na arvore
    if (*raiz == NULL) {
        *raiz = novo;

    // caso tenha algum elemento na arvore
    } else {
        tipoNo *atual = *raiz;
        tipoNo *ant = NULL;
        while (atual != NULL) {
            ant = atual;
            // se a chave ja existir, nao insere
            if (item.chave == atual->item.chave) {
                free(novo);
                return 0;
            }
            // se a chave for maior que a chave do no atual, vai pra direita
            if (item.chave > atual->item.chave) {
                atual = atual->dir;
            // Se nao, vai pra esquerda
            } else {
                atual = atual->esq;
            }
        }
        if (item.chave > ant->item.chave) {
            ant->dir = novo;
        } else {
            ant->esq = novo;
        }
    }
    return 1;
}

tipoItem pesquisaArvore(tipoArvore *raiz, int chave)
{
    if (raiz == NULL) {
        printf("erro, a raiz nao existe\n");
        return;
    }
    tipoNo *atual = *raiz;
    while (atual != NULL) {
        if (chave == atual->item.chave) {
            return atual->item;
        }
        if (chave > atual->item.chave) {
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    printf("nao encontrado\n");
}

void antecessor(tipoNo *q, tipoNo *r)
{
    if (r->dir != NULL) {
        antecessor(q, r->dir);
        return;
    }
    q->item = r->item;
    q = r;
    r = r->esq;
    free(q);
}

void retira(tipoArvore *raiz, int x)
{
    if (raiz == NULL) {
        printf("erro, a raiz nao existe\n");
        return;
    }
    tipoNo *p = *raiz;
    if (p == NULL) {
        printf("erro, arvore vazia\n");
        return;
    }
    if (x > p->item.chave) {
        retira(&(p->dir), x);
        return;
    }
    if (x < p->item.chave) {
        retira(&(p->esq), x);
        return;
    }
    if (p->dir == NULL) {
        *raiz = p->esq;
        free(p);
        return;
    }
    if (p->esq != NULL) {
        antecessor(p, p->esq);
        return;
    }
    *raiz = p->dir;
    free(p);
}

// outras funções
void leituraArquivo (tipoArvore *arvore, char *nomeArquivo) {
    FILE *arq;
    char linha[100];
    tipoItem item;

    arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    while (fgets(linha, sizeof(linha), arq) != NULL) {
      if (sscanf(linha, "%19[^;];%2[^;];%99[^;];%99[^\n]", item.cep, item.estado, item.cidade, item.endereco) == 4) {
        item.chave = atoi(item.cep);
        insereArvore(arvore, item);
      }
    }
    fclose(arq);
}