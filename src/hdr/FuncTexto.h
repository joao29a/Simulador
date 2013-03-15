#ifndef FUNCTEXTO_H
#define FUNCTEXTO_H

#include "Memorias.h"
#include "Rotulos.h"

#define TAM_LINHA_MAX 20

int LeituraArquivo(FILE *Arquivo, MemoriaCode *MainMemory);

int lerLinha(FILE *Arquivo, char *palavra, char *opcode, char *dest, char *orig1, char *orig2);

void selecionarRotulos(FILE *Arquvo, Rotulos **rot);

void removerLinha(char *palavra, int pos);

void resetarBuffer(char *buffer);

#endif
