#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//typedef struct no No;
// estrutura base do vetor de quotes, "year" vai ser usado pra fazer a busca binaria
typedef struct {
    char quoteLine[409];
    char movieName[50];
    int year;
}movieQuote;

// Definição das estruturas
typedef struct wordInfoList {
    char word[20]; // ou o tamanho adequado
    int index;  // vai guardar o indice da quote no vetor
} wordInfoList;

// no da arvore, cada no vai representar uma frequencia e guardar uma lista de palavras que
// aparecem com essa frequencia
typedef struct No {
    wordInfoList *item; // lista de palavras
    int itemSize; // tamanho da lista
    int frequency; // frequencia que palavaras aparecem
    int height;
    int offset;
    struct No *left;
    struct No *right;
} No;

// raiz da arvore
typedef No *avlTreeRoot;

// funções
int processCitations(char *filename, movieQuote *quoteList); // função de leitura de arquivo
void lowerItem (movieQuote *item); // função que deixa tudo minusculo
// funções do vetor de busca binaria
int findPreviousIndex(movieQuote *quoteList, int currentIndex); // confere se o indice anterior é o mesmo que o atual
int binarySearch(movieQuote *quoteList, int left, int right, movieQuote *movie);
void showArray(movieQuote *quoteList, int citationCounter);
// funções da arvore
int nodeHeight(No *node); // retorna a altura do nó
int balanceFactor(No *node); // retorna a diferença entre a altura da subarvore esquerda e direita
int max(int x, int y);
void leftRotation(avlTreeRoot *root);
void rightRotation(avlTreeRoot *root);
void doubleLeftRotation(avlTreeRoot *root);
void doubleRightRotation(avlTreeRoot *root);
int insertNode(avlTreeRoot *root, wordInfoList *item, int frequency, int offset); // insere um nó na arvore
void fillTree(avlTreeRoot *root, movieQuote *quoteList, int citationCounter);
int searchForFrequency(movieQuote *quoteList, int citationCounter, char *word); // retorna o numero de entradas com a frequencia especifica
int insertIntoWordlist(No *node, wordInfoList *item); // insere um item na lista de palavras do nó
void searchByFrequency(avlTreeRoot *root, movieQuote *quoteList, int frequency); // vai procurar na arvore por todas as entradas com a frequencia especifica
avlTreeRoot *createTree(); // cria a arvore
int searchForFrequency(movieQuote *quoteList, int citationCounter, char *word); // procura pela frequencia que uma palavra aparece na lista
int isWordInStack (wordInfoList *wordStack, int wordStackSize, char *word); // confere se a palavra ja esta na stack
int searchTreeForFrequency(avlTreeRoot *root, wordInfoList item, int frequency); // procura na arvore por uma frequencia especifica e insere items com essa frequencia
void copyQuoteList(movieQuote *quoteList, movieQuote *quoteListCopy, int citationCounter); // duplica a lista, necessaria pq strtok altera a string