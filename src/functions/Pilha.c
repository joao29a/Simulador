#include <stdio.h>
#include <stdlib.h>
#include "../hdr/Pilha.h"

Pilha *Stack;

void Empilhar(Pilha **stack, int valor){
     Pilha *stackAux;
     
     stackAux=(*stack);
     
     if (stackAux==NULL){
        stackAux=malloc(sizeof(Pilha));
        stackAux->ant=NULL;
        stackAux->num=valor;
        stackAux->prox=NULL;
     }
     else{
          stackAux->prox=malloc(sizeof(Pilha));
          Pilha *temp;
          temp=stackAux;
          stackAux=stackAux->prox;
          stackAux->ant=temp;
          stackAux->num=valor;
          stackAux->prox=NULL;
     }
     (*stack)=stackAux;
}

int Desempilhar(Pilha **stack){
     Pilha *stackAux;
     stackAux=(*stack);
     (*stack)=(*stack)->ant;
     if ((*stack)!=NULL)
        (*stack)->prox=NULL;
     int elemento=stackAux->num;
     free(stackAux);
     return elemento;
}
