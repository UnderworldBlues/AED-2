#include "arvoreAVL.h"

arvoreAVL *criaArvoreAVL() {
    arvoreAVL *raiz = (arvoreAVL *) malloc(sizeof(arvoreAVL));
    if (raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

int liberaArvoreAVL(arvoreAVL *raiz) {
    if (raiz == NULL) {
        // retorna 1 se a arvore nao existir
        return 1;
    }
    liberaNo(*raiz);
    free(raiz);
    return 0;
}

void liberaNo(No *no) {
    if (no == NULL) {
        return;
    }
    liberaNo(no->esq);
    liberaNo(no->dir);
    free(no);
    no = NULL;
}

int maior (int x, int y) {
    if (x > y) {
        return x;
    }
    return y;
}

int alturaNo(No *no) {
    if (no == NULL) {
        return -1;
    }
    return no->altura;
}

int fatorBalanceamentoNo(No *no) {
    return labs(alturaNo(no->esq) - alturaNo(no->dir));
}

void rotacaoRR (arvoreAVL *raiz) {
    No *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->altura = maior(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;
    no->altura = maior(alturaNo(no->dir), (*raiz)->altura) + 1;
    (*raiz) = no;
}

void rotacaoLL (arvoreAVL *raiz) {
    No *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = (*raiz);
    (*raiz)->altura = maior(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;
    no->altura = maior(alturaNo(no->esq), (*raiz)->altura) + 1;
    (*raiz) = no;
}

void rotacaoLR (arvoreAVL *raiz) {
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}

void rotacaoRL (arvoreAVL *raiz) {
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}

int insereArvoreAVL(arvoreAVL *raiz, int chave){

    if (*raiz == NULL) {
        No *novo;
        novo = (No *) malloc(sizeof(No));
        if (novo == NULL) {
            return 0;
        }
        novo->chave = chave;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    No *atual = *raiz;
    if(chave < atual->chave) {
        if ((insereArvoreAVL(&(atual->esq), chave)) == 1) {
            if (fatorBalanceamentoNo(atual) >= 2) {
                if (chave < (*raiz)->esq->chave) {
                    rotacaoLL(raiz);
                } else {
                    rotacaoLR(raiz);
                }
            }
        }
    } else {
        if (chave > atual->chave) {
            if ((insereArvoreAVL(&(atual->dir), chave)) == 1) {
                if (fatorBalanceamentoNo(atual) >= 2) {
                    if ((*raiz)->dir->chave < chave) {
                        rotacaoRR(raiz);
                    } else {
                        rotacaoRL(raiz);
                    }
                }
            }
        } else {
            printf("Valor duplicado!\n");
            return 0;
        }
    }
}


No *procuraMenor(No *atual) {
    No *no1 = atual;
    No *no2 = atual->esq;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int removeArvoreAVL(arvoreAVL *raiz, int chave) {
    if (*raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return 0;
    }
    int retorno;
    if (chave < (*raiz)->chave) {
        if ((retorno = removeArvoreAVL(&(*raiz)->esq, chave)) == 1) {
            if (fatorBalanceamentoNo(*raiz) >= 2) {
                if (alturaNo((*raiz)->dir->esq) <= alturaNo((*raiz)->dir->dir)) {
                    rotacaoRR(raiz);
                } else {
                    rotacaoRL(raiz);
                }
            }
        }
    }
    if ((*raiz)->chave < chave) {
        if ((retorno = removeArvoreAVL(&(*raiz)->dir, chave)) == 1) {
            if (fatorBalanceamentoNo(*raiz) >= 2) {
                if (alturaNo((*raiz)->esq->dir) <= alturaNo((*raiz)->esq->esq)) {
                    rotacaoLL(raiz);
                } else {
                    rotacaoLR(raiz);
                }
            }
        }
    }
    if ((*raiz)->chave == chave) {
        if (((*raiz)->esq == NULL || (*raiz)->dir == NULL)) {
            No *aux = (*raiz);
            if ((*raiz)->esq != NULL) {
                *raiz = (*raiz)->esq;
            } else {
                *raiz = (*raiz)->dir;
            }
            free(aux);
        } else {
            No *temp = procuraMenor((*raiz)->dir);
            (*raiz)->chave = temp->chave;
            removeArvoreAVL(&(*raiz)->dir, (*raiz)->chave);
            if (fatorBalanceamentoNo(*raiz) >= 2) {
                if (alturaNo((*raiz)->esq->dir) <= alturaNo((*raiz)->esq->esq)) {
                    rotacaoLL(raiz);
                } else {
                    rotacaoLR(raiz);
                }
            }
        }
        if (*raiz != NULL) {
            (*raiz)->altura = maior(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;
        }
        return 1;
    }
    (*raiz)->altura = maior(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;
    return retorno;
}

void eliminaMenores (arvoreAVL *raiz, int v) {
    if (*raiz == NULL) {
        return;
    }
    eliminaMenores(&(*raiz)->esq, v);
    eliminaMenores(&(*raiz)->dir, v);
    if ((*raiz)->chave < v) {
        removeArvoreAVL(raiz, (*raiz)->chave);
    }
}

int buscaArvoreAVL(arvoreAVL *raiz, int chave) {
    if (*raiz == NULL) {
        // retorna um numero negativo se a arvore estiver vazia
        return -1;
    }
    No *atual = *raiz;
    while (atual != NULL) {
        if (chave == atual->chave) {
            // retorna a altura do elemento se encotrada
            return atual->altura;
        }
        if (chave > atual->chave) {
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    // retornada -2 se o elemento nao for encontrado
    return -2;
}

int alturaArvoreAVL(arvoreAVL *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    if (*raiz == NULL) {
        return 0;
    }
    int alturaEsq = alturaArvoreAVL(&((*raiz)->esq));
    int alturaDir = alturaArvoreAVL(&((*raiz)->dir));
    if (alturaEsq > alturaDir) {
        return (alturaEsq + 1);
    } else {
        return (alturaDir + 1);
    }
}

int avlSimilar(arvoreAVL *raiz1, arvoreAVL *raiz2){
    // se as duas arvores estiverem vazias, elas sao iguais, retorna 0
    if (*raiz1 == NULL && *raiz2 == NULL) {
        return 0;
    }
    if (*raiz1 != NULL && *raiz2 != NULL) {
        return (avlSimilar(&(*raiz1)->esq, &(*raiz2)->esq) && avlSimilar(&(*raiz1)->dir, &(*raiz2)->dir));
    }
    // se uma arvore for vazia e a outra nao, elas nao sao iguais, retorna 1
    return 1;
}

void mostrapreOrdem(arvoreAVL *raiz) {
    if (raiz == NULL) {
        return;
    }
    if (*raiz != NULL) {
        printf("[%d]\n", (*raiz)->chave);
        mostrapreOrdem(&((*raiz)->esq));
        mostrapreOrdem(&((*raiz)->dir));
    }
}