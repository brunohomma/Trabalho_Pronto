#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <registro1.h>
#include <buscafiltrada.h>

//--------------------------------------------- Parte 2 feita por Leonardo------------------------------------------------//
// Keith ou Valeska, testem a parte do leonardo no seus notebooks e me digam se funcionou, caso não funcione utilize minha parte
void lerRegistroBinario(FILE *stream){
	int i, fieldSize = 0, regSize; // cria uma variavel para armazenar o tamanho do registro, e o contador do tamanho de campos.
	char c;	// cria uma variavel para armazenar o byte lido no arquivo.

	// lê o tamanho do registro, contido nos 4 primeiros bytes do arquivo.
	fread(&regSize, sizeof(int), 1, stream);

	char CNPJ[19];	// cria a variavel CNPJ, que tem tamanho fixo de 19 caracteres.
	fread(&CNPJ[0], sizeof(char), sizeof(CNPJ), stream);	// realiza a leitura do CNPJ.
	for(i = 0; i < sizeof(CNPJ); i++) printf("%c", CNPJ[i]);	// imprime na tela o CNPJ e um \n logo após.
	printf("\n");
	
	// varre o arquivo procurando por um delimitador de campo '|' e ao mesmo tempo incrementa um contador.
	while(c != '|'){
		fread(&c, sizeof(char), 1, stream);
		fieldSize++;
	}
	fseek(stream, fieldSize*-1, SEEK_CUR);	// assim que acha o '|', volta fieldSize vezes no arquivo.

	char nomeSocial[fieldSize-1];	// cria a variavel para armazenar o Nome Social.
	fread(&nomeSocial[0], sizeof(char), fieldSize-1, stream);	// faz a leitura do nome social.
	for(i = 0; i < fieldSize-1; i++) printf("%c", nomeSocial[i]);	// imprime na tela o nome social e um \n logo após.	printf("\n");
	printf("\n");
	fieldSize = 0;	// zera o contador de campos de tamanho variado.
	c = 0;	// atribui nulo para c.

	fseek(stream, 1, SEEK_CUR);	// pula o delimitador

	while(c != '|'){
		fread(&c, sizeof(char), 1, stream);
		fieldSize++;
	}
	fseek(stream, fieldSize*-1, SEEK_CUR);

	// APLICA A MESMA LOGICA AO NOME FANTASIA
	char nomeFantasia[fieldSize-1];
	fread(&nomeFantasia[0], sizeof(char), fieldSize-1, stream);
	for(i = 0; i < fieldSize-1; i++) printf("%c", nomeFantasia[i]);
	printf("\n");
	fieldSize = 0;
	c = 0;

	fseek(stream, 1, SEEK_CUR);	// pula o delimitador

	char dataRegistro[9];
	fread(&dataRegistro[0], sizeof(char), sizeof(dataRegistro), stream);
	for(i = 0; i < sizeof(dataRegistro); i++) printf("%c", dataRegistro[i]);
	printf("\n");
	
	
	char dataCancelamento[9];
	fread(&dataCancelamento[0], sizeof(char), sizeof(dataCancelamento), stream);
	for(i = 0; i < sizeof(dataCancelamento); i++) printf("%c", dataCancelamento[i]);
	printf("\n");
	

	while(c != '|'){
		fread(&c, sizeof(char), 1, stream);
		fieldSize++;
	}	
	fseek(stream, fieldSize*-1, SEEK_CUR);
	char motivoCancelamento[fieldSize-1];
	fread(&motivoCancelamento[0], sizeof(char), fieldSize-1, stream);
	for(i = 0; i < fieldSize-1; i++) printf("%c", motivoCancelamento[i]);
	printf("\n");
	fieldSize = 0;
	c = 0;


	fseek(stream, 1, SEEK_CUR);

	while(c != '|'){
		fread(&c, sizeof(char), 1, stream);
		fieldSize++;
	}
	fseek(stream, fieldSize*-1, SEEK_CUR);

	char nomeEmpresa[fieldSize-1];
	fread(&nomeEmpresa[0], sizeof(char), sizeof(nomeEmpresa), stream);
	for(i = 0; i < fieldSize-1; i++) printf("%c", nomeEmpresa[i]);
	printf("\n");

	fseek(stream, 1, SEEK_CUR);

	char CNPJAuditor[19];
	fread(&CNPJAuditor[0], sizeof(char), sizeof(CNPJAuditor), stream);
	for(i = 0; i < 19; i++) printf("%c", CNPJAuditor[i]);
	printf("\n");
}


void lerArquivoBinario(){
	FILE *binaryFile = fopen("RegBin_metodo1.dat", "rb");

	char CNPJ[18], c;
	int regIndex = 1;
		
	if(binaryFile == NULL){
		printf("I could not read this file!\n");
		return;
	}else {
		while(regIndex < 199){
			printf("------------------- REGISTRO %d --------------------------\n", regIndex);
			lerRegistroBinario(binaryFile);
			printf("----------------------------------------------------------\n\n");
			regIndex++;
		}
		
	}
	
	fclose(binaryFile);
}
//----------------------------------------Fim da parte 2 Feita por Leonardo----------------------------------------//
//---------------------------------------------Parte 2 feita por Bruno--------------------------------------------//
/*void lerRegistroBinario(FILE *stream) {
	char *registro;
	int reg_size, reg_pos = 1;

	do {
		registro = registros(stream, &reg_size); // guarda o registro na memória
		if (registro != NULL) { // verifica se a memória não está vazia
			printRegistro(registro, reg_pos); // imprime os dados do registro
			reg_pos++; // incrementa a posição do registro
			free(registro); // libera o registro atual da memória
			free(pos); // libera um vetor auxiliar para imprimir os dados do registro
		}
	} while(reg_size); // enquanto ainda tiver registros com tamanho maior que zero para ler
}

// Lê todos os registros e os imprime
void lerArquivoBinario(){
	FILE *binaryFile = fopen("RegBin_metodo1.dat", "rb");

	char CNPJ[18], c;
	int regIndex = 1;
		
	if(binaryFile == NULL){
		printf("I could not read this file!\n");
		return;
	}else {
			lerRegistroBinario(binaryFile);
	}
	
	fclose(binaryFile);
}*/
//--------------------------------------- Fim da parte 2 Feita por Bruno -----------------------------//

////////////////////////////// parte 5 e 6 ////////////////////////////
struct registro * devolveRegistroBuscado(FILE *stream, int nroRegistro){
	int regSize, countReg=0, achou = 0;
	char c;
	struct registro *reg;
	char *CNPJ, *nomeSocial, *nomeFantasia, *dataRegistro, *dataCancelamento, *motivoCancelamento, *nomeEmpresa, *CNPJAuditor;
	CNPJ = NULL;
	nomeSocial = NULL;
	nomeFantasia = NULL;
	dataRegistro = NULL;
	dataCancelamento = NULL;
	motivoCancelamento = NULL;
	nomeEmpresa = NULL;
	CNPJAuditor = NULL;

	if (nroRegistro > regQtd) { // caso não encontre o registro escolhido 
		printf("Registro não encontrado...\n");
		return NULL;
	}

	//enquanto nao achou o registro dentro do arquivo binario
	while(!achou){
		if(countReg == nroRegistro-1){ //se o contador for igual ao numero do registro buscado entra no if
			achou = 1; //seta a flag para 1 para sair do while
			fread(&regSize, sizeof(int),1,stream); //le o tamanho do registro
			reg = (struct registro *) malloc(regSize); //aloca espaco na memoria para o registro
			
			//leitura do CNPJ
			CNPJ = (char *) calloc(19,sizeof(char));
			fread(CNPJ,sizeof(char),19,stream);
			
			int strSize=0;
			//leitura do nomeSocial
			fread(&c,sizeof(char),1,stream);
			while(c != '|'){
				nomeSocial = (char *) realloc(nomeSocial,sizeof(char)*(strSize+1));
				nomeSocial[strSize] = c;
				strSize++;
				fread(&c,sizeof(char),1,stream);
			}

			strSize = 0;
			//leitura nomeFantasia
			fread(&c,sizeof(char),1,stream);
			while(c != '|'){
				nomeFantasia = (char *) realloc(nomeFantasia,sizeof(char)*(strSize+1));
				nomeFantasia[strSize] = c;
				strSize++;
				fread(&c,sizeof(char),1,stream);
			}

			//leitura dataRegistro
			dataRegistro = (char *) calloc(9,sizeof(char));
			fread(dataRegistro,sizeof(char),9,stream);

			//leitura dataCancelamento
			dataCancelamento = (char *) calloc(9,sizeof(char));
			fread(dataCancelamento,sizeof(char),9,stream);

			strSize = 0;
			//leitura motivoCancelamento
			fread(&c,sizeof(char),1,stream);
			while(c != '|'){
				motivoCancelamento = (char *) realloc(motivoCancelamento,sizeof(char)*(strSize+1));
				motivoCancelamento[strSize] = c;
				strSize++;
				fread(&c,sizeof(char),1,stream);
			}

			strSize = 0;
			//leitura nomeEmpresa
			fread(&c,sizeof(char),1,stream);
			while(c != '|'){
				nomeEmpresa = (char *) realloc(nomeEmpresa,sizeof(char)*(strSize+1));
				nomeEmpresa[strSize] = c;
				strSize++;
				fread(&c,sizeof(char),1,stream);
			}

			//leitura CNPJAuditor
			CNPJAuditor = (char *) calloc(19,sizeof(char));
			fread(CNPJAuditor,sizeof(char),19,stream);

		}else{
			fread(&regSize, sizeof(int),1,stream);//le o tamanho do registro
			countReg++; //aumenta o contador de registros lidos
			fseek(stream,regSize,SEEK_CUR); //posiciona o arquivo no proximo registro
		}
	}

	reg->CNPJ = CNPJ;
	reg->nomeSocial = nomeSocial;
	reg->nomeFantasia = nomeFantasia;
	reg->dataRegistro = dataRegistro;
	reg->dataCancelamento = dataCancelamento;
	reg->motivoCancelamento = motivoCancelamento;
	reg->nomeEmpresa = nomeEmpresa;
	reg->CNPJAuditor = CNPJAuditor;
	return reg;
}

//Libera a memoria alocada para o registro
void freeReg(struct registro *reg){
	free(reg->CNPJ);
	free(reg->nomeSocial);
	free(reg->nomeFantasia);
	free(reg->dataRegistro);
	free(reg->dataCancelamento);
	free(reg->motivoCancelamento);
	free(reg->nomeEmpresa);
	free(reg->CNPJAuditor);
	free(reg);
}

//imprime os dados do registro buscado
void printaRegistroBuscado(struct registro *reg, int nroReg){
	printf("---------------------------------REGISTRO %d---------------------------------\n",nroReg);
	printf("CNPJ: %s\n",reg->CNPJ);
	printf("Nome Social: %s\n",reg->nomeSocial);
	printf("Nome Fantasia: %s\n",reg->nomeFantasia);
	printf("Data Registro: %s\n",reg->dataRegistro);
	printf("Data Cancelamento: %s\n",reg->dataCancelamento);
	printf("Motivo Cancelamento: %s\n",reg->motivoCancelamento);
	printf("Nome Empresa: %s\n",reg->nomeEmpresa);
	printf("CNPJ do Auditor: %s\n",reg->CNPJAuditor);
	printf("------------------------------------------------------------------------------\n");

}

//imprime campo passado por parametro do registro tambem passado por parametro
void printaCampoBuscado(struct registro *reg, int nroReg, int nroCampo){
	printf("----------------------------Registro %d | Campo %d----------------------------\n",nroReg,nroCampo);
	switch(nroCampo){
		case 1:
			printf("CNPJ: %s\n",reg->CNPJ);
			break;
		case 2:
			printf("Nome Social: %s\n",reg->nomeSocial);
			break;
		case 3:
			printf("Nome Fantasia: %s\n",reg->nomeFantasia);
			break;
		case 4:
			printf("Data Registro: %s\n",reg->dataRegistro);
			break;
		case 5:
			printf("Data de Cancelamento: %s\n",reg->dataCancelamento);
			break;
		case 6:
			printf("Motivo de Cancelamento: %s\n",reg->motivoCancelamento);
			break;	
		case 7:
			printf("Nome Empresa: %s\n", reg->nomeEmpresa);
			break;
		case 8:
			printf("CNPJ do Auditor: %s\n",reg->CNPJAuditor);
			break;

		default:
			printf("Não possui esse campo\n");
			break;	
	}
	printf("------------------------------------------------------------------------------\n");

}

// Busca o campo de um registro desejado
void buscaCampo(int nroCampo,int nroReg){
	FILE *binaryFile = fopen("RegBin_metodo1.dat", "rb");
	struct registro *reg = devolveRegistroBuscado(binaryFile,nroReg);
	if (reg == NULL) return;
	printaCampoBuscado(reg,nroReg,nroCampo);
	printf("\n");
	fclose(binaryFile);
	freeReg(reg);
}

// Busca o registro desejado
void buscaRegistro(int nroReg){
	FILE *binaryFile = fopen("RegBin_metodo1.dat", "rb");
	struct registro *reg = devolveRegistroBuscado(binaryFile,nroReg);
	if (reg == NULL) return; // caso não encontre o registro escolhido
	printaRegistroBuscado(reg,nroReg);
	printf("\n");
	fclose(binaryFile);
	freeReg(reg);
}
