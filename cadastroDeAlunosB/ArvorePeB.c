#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "ArvorePeB.h"

typedef struct no No;
typedef struct aluno Aluno;

struct arvore {
	No * raiz;
};

struct aluno {
	int matricula;
	char nome[50];
	char email[50];
	char telefone[50];
};

struct no {
	No * pai;
	No * esq;
	No * dir;
	Aluno * aluno;
};

Arvore * criar() {
	Arvore * a = malloc(sizeof(Arvore));
	a->raiz = NULL;
	return a;
}

void destruir(Arvore * a) {
	free(a);
}

void pre_ordem(No * raiz) {
	if (raiz != NULL) {
		printf("%d | ", raiz->aluno->matricula);
		printf("%s | ", raiz->aluno->nome);
		printf("%s | ", raiz->aluno->email);
		printf("%s \n\n", raiz->aluno->telefone);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

void in_ordem(No * raiz) {
	if (raiz != NULL) {
		in_ordem(raiz->esq);
		printf("%d ", raiz->aluno->matricula);
		in_ordem(raiz->dir);
	}
}

void pos_ordem(No * raiz) {
	if (raiz != NULL) {
		pos_ordem(raiz->esq);
		pos_ordem(raiz->dir);
		printf("%d | ", raiz->aluno->matricula);
		printf("%s | ", raiz->aluno->nome);
		printf("%s | ", raiz->aluno->email);
		printf("%s \n\n", raiz->aluno->telefone);
	}
}

void imprimirPre(Arvore * a) {
	pre_ordem(a->raiz);
}

void imprimirIn(Arvore * a) {
	in_ordem(a->raiz);
}

void imprimirPos(Arvore * a) {
	pos_ordem(a->raiz);
}

void inserir_rec(No * * pRaiz, Aluno * aluno) {
	No* raiz = *pRaiz;
	if (raiz != NULL) {
		if (aluno->matricula < raiz->aluno->matricula) inserir_rec(&raiz->esq, aluno);
		if (aluno->matricula > raiz->aluno->matricula) inserir_rec(&raiz->dir, aluno);
	}
	else {
		raiz = (No *)malloc(sizeof(No));
		raiz->aluno = aluno;
		raiz->esq = NULL;
		raiz->dir = NULL;

		*pRaiz = raiz;
	}
}

void inserir(Arvore * a, int matricula, char nome[], char email[], char telefone[]) {
	Aluno * aluno = (Aluno *)malloc(sizeof(Aluno));
	aluno->matricula = matricula;
	strcpy(aluno->nome, nome);
	strcpy(aluno->email, email);
	strcpy(aluno->telefone, telefone);

	inserir_rec(&a->raiz, aluno);
}

void imprimirAluno(Aluno * a) {
	printf("\nMatricula: %d\n", a->matricula);
	printf("\nNome: %s\n", a->nome);
	printf("\nEmail: %s\n", a->email);
	printf("\nTelefone: %s\n", a->telefone);
}

Aluno * buscar_rec(No * raiz, int matricula) {
	if (raiz != NULL) {
		if (matricula < raiz->aluno->matricula) return buscar_rec(raiz->esq, matricula);
		if (matricula > raiz->aluno->matricula) return buscar_rec(raiz->dir, matricula);
		return raiz->aluno;
	}
	return NULL;
}

int consultar(Arvore * a, int matricula) {
	Aluno * aluno = buscar_rec(a->raiz, matricula);
	if (aluno != NULL) {
		imprimirAluno(aluno);
		return 1;
	}
	return 0;
}

int editarAluno(Arvore * a, int matricula) {
	Aluno * aluno = buscar_rec(a->raiz, matricula);
	if (aluno != NULL) {
		int opcao = 1;
		while (opcao != 5) {
			printf("======================Menu de edicao======================\n");
			printf("1\. Alterar nome\n"
				"2\. Alterar email\n"
				"3\. Alterar telefone\n"
				"4\. Alterar tudo\n"
				"5\. Sair da edicao\n");
			printf("==========================================================\n");
			printf("\nQual opcao do menu deseja executar?\n");
			scanf("%d", &opcao);
			if (opcao == 1) {
				system("cls");
				printf("--------------------------\n"
					"|                        |\n"
					"|      Alterar nome      |\n"
					"|                        |\n"
					"--------------------------\n");
				fflush(stdin);
				printf("\nNome: ");
				scanf("%s", aluno->nome);
			}
			if (opcao == 2) {
				system("cls");
				printf("--------------------------\n"
					"|                        |\n"
					"|      Alterar email     |\n"
					"|                        |\n"
					"--------------------------\n");
				fflush(stdin);
				printf("\nEmail: ");
				scanf("%s", aluno->email);
			}
			if (opcao == 3) {
				system("cls");
				printf("--------------------------\n"
					"|                        |\n"
					"|    Alterar telefone    |\n"
					"|                        |\n"
					"--------------------------\n");
				fflush(stdin);
				printf("\nTelefone: ");
				scanf("%s", aluno->telefone);
			}
			if (opcao == 4) {
				system("cls");
				printf("--------------------------\n"
					"|                        |\n"
					"|      Alterar tudo      |\n"
					"|                        |\n"
					"--------------------------\n"); 
				fflush(stdin);
				printf("\nNome: ");
				scanf("%s", aluno->nome);
				fflush(stdin);
				printf("\nEmail: ");
				scanf("%s", aluno->email);
				fflush(stdin);
				printf("\nTelefone: ");
				scanf("%s", aluno->telefone);
				fflush(stdin);
			}
			if (opcao == 5) {
				system("cls");
				printf("\n\n============================");
				printf("A operacao de edicao encerrada.");
				printf("===========================\n\n");
			}
			if (opcao < 1 || opcao > 5) {
				system("cls");
				printf("\n=============================");
				printf("Operacao invalida.");
				printf("================================\n");
			}
		}
		return 1;
	}
	return 0;
}

int remover_maior_rec(No * * pRaiz) {
	No * raiz = *pRaiz;
	if (raiz->dir != NULL) {
		return remover_maior_rec(&raiz->dir);
	}
	*pRaiz = raiz->esq;
	int info = raiz->aluno->matricula;
	free(raiz->aluno);
	free(raiz);
	return info;
}

int remover_menor_rec(No * * pRaiz) {
	No * raiz = *pRaiz;
	if (raiz->esq != NULL) {
		return remover_menor_rec(&raiz->esq);
	}
	*pRaiz = raiz->dir;
	int info = raiz->aluno->matricula;
	free(raiz->aluno);
	free(raiz);
	return info;
}

void remover_rec(No * * pRaiz, int matricula) {
	No * raiz = *pRaiz;
	if (raiz != NULL) {
		if (matricula < raiz->aluno->matricula) remover_rec(&raiz->esq, matricula);
		else if (matricula > raiz->aluno->matricula) remover_rec(&raiz->dir, matricula);
		else {
			//Folha
			if (raiz->esq == NULL && raiz->dir == NULL) {
				*pRaiz = NULL;
				free(raiz->aluno);
				free(raiz);
			}
			else {
				//Dois filhos
				if (raiz->esq != NULL && raiz->dir != NULL) {
					raiz->aluno->matricula = //remover_maior_rec(&raiz->esq);
						remover_menor_rec(&raiz->dir);
				}
				else {//Um filho
					if (raiz->esq != NULL) {
						*pRaiz = raiz->esq;
					}
					else {
						*pRaiz = raiz->dir;
					}
					free(raiz->aluno);
					free(raiz);
				}
			}
		}
	}
}

int remover(Arvore * a, int matricula) {
	Aluno * aluno = buscar_rec(a->raiz, matricula);
	if (aluno != NULL) {
		remover_rec(&a->raiz, matricula);
		return 1;
	}
	return 0;
}

void remover_todos_rec(Arvore * a, No * raiz) {
	if (raiz != NULL) {
		remover_todos_rec(a, raiz->esq);
		remover_todos_rec(a, raiz->dir);
		remover(a, raiz->aluno->matricula);
	}
}

void remover_todos(Arvore * a) {
	remover_todos_rec(a, a->raiz);
}