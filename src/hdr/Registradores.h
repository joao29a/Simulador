#ifndef REGISTRADORES_H
#define REGISTRADORES_H

#define QTD_REG 26

extern char *TabelaRegistradores[];

typedef struct Registradores{
	char *reg;
	int numero;
}Registradores;

extern Registradores registrador[QTD_REG];

void atribuirLetrasReg();

#endif
