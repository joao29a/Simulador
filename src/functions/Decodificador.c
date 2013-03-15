#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../hdr/Registradores.h"
#include "../hdr/Rotulos.h"
#include "../hdr/Decodificador.h"
#include "../hdr/Opcode.h"

int decOpcode(char *opcode){
	int i;
	int valor=0;
	for (i=0;i<QTD_INSTRUCOES;i++)
		if (strcmp(opcode,TabelaOpcode[i])==0){
			valor=i;
			break;
		}
	return valor;
}

int decDestino(char *dest){
	int ascii=dest[0];
	int valor=0;
	if (ascii>=97 && ascii<=122)
		valor=procurarRotulo(dest,TabelaRotulos);	
	else {
		int i;
		for (i=0;i<QTD_REG;i++)
			if (strcmp(dest,TabelaRegistradores[i])==0){
				valor=i;
				break;
			}
	}
	return valor;
}

int decOperando(char *orig){
	int ascii=orig[0];
	int valor=0;
	if (ascii>=65 && ascii<=90){
		int i;
		for (i=0;i<QTD_REG;i++)
			if (strcmp(orig,registrador[i].reg)==0){
				valor=registrador[i].inteiro;
				break;
			}
	}
	else
		valor=atoi(orig);
	return valor;
}
