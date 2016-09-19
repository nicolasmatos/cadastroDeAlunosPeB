#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvorePeB.h"

/*
1.	Carregar os alunos para memória a partir da base de dados.
2.	Inserir um novo aluno na memória a partir de nome, email e telefone fornecidos. O valor da nova matrícula deve ser gerado automaticamente, sendo sempre a maior matrícula na base de dados mais 1.
3.	Listar os dados de todos os alunos por ordem de matrícula.
4.	Listar os dados de todos os alunos cujas matrículas estão contidas em um arquivo (ver anexos).
5.	Consultar dados do aluno a partir da matrícula fornecida.
6.	Alterar os dados de nome, email e telefone a partir da matrícula fornecida.
7.	Remover um aluno a partir da matrícula fornecida.
8.	Remover os dados de todos os alunos cujas matrículas estão contidas em um arquivo (ver anexos).
9.	Remover todos os alunos.
10.	Salvar os alunos na base de dados a partir da memória, refletindo qualquer inclusão, exclusão ou alteração feita através do programa.
*/

void carregaAlunos(Arvore * a, FILE * fp) {
	int i = 0;
	char c = fgetc(fp);
	
	char nome[50];
	char email[50];
	char telefone[50];
	int matricula;
	
	char buffer[500];
	
	while(fgets(buffer,sizeof(buffer),fp)) { //Cada vez que a fun��o fgets � chamada, ele armazena em buffer a pr�xima linha do arquivo.
		sscanf(buffer,"%d | %[^|] | %[^|] | %[^\n]",&matricula,nome,email,telefone); //Formata a string no formato desejado e armazena em variaveis
		
		char nome[strlen(nome)-1] = '\n';//retira ultimo espa�o em branco
		char email[strlen(nome)-1] = '\n';
		
		inserir(a, mat, nome, email, telefone);//Insere na arvore
	}

	
	fclose(fp);
}

void removerAlunos(Arvore * a, FILE * fp) {
	int i = 0;
	char c = fgetc(fp);

	while (c != EOF) {
		char matricula[50];
		int mat;

		while (c != '\n') {
			matricula[i] = c;
			i++;
			c = fgetc(fp);
		}
		matricula[i] = '\0';
		i = 0;
		mat = atoi(matricula);
		remover(a, mat);

		c = fgetc(fp);
	}
	fclose(fp);
}

void consultarAlunos(Arvore * a, FILE * fp) {
	int i = 0;
	char c = fgetc(fp);

	while (c != EOF) {
		char matricula[50];
		int mat;

		while (c != '\n') {
			matricula[i] = c;
			i++;
			c = fgetc(fp);
		}
		matricula[i] = '\0';
		i = 0;
		mat = atoi(matricula);
		consultar(a, mat);

		c = fgetc(fp);
	}
	fclose(fp);
}

void chamaArquivo(Arvore * a, char arquivo[]) {
	char caminho[100];
	strcpy(caminho, "Arquivos\\");
	strcat(caminho, arquivo);
	strcat(caminho, ".txt");

	FILE * fp;
	fp = fopen(caminho, "r");
	if (fp == NULL) {
		printf("\nErro na abertura do arquivo\n");
		printf("OBS: Verifique o nome do arquivo\n\n");
	}
	carregaAlunos(a, fp);
}

void chamaArquivoR(Arvore * a, char arquivo[]) {
	char caminho[100];
	strcpy(caminho, "Arquivos\\");
	strcat(caminho, arquivo);
	strcat(caminho, ".txt");

	FILE * fp;
	fp = fopen(caminho, "r");
	if (fp == NULL) {
		printf("\nErro na abertura do arquivo\n");
		printf("OBS: Verifique o nome do arquivo\n\n");
	}
	removerAlunos(a, fp);
}

void chamaArquivoC(Arvore * a, char arquivo[]) {
	char caminho[100];
	strcpy(caminho, "Arquivos\\");
	strcat(caminho, arquivo);
	strcat(caminho, ".txt");

	FILE * fp;
	fp = fopen(caminho, "r");
	if (fp == NULL) {
		printf("\nErro na abertura do arquivo\n");
		printf("OBS: Verifique o nome do arquivo\n\n");
	}
	consultarAlunos(a, fp);
}

int main() {
	Arvore * a = criar();
	int opcao = 1;

	while (opcao != 11) {
		printf("================================Menu de opcoes================================\n");
		printf("1\. Carregar os alunos\n"
			"2\. Inserir um novo aluno\n"
			"3\. Listar os dados de todos os alunos por ordem de matricula\n"
			"4\. Listar os dados de todos os alunos de um arquivo\n"
			"5\. Consultar dados do aluno por matricula\n"
			"6\. Alterar os dados do aluno por matricula\n"
			"7\. Remover um aluno por matricula\n"
			"8\. Remover os dados de todos os alunos de um arquivo\n"
			"9\. Remover todos os alunos\n"
			"10\. Salvar os alunos \n"
			"11\. Sair do programa\n");
		printf("===============================================================================\n");
		printf("\nQual opcao do menu deseja executar?\n");
		scanf("%d", &opcao);
		if (opcao == 1) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|     Carregar alunos    |\n"
				"|                        |\n"
				"--------------------------\n");
			char arquivo[50];
			fflush(stdin);
			printf("Nome do arquivo a ser carregado: ");
			scanf("%s", arquivo);
			fflush(stdin);

			chamaArquivo(a, arquivo);
			imprimirPre(a);
		}
		if (opcao == 2) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|     Inserir aluno      |\n"
				"|                        |\n"
				"--------------------------\n");
			int matricula;
			char nome[50];
			char email[50];
			char telefone[50];
			printf("\nMatricula: ");
			scanf("%d", &matricula);

			fflush(stdin);
			printf("\nNome: ");
			scanf("%s", nome);
			fflush(stdin);
			printf("\nEmail:");
			scanf("%s", email);
			fflush(stdin);
			printf("\nTelefone: ");
			scanf("%s", telefone);
			fflush(stdin);

			inserir(a, matricula, nome, email, telefone);
			printf("\n");
			imprimirPre(a);
		}
		if (opcao == 3) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"| Listando por matricula |\n"
				"|                        |\n"
				"--------------------------\n");
		}
		if (opcao == 4) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|  Listando de arquivo   |\n"
				"|                        |\n"
				"--------------------------\n");
			char arquivo[50];
			fflush(stdin);
			printf("Nome do arquivo a ser carregado: ");
			scanf("%s", arquivo);
			fflush(stdin);

			chamaArquivoC(a, arquivo);
		}
		if (opcao == 5) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"| Consulta por matricula |\n"
				"|                        |\n"
				"--------------------------\n");
			int matricula;
			printf("\nMatricula: ");
			scanf("%d", &matricula);
			int result = consultar(a, matricula);
			if (result == 0) printf("\nO aluno nao foi encontrado.\n");
		}
		if (opcao == 6) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|  Edicao por matricula  |\n"
				"|                        |\n"
				"--------------------------\n");
			int matricula;
			printf("\nMatricula: ");
			scanf("%d", &matricula);
			int result = editarAluno(a, matricula);
			if (result == 0) printf("\nO aluno nao foi encontrado.\n");
		}
		if (opcao == 7) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"| Remocao por matricula  |\n"
				"|                        |\n"
				"--------------------------\n");
			int matricula;
			printf("\nMatricula: ");
			scanf("%d", &matricula);
			int result = remover(a, matricula);
			if (result == 0) printf("\nO aluno nao foi encontrado.\n");
		}
		if (opcao == 8) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|  Remocao por arquivo   |\n"
				"|                        |\n"
				"--------------------------\n");
			char arquivo[50];
			fflush(stdin);
			printf("Nome do arquivo a ser carregado: ");
			scanf("%s", arquivo);
			fflush(stdin);

			chamaArquivoR(a, arquivo);
		}
		if (opcao == 9) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|    Removendo todos     |\n"
				"|                        |\n"
				"--------------------------\n");
			remover_todos(a);
		}
		if (opcao == 10) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|  Salvando interacoes   |\n"
				"|                        |\n"
				"--------------------------\n");
		}
		if (opcao == 11) {
			system("cls");
			printf("\n\n============================");
			printf("A operacao foi encerrada.");
			printf("===========================\n\n");
			getch();
		}
		if (opcao < 1 || opcao > 11) {
			system("cls");
			printf("\n=============================");
			printf("Operacao invalida.");
			printf("================================\n");
		}
	}
	destruir(a);
	system("pause");
}
