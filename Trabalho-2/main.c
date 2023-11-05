#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include <time.h>

int main (){
    int opc;
    int index;
    movieQuote quoteList[732];
    movieQuote quoteListCopy[732];
    movieQuote movie;
    // inicializando as estruturas
    printf("carregando as estruturas...\n");
    clock_t tic = clock();
    avlTreeRoot *root = createTree();
    int citationCounter = processCitations("movie_quotes.csv", quoteList);
    copyQuoteList(quoteList, quoteListCopy, citationCounter);
    fillTree(root, quoteListCopy, citationCounter);
    clock_t toc = clock();
    printf("estruturas carregadas em %f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    // menu
    printf("Bem vindo(a)\n");
    do
    {
        printf("Voce deseja:\n");
        printf("1 - Buscar frases por ano\n");
        printf("2 - Buscar palavras/frases por frequencia\n");
        printf("3 - Buscar frequencia com que uma palavra aparece\n");
        printf("4 - Visualizar todas as frases\n");
        printf("5 - Sair\n");
        scanf("%d", &opc);
        if(opc < 1 || opc > 5){
            printf("Opcao invalida\n");
            continue;
        }
        
        switch (opc)
        {

            case 1:
                printf("Buscar frases por ano\n");
                printf("Digite um ano: ");
                scanf("%d", &movie.year);
                tic = clock();
                index = binarySearch(quoteList, 0, citationCounter, &movie);
                toc = clock();
                printf("Busca binaria concluida em %f segundos\nResultado:\n", (double)(toc - tic) / CLOCKS_PER_SEC);
                if (index == -1)
                {
                    printf("Nenhum filme nesse ano\n");
                    break;
                }
                else
                {
                    printf("Filmes nesse ano:\n");
                    for(int i = index; i < citationCounter; i++)
                    {
                        if(quoteList[i].year != movie.year)
                            break;
                        printf("========================================\n");
                        printf("[%s]\n", quoteList[i].quoteLine);
                        printf("%s - %d\n", quoteList[i].movieName, quoteList[i].year);
                        printf("Offset: %d\n", i);
                        printf("========================================\n");
                    }
                }
                break;
            case 2:
                printf("Buscar palavras/frases por frequencia\n");
                printf("Digite a frequencia: ");
                scanf("%d", &movie.year);
                tic = clock();
                searchByFrequency(root,quoteList, movie.year);
                toc = clock();
                printf("Busca por frequencia concluida em %f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
                break;
            case 3:
                printf("Buscar frequencia com que uma palavra aparece\n");
                printf("Digite a palavra: ");
                fflush(stdin);
                scanf("%s", movie.movieName);
                lowerItem(&movie);
                tic = clock();
                int frequency = searchForFrequency(quoteList, citationCounter, movie.movieName);
                toc = clock();
                printf("Busca concluida em %f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
                if(frequency == 0)
                    printf("Palavra nao encontrada\n");
                else
                {
                    printf("A palavra %s aparece %d vezes\n", movie.movieName, frequency-1);
                    printf("Deseja ver as frases? (1 - sim, 2 - nao)\n");
                    scanf("%d", &opc);
                    if(opc == 1)
                    {
                        for(int i = 0; i < citationCounter; i++)
                        {
                            if(strstr(quoteList[i].quoteLine, movie.movieName) != NULL)
                            {
                                printf("========================================\n");
                                printf("[%s]\n", quoteList[i].quoteLine);
                                printf("%s - %d\n", quoteList[i].movieName, quoteList[i].year);
                                printf("Offset: %d\n", i);
                                printf("========================================\n");
                            }
                        }
                    }
                }
                break;
            case 4 :
                printf("Visualizar todas as frases\n");
                showArray(quoteList, citationCounter);
                break;

        }    

    }while(opc != 5);


   
    system("pause");
    return 0;
}