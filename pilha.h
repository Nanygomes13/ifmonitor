#ifndef PILHA_H
#define PILHA_H

typedef struct nopilha {
    char nomeAluno[50];
    struct nopilha *prox;
} noPilha;

typedef struct pilha {
    noPilha *topo;
} Pilha;

void inicializarPilha(Pilha *p);
void push(Pilha *p, char nomeAluno[50]);
void pop(Pilha *p);
void mostrarhistorico(Pilha *p);
void liberarPilha(Pilha *p);

#endif
