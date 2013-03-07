#include <stdlib.h>
#include <stdio.h>
#include "Interface.h"
#include "Memorias.h"
#include "Registradores.h"

void MostraMemoriaCode(MemoriaCode memory[]){
     int i;
     printf("Memoria:\n");
     for (i=0;i<TAM_MEM;i++)
         printf("%3d - %d%d%d%d\n",i,memory[i].opcode,memory[i].destino,memory[i].operando1,memory[i].operando2);
     printf("\n");
}

void mostraRegistradores(Registradores reg[]){
	int i;
	for (i=0;i<QTD_REG;i++){
		if (reg[i].string!=NULL)
			printf("%s: %s\n",reg[i].reg,reg[i].string);
		else
			printf("%s: %d\n",reg[i].reg,reg[i].inteiro);
		
	}
}
