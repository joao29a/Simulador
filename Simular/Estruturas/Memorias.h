#ifndef MEMORIAS_H
#define MEMORIAS_H

#define TAM_MEM 256

typedef struct MemoriaCode{
        int opcode;
        int destino;
        int operando1;
        int operando2;
        
}MemoriaCode;

void IniciarMemoriaCode(MemoriaCode *memory);

void CarregarMemoriaCode(MemoriaCode *memory, int endereco, int opcode, int dest, int orig1, int orig2);
#endif
