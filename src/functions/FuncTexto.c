#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/FuncTexto.h"
#include "../hdr/Memorias.h"
#include "../hdr/Rotulos.h"
#include "../hdr/Decodificador.h"

int PCRotulos=0;

void LeituraMemoriaData(FILE *Arquivo){
	char palavra[TAM_LINHA_MAX];
	while (fgets(palavra,TAM_LINHA_MAX,Arquivo)!=NULL){
		removerLinha(palavra,strlen(palavra)-1);
		if (strcmp(palavra,".code:")==0)
			break;
		lerLinhaData(palavra);
	}
}

void lerLinhaData(char *palavra){
	if (palavra[0]=='\t'){
		char rotulo[TAM_LINHA_MAX], tipo[TAM_LINHA_MAX], dado[TAM_LINHA_MAX];
		sscanf(palavra,"%s%s %[^\n]",rotulo,tipo,dado);
		CarregarMemoriaData(rotulo,tipo,dado);
	}
}

void LeituraMemoriaCode(FILE *Arquivo, MemoriaCode *MainMemory, int PC){
	char palavra[TAM_LINHA_MAX];
	int rotulo;
	while (fgets(palavra,TAM_LINHA_MAX,Arquivo)!=NULL){
		if (palavra[0]=='@')
			break;
		char opcode[TAM_LINHA_MAX],dest[TAM_LINHA_MAX],
		     orig1[TAM_LINHA_MAX],orig2[TAM_LINHA_MAX];
		resetarBuffer(opcode);
		resetarBuffer(dest);
		resetarBuffer(orig1);
		resetarBuffer(orig2);
		removerLinha(palavra,strlen(palavra)-1);
		rotulo=lerLinhaCode(palavra,opcode,dest,orig1,orig2);
		if (!rotulo){
			if (decOpcode(opcode)==2){
				int destino=ProcurarRotuloMemoriaData(dest);
				CarregarMemoriaCode(MainMemory,PC,decOpcode(opcode),destino,orig1,orig2);
			}
			else if (decOpcode(opcode)==16 && strlen(dest)>1){
				MainMemory[PC].address='M';
				int destino=ProcurarRotuloMemoriaData(dest);
				CarregarMemoriaCode(MainMemory,PC,decOpcode(opcode),destino,orig1,orig2);
			}
			else {
				if (decOpcode(opcode)==1){
					int origem=ProcurarRotuloMemoriaData(orig1);
					sprintf(orig1,"%d",origem);
				}
				else if (decOpcode(opcode)==16)
					MainMemory[PC].address='R';
				CarregarMemoriaCode(MainMemory,PC,decOpcode(opcode),decDestino(dest),orig1,orig2);
			}
			PC++;
		}
	}
}

int lerLinhaCode(char *palavra, char *opcode, char *dest, char *orig1, char *orig2){
	int rotulo=1;
	if (palavra[0]=='\t'){
		rotulo=0;
		sscanf(palavra,"%s %s %s %s",opcode,dest,orig1,orig2);
		sscanf(dest,"%[^,\n]",dest);
		sscanf(orig1,"%[^,\n]",orig1);
		sscanf(orig2,"%[^,\n]",orig2);
	}
	return rotulo;
}

void selecionarRotulos(FILE *Arquivo){
	char palavra[TAM_LINHA_MAX];
	while (fgets(palavra,TAM_LINHA_MAX,Arquivo)!=NULL){	
		removerLinha(palavra,strlen(palavra)-1);
		if (palavra[0]!='\t' && palavra[0]!='@')
			armazenarRotulo(palavra,PCRotulos);
		else if (palavra[0]=='@'){
			int PC=PCRotulos;
			armazenarRotulo(palavra,PC);
			int pos=ftell(Arquivo);
			selecionarRotulos(Arquivo);
			fseek(Arquivo,pos,SEEK_SET);
			LeituraMemoriaCode(Arquivo,MainMemory,PC);
			break;
		}
		else
			PCRotulos++;
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
