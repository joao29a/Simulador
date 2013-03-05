#include <stdio.h>
#include "Memorias.h"

void IniciarMemoriaCode(MemoriaCode *memory){
     int i;
     for (i=0;i<TAM_MEM;i++){
         memory[i].opcode=0;
         memory[i].destino=0;
         memory[i].operando1=0;
         memory[i].operando2=0;
     }
}

//carrega instruções do txt que ja foram convertidas para int para a memoria
void CarregarMemoriaCode(MemoriaCode *memory, int endereco, int opcode, int dest, int orig1, int orig2){
	memory[endereco].opcode=opcode;
     	memory[endereco].destino=dest;
     	memory[endereco].operando1=orig1;
     	memory[endereco].operando2=orig2;
}
