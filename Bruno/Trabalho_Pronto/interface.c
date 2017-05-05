#include <stdio.h>
#include <stdlib.h>

void interfaceInicial() {
	printf("########################Trabalho de Organização########################\n");
	printf("Autores:\nBruno Homma\nLeonardo Mendes\nKeith Tsukada Sasaki\nValeska Paroni\n\n");
	printf("Escolha uma das opções abaixo:\n");
	printf("1 - Criar arquivo organizado com campos e registros\n");
	printf("2 - Recuperar os dados de todos os registros no arquivos\n");
	printf("3 - Recuperar dados de um registro do arquivo por filtro de pesquisa\n");
	printf("4 - Recuperar dados de um registro selecionado\n");
	printf("5 - Recuperar o dado de um campo selecionado de um registro escolhido\n");
	printf("6 - Limpar a tela\n");
	printf("7 - excluir os arquivos binários\n");
	printf("8 - Encerrar o programa\n");
}

void interfaceFacial() {
	printf("Preencher os  filtros da seguinte maneira:\n");
	printf("Tipos de Campos(escolher por valor dado abaixo):\n");
	printf("1 - cnpj\n");
	printf("2 - nome_social\n");
	printf("3 - nome_fantasma\n");
	printf("4 - data_registro\n");
	printf("5 - data_cancelamento\n");
	printf("6 - motivo_cancelamento\n");
	printf("7 - nome_empresa\n");
	printf("8 - cnpj_auditor\n");
}	