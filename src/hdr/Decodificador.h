#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H

int decOpcode(char *opcode);

char* reverseOpcode(int opcode);

int decDestino(char *dest);

int decOperando(char *orig);

#endif
