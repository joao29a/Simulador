#ifndef FUNCTEXTO_H
#define FUNCTEXTO_H

#include "Memorias.h"
#include "Rotulos.h"

#define TAM_LINHA_MAX 255

extern int PCRotulos;

void LeituraMemoriaData(FILE *Arquivo);

void lerLinhaData(char *palavra);

void LeituraMemoriaCode(FILE *Arquivo, MemoriaCode *MainMemory, int PC);

int lerLinhaCode(char *palavra, char *opcode, char *dest, char *orig1, char *orig2);

void selecionarRotulos(FILE *Arquvo);

void removerLinha(char *palavra, int pos);

void resetarBuffer(char *buffer);

#endif
