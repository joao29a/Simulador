#ifndef FUNCTEXTO_H
#define FUNCTEXTO_H

#include "Memorias.h"
#include "Rotulos.h"

#define TAM_LINHA_MAX 20

int LeituraArquivo(FILE *Arquivo, MemoriaCode *MainMemory, Rotulos **rot);

int lerLinha(FILE *Arquivo, char *palavra, char *opcode, char *dest, char *orig1, char *orig2, Rotulos **rot, int PC);

void selecionarRotulos(FILE *Arquvo, Rotulos **rot, int PC);

void removerLinha(char *palavra, int pos);

void resetarBuffer(char *buffer);

#endif
