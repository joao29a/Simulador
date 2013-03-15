#ifndef ROTULOS_H
#define ROTULOS_H

typedef struct rotulos{
	char *rotulo;
	int pos;
	struct rotulos *prox;
}Rotulos;

void iniciarTabelaRotulo(Rotulos **rot);

void armazenarRotulo(char *palavra, Rotulos **rot, int PC);

int procurarRotulo(char *palavra, Rotulos *rot);
#endif
