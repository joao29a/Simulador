#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas/Interface.h"
#include "Estruturas/Memorias.h"
#include "Estruturas/Registradores.h"
#include "Estruturas/Rotulos.h"

#define TAM_LINHA_MAX 30

MemoriaCode MainMemory[TAM_MEM];
int PC=0;
int Registrador[REG];

//executa instrucao da memoria
void ExecutarInst(MemoriaCode *memory, int endereco){
     int op=memory[endereco].opcode;
     int posReg=memory[endereco].destino;
     int oper1=memory[endereco].operando1;
     int oper2=memory[endereco].operando2;
     
     Registrador[posReg]=excInstrucao(op,oper1,oper2);
}

//decodifica opcode e joga valor no registrador
int excInstrucao(int op, int B, int C){
     int A;
     switch(op){
         case 1:
              A=B+C;
              break;
         case 2:
              A=B-C;
              break;
         case 3:
              A=B*C;
              break;
         case 4:
              A=B/C;
              break;
     }
     return A;     
}

//transforma a string do opcode para um inteiro
int decOpcode(char *opcode){
    int op;
    
    if (strcmp("add",opcode)==0)
       op=1;
    else if (strcmp("sub",opcode)==0)
       op=2;
    else if (strcmp("mult",opcode)==0)
       op=3;
    else if (strcmp("div",opcode)==0)
       op=4;
    else if (strcmp("str",opcode)==0)
       op=5;
    else if (strcmp("load",opcode)==0)
       op=6;
    else if (strcmp("sys",opcode)==0)
       op=7;
    else if (strcmp("push",opcode)==0)
       op=8;
    else if (strcmp("pop",opcode)==0)
       op=9;
    else if (strcmp("move",opcode)==0)
       op=10;
    
    return op;
}

//verifica qual registrador sera utilizado
//transforma a string do registrador para um inteiro
int decReg(char *dest){
    int reg;
    
    if (strcmp("A",dest)==0)
       reg=0;
    else if (strcmp("B",dest)==0)
       reg=1;
    else if (strcmp("C",dest)==0)
       reg=2;
    else if (strcmp("D",dest)==0)
       reg=3;
    else if (strcmp("E",dest)==0)
       reg=4;
    else if (strcmp("F",dest)==0)
       reg=5;
    else if (strcmp("G",dest)==0)
       reg=6;
    else if (strcmp("H",dest)==0)
       reg=7;
    
    return reg;
    
}

//transforma a string dos operandos em um int para poder somar,sub...
int decOrig(char *orig){
    int i;
    int mult=1;
    int valor=0;
    int tamanho=strlen(orig);
    for (i=strlen(orig)-1;i>=0;i--){
        int temp=orig[i];
        temp=temp-48;
        temp*=mult;
        valor+=temp;
        mult*=10;
    }
    
    return valor;
}

//le uma linha do arquivo texto e identifica o opcode, dest...
void lerLinha(FILE *Arquivo, char *palavra, char *opcode, char *dest, char *orig1, char *orig2){
     int i, k=0, parte=0;
     for (i=0;i<=strlen(palavra);i++){
         if (palavra[i]!=' ' && parte==0)
            opcode[k++]=palavra[i];
         else if (palavra[i]!=' ' && parte==1)
            dest[k++]=palavra[i];
         else if (palavra[i]!=' ' && parte==2)
            orig1[k++]=palavra[i];
         else if (parte==3)
            orig2[k++]=palavra[i];
         if (palavra[i]==' ' || palavra[i]=='\0'){
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

//inicia registrador
void IniciarRegistradores(int *Reg){
     int i;
     for (i=0;i<=REG;i++)
         Reg[i]=0;    
}

//imprime valor dos registradores
void MostraRegistradores(int *Reg){
     int i;
     printf("Registradores:\n");
     for (i=0;i<=REG;i++){
         switch(i){
            case 0:
                 printf("A=%d\n",Reg[i]);
                 break;
            case 1:
                 printf("B=%d\n",Reg[i]);
                 break;
            case 2:
                 printf("C=%d\n",Reg[i]);
                 break;
            case 3:
                 printf("D=%d\n",Reg[i]);
                 break;
            case 4:
                 printf("E=%d\n",Reg[i]);
                 break;
            case 5:
                 printf("F=%d\n",Reg[i]);
                 break;
            case 6:
                 printf("G=%d\n",Reg[i]);
                 break;
            case 7:
                 printf("H=%d\n",Reg[i]);     
                 break;
         }
     }     
}

//inicia a leitura na memoria e executa programa
void ExecutaMemoria(int TamanhoPrograma){
     for (PC=0;PC<=TamanhoPrograma;PC++)
           ExecutarInst(MainMemory,PC);                     
}

//le o arquivo todo
void LeituraArquivo(FILE *Arquivo){
     char palavra[TAM_LINHA_MAX];
     while (fgets(palavra,TAM_LINHA_MAX,Arquivo)!=NULL){
          char opcode[TAM_LINHA_MAX],dest[TAM_LINHA_MAX],orig1[TAM_LINHA_MAX];
          char orig2[TAM_LINHA_MAX];
	  int tamanho=strlen(palavra);
          removerLinha(palavra,strlen(palavra)-1);
          lerLinha(Arquivo,palavra,opcode,dest,orig1,orig2);
          CarregarMemoriaCode(MainMemory,PC,decOpcode(opcode),decReg(dest),decOrig(orig1),decOrig(orig2));
          PC++;
       }     
}

//inicia simulador
int main(){
    IniciarMemoriaCode(MainMemory);
    IniciarRegistradores(Registrador);
    
    FILE *Arquivo=fopen("assembly.txt","r");
    if (Arquivo!=NULL){
       LeituraArquivo(Arquivo);
       MostraMemoriaCode(MainMemory);
       ExecutaMemoria(PC-1);
       MostraRegistradores(Registrador);
    }
    else{
         printf("Arquivo nao encontrado");
    }	
    return 0;
}
