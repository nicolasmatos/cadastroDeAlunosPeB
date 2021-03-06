typedef struct arvore Arvore;
typedef struct no No;
typedef struct aluno Aluno;

Arvore * criar();
void destruir(Arvore * a);
void imprimirPre(Arvore * a);
void imprimirIn(Arvore * a);
void imprimirPos(Arvore * a);

void inserir(Arvore * a, int matricula, char nome[], char email[], char telefone[]);
Aluno * buscar(Arvore * a, int v);
int buscar_maior(Arvore * a);
int remover(Arvore * a, int v);

int esta_vazia(Arvore * a);