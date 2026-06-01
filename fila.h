#ifndef FILA_H
#define FILA_H
#include "estruturas.h"

void inicializarFila(Fila *f);
void enfileirar(Fila *f, char nome[50]);
void desenfileirar(Fila *f);
void mostrarFila(Fila *f);
void liberarFila(Fila *f);

#endif
