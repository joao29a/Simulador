#ifndef FUNCTEXTO_H
#define FUNCTEXTO_H

#include "Memorias.h"

#define TAM_LINHA_MAX 20

int LeituraArquivo(FILE *Arquivo, MemoriaCode *MainMemory);

void lerLinha(FILE *Arquivo, char *palavra, char *opcode, char *dest, char *orig1, char *orig2);

void removerLinha(char *palavra, int pos);

void resetarBuffer(char *buffer);

#endif
