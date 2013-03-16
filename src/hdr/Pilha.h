#ifndef PILHA_H_GUARD
#define PILHA_H_GUARD
typedef struct stack{
        struct stack *ant;
        int num;
        struct stack *prox;
}Pilha;

extern Pilha *Stack;

void Empilhar(Pilha **stack, int valor);

int Desempilhar(Pilha **stack);
#endif
