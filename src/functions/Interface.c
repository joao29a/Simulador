#include <stdlib.h>
#include <stdio.h>
#include "../hdr/Interface.h"
#include "../hdr/Memorias.h"
#include "../hdr/Registradores.h"

     
void MostraMemoria(){
	MemoriaData *aux;
	aux=DataMemory;
     	printf("Memoria:\n");
	while (aux!=NULL){
		printf("%03d - %d\n",aux->pos,aux->inteiro);
		aux=aux->prox;
	}
	int i;
     	for (i=0;i<TAM_MEM;i++)
         	printf("%03d - %d%d%s%s\n",i+PCData,MainMemory[i].opcode,MainMemory[i].destino,MainMemory[i].operando1,
				MainMemory[i].operando2);
     	printf("\n");
}

void MostraRegistradores(Registradores reg[]){
	int i;
	for (i=0;i<QTD_REG;i++){
		if (reg[i].string!=NULL)
			printf("%s: %s\n",reg[i].reg,reg[i].string);
		else
			printf("%s: %d\n",reg[i].reg,reg[i].inteiro);
		
	}
}
