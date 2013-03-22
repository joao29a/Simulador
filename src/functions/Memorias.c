#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/Memorias.h"
#include "../hdr/FuncTexto.h"

MemoriaData *DataMemory;
MemoriaCode MainMemory[TAM_MEM];

void IniciarMemoriaCode(MemoriaCode *memory){
     int i;
     for (i=0;i<TAM_MEM;i++){
         memory[i].opcode=0;
         memory[i].destino=0;
         memory[i].operando1=malloc(sizeof(char)*TAM_LINHA_MAX);
         memory[i].operando2=malloc(sizeof(char)*TAM_LINHA_MAX);
     }
}

void CarregarMemoriaCode(MemoriaCode *memory, int endereco, int opcode, int dest, char *orig1, char *orig2){
	memory[endereco].opcode=opcode;
     	memory[endereco].destino=dest;
     	strcpy(memory[endereco].operando1,orig1);
	strcpy(memory[endereco].operando2,orig2);
}

void IniciarMemoriaData(){
	DataMemory=NULL;
}
