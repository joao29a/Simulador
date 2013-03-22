#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/Rotulos.h"

Rotulos *TabelaRotulos;

void iniciarTabelaRotulo(){
	TabelaRotulos=NULL;
}

void armazenarRotulo(char *palavra, int PC){
	Rotulos *aux;
	int tamanho=strlen(palavra);
	palavra[tamanho-1]='\0';
	aux=TabelaRotulos;
	if (aux==NULL){
		aux=malloc(sizeof(Rotulos));
		aux->rotulo=malloc(sizeof(char)*tamanho);
		strcpy(aux->rotulo,palavra);
		aux->pos=PC;
		aux->prox=NULL;
		TabelaRotulos=aux;
	}
	else{
		while (aux->prox!=NULL){
			aux=aux->prox;
		}
		aux->prox=malloc(sizeof(Rotulos));
		aux=aux->prox;
		aux->rotulo=malloc(sizeof(char)*tamanho);
		strcpy(aux->rotulo,palavra);
		aux->pos=PC;
		aux->prox=NULL;
	}
}

int procurarRotulo(char *palavra){
	Rotulos *aux;
	aux=TabelaRotulos;
	while (strcmp(aux->rotulo,palavra)!=0)
		aux=aux->prox;
	return aux->pos;
}
