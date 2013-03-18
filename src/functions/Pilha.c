#include <stdio.h>
#include <stdlib.h>
#include "../hdr/Pilha.h"
#include "../hdr/Registradores.h"

Pilha *Stack;

void IniciarPilha(){
	Stack=NULL;
}

void Empilhar(int valor){
	if (Stack==NULL){
		Stack=malloc(sizeof(Pilha));
		Stack->num=valor;
		Stack->prox=NULL;
	}
	else{
		Pilha *temp=malloc(sizeof(Pilha));
		temp->num=valor;
		temp->prox=Stack;
		Stack=temp;
	}
}

int Desempilhar(){
	Pilha *temp;
	temp=Stack;
	Stack=Stack->prox;
	int valor=temp->num;
	free(temp);
	return valor;
}
