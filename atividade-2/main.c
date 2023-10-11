#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main() 
{
    char alvo[10];
    int tamanhoMaximo = 585881, opc;
    CEP *ceps = (CEP *)malloc(tamanhoMaximo * sizeof(CEP));
    int numEntradas = lerArquivo(ceps, "cep.txt");

    quickSort(ceps, 0, numEntradas - 1);
    do 
    {
        printf("voce deseja buscar um cep?\n1 - sim\n2 - nao, sair\n");
        scanf("%d", &opc);
        if (opc < 1 || opc > 2) 
        {
            printf("opcao invalida\n");
            continue;
        }
        if (opc == 1) 
        {
            printf("digite o cep que deseja buscar (modelo: XXXXX-XXX)\n");
            fflush(stdin);
            gets(alvo);

            int posicao = buscaBinaria(ceps, alvo, 0, numEntradas - 1);
            
            if (posicao == 0) 
            {
                printf("cep nao encontrado\n");
            } 
            else 
            {
                printf("cep encontrado\n");
                printf("cep: %s\n", ceps[posicao].cep);
                printf("estado: %s\n", ceps[posicao].estado);
                printf("cidade: %s\n", ceps[posicao].cidade);
                printf("endereco: %s\n", ceps[posicao].endereco);
            }

        }else 
        {
            break;
        }

    } while (opc != 2);

    free(ceps);

    return 0;
}

