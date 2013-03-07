#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas/Interface.h"
#include "Estruturas/Memorias.h"
#include "Estruturas/Registradores.h"
#include "Estruturas/Rotulos.h"

#define TAM_LINHA_MAX 30
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

void ExecutarInst(MemoriaCode *memory, int endereco){
	int op=memory[endereco].opcode;
	int posReg=memory[endereco].destino;
	int oper1=memory[endereco].operando1;
	int oper2=memory[endereco].operando2;
	registrador[posReg].inteiro=excInstrucao(op,oper1,oper2);
}

//decodifica opcode e joga valor no registrador
int excInstrucao(int op, int B, int C){
	int A;
	switch(op){
		case 0:
			//MOV
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
			//REST
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
			//SYS
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

//transforma a string dos operandos em um int para poder somar,sub...
int decOrig(char *orig){
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

//le uma linha do arquivo texto e identifica o opcode, dest...
void lerLinha(FILE *Arquivo, char *palavra, char *opcode, char *dest, char *orig1, char *orig2){
	int i, k=0, parte=0;
	for (i=0;i<=strlen(palavra);i++){
		if (palavra[i]!=' ' && parte==0)
			opcode[k++]=palavra[i];
		else if (palavra[i]!=',' && parte==1)
			dest[k++]=palavra[i];
		else if (palavra[i]!=',' && parte==2) 
			orig1[k++]=palavra[i];
		else if (parte==3)
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

//remove \n do vetor de caracteres
void removerLinha(char *palavra, int pos){
	if (palavra[pos]=='\n'){
		palavra[pos+1]=' ';
		palavra[pos]='\0';
	}
}

//le o arquivo todo
void LeituraArquivo(FILE *Arquivo){
	char palavra[TAM_LINHA_MAX];
	while (fgets(palavra,TAM_LINHA_MAX,Arquivo)!=NULL){
		char opcode[TAM_LINHA_MAX],dest[TAM_LINHA_MAX],
		     orig1[TAM_LINHA_MAX],orig2[TAM_LINHA_MAX];
		removerLinha(palavra,strlen(palavra)-1);
		lerLinha(Arquivo,palavra,opcode,dest,orig1,orig2);
		CarregarMemoriaCode(MainMemory,PC,decOpcode(opcode),decRegistrador(dest),decOrig(orig1),decOrig(orig2));
		ExecutarInst(MainMemory,PC);
		PC++;
	}     
}

//inicia simulador
int main(){
	IniciarMemoriaCode(MainMemory);
	atribuirLetrasReg(registrador);
	FILE *Arquivo=fopen("assembly.txt","r");
	if (Arquivo!=NULL){
		LeituraArquivo(Arquivo);
		MostraMemoriaCode(MainMemory);
		mostraRegistradores(registrador);
	}
	else{
		printf("Arquivo nao encontrado");
	}	
	return 0;
}
