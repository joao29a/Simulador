#include <stdlib.h>
#include <stdio.h>
#include "../hdr/Interface.h"
#include "../hdr/Memorias.h"
#include "../hdr/Registradores.h"

     
void MostraMemoria(){
     	printf("####### Memoria #######\n");
	MostraDataMemory();
	MostraMainMemory();	
}

void MostraDataMemory(){
	MemoriaData *aux;
	aux=DataMemory;
	while (aux!=NULL){
		if (aux->tipo=='s'){
			if (aux->string=='\n')
				printf("%03d - \\n\n",aux->pos);
			else if (aux->string=='\t')
				printf("%03d - \\t\n",aux->pos);
			else
				printf("%03d - %c\n",aux->pos,aux->string);
		}
		else
			printf("%03d - %d\n",aux->pos,aux->numero);
		aux=aux->prox;
	}
}

void MostraMainMemory(){
	int i=0;
	while (MainMemory[i].state!='F'){
         	printf("%03d - %d%d%s%s\n",i+PCData,MainMemory[i].opcode,MainMemory[i].destino,MainMemory[i].operando1,
				MainMemory[i].operando2);
		i++;
	}
}

void MostraRegistradores(){
     	printf("###### Registradores ######\n");
	int i;
	for (i=0;i<QTD_REG;i++)
		printf("%s: %d\n",registrador[i].reg,registrador[i].numero);
}
