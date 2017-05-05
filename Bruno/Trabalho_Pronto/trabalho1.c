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

int main (int argc, char **argv) {
	FILE *stream;
	char *chave;
	int op; // auxiliar para escolher as opções do programa
	int nroCampo, nroRegistro, filtro;
	regQtd = 0;

	do {
		FILE *aux = fopen("regQtd.dat", "rb"); // verifica se tem o arquivo que contem a quantidade de registros criados 
		if (aux != NULL) {
			fread(&regQtd, sizeof(int), 1, aux);
			fclose(aux);
		}	
		printf("Quantidade de registros: %d\n", regQtd);
		interfaceInicial(); // cria um menu para escolher as operações do programa
		do {
			op = fgetc(stdin)-48; // pega um valor do teclado;
			if (op == 0 || op > 8) printf("Opcão Inválida. Escolha uma opção válida!\n");
			getchar();
		} while (op == 0 || op > 8);	
			
		switch(op) {
			case 1: // cria o arquivo binario
				stream = fopen("SCC0215012017projeto01turmaBdadosCompanhias.csv", "r"); // abre o arquivo de entrada para organizar os registros em um arquivos de saidas
				importaRegistro_metodo1(stream);
				printf("Arquivo 1 Criado com sucesso!\n");
				fclose(stream);
				stream = fopen("SCC0215012017projeto01turmaBdadosCompanhias.csv", "r");
				importaRegistro_metodo2(stream);
				printf("Arquivo 2 Criado com sucesso!\n");
				fclose(stream);
				break;

			case 2: // mostra todos os registros do arquivo binário
			lerArquivoBinario();
			break;	

			case 3: // busca registros por filtração de dados
				stream = fopen("RegBin_metodo1.dat", "rb");
				interfaceFacial();
				printf("Filtro: ");
				fscanf(stdin, "%d", &filtro);
				getchar();
				catch_string(&chave);
				buscaFiltrada(stream, filtro, chave);
				fclose(stream);
				break;


			case 4: // busca registro pela sua posição lógica
				printf("Registro: ");
				fscanf(stdin, "%d", &nroRegistro);
				printf("\n");
				getchar();
				buscaRegistro(nroRegistro);
				break;

			case 5: // busca um campo de um determinado registro (posições lógicas em ambos)
				printf("Campo: ");
				fscanf(stdin, "%d", &nroCampo);
				getchar();
				printf("Registro: ");
				fscanf(stdin, "%d", &nroRegistro);
				printf("\n");
				getchar();
				buscaCampo(nroCampo, nroRegistro);
				break;	

			case 6: // clear na tela do terminal
				 printf("\e[H\e[2J");
				break;	

			case 7: // apaga arquivos
				remove("RegBin_metodo1.dat");
				remove("RegBin_metodo2.dat");
				remove("regQtd.dat");
				regQtd = 0;
				break;	

			case 8: // só mostra mensagem de encerramento
				printf("Programa encerrado...\n");
				break;		
		}
	} while (op != 8);	
	
	return 0;
}
