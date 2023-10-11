#include "func.h"

void trocar(CEP *a, CEP *b) {
    CEP temp;
    memcpy(&temp, a, sizeof(CEP));
    memcpy(a, b, sizeof(CEP));
    memcpy(b, &temp, sizeof(CEP));
}

void quickSort(CEP *ceps, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = inicio;
        int i = inicio;
        int j = fim;

        while (i < j) {
            while (strcmp(ceps[i].cep, ceps[pivo].cep) <= 0 && i < fim) i++;
            while (strcmp(ceps[j].cep, ceps[pivo].cep) > 0) j--;

            if (i < j) {
                trocar(&ceps[i], &ceps[j]);
            }
        }

        trocar(&ceps[pivo], &ceps[j]);
        quickSort(ceps, inicio, j - 1);
        quickSort(ceps, j + 1, fim);
    }
}

int buscaBinaria(CEP *ceps, char *alvo, int inicio, int fim) {
    if (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int comparacao = strcmp(ceps[meio].cep, alvo);

        if (comparacao == 0) {
            return meio;
        } else if (comparacao < 0) {
            return buscaBinaria(ceps, alvo, meio + 1, fim);
        } else {
            return buscaBinaria(ceps, alvo, inicio, meio - 1);
        }
    }

    return 0;
}

int lerArquivo(CEP *ceps, char *nomeArquivo) 
{
    char linha[100];
    FILE *arquivo = fopen(nomeArquivo, "r");
    int contador = 0;

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo");
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) 
    {

      if (sscanf(linha, "%19[^;];%2[^;];%99[^;];%99[^\n]", ceps[contador].cep, ceps[contador].estado, ceps[contador].cidade, ceps[contador].endereco) == 4) {
          
      }
    
      contador ++;
    }

    fclose(arquivo);
    return contador;

}