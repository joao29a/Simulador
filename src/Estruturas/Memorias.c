#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Memorias.h"

void IniciarMemoriaCode(MemoriaCode *memory){
     int i;
     for (i=0;i<TAM_MEM;i++){
         memory[i].opcode=0;
         memory[i].destino=0;
         memory[i].operando1=malloc(sizeof(char));
         memory[i].operando2=malloc(sizeof(char));
     }
}

//carrega instruções do txt que ja foram convertidas para int para a memoria
void CarregarMemoriaCode(MemoriaCode *memory, int endereco, int opcode, int dest, char *orig1, char *orig2){
	memory[endereco].opcode=opcode;
     	memory[endereco].destino=dest;
     	strcpy(memory[endereco].operando1,orig1);
	strcpy(memory[endereco].operando2,orig2);
}
