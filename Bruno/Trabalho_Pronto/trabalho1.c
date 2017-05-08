/*
 * Trabalho de Organização de Arquivos - Arquivo Principal
 * Autores do Trabalho (Nome/NUSP):
 * - Bruno Mitsuo Homma 		9293605
 * - Leonardo Mendes Bonato		9074308
 * - Keith Tsukada Sasaki 		9293414
 * - Valeska Paroni Silva 		7977886
 */
#include <stdio.h>
#include <stdlib.h>
#include <registro1.h>
#include <registro2.h>
#include <buscafiltrada.h>
#include <interface.h>
#include <leituraArquivoBinario.h>

#define ENTER 10
#define ESPACO 32

// palavra-chave para a busca por filtro
void catch_string(char **str2) {
	char letra;
	int s1 = 0, s2 = 0;

	(*str2) = NULL;

	printf("Buscar por: ");
	do {
		letra = fgetc(stdin);
		(*str2) = (char *)realloc((*str2), sizeof(char)*(s2+1));
		if (letra != ENTER) (*str2)[s2++] = letra;
		else (*str2)[s2++] = '\0';
	} while(letra != ENTER);
}

// verifica se os arquivos existem
int existeArquivos(const char *f1, const char *f2, const char *f3) {
	FILE *stream1 = NULL, *stream2 = NULL, *stream3 = NULL;

	stream1 = fopen(f1, "rb");
	stream2 = fopen(f2, "rb");
	stream3 = fopen(f3, "rb");

	if (stream1 == NULL && stream2 == NULL && stream3 == NULL) return 0;

	fclose(stream1);
	fclose(stream2);
	fclose(stream3);

	return 1;
}

int main (int argc, char **argv) {
	FILE *stream;
	char *chave, c;
	int op; // auxiliar para escolher as opções do programa
	int nroCampo, nroRegistro, filtro;
	regQtd = 0;

	do {
		FILE *aux = fopen("regQtd.dat", "rb"); // verifica se tem o arquivo que contem a quantidade de registros criados 
		if (aux != NULL) {
			fread(&regQtd, sizeof(int), 1, aux);
			fclose(aux);
		}	

		interfaceInicial(); // cria um menu para escolher as operações do programa
		do {
			op = fgetc(stdin)-48; // pega um valor do teclado;
			if (op <= 0 || op > 7) {
				printf("Opcão Inválida. Escolha uma opção válida!\n");
				apagaTela();
			}
			else getchar();		
		} while (op == 0 || op > 7);	
			
		switch(op) {
			case 1: // cria o arquivo binario
				printf("\e[H\e[2J");
				stream = fopen("SCC0215012017projeto01turmaBdadosCompanhias.csv", "r"); // abre o arquivo de entrada para organizar os registros em um arquivos de saidas
				importaRegistro_metodo1(stream);
				printf("Arquivo 1 Criado com sucesso!\n");
				fclose(stream);
				stream = fopen("SCC0215012017projeto01turmaBdadosCompanhias.csv", "r");
				importaRegistro_metodo2(stream);
				printf("Arquivo 2 Criado com sucesso!\n");
				fclose(stream);
				apagaTela();
				break;

			case 2: // mostra todos os registros do arquivo binário
			printf("\e[H\e[2J");
			lerArquivoBinario();
			apagaTela();
			break;	

			case 3: // busca registros por filtração de dados
				stream = fopen("RegBin_metodo1.dat", "rb");
				printf("\e[H\e[2J");
				if (stream == NULL) {
					printf("Não foi possível Ler o arquivo! Arquivo inexistente...\n");
					apagaTela();
					break;
				}
				interfaceFacial();
				printf("Selecione um campo: ");
				fscanf(stdin, "%d", &filtro);
				getchar();
				catch_string(&chave);
				buscaFiltrada(stream, filtro, chave);
				fclose(stream);
				apagaTela();
				break;


			case 4: // busca registro pela sua posição lógica
				printf("\e[H\e[2J");
				printf("Escolha qual registro a ser buscado: ");
				fscanf(stdin, "%d", &nroRegistro);
				getchar();
				buscaRegistro(nroRegistro);
				apagaTela();
				break;

			case 5: // busca um campo de um determinado registro (posições lógicas em ambos)
				printf("\e[H\e[2J");
				printf("Escolha um campo de um registro para ser buscado:\n");
				printf("Campo: ");
				fscanf(stdin, "%d", &nroCampo);
				getchar();
				printf("Registro: ");
				fscanf(stdin, "%d", &nroRegistro);
				getchar();
				buscaCampo(nroCampo, nroRegistro);
				apagaTela();
				break;	

			case 6: // remove todos os arquivos binarios criados pelo programa
				printf("\e[H\e[2J");
				if (existeArquivos("RegBin_metodo1.dat", "RegBin_metodo2.dat", "regQtd.dat")) {
					printf("Removendo os arquivos binários...\n");
					remove("RegBin_metodo1.dat");
					remove("RegBin_metodo2.dat");
					remove("regQtd.dat");
				}

				else printf("Arquivos não existentes. Nada foi removido...\n");	
				apagaTela();
				regQtd = 0;
				break;	

			case 7: // só mostra mensagem de encerramento
				printf("\e[H\e[2J");
				printf("Programa encerrado...\n");
				break;		
		}
	} while (op != 7);	
	
	return 0;
}
