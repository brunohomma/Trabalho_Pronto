#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <registro1.h>
#include <buscafiltrada.h>

// imprime o registro com a palavra-chave detectada
void printRegistro(char *registro, int reg_pos) {
	int campo = 1;
	int p = 0;
	char aux;

	printf("---------------------------------Registro %d---------------------------------\n", reg_pos);
	while (campo < 9) {
		switch(campo) {
			case 1:
				printf("\nCNPJ: ");
				while (registro[p] != '\0') {
					printf("%c", registro[p]);
					p++;
				}
				printf("\n");
				break;
			case 2:
				printf("Nome Social: ");
				while (registro[p] != '\0') {
					printf("%c", registro[p]);
					p++;
				}
				printf("\n");
				break;
			case 3:
				printf("Nome Fantasma: ");
				while (registro[p] != '\0') {
					printf("%c", registro[p]);
					p++;
				}
				printf("\n");
				break;
			case 4:
				printf("Data de Registro: ");
				while (registro[p] != '\0') {
					printf("%c", registro[p]);
					p++;
				}
				printf("\n");
				break;
			case 5:
				printf("Data de Cancelamento: ");
				while (registro[p] != '\0') {
					printf("%c", registro[p]);
					p++;
				}
				printf("\n");
				break;
			case 6:
				printf("Motivo do Cancelamento: ");
				while (registro[p] != '\0') {
					printf("%c", registro[p]);
					p++;
				}
				printf("\n");
				break;
			case 7:
				printf("Nome da Empresa: ");
				while (registro[p] != '\0') {
					printf("%c", registro[p]);
					p++;
				}
				printf("\n");
				break;
			case 8:
				printf("CNPJ do Auditor: ");
				while (registro[p] != '\0') {
					printf("%c", registro[p]);
					p++;
				}
				printf("\n\n");
				break;
		}

		if (registro[p] == '\0') {
			campo++;
			p++;
			if (registro[p] == '|') p++;
		}	
	}
	printf("-----------------------------------------------------------------------------\n");

}

// busca por palavras-chaves dentro de um determinado campo
void buscaPor(char *registro, int size, char *chave, int campo, int reg_pos) {
	int p = 0; // somente usado para auxiliar no preenchimento da string palavraChave
	int inicial, final, tam; // para definir o tamanho da string palavraChave
	char *palavraChave; // armazena a string do mesmo campo para cada registro
	char *aux; // auxiliar que se não tiver nulo, é porque achou a string chave contida na string palavraChave

	// Verifica qual campo deve ser verificado para cada registro
	if (campo > 1) {
		inicial = pos[campo-2]+1;
		if (registro[inicial] == '|') inicial += 1;
		final = pos[campo-1]+1;
		tam = final-inicial;
		palavraChave = (char *)malloc(sizeof(char)*tam);
		for (int i = inicial; i < final; i++) palavraChave[p++] = registro[i];
	}
	
	// procura a sub-string chave na string palavraChave
	aux = strstr(palavraChave, chave);

	if (aux != NULL) {
		printRegistro(registro, reg_pos); // imprime o registro caso encontre a sub-string
	} 
}

// Carrega um registro na memória
char *registros(FILE *stream, int *s) {
	int reg_size, p = 0, i;
	char *registro;
	pos = (int *)malloc(sizeof(int)*8); // armazena as posições dos '\0' que estão na string registro

	// armazena o tamanho do registro
	fread(&reg_size, sizeof(int), 1, stream);
	if (feof(stream)) { // caso não tenha mais nada a ser lido
		(*s) = 0;
		return NULL;
	}

	// armazena um registro do arquivo binário nnuma string
	registro = (char *)malloc(sizeof(char)*reg_size);
	for (i = 0; i < reg_size; i++) {
		fread(&registro[i], sizeof(char), 1, stream);
		if (registro[i] == '\0' && registro[i-1] != '\0') { // registro[i-1] != '\0' (correção de bugs com campos com mais de um '\0')
			pos[p] = i; //vai armazenando as posições do '\0'
			p++;
		}	
	}

	(*s) = reg_size; // retorna o tamanho do registro

	return registro; // retorna a string que está armazenada o registro	
}

// busca registros por filtro
void buscaFiltrada(FILE *stream, int filtro, char *chave) {
	char *registro;
	int reg_size;
	int reg_pos = 1;

	do {
		registro = registros(stream, &reg_size); // carrega um registro na memória
		
		if (reg_size) { // se o registro existir

			// verifica qual tipo de filtro e busca por palavra-chave
			if (filtro == 1) { 
				buscaPor(registro, reg_size, chave, 1, reg_pos);
			}
			
			else if (filtro == 2) {
				buscaPor(registro, reg_size, chave, 2, reg_pos);
			}
			
			else if (filtro == 3) {
				buscaPor(registro, reg_size, chave, 3, reg_pos);
			}
			 
			else if (filtro == 4) {
				buscaPor(registro, reg_size, chave, 4, reg_pos);
			}
			
			else if (filtro == 5) {
				buscaPor(registro, reg_size, chave, 5, reg_pos);
			}
			
			else if (filtro == 6) {
				buscaPor(registro, reg_size, chave, 6, reg_pos);
			}
			
			else if (filtro == 7) {
				buscaPor(registro, reg_size, chave, 7, reg_pos);
			}
			
			else if (filtro == 8) {
				buscaPor(registro, reg_size, chave, 8, reg_pos);
			}

			else printf("Não existe buscas para esse filtro!\n");

			if (registro != NULL) {
				free(registro); // libera o registro atual para carregar o próximo registro na memória
				free(pos); // libera o vetor auxiliar que ajuda na busca por palavras chave
			}
		}
		
		reg_pos++; // mostra em qual resgistro está
	} while(reg_size);	// enquanto tiver registros não vázios no arquivo binário.		
}
