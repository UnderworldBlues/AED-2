#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvoreAVL.h"

int main (){
    srand(time(NULL));
    arvoreAVL *raiz = criaArvoreAVL();
    int i, n, v;
    for (i = 0; i < 100; i++) {
        n = rand() % 10000;
        insereArvoreAVL(raiz, n);
    }
    printf("ao iniciar, a arvore ja possui 100 valores aleatorios\n");
    
    do{
        printf("vc deseja:\n1- inserir um valor\n2- Buscar um valor \n3- remover valores menores que N\n4-visualizar a arvore\n5- descobrir se as subarvores sao similares\n6- sair\n");
        scanf("%d", &v);
        if((v < 1) || (v > 6)){
            printf("valor invalido\n");
            continue;
        }
        switch(v){

            case 1:
                printf("digite o valor a ser inserido\n");
                scanf("%d", &n);
                insereArvoreAVL(raiz, n);
                break;

            case 2:
                printf("digite o valor a ser buscado\n");
                scanf("%d", &n);
                if((n = buscaArvoreAVL(raiz, n)) < 0){
                    printf("valor nao encontrado\n");
                }else{
                    printf("valor encontrado, esta na altura %d\n", n);
                }
                break;

            case 3:
                printf("digite o valor N\n");
                scanf("%d", &n);
                eliminaMenores(raiz, n);
                break;

            case 4:

                mostrapreOrdem(raiz);
                break;
                
            case 5:
                if(avlSimilar(raiz, raiz)){
                    printf("as subarvores sao similares\n");
                }else{
                    printf("as subarvores nao sao similares\n");
                }
                break;
        }
    }while(v != 6);

    
}
