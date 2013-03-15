#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/FuncTexto.h"
#include "../hdr/Memorias.h"
#include "../hdr/Rotulos.h"
#include "../hdr/Decodificador.h"

int LeituraArquivo(FILE *Arquivo, MemoriaCode *MainMemory){
	char palavra[TAM_LINHA_MAX];
	int rotulo;
	int PC=0;
	while (fgets(palavra,TAM_LINHA_MAX,Arquivo)!=NULL){
		char opcode[TAM_LINHA_MAX],dest[TAM_LINHA_MAX],
		     orig1[TAM_LINHA_MAX],orig2[TAM_LINHA_MAX];
		resetarBuffer(opcode);
		resetarBuffer(dest);
		resetarBuffer(orig1);
		resetarBuffer(orig2);
		removerLinha(palavra,strlen(palavra)-1);
		rotulo=lerLinha(palavra,opcode,dest,orig1,orig2);
		if (rotulo==0){
			CarregarMemoriaCode(MainMemory,PC,decOpcode(opcode),decDestino(dest),
					orig1,orig2);
			PC++;
		}
	}
	return PC;
}

int lerLinha(char *palavra, char *opcode, char *dest, char *orig1, char *orig2){
	int i, k=0, parte=0, rotulo=1;
	if (palavra[0]=='\t'){
		rotulo=0;
		int tamanho=strlen(palavra);
		for (i=1;i<=tamanho;i++){
			if (palavra[i]!=' ' && parte==0)
				opcode[k++]=palavra[i];
			else if (palavra[i]!=',' && parte==1 && palavra[i]!='\0')
				dest[k++]=palavra[i];
			else if (palavra[i]!=',' && parte==2 && palavra[i]!='\0') 
				orig1[k++]=palavra[i];
			else if (parte==3 && palavra[i]!='\0')
				orig2[k++]=palavra[i];
			if (palavra[i]==' ' || palavra[i]=='\0' || palavra[i]==','){
				switch(parte){
					case 0:
						opcode[k]='\0';
						break;
					case 1:
						dest[k]='\0';
						break;
					case 2:
						orig1[k]='\0';
						break;
					case 3:
						orig2[k]='\0';
						break;
				}
				if (palavra[i]==',')
					i++;
				parte++;
				k=0;
			}
		}
	}
	return rotulo;
}

void selecionarRotulos(FILE *Arquivo, Rotulos **rot){
	char palavra[TAM_LINHA_MAX];
	int PC=0;
	while (fgets(palavra,TAM_LINHA_MAX,Arquivo)!=NULL){	
		removerLinha(palavra,strlen(palavra)-1);
		if (palavra[0]!='\t')
			armazenarRotulo(palavra,&*rot,PC);
		else
			PC++;
	}
}

void removerLinha(char *palavra, int pos){
	if (palavra[pos]=='\n'){
		palavra[pos+1]=' ';
		palavra[pos]='\0';
	}
}

void resetarBuffer(char *buffer){
	if (buffer[0]!='\0')
		buffer[0]='\0';
}