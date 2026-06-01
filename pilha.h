#ifndef PILHA_H
#define PILHA_H
#include "estruturas.h"

void inicializarPilha(Pilha *p);
void push(Pilha *p, char nomeAluno[50]);
void pop(Pilha *p);
void mostrarhistorico(Pilha *p);
void liberarPilha(Pilha *p);

#endif
