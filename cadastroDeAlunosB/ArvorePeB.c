#include <stdio.h>
#include <stdlib.h>
#include "ArvorePeB.h"

typedef struct no No;
typedef struct aluno Aluno;

struct arvore {
	No * raiz;
};

struct no {
	No * pai;
	No * esq;
	No * dir;

	struct aluno {
		int matricula;
		char nome[50];
		char email[50];
		char telefone[50];
	};
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
		printf("%d ", raiz->matricula);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

void in_ordem(No * raiz) {
	if (raiz != NULL) {
		in_ordem(raiz->esq);
		printf("%d ", raiz->matricula);
		in_ordem(raiz->dir);
	}
}

void pos_ordem(No * raiz) {
	if (raiz != NULL) {
		pos_ordem(raiz->esq);
		pos_ordem(raiz->dir);
		printf("%d ", raiz->matricula);
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

int contar_nos_rec(No * raiz) {
	if (raiz != NULL) {
		return contar_nos_rec(raiz->esq) +
			contar_nos_rec(raiz->dir) + 1;
	}
	return 0;
}

int contar_nos(Arvore * a) {
	return contar_nos_rec(a->raiz);
}

int altura_rec(No * raiz) {
	if (raiz != NULL) {
		int ae = altura_rec(raiz->esq);
		int ad = altura_rec(raiz->dir);
		return ae > ad ? ae + 1 : ad + 1;
		//return (ae > ad ? ae : ad) + 1;
	}
	return -1;
}

int altura(Arvore * a) {
	return altura_rec(a->raiz);
}

int contar_folhas_rec(No * raiz) {
	if (raiz != NULL) {
		if (raiz->esq != NULL || raiz->dir != NULL) {
			return contar_folhas_rec(raiz->esq) +
				contar_folhas_rec(raiz->dir);
		}
		else {
			return 1;
		}
	}
	return 0;
}

int contar_folhas(Arvore * a) {
	return contar_folhas_rec(a->raiz);
}

void imprimir_nivel_rec(No * raiz, int nivel) {
	if (raiz != NULL) {
		if (nivel == 0) {
			printf("%d ", raiz->matricula);
		}
		else {
			imprimir_nivel_rec(raiz->esq, nivel - 1);
			imprimir_nivel_rec(raiz->dir, nivel - 1);
		}
	}
}

void imprimir_nivel(Arvore * a, int nivel) {
	imprimir_nivel_rec(a->raiz, nivel);
}

int imprimir_alt_rec(No * raiz, int altura) {
	if (raiz && (altura == 0 ||
		imprimir_alt_rec(raiz->esq, altura - 1) ||
		imprimir_alt_rec(raiz->dir, altura - 1))) {
		printf("%d ", raiz->matricula);
		return 1;
	}
	return 0;
}

void imprimir_alt(Arvore * a) {
	imprimir_alt_rec(a->raiz, altura(a));
}

/*
No * inserir_rec(No * raiz, int v) {
if (raiz != NULL) {
if (v < raiz->info) raiz->esq = inserir_rec(raiz->esq, v);
if (v > raiz->info) raiz->dir = inserir_rec(raiz->dir, v);
}
else {
raiz = (No *)malloc(sizeof(No));
raiz->info = v;
raiz->esq = NULL;
raiz->dir = NULL;
}
return raiz;
}
*/

void inserir_rec(No * * pRaiz, int v) {
	No* raiz = *pRaiz;
	if (raiz != NULL) {
		if (v < raiz->matricula) inserir_rec(&raiz->esq, v);
		if (v > raiz->matricula) inserir_rec(&raiz->dir, v);
	}
	else {
		raiz = (No *)malloc(sizeof(No));
		raiz->matricula = v;
		raiz->esq = NULL;
		raiz->dir = NULL;

		*pRaiz = raiz;
	}
}

void inserir(Arvore * a, int v) {
	//Recursivo
	////a->raiz = inserir_rec(a->raiz, v);
	//inserir_rec(&a->raiz, v);

	//Não recursivo
	No *ant = NULL, *raiz = a->raiz;
	while (raiz != NULL && raiz->matricula != v) {
		ant = raiz;
		raiz = v < raiz->matricula ? raiz->esq : raiz->dir;
	}
	if (raiz == NULL) {
		raiz = (No *)malloc(sizeof(No));
		raiz->matricula = v;
		raiz->esq = NULL;
		raiz->dir = NULL;
		if (ant == NULL) {
			a->raiz = raiz;
		}
		else {
			if (v < ant->matricula) {
				ant->esq = raiz;
			}
			else {
				ant->dir = raiz;
			}
		}
	}
}

int buscar_rec(No * raiz, int v) {
	if (raiz != NULL) {
		if (v < raiz->matricula) return buscar_rec(raiz->esq, v);
		if (v > raiz->matricula) return buscar_rec(raiz->dir, v);
		return 1;
	}
	return 0;
}

int buscar(Arvore * a, int v) {
	//Recursivo
	//return buscar_rec(a->raiz, v);

	//Não recursivo
	No * raiz = a->raiz;
	while (raiz != NULL && raiz->matricula != v) {
		raiz = v < raiz->matricula ? raiz->esq : raiz->dir;
	}
	return raiz != NULL ? 1 : 0;
}

int remover_maior_rec(No * * pRaiz) {
	No * raiz = *pRaiz;
	if (raiz->dir != NULL) {
		return remover_maior(&raiz->dir);
	}
	*pRaiz = raiz->esq;
	int info = raiz->matricula;
	free(raiz);
	return info;
}

int remover_maior(No * * pRaiz) {
	No * ant = NULL, *raiz = *pRaiz;
	while (raiz->dir != NULL) {
		ant = raiz;
		raiz = raiz->dir;
	}
	if (ant == NULL) {
		*pRaiz = raiz->esq;
	}
	else {
		ant->dir = raiz->esq;
	}
	int info = raiz->matricula;
	free(raiz);
	return info;
}

int remover_menor_rec(No * * pRaiz) {
	No * raiz = *pRaiz;
	if (raiz->esq != NULL) {
		return remover_maior(&raiz->esq);
	}
	*pRaiz = raiz->dir;
	int info = raiz->matricula;
	free(raiz);
	return info;
}

int remover_menor(No * * pRaiz) {
	No * ant = NULL, *raiz = *pRaiz;
	while (raiz->esq != NULL) {
		ant = raiz;
		raiz = raiz->esq;
	}
	if (ant == NULL) {
		*pRaiz = raiz->dir;
	}
	else {
		ant->esq = raiz->dir;
	}
	int info = raiz->matricula;
	free(raiz);
	return info;
}

void remover_rec(No * * pRaiz, int v) {
	No * raiz = *pRaiz;
	if (raiz != NULL) {
		if (v < raiz->matricula) remover_rec(&raiz->esq, v);
		else if (v > raiz->matricula) remover_rec(&raiz->dir, v);
		else {
			//Folha
			if (raiz->esq == NULL && raiz->dir == NULL) {
				*pRaiz = NULL;
				free(raiz);
			}
			else {
				//Dois filhos
				if (raiz->esq != NULL && raiz->dir != NULL) {
					raiz->info = //remover_maior_rec(&raiz->esq);
						remover_menor_rec(&raiz->dir);
				}
				else {//Um filho
					if (raiz->esq != NULL) {
						*pRaiz = raiz->esq;
					}
					else {
						*pRaiz = raiz->dir;
					}
					free(raiz);
				}
			}
		}
	}
}

void ajustar_anterior(Arvore * a, No * ant, int v, No * no) {
	if (ant == NULL) {
		a->raiz = no;
	}
	else {
		if (v < ant->matricula) {
			ant->esq = no;
		}
		else {
			ant->dir = no;
		}
	}
}

void remover(Arvore * a, int v) {
	//Recursivo
	//return remover_rec(&a->raiz, v);

	//Não recursivo
	No * ant = NULL, *raiz = a->raiz;
	while (raiz != NULL && raiz->matricula != v) {
		ant = raiz;
		raiz = v < raiz->matricula ? raiz->esq : raiz->dir;
	}
	if (raiz != NULL) {
		//Folha
		if (raiz->esq == NULL && raiz->dir == NULL) {
			ajustar_anterior(a, ant, v, NULL);
			free(raiz);
		}
		else {
			//Dois filhos
			if (raiz->esq != NULL && raiz->dir != NULL) {
				raiz->matricula = //remover_maior(&raiz->esq);
					remover_menor(&raiz->dir);
			}
			else {//Um filho
				if (raiz->esq != NULL) {
					ajustar_anterior(a, ant, v, raiz->esq);
				}
				else {
					ajustar_anterior(a, ant, v, raiz->dir);
				}
				free(raiz);
			}
		}
	}
}