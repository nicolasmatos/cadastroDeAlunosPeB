typedef struct arvore Arvore;
typedef struct no No;

Arvore * criar();
void destruir(Arvore * a);
void imprimirPre(Arvore * a);
void imprimirIn(Arvore * a);
void imprimirPos(Arvore * a);

int contar_nos(Arvore * a);
int contar_nos_rec(No * raiz);

int altura(Arvore * a);
int altura_rec(No * raiz);

int contar_folhas(Arvore * a);
int contar_folhas_rec(No * raiz);

void inserir(Arvore * a, int v);
int buscar(Arvore * a, int v);
void remover(Arvore * a, int v);