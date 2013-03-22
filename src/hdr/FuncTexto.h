#ifndef FUNCTEXTO_H
#define FUNCTEXTO_H

#include "Memorias.h"
#include "Rotulos.h"

#define TAM_LINHA_MAX 20

extern int PCRotulos;

void LeituraArquivo(FILE *Arquivo, MemoriaCode *MainMemory, int PC);

int lerLinha(char *palavra, char *opcode, char *dest, char *orig1, char *orig2);

void selecionarRotulos(FILE *Arquvo);

void removerLinha(char *palavra, int pos);

void resetarBuffer(char *buffer);

#endif
