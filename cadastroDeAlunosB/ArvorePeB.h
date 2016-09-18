typedef struct arvore Arvore;
typedef struct no No;
typedef struct aluno Aluno;

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

void inserir(Arvore * a, int matricula, char nome[], char email[], char telefone[]);
int buscar(Arvore * a, int v);
int remover(Arvore * a, int v);