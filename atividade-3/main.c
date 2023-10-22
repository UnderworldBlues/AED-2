#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <string.h>

int main () {
  tipoArvore *arvore = inicializaArvore();
  tipoItem item;
  int opc = 0;
  leituraArquivo(arvore, "cep.txt");
  printf("ola\n");
  do {
    printf("voce deseja:\n1-procurar um endereco na arvore\n2-visualizar a arvore (nao recomendado)\n3-remover um endereco da arvore\n4-altura da arvore\n5-sair\n");
    scanf("%d", &opc);
    if((opc < 0) || (opc > 5)) {
      printf("opcao invalida\n");
      continue;
    }
    switch (opc){
      case 1:
        printf("digite o cep que deseja procurar, EXEMPLO: 55555-000\n");
        fflush(stdin);
        scanf("%s", item.cep);
        item.chave = atoi(item.cep);
        item = pesquisaArvore(arvore, item.chave);
        printf("o endereco eh: %s, %s, %s, %s\n", item.cep, item.estado, item.cidade, item.endereco);
        break;
      case 2:
        mostraArvorePosOrdem(arvore);
        break;
      case 3:
        printf("digite o cep que deseja remover, EXEMPLO: 55555-000\n");
        fflush(stdin);
        scanf("%s", item.cep);
        item.chave = atoi(item.cep);
        retira(arvore, item.chave);
        printf("item removido\n");
        break;

      case 4:
        printf("altura da arvore eh: %d\n", alturaArvore(arvore));
        break;
      
    }
  }while (opc != 5);
  return 0;
}