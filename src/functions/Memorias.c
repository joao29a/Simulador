#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/Memorias.h"
#include "../hdr/FuncTexto.h"

int PCData=0;
MemoriaData *DataMemory;
MemoriaCode MainMemory[TAM_MEM];

void IniciarMemoriaCode(){
	int i;
	for (i=0;i<TAM_MEM;i++){
		MainMemory[i].opcode=0;
		MainMemory[i].destino=0;
		MainMemory[i].operando1=malloc(sizeof(char)*TAM_LINHA_MAX);
		MainMemory[i].operando2=malloc(sizeof(char)*TAM_LINHA_MAX);
		MainMemory[i].state='F';
	}
}

void CarregarMemoriaCode(MemoriaCode *memory, int endereco, int opcode, int dest, char *orig1, char *orig2){
	memory[endereco].opcode=opcode;
	memory[endereco].destino=dest;
	strcpy(memory[endereco].operando1,orig1);
	strcpy(memory[endereco].operando2,orig2);
	memory[endereco].state='B';
}

void IniciarMemoriaData(){
	DataMemory=NULL;
}

void alocarDataMemory(char tipo, char *dado, char *rotulo, char dadoChar, int tamanho){
	if (DataMemory==NULL){
		DataMemory=malloc(sizeof(MemoriaData));
		DataMemory->pos=PCData;
		DataMemory->rotulo=malloc(sizeof(char)*tamanho);
		strcpy(DataMemory->rotulo,rotulo);
		if (tipo=='i')
			DataMemory->numero=atoi(dado);
		else
			DataMemory->string=dadoChar;
		DataMemory->tipo=tipo;
		DataMemory->prox=NULL;
	} else {
		MemoriaData *aux;
		aux=DataMemory;
		while (aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=malloc(sizeof(MemoriaData));
		aux=aux->prox;
		aux->pos=PCData;
		aux->rotulo=malloc(sizeof(char)*tamanho);
		strcpy(aux->rotulo,rotulo);
		if (tipo=='i')
			aux->numero=atoi(dado);
		else
			aux->string=dadoChar;
		aux->tipo=tipo;
		aux->prox=NULL;
	}
	PCData++;
}

void CarregarMemoriaData(char *rotulo, char *tipo, char *dado){
	int tamanho=strlen(rotulo);
	rotulo[tamanho-1]='\0';
	if (strcmp(tipo,".int")==0)
		alocarDataMemory('i',dado,rotulo,dado[0],tamanho);
	else if (strcmp(tipo,".ascii")==0){
		int tamanhoDado=strlen(dado);
		int i;
		for (i=1;i<tamanhoDado-1;i++){
			if (dado[i]=='\\'){
				int j=i+1;
				if (dado[j]=='n')
					dado[i]='\n';
				else if (dado[j]=='t')
					dado[i]='\t';
				alocarDataMemory('s',dado,rotulo,dado[i],tamanho);
				i++;
			}
			else
				alocarDataMemory('s',dado,rotulo,dado[i],tamanho);
		}
	}
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
	return aux->numero;
}

void ArmazenarValorMemoriaData(int pos, int valor){
	MemoriaData *aux;
	aux=DataMemory;
	while (aux->pos!=pos)
		aux=aux->prox;
	aux->numero=valor;
}
