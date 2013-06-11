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
			registrador[dest].numero=B;
			break;
		case 1:
			registrador[dest].numero=ProcurarValorMemoriaData(B);
			break;
		case 2:
			ArmazenarValorMemoriaData(dest,B);
			break;
		case 3:
			registrador[dest].numero=B+C;
			break;
		case 4:
			registrador[dest].numero=B-C;
			break;
		case 5:
			registrador[dest].numero=B*C;
			break;
		case 6:
			registrador[dest].numero=B/C;
			break;
		case 7:
			registrador[dest].numero=B%C;
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
			Empilhar(registrador[dest].numero);
			break;
		case 14:
			registrador[dest].numero=Desempilhar();
			break;
		case 15:
			Empilhar(PC);
			PC=dest-1;
			break;
		case 16:
			switch(B){
				case 1:{
					char buffer[50];
					fgets(buffer,50,stdin);
					registrador[dest].numero=atoi(buffer);
					break;
				}
				case 2:
					if (MainMemory[PC].address=='R')
						printf("%d\n",registrador[dest].numero);
					else{
						MemoriaData *aux;
						aux=DataMemory;
						while (aux->pos!=dest)
							aux=aux->prox;
						if (aux->tipo=='i'){
							MemoriaData *buffer;
							buffer=aux;
							while (aux!=NULL && (strcmp(aux->rotulo,buffer->rotulo)==0)){
								printf("%d\n",aux->numero);
								aux=aux->prox;
							}
						}
					}
					break;
				case 3:{
					       MemoriaData *aux;
					       aux=DataMemory;
					       while (aux->pos!=dest)
						       aux=aux->prox;
					       if (aux->tipo=='s'){
						       MemoriaData *buffer;
						       buffer=aux;
						       while (aux!=NULL && (strcmp(aux->rotulo,buffer->rotulo)==0)){
							       printf("%c",aux->string);
							       aux=aux->prox;
						       }
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
			printf("Simulação finalizada.\n");
			//while (getchar()!='\r' && getchar()!='\n');
			break;
	}
}

void BuscaInstrucao(MemoriaCode *memory, int endereco, char tipo){
	int op=memory[endereco].opcode;
	int dest=memory[endereco].destino;
	int oper1=decOperando(memory[endereco].operando1);
	int oper2=decOperando(memory[endereco].operando2);
	if (tipo=='s'){
		printf("\nPC: %d\n",PC);
		printf("Instrução: %d%d%s%s\n",memory[endereco].opcode,memory[endereco].destino,
			memory[endereco].operando1,memory[endereco].operando2);
		printf("Opcode: %s\n",reverseOpcode(op));
		while (getchar()!='\n' && getchar()!='\r');
	}
	ExecutaInstrucao(op,dest,oper1,oper2);
}

void IniciarExecucao(int TamanhoPrograma, char tipo){
	printf("###### Simulacao ######\n");
	for (PC=0;PC<TamanhoPrograma;PC++){
		BuscaInstrucao(MainMemory,PC,tipo);
		if (PC==-1)
			break;
	}
	free(Stack);
	free(TabelaRotulos);
}

void inserirPrograma(int argc, char *argv[]){
	FILE *Arquivo=fopen(argv[1],"r");
	if (Arquivo!=NULL){
		LeituraMemoriaData(Arquivo);
		int pos=ftell(Arquivo);
		selecionarRotulos(Arquivo);
		fseek(Arquivo,pos,SEEK_SET);
		LeituraMemoriaCode(Arquivo,MainMemory,PC);
		PC=PCRotulos;
		int i=2;
		while (i<argc){
			if (strcmp(argv[i],"-m")==0)
				MostraMemoria();
			else if (strcmp(argv[i],"-md")==0){
				printf("###### Memoria de Dados ######\n");
				MostraDataMemory();
			}
			else if (strcmp(argv[i],"-mc")==0){
				printf("###### Memoria de Instrucoes ######\n");
				MostraMainMemory();
			}
			else if (strcmp(argv[i],"-e")==0)
				IniciarExecucao(PC,'a');
			else if (strcmp(argv[i],"-es")==0)
				IniciarExecucao(PC,'s');
			else if (strcmp(argv[i],"-r")==0)
				MostraRegistradores();
			i++;
		}
	}
	else
		printf("Arquivo não encontrado!\n");
}

int main(int argc, char *argv[]){
	if (argc > 1){
		IniciarMemoriaData();
		IniciarMemoriaCode();
		IniciarPilha();
		atribuirLetrasReg();
		iniciarTabelaRotulo();
		inserirPrograma(argc,argv);
		free(DataMemory);
	} else
		printf("Não há programa para ser simulado!\n");
	return 0;
}
