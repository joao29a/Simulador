#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdr/FuncTexto.h"
#include "hdr/Interface.h"
#include "hdr/Memorias.h"
#include "hdr/Registradores.h"
#include "hdr/Rotulos.h"
#include "hdr/Decodificador.h"
#include "hdr/Opcode.h"

int PC=0;

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

void IniciarExecucao(int TamanhoPrograma){
	for (PC=0;PC<=TamanhoPrograma;PC++){
		BuscaInstrucao(MainMemory,PC);
		if (PC==-1)
			break;
	}
}

void inserirPrograma(){
	char *programa=(char*)malloc(255*sizeof(char));
	printf("Nome do programa: ");
	scanf("%s",programa);
	FILE *Arquivo=fopen(programa,"r");
	if (Arquivo!=NULL){
		selecionarRotulos(Arquivo,&TabelaRotulos);
		rewind(Arquivo);
		PC=LeituraArquivo(Arquivo,MainMemory);
		//MostraMemoriaCode(MainMemory);
		IniciarExecucao(PC-1);	
		//mostraRegistradores(registrador);
	}
	else
		printf("Arquivo nao encontrado\n");
}

int main(){
	IniciarMemoriaCode(MainMemory);
	atribuirLetrasReg(registrador);
	iniciarTabelaRotulo(&TabelaRotulos);
	inserirPrograma();	
	return 0;
}
