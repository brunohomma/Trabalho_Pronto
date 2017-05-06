/*
 * Trabalho de Organização de Arquivos - Arquivo Interface Básica
 * Autores do Trabalho (Nome/NUSP):
 * - Bruno Mitsuo Homma 		9293605
 * - Leonardo Mendes Bonato		9074308
 * - Keith Tsukada Sasaki 		9293414
 * - Valeska Paroni Silva 		7977886
 */
#include <stdio.h>
#include <stdlib.h>

// Mostra um menu inicial com as funções do programa
void interfaceInicial() {
	printf("########################Trabalho de Organização########################\n");
	printf("Autores:\nBruno Homma\nLeonardo Mendes\nKeith Tsukada Sasaki\nValeska Paroni\n\n");
	printf("Escolha uma das opções abaixo:\n");
	printf("1 - Criar arquivo organizado com campos e registros\n");
	printf("2 - Recuperar os dados de todos os registros no arquivos\n");
	printf("3 - Recuperar dados de um registro do arquivo por filtro de pesquisa\n");
	printf("4 - Recuperar dados de um registro selecionado\n");
	printf("5 - Recuperar o dado de um campo selecionado de um registro escolhido\n");
	printf("6 - excluir os arquivos binários\n");
	printf("7 - Encerrar o programa\n");
}

// Mostra um menu de campos para o usuario escolher para usar na busca filtrada
void interfaceFacial() {
	printf("Escolha por qual campo deve ser filtrado a busca (Escolha por números mostrados no menu abauxo):\n");
	printf("1 - CNPJ\n");
	printf("2 - Nome Social\n");
	printf("3 - Nome Fantasma\n");
	printf("4 - Data Registro\n");
	printf("5 - Data Cancelamento\n");
	printf("6 - Motivo Cancelamento\n");
	printf("7 - Nome Empresa\n");
	printf("8 - CNPJ Auditor\n");
}	

// Apaga a tela depois que o usuario pressionar a tecla ENTER
void apagaTela() {
	char c;

	do {
		printf("Pressione a tecla enter para continuar...\n");
		c = fgetc(stdin);
	} while(c != 10);
	printf("\e[H\e[2J");
}