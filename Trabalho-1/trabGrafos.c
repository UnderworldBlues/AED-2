#include <stdio.h>
#include <stdlib.h>
#include <string.h> // para funções de manipulação de strings
#include <limits.h> // para INT_MAX
#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define FALSE           0
#define TRUE            1

// MAIN NA LINHA 439

// removi aquele execesso de typedefs pra ficar mais facil de ler
typedef struct tipoNode tipoNode;
typedef int tipoPeso;

// tipo item vai guardar as ligações entre os professores
typedef struct tipoItem {
    // vertice guarda a posição do professor no vetor de professores
    int vertice;
    // numArtigos guarda o numero de artigos que o professor tem em relação ao outro professor
    int numArtigos;
    // ex: Barioni na posição 0 e ze gustavo na 3 tem 2 artigos juntos
    // esse tipo guardaria a posição de um deles e o numero de artigos que eles tem juntos
} tipoItem;

// tipo node são os "nós" da lista
typedef struct tipoNode {
    tipoItem item;
    struct tipoNode *prox;
} tipoNode;

// tipolsita é a cabeça da lista, cada vertice no grafo tem uma lista propria
typedef struct tipoLista {
    tipoNode *primeiro, *ultimo;
} tipoLista;

typedef struct tipoGrafo {
    // a matriz de professores guarda a posição e o nome de cada professor
    char professor[MAXNUMVERTICES][100];
    // a lista de adjacencia guarda as ligações entre os professores
    // os vertices tem que condizer com a matriz de professores
    tipoLista *adj;
    int numVertices;
    int numArestas;
} tipoGrafo;

typedef struct tipoHeap {
    int tamanho;
    int *posicao;
    int *vetor;
} tipoHeap;

// tipo componente fortemente conexa guarda os professores que estão no mesmo componente
typedef struct componenteFortementeConexos {
    // professores guarda a posição dos professores no vetor de professores
    int professores[MAXNUMVERTICES];
    // size guarda o numero de professores na componente
    int size;
} tipoComponenteFortementeConexa;

tipoHeap *criaheap ()
{
    tipoHeap *heap = (tipoHeap *) malloc(sizeof(tipoHeap));
    heap->posicao = (int *) malloc(MAXNUMVERTICES * sizeof(int));
    heap->vetor = (int *) malloc(MAXNUMVERTICES * sizeof(int));
    heap->tamanho = 0;
    return heap;
}

void swap (int *a, int *b) 
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

// função pra fazer o heapify
void minheapify (tipoHeap *heap, int indice) 
{
    // menor recebe o indice do nó atual
    int menor = indice;
    // esquerda recebe o indice do filho da esquerda
    int esquerda = 2 * indice + 1;
    // direita recebe o indice do filho da direita
    int direita = 2 * indice + 2;

    // se o filho da esquerda for menor que o nó atual
    if (esquerda < heap->tamanho && heap->vetor[esquerda] < heap->vetor[menor])
        // menor recebe o indice do filho da esquerda
        menor = esquerda;
    // se o filho da direita for menor que o nó atual
    if (direita < heap->tamanho && heap->vetor[direita] < heap->vetor[menor])
        // menor recebe o indice do filho da direita
        menor = direita;

    // se o menor não for o nó atual
    if (menor != indice) 
    {
        // troca o nó atual com o menor
        // e chama a função recursivamente para o nó que foi trocado
        // até que o nó atual seja o menor dentro da subarvore
        heap->posicao[heap->vetor[menor]] = indice;
        heap->posicao[heap->vetor[indice]] = menor;
        swap(&heap->vetor[menor], &heap->vetor[indice]);
        minheapify(heap, menor);
    }
    // basicamente o minheapify vai trocando o raiz do heap seja o menor elemento
}

// função de inserção de items no heap
void insereHeap (tipoHeap *heap, tipoItem item)
{
    // aumenta o tamanho do heap a cada chamada
    heap->tamanho++;
    int i = heap->tamanho - 1;

    heap->vetor[i] = item.vertice;
    heap->posicao[item.vertice] = i;
    // basicamente o heap vai subindo até que o nó atual seja menor que o pai
    while (i && heap->vetor[i] < heap->vetor[(i - 1) / 2]) {
        heap->posicao[heap->vetor[i]] = (i - 1) / 2;
        heap->posicao[heap->vetor[(i - 1) / 2]] = i;
        swap(&heap->vetor[i], &heap->vetor[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

tipoItem *removeHeap (tipoHeap *heap) 
{
    if (heap->tamanho == 0)
        return NULL;

    tipoItem *raiz = (tipoItem *) malloc(sizeof(tipoItem));
    raiz->vertice = heap->vetor[0];
    heap->vetor[0] = heap->vetor[heap->tamanho - 1];
    heap->posicao[heap->vetor[0]] = 0;
    heap->tamanho--;
    minheapify(heap, 0);
    return raiz;
}

/* A primeira parte da função inicializa um vetor de distâncias com valores infinitos, 
cria um heap mínimo e inicializa seus valores com os índices dos vértices do grafo
Em seguida, o valor da distância do vértice de origem é definido como zero e o heap é atualizado
O loop principal da função remove o vértice com a menor distância do heap e atualiza as distâncias dos seus vizinhos,
caso a distância atual seja maior do que a distância calculada passando pelo vértice atual.
No fim da algoritmo, a função retorna a distância do vértice de destino.*/
int dijkstra (tipoGrafo *grafo, int origem, int destino)
{
    // distancia guarda a distancia entre os vertices
    int distancia[grafo->numVertices];
    tipoHeap *heap = criaheap();

    // inicializa o heap e o vetor de distancias
    // o heap guarda os vertices e a distancia guarda a distancia entre eles
    // distancia é iniciado com o valor maximo possivel de uma variavel inteira
    for (int i = 0; i < grafo->numVertices; i++) 
    {
        distancia[i] = INT_MAX;
        heap->vetor[i] = i;
        heap->posicao[i] = i;
    }

    heap->tamanho = grafo->numVertices;
    heap->vetor[origem] = 0;
    heap->vetor[0] = origem;
    heap->posicao[origem] = 0;
    heap->posicao[0] = origem;
    distancia[origem] = 0;

    // loop principal, vai até o heap ficar vazio
    while (heap->tamanho) 
    {
        // remove o vertice com a menor distancia do heap
        tipoItem *item = removeHeap(heap);
        int u = item->vertice;
        tipoNode *atual = grafo->adj[u].primeiro->prox;

        // atualiza a distancia dos vizinhos do vertice removido
        while (atual != NULL) 
        {
            // v recebe o vertice vizinho
            int v = atual->item.vertice;

            // se o vertice vizinho estiver no heap e a distancia do vertice removido for diferente de infinito
            // e a distancia do vertice vizinho for maior que a distancia do vertice removido + o numero de artigos entre eles
            // atualiza a distancia do vertice vizinho
            if (heap->posicao[v] < heap->tamanho && distancia[u] != INT_MAX && atual->item.numArtigos + distancia[u] < distancia[v]) 
            {
                distancia[v] = distancia[u] + atual->item.numArtigos;
                heap->vetor[heap->posicao[v]] = distancia[v];
                heap->vetor[heap->posicao[distancia[v]]] = v;
                heap->posicao[v] = heap->posicao[distancia[v]];
                heap->posicao[distancia[v]] = v;
            }
            atual = atual->prox;
        }
    }
    // retorna a distancia entre os dois vertices 
    return distancia[destino];
}

tipoGrafo *criaGrafo(int numVertices) {

    tipoGrafo *grafo = (tipoGrafo *) malloc(sizeof(tipoGrafo));
    grafo->adj = (tipoLista *) malloc(numVertices * sizeof(tipoLista));
    grafo->numVertices = numVertices;
    grafo->numArestas = 0;

    for (int i = 0; i < numVertices; i++) 
    {
        grafo->adj[i].primeiro = (tipoNode *) malloc(sizeof(tipoNode));
        grafo->adj[i].ultimo = grafo->adj[i].primeiro;
        grafo->adj[i].primeiro->prox = NULL;
    }

    return grafo;
}

// insere um item na lista
void insere (tipoItem x, tipoGrafo *grafo, int vertice)
{
    // aloca um espaço na memoria para o ultimo nó da lista
    grafo->adj[vertice].ultimo->prox = (tipoNode*) malloc(sizeof(tipoNode));
    // aponta o ultimo para o ultimo nó da lista
    grafo->adj[vertice].ultimo = grafo->adj[vertice].ultimo->prox;
    // e aponta o proximo nó para null
    grafo->adj[vertice].ultimo->prox = NULL;
    // e guarda o item no ultimo nó
    grafo->adj[vertice].ultimo->item = x;
}

// insere uma aresta no grafo
// v1 é o vertice de origem e v2 é o vertice de chegada, ou autor e coautor se vc preferir
void insereAresta(int *v1, int *v2, int *peso, tipoGrafo *grafo)
{
    // cria um item
    tipoItem x;
    // guarda o vertice 2 no item
    x.vertice = *v2;
    // guarda o peso no item
    x.numArtigos = *peso;
    // e finalmente insere o item na lista do vertice 1
    insere(x, grafo, *v1);
}

// procura um vertice no grafo
int findVertice(tipoGrafo *grafo, char *professor)
{
    // percorre o vetor de professores
    for (int i = 0; i < grafo->numVertices; i++)
        // se o nome do professor for igual ao nome do professor na posição i do vetor
        if (strcmp(grafo->professor[i], professor) == 0)
            // retorna a posição dele no vetor
            return i;
    // se não encontrar o professor, retorna -1
    return -1;
}


// lê o arquvio e guarda as ligações entre os professores dele no grafo
void lerArquivo(tipoGrafo *g) {

    int i = 0;
    // origem guarda o nome do professor de origem, o autor
    char origem[100];
    // destino guarda o nome do professor de destino, o coautor
    char destino[100];
    // indice guarda o numero de professores extraidos do arquivo
    int artigos, indice = 0;
    // V1 e V2 guardam a posição dos professores no vetor de professores
    int V1, V2;

    FILE *professores = fopen("lista_professores.txt", "r");
    if (professores == NULL) {
        // se não for possivel abrir o arquivo, o programa é encerrado
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    // lê o arquivo enquanto não chegar no fim dele
    while (fscanf(professores, "%[^,], %[^,], %d\n", origem, destino, &artigos) != EOF) {

        for (i = 0; i < indice; i++)
            if (strcmp(g->professor[i], origem) == 0)
                break;
        if (i == indice)
            strcpy(g->professor[indice++], origem);

        for (i = 0; i < indice; i++)
            if ((strcmp(g->professor[i], destino) == 0))
                break;

        if (i == indice)
            strcpy(g->professor[indice++], destino);

        for (i = 0; i < indice; i++)
            if (strcmp(g->professor[i], origem) == 0)
                break;

        // procura o vertice de origem e destino no vetor de professores
        V1 = findVertice(g, origem);
        V2 = findVertice(g, destino);

        g->numArestas++;
        insereAresta(&V1, &V2, &artigos, g);
    }

    fclose(professores);
    
}
// função auxiliar do dfs
tipoComponenteFortementeConexa *dfs (tipoGrafo *grafo, int vertice, int *tempo, int *descoberta, int *termino, int *visitado, tipoComponenteFortementeConexa *componente) {
    visitado[vertice] = TRUE;
    descoberta[vertice] = (*tempo)++;
    componente->professores[componente->size++] = vertice;
    tipoNode *atual = grafo->adj[vertice].primeiro->prox;
    while (atual != NULL) {
        int v = atual->item.vertice;
        if (visitado[v] != TRUE)
            componente = dfs(grafo, v, tempo, descoberta, termino, visitado, componente);
        atual = atual->prox;
    }
    termino[vertice] = (*tempo)++;
    return componente;
}

// imprime o grafo
void imprimeGrafo(tipoGrafo *grafo)
{
    // variavel auxiliar
    tipoNode *aux, *aux2;
    int i = 0;
    // percorre o vetor de professores
    while (aux != NULL) {
        // aux recebe o nó atual da lista e aux2 aponta para ele
        aux = grafo->adj[i].primeiro->prox;
        aux2 = aux;
        // imprime o nome do professor
        printf("%s: ", grafo->professor[i]);
        // enquanto aux não for null
        while (aux2 != NULL) {
            // imprime o nome do coautor
            printf("%s ", grafo->professor[aux2->item.vertice]);
            // e o numero de artigos que eles tem juntos
            printf("(%d) ", aux2->item.numArtigos);
            // e avança para o proximo nó
            aux2 = aux2->prox;
        }
        i++;
        // imprime uma quebra de linha
        printf("\n");
    }
}

void buscarCoautores(tipoGrafo *grafo, char *nome)
{
    // variavel auxiliar
    tipoNode *aux;
    // check é uma variavel que vai verificar se o professor tem coautores/foi encontrado
    int check = FALSE;

    for(int i = 0; i < grafo->numVertices; i++)
    {
        // se o nome do professor for igual ao nome do professor na posição i do vetor
        if (strcmp(grafo->professor[i], nome) == 0)
        {
            printf("Coautores de %s:\n", nome);
            // aux recebe o primeiro nó da lista
            aux = grafo->adj[i].primeiro->prox;
            // enquanto aux não for null
            while (aux != NULL)
            {
                // imprime o nome do coautor
                printf("%s publicou ", grafo->professor[aux->item.vertice]);
                // e o numero de artigos que eles tem juntos
                printf("(%d) artigos com ", aux->item.numArtigos);
                // imprime o nome do autor
                printf("%s\n", nome);
                // e avança para o proximo nó
                aux = aux->prox;
            }

            check = TRUE;
            // quebra linha
            printf("\n");
        }
    }
    if (check == FALSE)
        printf("Professor nao encontrado! Certifique-se de que você escreveu o nome correto.\n");
}

void buscarCoautoresNartigos (tipoGrafo *grafo, char *nome, int numArtigos)
{
    // variavel auxiliar
    tipoNode *aux;
    // check vai verificar se o professor foi encontrado
    int check = FALSE;
    // check2 vai verificar se o professor tem coautores com o numero de artigos especificado
    int check2 = FALSE;
    printf("Coautores de %s com %d artigos publicados:\n", nome, numArtigos);

    for(int i = 0; i < grafo->numVertices; i++)
    {
        // se o nome do professor for igual ao nome do professor na posição i da matriz
        if (strcmp(grafo->professor[i], nome) == 0)
        {
            // aux recebe o primeiro nó da lista
            aux = grafo->adj[i].primeiro->prox;
            // enquanto aux não for null
            while (aux != NULL)
            {
                if (aux->item.numArtigos >= numArtigos)
                {
                    // imprime o nome do coautor
                    printf("%s publicou ", grafo->professor[aux->item.vertice]);
                    // e o numero de artigos que eles tem juntos
                    printf("(%d) artigos com ", aux->item.numArtigos);
                    // imprime o nome do autor
                    printf("%s\n", grafo->professor[i]);
                    // e avança para o proximo nó
                    check2 = TRUE;
                }
                aux = aux->prox;
            }

            check = TRUE;
            // quebra linha
            printf("\n");
        }
    }
    if (check == FALSE)
        printf("Professor nao encontrado! Certifique-se de que você escreveu o nome correto.\n");
    if (check2 == FALSE)
        printf("Nenhum coautor encontrado com %d artigos publicados.\n", numArtigos);

}

int main ()
{
    char nome[100];
    tipoGrafo grafo;
    int v, opc;
    tipoComponenteFortementeConexa componente;
    grafo = *criaGrafo(MAXNUMVERTICES);
    lerArquivo(&grafo);
    
    do{
        printf("voce deseja:\n1-Vizualizar o grafo\n2-Buscar coautores\n3-Buscar coautores com um numero de artigos especifico\n4-Buscar componentes fortemente conexos\n5-Procurar caminho de custo minimo entre dois vertices\n6-Sair\n");
        scanf("%d", &opc);
        if((opc < 1)||(opc > 6))
        {
            printf("opcao invalida\n");
            continue;
        }
        switch(opc)
        {
            case 1:
                printf("existem %d vertices e %d arestas\n", grafo.numVertices, grafo.numArestas);
                imprimeGrafo(&grafo);
                break;
            case 2:
                printf("devido as limitações da linguagem C, pedimos que o usuario omita acentos, caracteres especiais e que leia a cedilha como o caractere C\n");
                printf("digite o nome do professor\n");
                fflush(stdin);
                scanf ("%[^\n]%*c", nome);
                buscarCoautores(&grafo, nome);
                printf("\n");
                break;
            case 3:
                printf("devido as limitações da linguagem C, pedimos que o usuario omita acentos, caracteres especiais e que leia a cedilha como o caractere C\n");
                printf("digite o nome do professor\n");
                fflush(stdin);
                scanf ("%[^\n]%*c", nome);
                printf("digite o numero de artigos\n");
                scanf("%d", &v);
                buscarCoautoresNartigos(&grafo, nome, v);
                printf("\n");
                break;
            case 4:
                printf("devido as limitações da linguagem C, pedimos que o usuario omita acentos, caracteres especiais e que leia a cedilha como o caractere C\n");
                printf("digite o nome do professor\n");
                fflush(stdin);
                scanf ("%[^\n]%*c", nome);
                int vertice = findVertice(&grafo, nome);
                int tempo = 0;
                int descoberta[MAXNUMVERTICES];
                int termino[MAXNUMVERTICES];
                int visitado[MAXNUMVERTICES];
                componente.size = 0;
                componente = *dfs(&grafo, vertice, &tempo, descoberta, termino, visitado, &componente);
                printf("Componente fortemente conexa de %s:\n", nome);
                for (int i = 0; i < componente.size; i++)
                    printf("%s\n", grafo.professor[componente.professores[i]]);
                printf("\n");
                break;
            case 5:
                printf("devido as limitações da linguagem C, pedimos que o usuario omita acentos, caracteres especiais e que leia a cedilha como o caractere C\n");
               // função para encontrar o caminho de custo mínimo entre dois vértices (Professores(as) P1 e P2), usando fila de prioridades com heap
                printf("digite o nome do professor de origem\n");
                fflush(stdin);
                scanf ("%[^\n]%*c", nome);
                int origem = findVertice(&grafo, nome);
                printf("digite o nome do professor de destino\n");
                fflush(stdin);
                scanf ("%[^\n]%*c", nome);
                int destino = findVertice(&grafo, nome);
                int distancia = dijkstra(&grafo, origem, destino);
                printf("A distancia entre %s e %s eh %d\n", grafo.professor[origem], grafo.professor[destino], distancia);
                printf("\n");
                break;

            case 6:
                break;
        }

    }while(opc != 6);

    return 0;
}
