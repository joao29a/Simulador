#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas/FuncTexto.h"
#include "Estruturas/Interface.h"
#include "Estruturas/Memorias.h"
#include "Estruturas/Registradores.h"
#include "Estruturas/Rotulos.h"

#define QTD_INSTRUCOES 19

char *TabelaOpcode[]={"MOV","LD","ST","ADD","SUB","MUL","DIV","REST","DIVR",
	"JUMP","JUMPN","JUMPP","JUMPZ","PUSH","POP","CALL","SYS","RET","EXIT"};

char *TabelaRegistradores[]={"A","B","C","D","E","F","G","H","I","J","K","L",
	"M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

MemoriaCode MainMemory[TAM_MEM];
Registradores registrador[QTD_REG];
Rotulos *TabelaRotulos;
int PC=0;

void atribuirLetrasReg(Registradores *reg){
	int i;
	for (i=0;i<QTD_REG;i++)
		reg[i].reg=TabelaRegistradores[i];
}

void ExecutaInstrucao(int op, int dest, int B, int C){
	switch(op){
		case 0:
			registrador[dest].inteiro=B;
			break;
		case 1:
			//LD
			break;
		case 2:
			//ST
			break;
		case 3:
			registrador[dest].inteiro=B+C;
			break;
		case 4:
			registrador[dest].inteiro=B-C;
			break;
		case 5:
			registrador[dest].inteiro=B*C;
			break;
		case 6:
			registrador[dest].inteiro=B/C;
			break;
		case 7:
			registrador[dest].inteiro=B%C;
			break;
		case 8:
			//DIVR
			break;
		case 9:
			PC=dest-1;
			break;
		case 10:
			if (B<0)
				PC=dest-1;
			break;
		case 11:
			if (B>0)
				PC=dest-1;
			break;
		case 12:
			if (B==0)
				PC=dest-1;
			break;
		case 13:
			//PUSH
			break;
		case 14:
			//POP
			break;
		case 15:
			//CALL
			break;
		case 16:
			switch(B){
				case 1:
					scanf("%d",&registrador[dest].inteiro);
					break;
				case 2:
					printf("%d\n",registrador[dest].inteiro);
					break;
			}
			break;
		case 17:
			//RET
			break;
		case 18:
			PC=-1;
			printf("Programa encerrado...\n");
			break;
	}
}

void BuscaInstrucao(MemoriaCode *memory, int endereco){
	int op=memory[endereco].opcode;
	int dest=memory[endereco].destino;
	int oper1=decOperando(memory[endereco].operando1);
	int oper2=decOperando(memory[endereco].operando2);
	ExecutaInstrucao(op,dest,oper1,oper2);
}

int decOpcode(char *opcode){
	int i;
	for (i=0;i<QTD_INSTRUCOES;i++)
		if (strcmp(opcode,TabelaOpcode[i])==0)
			return i;
}

int decDestino(char *dest){
	int ascii=dest[0];
	if (ascii>=97 && ascii<=122)
		return procurarRotulo(dest,TabelaRotulos);	
	else {
		int i;
		for (i=0;i<QTD_REG;i++)
			if (strcmp(dest,TabelaRegistradores[i])==0)
				return i;
	}
}

int decOperando(char *orig){
	int ascii=orig[0];
	int valor=0;
	if (ascii>=65 && ascii<=90){
		int i;
		for (i=0;i<QTD_REG;i++)
			if (strcmp(orig,registrador[i].reg)==0)
				return registrador[i].inteiro;
	}
	else
		return atoi(orig);
}

void IniciarExecucao(int TamanhoPrograma){
	for (PC=0;PC<=TamanhoPrograma;PC++){
		BuscaInstrucao(MainMemory,PC);
		if (PC==-1)
			break;
	}
}

int main(){
	IniciarMemoriaCode(MainMemory);
	atribuirLetrasReg(registrador);
	iniciarTabelaRotulo(&TabelaRotulos);	
	FILE *Arquivo=fopen("maiorElemento.txt","r");
	if (Arquivo!=NULL){
		PC=LeituraArquivo(Arquivo,MainMemory,&TabelaRotulos);
		//MostraMemoriaCode(MainMemory);
		IniciarExecucao(PC-1);	
		//mostraRegistradores(registrador);
	}
	else
		printf("Arquivo nao encontrado");	
	return 0;
}
