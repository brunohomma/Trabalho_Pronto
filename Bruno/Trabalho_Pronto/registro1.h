#ifndef _REGISTRO1_H_
#define _REGISTRO1_H_

// Estrutura que compõe os dados de um registro, isto é, cada variável representa um campo e a estrutura, o registro.
struct registro {
	char *CNPJ; // campo fixo (tamanho 19)
	char *nomeSocial; // campo variavel
	char *nomeFantasia; // campo variavel
	char *dataRegistro; // campo fixo (tamanho 9)
	char *dataCancelamento; // campo fixo (tamanho 9)
	char *motivoCancelamento; // campo variavel
	char *nomeEmpresa; // campo variavel
	char *CNPJAuditor; // campo fixo (tamanho 19)
};

typedef struct registro t_registro;
int regQtd; // armazena a quantidades de registros existentes no arquivo binário
int flag; // flag para indicar que o arquivo binário foi completamente lido

void importaRegistro_metodo1(FILE *stream);

#endif