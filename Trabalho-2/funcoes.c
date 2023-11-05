#include "funcoes.h"

void lowerItem(movieQuote *item)
{
    for(int i = 0; i < strlen(item->quoteLine); i++)
        item->quoteLine[i] = tolower(item->quoteLine[i]);

    for(int i = 0; i < strlen(item->movieName); i++)
        item->movieName[i] = tolower(item->movieName[i]);
}

// função de leitura de arquivo 1
int processCitations(char *filename, movieQuote *quoteList) {
    // abre o arquivo e confere se o ponteiro é valido

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // variaveis auxuliares
    int citationCounter = 0; // contador de citações para manipulação do vetor
    char *token; // delimitador para leitura do arquivo
    movieQuote itemToBeAdded; // item a ser adicionado no vetor
    char line[600]; // linha do arquivo

    // leitura do arquivo
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        // inicializa o token e copia o item separado para o vetor
        // o token é o delimitador, que no caso é o "_"
        // como tem 3 elementos no vetor, tem q repetir esse processo 3 vezes
        token = strtok(line, "_");
        if (token != NULL) 
        {
            // se o token for valido, copia ele pro vetor
            strncpy(itemToBeAdded.quoteLine, token, sizeof(itemToBeAdded.quoteLine) - 1);
            itemToBeAdded.quoteLine[sizeof(itemToBeAdded.quoteLine) - 1] = '\0';

            token = strtok(NULL, "_");
            if (token != NULL) 
            {
                strncpy(itemToBeAdded.movieName, token, sizeof(itemToBeAdded.movieName) - 1);
                itemToBeAdded.movieName[sizeof(itemToBeAdded.movieName) - 1] = '\0';

                // como é o ultimo item, o delimitador é o \n
                token = strtok(NULL, "\n");
                if (token != NULL) 
                {
                    // converte o ultimo item pra inteiro e insere no vetor
                    itemToBeAdded.year = atoi(token);
                    lowerItem(&itemToBeAdded);
                    quoteList[citationCounter] = itemToBeAdded;
                    citationCounter++;
                }
            }
        }
    }
    // fecha o arquivo e retorna o contador
    fclose(file);
    return citationCounter;
}

// função de busca binaria
int binarySearch(movieQuote *quoteList, int left, int right, movieQuote *movie){
    // primeiro a gente percorre o array procurando pelo ano do filme
    if(right >= left)
    {
        int mid = left + (right - left) / 2;
        // se encontrado, é feita uma busca linear no subarray com o ano encontrado
        if(quoteList[mid].year == movie->year)
        {
            // se o ano anterior for o mesmo, então o indicide atual não é a primeira ocorrencia daquele ano
            // então é feita uma busca linear pra trás até encontrar a primeira ocorrencia daquele ano
            if (quoteList[mid].year == quoteList[mid - 1].year)
                return findPreviousIndex(quoteList, mid);
            // se nao, retorna o indice atual
            return mid;
        }
        // se o ano for menor que o ano do item atual, procura no subarray da direita
        if(quoteList[mid].year > movie->year)
            return binarySearch(quoteList, left, mid - 1, movie);
        // se o ano for maior que o ano do item atual, procura no subarray da esquerda
        return binarySearch(quoteList, mid + 1, right, movie);
    }
    return -1;
}

// encontra a primeira ocorrencia de um ano especifico dentro do array
int findPreviousIndex(movieQuote *quoteList, int currentIndex){
    int previousIndex = currentIndex - 1;
    while(quoteList[previousIndex].year == quoteList[currentIndex].year)
        previousIndex--;
    return previousIndex + 1;
}

void showArray(movieQuote *quoteList, int citationCounter){
    for(int i = 0; i < citationCounter; i++)
    {
        printf("========================================\n");
        printf("%s - %d", quoteList[i].movieName, quoteList[i].year);
        printf("[%s]\n", quoteList[i].quoteLine);
    }
}

int nodeHeight(No *node){
    if(node == NULL)
        return -1;
    else
        return node->height;
}

int balanceFactor(No *node){
    return labs(nodeHeight(node->left) - nodeHeight(node->right));
}

int max(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

void leftRotation(avlTreeRoot *root){
    No *aux;
    aux = (*root)->left;
    (*root)->left = aux->right;
    aux->right = *root;
    (*root)->height = max(nodeHeight((*root)->left), nodeHeight((*root)->right)) + 1;
    aux->height = max(nodeHeight(aux->left), (*root)->height) + 1;
    *root = aux;
}

void rightRotation(avlTreeRoot *root){
    No *aux;
    aux = (*root)->right;
    (*root)->right = aux->left;
    aux->left = *root;
    (*root)->height = max(nodeHeight((*root)->left), nodeHeight((*root)->right)) + 1;
    aux->height = max(nodeHeight(aux->right), (*root)->height) + 1;
    *root = aux;
}

void doubleLeftRotation(avlTreeRoot *root){
    rightRotation(&(*root)->left);
    leftRotation(root);
}

void doubleRightRotation(avlTreeRoot *root){
    leftRotation(&(*root)->right);
    rightRotation(root);
}

// função de inserção na arvore,
int insertNode(avlTreeRoot *root, wordInfoList *item, int frequency, int offset)
{
    if(*root == NULL)
    {
        No *newNode = (No*)malloc(sizeof(No));
        if(newNode == NULL) return 0;
        newNode->item = (wordInfoList*)malloc(sizeof(wordInfoList));
        if(newNode->item == NULL) return 0;
        strcpy(newNode->item[0].word, item->word);
        newNode->item[0].index = item->index;
        newNode->itemSize = 1;
        newNode->offset = offset;
        newNode->frequency = frequency;
        newNode->height = 0;
        newNode->left = NULL;
        newNode->right = NULL;
        *root = newNode;
        return 1;
    }
    int retorno;
    No *currentNode = *root;
    // usa a frequencia como chave de ordenação
    if(frequency < currentNode->frequency)
    {
        if((retorno = insertNode(&(currentNode->left), item, frequency, offset + 1)) == 1)
        {
            if(balanceFactor(currentNode) >= 2)
            {
                if(frequency < (*root)->left->frequency)
                    leftRotation(root);
                else
                    doubleLeftRotation(root);
            }
        }
    }
    else
    {
        if(frequency > currentNode->frequency)
        {
            if((retorno = insertNode(&(currentNode->right), item, frequency, offset + 1)) == 1)
            {
                if(balanceFactor(currentNode) >= 2)
                {
                    if(frequency > (*root)->right->frequency)
                        rightRotation(root);
                    else
                        doubleRightRotation(root);
                }
            }
        }
        else
            // palavra ja existe na arvore
            return 0;
    }
    currentNode->height = max(nodeHeight(currentNode->left), nodeHeight(currentNode->right)) + 1;
    return retorno;
}

// cria a arvore
avlTreeRoot *createTree(){
    avlTreeRoot *root = (avlTreeRoot*)malloc(sizeof(avlTreeRoot));
    if(root != NULL)
        *root = NULL;
    return root;
}

void searchByFrequency(avlTreeRoot *root,movieQuote *quoteList, int frequency){
    // confere se a arvore é valida
    if(*root == NULL)
    {
        printf("Arvore vazia\n");
        return;
    }

    // se sim, procura pelo node com a frequencia especifica
    No *currentNode = *root;
    while(currentNode != NULL)
    {
        // se econtrar, imprime os dados dele
        if(frequency == currentNode->frequency)
        {
            int opc;
            printf("=============================================\n");
            printf("Palavras que aparecem com frequencia [%d]\n", frequency);
            // percorre a lista de palavras do nó e imprime as palavras
            for(int i = 0; i < currentNode->itemSize; i++)
                printf("[%s] ", currentNode->item[i].word);

            printf("\nOffset: %d\n", currentNode->offset);
            printf("=============================================\n");
            printf("Deseja visualizar as frases? (1- sim/0- nao)\n");
            scanf("%d", &opc);
            if(opc == 1)
            {
                for(int i = 0; i < currentNode->itemSize; i++)
                {
                    printf("========================================\n");
                    printf("[%s]\n", quoteList[currentNode->item[i].index].quoteLine);
                    printf("%s - %d\n", quoteList[currentNode->item[i].index].movieName, quoteList[currentNode->item[i].index].year);
                    printf("========================================\n");
                }
            }
            
            return;
        }
        // se não, continua a busca
        if(frequency > currentNode->frequency)
            currentNode = currentNode->right;
        else
            currentNode = currentNode->left;
    }
    // se não encontrar, imprime uma mensagem e retorna a chamada
    printf("Frequencia nao encontrada\n");
    return;
}

//função de preenchimento da arvore
void fillTree(avlTreeRoot *root, movieQuote *quoteList, int citationCounter)
{
    // wordStack vai ser a lista de palavras que ja foram inseridas na arvore[
    wordInfoList *wordStack = (wordInfoList*)malloc(sizeof(wordInfoList));
    if(wordStack == NULL) return;
    int wordStackSize = 0;
    wordInfoList itemToBeAdded;
    char *token; // delimitador
    int frequency = 0; // frequencia da palavra

    // percorre o vetor
    for(int i = 0; i < citationCounter; i++){
        // ao encontrar uma quote, separa as palavras dela
        token = strtok(quoteList[i].quoteLine, " ,.!?");
        // pra ter certeza que a pontuação vai ser removida
        token = strtok(quoteList[i].quoteLine, ",.");
        token = strtok(quoteList[i].quoteLine, ",.");
        token = strtok(quoteList[i].quoteLine, ",.");

        while(token != NULL)
        {
            // se a palavra for maior que 4 caracteres, ela é selecionada pra ser inserida na arvore
            if(strlen(token) >= 4)
            {
                // se a palavra não estiver na stack, 
                if(isWordInStack(wordStack, wordStackSize, token) == 0)
                {
                    // remove a pontuação da palavra
                    // aloca um item novo pra wordStack
                    wordStack = (wordInfoList*)realloc(wordStack, (wordStackSize + 1) * sizeof(wordInfoList));
                    // copia a palavra para o novo item da wordstack
                    strcpy(wordStack[wordStackSize].word, token);
                    // e então atualiza o tamanho da stack
                    wordStackSize++;
                    // copia os dados para itemToBeAdded
                    strcpy(itemToBeAdded.word, token);
                    itemToBeAdded.index = i;
                    // e então procura pela frequencia da palavra
                    frequency = searchForFrequency(quoteList, citationCounter, token);
                    // e então procura por ocorrencias dessa frequencia na arvore
                    // se encontrar, insere o item na lista de palavras do nó
                    if(searchTreeForFrequency(root, itemToBeAdded, frequency) == 0)
                    {
                        // se a palavra for encontrada, ela é inserida na arvore
                        insertNode(root, &itemToBeAdded, frequency, 0);
                    }
                }
            }
            // e então o token é atualizado
            token = strtok(NULL, " ");
        }
    }
}

// função de busca por palavra
int searchForFrequency(movieQuote *quoteList, int citationCounter, char *word){
    int frequency = 0;
    // percorre o vetor de quotes
    for(int i = 0; i < citationCounter; i++)
    {
        // se a palavra estiver na quote, atualiza a frequencia
        if(strstr(quoteList[i].quoteLine, word) != NULL)
                frequency++;
    }
    return frequency;

}

// confere se a palavra ja esta na stack
int isWordInStack (wordInfoList *wordStack, int wordStackSize, char *word){
    for(int i = 0; i < wordStackSize; i++)
    {
        if(strcmp(wordStack[i].word, word) == 0)
            return 1;
    }
    return 0;
}

int searchTreeForFrequency(avlTreeRoot *root, wordInfoList item, int frequency){
    // confere se a arvore é valida
    if(*root == NULL)
    {
        return 0;
    }
    No *currentNode = *root;

    while(currentNode != NULL)
    {
        // se a frequencia for encontrada, vai inserir o item nesse node
        if(frequency == currentNode->frequency)
        {
            // aloca mais um espaço na lista de palavras
            currentNode->item = (wordInfoList*)realloc(currentNode->item, (currentNode->itemSize + 1) * sizeof(wordInfoList));
            if(currentNode->item == NULL) return 0;
            // e copia os dados
            strcpy(currentNode->item[currentNode->itemSize].word, item.word);
            currentNode->item[currentNode->itemSize].index = item.index;
            currentNode->itemSize++;
            // retorna 1 pra indicar que o item foi inserido
            return 1;
        }
        // se não, continua procurando pelo node com a frequencia especifica
        if(frequency > currentNode->frequency)
            currentNode = currentNode->right;
        else
            currentNode = currentNode->left;
    }
    // se não encontrar, retorna 0
    return 0;
}

// duplica a quoteList
void copyQuoteList(movieQuote *quoteList, movieQuote *quoteListCopy, int citationCounter){
    for(int i = 0; i < citationCounter; i++)
        quoteListCopy[i] = quoteList[i];
}