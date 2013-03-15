#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/Rotulos.h"

void iniciarTabelaRotulo(Rotulos **rot){
	(*rot)=NULL;
}

void armazenarRotulo(char *palavra, Rotulos **rot, int PC){
	Rotulos *aux;
	int tamanho=strlen(palavra);
	palavra[tamanho-1]='\0';
	aux=(*rot);
	if (aux==NULL){
		aux=malloc(sizeof(Rotulos));
		aux->rotulo=malloc(sizeof(char));
		strcpy(aux->rotulo,palavra);
		aux->pos=PC;
		aux->prox=NULL;
		(*rot)=aux;
	}
	else{
		while (aux->prox!=NULL){
			aux=aux->prox;
		}
		aux->prox=malloc(sizeof(Rotulos));
		aux=aux->prox;
		aux->rotulo=malloc(sizeof(char));
		strcpy(aux->rotulo,palavra);
		aux->pos=PC;
		aux->prox=NULL;
	}
}

int procurarRotulo(char *palavra, Rotulos *rot){
	Rotulos *aux;
	aux=rot;
	while (strcmp(aux->rotulo,palavra)!=0)
		aux=aux->prox;
	return aux->pos;
}
