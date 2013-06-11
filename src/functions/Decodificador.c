#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../hdr/Registradores.h"
#include "../hdr/Rotulos.h"
#include "../hdr/Decodificador.h"
#include "../hdr/Opcode.h"
#include "../hdr/Pilha.h"

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

char* reverseOpcode(int opcode){
	return TabelaOpcode[opcode];
}

int decDestino(char *dest){
	int ascii=dest[0];
	int valor=0;
	if ((ascii>=97 && ascii<=122) || ascii==64)
		valor=procurarRotulo(dest);	
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
	int tamanho=strlen(orig);
	int ascii=orig[0];
	int valor=0;
	if (tamanho>=2 && orig[tamanho-1]=='P'){
		int pos=0;
		char numero[tamanho-1];
		while (pos<tamanho-1){
			numero[pos]=orig[pos];
			pos++;
		}
		pos=atoi(numero);
		Pilha *temp;
		temp=Stack;
		int i;
		for (i=0;i<pos;i++)
			temp=temp->prox;
		valor=temp->num;
	}
	else if (ascii>=65 && ascii<=90){
		int i;
		for (i=0;i<QTD_REG;i++)
			if (strcmp(orig,registrador[i].reg)==0){
				valor=registrador[i].numero;
				break;
			}
	}
	else
		valor=atoi(orig);
	return valor;
}
