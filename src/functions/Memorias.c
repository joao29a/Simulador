#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/Memorias.h"
#include "../hdr/FuncTexto.h"

int PCData=0;
MemoriaData *DataMemory;
MemoriaCode MainMemory[TAM_MEM];

void IniciarMemoriaCode(MemoriaCode *memory){
     int i;
     for (i=0;i<TAM_MEM;i++){
         memory[i].opcode=0;
         memory[i].destino=0;
         memory[i].operando1=malloc(sizeof(char)*TAM_LINHA_MAX);
         memory[i].operando2=malloc(sizeof(char)*TAM_LINHA_MAX);
     }
}

void CarregarMemoriaCode(MemoriaCode *memory, int endereco, int opcode, int dest, char *orig1, char *orig2){
	memory[endereco].opcode=opcode;
     	memory[endereco].destino=dest;
     	strcpy(memory[endereco].operando1,orig1);
	strcpy(memory[endereco].operando2,orig2);
}

void IniciarMemoriaData(){
	DataMemory=NULL;
}

void CarregarMemoriaData(char *rotulo, char *tipo, char *dado){
	int tamanho=strlen(rotulo);
	rotulo[tamanho-1]='\0';
	if (strcmp(tipo,".int")==0){
		if (DataMemory==NULL){
			DataMemory=malloc(sizeof(MemoriaData));
			DataMemory->pos=PCData;
			DataMemory->rotulo=malloc(sizeof(char)*tamanho);
			strcpy(DataMemory->rotulo,rotulo);
			DataMemory->inteiro=atoi(dado);
			DataMemory->tipo='i';
			DataMemory->prox=NULL;
		}
		else{
			MemoriaData *aux;
			aux=DataMemory;
			while (aux->prox!=NULL)
				aux=aux->prox;
			aux->prox=malloc(sizeof(MemoriaData));
			aux=aux->prox;
			aux->pos=PCData;
			aux->rotulo=malloc(sizeof(char)*tamanho);
			strcpy(aux->rotulo,rotulo);
			aux->inteiro=atoi(dado);
			aux->tipo='i';
			aux->prox=NULL;
		}
	}
	PCData++;
}

int ProcurarRotuloMemoriaData(char *origem){
	MemoriaData *aux;
	aux=DataMemory;
	while (strcmp(aux->rotulo,origem)!=0)
		aux=aux->prox;
	return aux->pos;
}

int ProcurarValorMemoriaData(int pos){
	MemoriaData *aux;
	aux=DataMemory;
	while (aux->pos!=pos)
		aux=aux->prox;
	return aux->inteiro;
}
