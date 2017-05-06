#ifndef _BUSCAFILTRADA_H_
#define _BUSCAFILTRADA_H_ 

int *pos; // vetor que armazena as posições dos '\0' dos campos, pois o registro é guardado em uma única string
int filtroNaoEncontrado; // flag que indica se o filtro foi ou não encontrado

void printRegistro(char *, int);
char *registros(FILE *, int *);
void buscaFiltrada(FILE *, int, char *);

#endif