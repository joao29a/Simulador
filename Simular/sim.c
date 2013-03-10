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
int PC=0;

void atribuirLetrasReg(Registradores *reg){
	int i;
	for (i=0;i<QTD_REG;i++)
		reg[i].reg=TabelaRegistradores[i];
}

void BuscaInstrucao(MemoriaCode *memory, int endereco){
	int op=memory[endereco].opcode;
	int posReg=memory[endereco].destino;
	int oper1=decOperando(memory[endereco].operando1);
	int oper2=decOperando(memory[endereco].operando2);
	registrador[posReg].inteiro=ExecutaInstrucao(op,posReg,oper1,oper2);
}

int ExecutaInstrucao(int op, int dest, int B, int C){
	int A;
	switch(op){
		case 0:
			A=B;
			break;
		case 1:
			//LD
			break;
		case 2:
			//ST
			break;
		case 3:
			A=B+C;
			break;
		case 4:
			A=B-C;
			break;
		case 5:
			A=B*C;
			break;
		case 6:
			A=B/C;
			break;
		case 7:
			A=B%C;
			break;
		case 8:
			//DIVR
			break;
		case 9:
			//JUMP
			break;
		case 10:
			//JUMPN
			break;
		case 11:
			//JUMPP
			break;
		case 12:
			//JUMPZ
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
					scanf("%d",&A);
					printf("%d\n",A);
					break;
				case 2:
					printf("%d\n",registrador[dest].inteiro);
					A=registrador[dest].inteiro;	
					break;
			}
			break;
		case 17:
			//RET
			break;
		case 18:
			//EXIT
			break;
	}
	return A;     
}

int decOpcode(char *opcode){
	int i;
	for (i=0;i<QTD_INSTRUCOES;i++)
		if (strcmp(opcode,TabelaOpcode[i])==0)
			return i;
}

int decRegistrador(char *dest){
	int i;
	for (i=0;i<QTD_REG;i++)
		if (strcmp(dest,TabelaRegistradores[i])==0)
			return i;
}

int decOperando(char *orig){
	int ascii=orig[0];
	int valor=0;
	if (ascii>=65 && ascii<=90){
		int i;
		for (i=0;i<QTD_REG;i++)
			if (strcmp(orig,registrador[i].reg)==0)
				valor=registrador[i].inteiro;
	}
	else {
		int i;
		int mult=1;
		int tamanho=strlen(orig);
		for (i=strlen(orig)-1;i>=0;i--){
			int temp=orig[i];
			temp=temp-48;
			temp*=mult;
			valor+=temp;
			mult*=10;
		}
	}

	return valor;
}

void IniciarExecucao(int TamanhoPrograma){
	for (PC=0;PC<=TamanhoPrograma;PC++)
		BuscaInstrucao(MainMemory,PC);
}

int main(){
	IniciarMemoriaCode(MainMemory);
	atribuirLetrasReg(registrador);
	FILE *Arquivo=fopen("assembly.txt","r");
	if (Arquivo!=NULL){
		PC=LeituraArquivo(Arquivo,MainMemory);
		MostraMemoriaCode(MainMemory);
		IniciarExecucao(PC-1);	
		mostraRegistradores(registrador);
	}
	else
		printf("Arquivo nao encontrado");	
	return 0;
}
