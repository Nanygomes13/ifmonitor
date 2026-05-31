#ifndef FILA_H
#define FILA_H

typedef struct nofila {
    char nome[50];
    struct nofila *ant;
    struct nofila *prox;
} noFila;

typedef struct fila {
    noFila *inicio;
    noFila *fim;
} Fila;

void inicializarFila(Fila *f);
void enfileirar(Fila *f, char nome[50]);
void desenfileirar(Fila *f);
void mostrarFila(Fila *f);
void liberarFila(Fila *f);

#endif
