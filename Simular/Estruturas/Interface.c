#include <stdlib.h>
#include <stdio.h>
#include "Interface.h"
#include "Memorias.h"

void MostraMemoriaCode(MemoriaCode *memory){
     int i;
     printf("Memoria:\n");
     for (i=0;i<TAM_MEM;i++)
         printf("%3d - %d%d%d%d\n",i,memory[i].opcode,memory[i].destino,memory[i].operando1,memory[i].operando2);
     printf("\n");
}
