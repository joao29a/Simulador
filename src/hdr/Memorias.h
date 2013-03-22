#ifndef MEMORIAS_H
#define MEMORIAS_H

#define TAM_MEM 256

typedef struct MemoriaData{
	int pos;
	int inteiro;
	char *rotulo;
	char caractere;
	char tipo;
	struct MemoriaData *prox;
}MemoriaData;

extern MemoriaData *DataMemory;

extern int PCData;

void IniciarMemoriaData();

void CarregarMemoriaData(char *rotulo, char *tipo, char *dado);

int ProcurarRotuloMemoriaData(char *origem);

int ProcurarValorMemoriaData(int pos);

typedef struct MemoriaCode{
        int opcode;
        int destino;
        char *operando1;
        char *operando2;
        
}MemoriaCode;

extern MemoriaCode MainMemory[TAM_MEM];

void IniciarMemoriaCode(MemoriaCode *memory);

void CarregarMemoriaCode(MemoriaCode *memory, int endereco, int opcode, int dest, char *orig1, char *orig2);

#endif
