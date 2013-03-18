#ifndef PILHA_H_GUARD
#define PILHA_H_GUARD
typedef struct stack{
        int num;
        struct stack *prox;
}Pilha;

extern Pilha *Stack;

void IniciarPilha();

void Empilhar(int valor);

int Desempilhar();

#endif
