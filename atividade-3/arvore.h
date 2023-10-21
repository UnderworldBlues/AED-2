typedef struct tipoChave {
    char cep[50];
    char estado[10];
    char cidade[50];
    char endereco[50];
} tipoChave;

typedef struct tipoNo tipoNo;
typedef tipoNo *tipoApontador;

typedef struct tipoNo {
    tipoChave chave;
    tipoApontador esq, dir;
} tipoNo;

// tipo arvore vai apontar para um tipoNo e agir como a raiz da arvore
typedef tipoApontador tipoArvore;

tipoArvore* inicializaArvore();
int arvoreVazia(tipoArvore arvore);
void insereArvore(tipoApontador no, tipoChave item);
void removeArvore(tipoArvore arvore, tipoChave chave);
void central(tipoArvore arvore);
void antecessor(tipoApontador q, tipoApontador *r);
void pesquisaArvore(tipoApontador no, tipoApontador retorno, char *chave);
int lerArquivo(tipoArvore *arvore, char *nomeArquivo);
