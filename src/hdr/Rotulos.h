#ifndef ROTULOS_H
#define ROTULOS_H

typedef struct rotulos{
	char *rotulo;
	int pos;
	struct rotulos *prox;
}Rotulos;

extern Rotulos *TabelaRotulos;

void iniciarTabelaRotulo();

void armazenarRotulo(char *palavra, int PC);

int procurarRotulo(char *palavra);
#endif
