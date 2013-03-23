#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdr/FuncTexto.h"
#include "hdr/Registradores.h"
#include "hdr/Memorias.h"
#include "hdr/Interface.h"
#include "hdr/Rotulos.h"
#include "hdr/Decodificador.h"
#include "hdr/Opcode.h"
#include "hdr/Pilha.h"

int PC=0;

void ExecutaInstrucao(int op, int dest, int B, int C){
	switch(op){
		case 0:
			registrador[dest].inteiro=B;
			break;
		case 1:
			registrador[dest].inteiro=ProcurarValorMemoriaData(B);
			break;
		case 2:
			ArmazenarValorMemoriaData(dest,B);
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
			Empilhar(registrador[dest].inteiro);
			break;
		case 14:
			registrador[dest].inteiro=Desempilhar();
			break;
		case 15:
			Empilhar(PC);
			PC=dest-1;
			break;
		case 16:
			switch(B){
				case 1:
					scanf("%d",&registrador[dest].inteiro);
					break;
				case 2:
					if (MainMemory[PC].address=='R')
						printf("%d\n",registrador[dest].inteiro);
					else{
						MemoriaData *aux;
						aux=DataMemory;
						while (aux->pos!=dest)
							aux=aux->prox;
						MemoriaData *buffer;
						buffer=aux;
						while (aux!=NULL && (strcmp(aux->rotulo,buffer->rotulo)==0)){
							printf("%c",aux->string);
							aux=aux->prox;
						}
					}							
					break;
			}
			break;
		case 17:
			PC=Desempilhar();
			break;
		case 18:
			PC=-1;
			printf("Program finished, press enter to continue...\n");
			while (getchar()!='\r' && getchar()!='\n');
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
	for (PC=0;PC<TamanhoPrograma;PC++){
		BuscaInstrucao(MainMemory,PC);
		if (PC==-1)
			break;
	}
	if (PC!=-1)
		printf("ERROR! SEGMENTATION FAULT!\n\n");
	free(Stack);
	free(TabelaRotulos);
}

void inserirPrograma(char *programa){
	//char *programa=(char*)malloc(255*sizeof(char));
	//printf("\nProgram's name: ");
	//scanf("%s",programa);
	FILE *Arquivo=fopen(programa,"r");
	if (Arquivo!=NULL){
		LeituraMemoriaData(Arquivo);
		int pos=ftell(Arquivo);
		selecionarRotulos(Arquivo);
		fseek(Arquivo,pos,SEEK_SET);
		LeituraMemoriaCode(Arquivo,MainMemory,PC);
		PC=PCRotulos;
		MostraMemoria();
		IniciarExecucao(PC);
		//MostraMemoria();
	}
	else
		printf("File not found!\n");
}

int main(int argc, char *argv[]){
	if (argc > 1){
		IniciarMemoriaData();
		IniciarMemoriaCode(MainMemory);
		IniciarPilha();
		atribuirLetrasReg(registrador);
		iniciarTabelaRotulo();
		inserirPrograma(argv[1]);
		free(DataMemory);
	} else
		printf("There is no program to execute!\n");
	return 0;
}
