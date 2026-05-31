#include "fila.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void enfileirar(Fila *f, char nome[50]) {
    noFila *novo;
    
    novo = (noFila*) malloc(sizeof(noFila));

    if(novo == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    strncpy(novo->nome, nome, 49);
    novo->nome[49] = '\0';
    
    novo->ant = NULL;
    novo->prox = NULL;

    if(f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        novo->ant = f->fim;
        f->fim->prox = novo;
        f->fim = novo;
    }

    printf("%s entrou na fila.\n", nome);
}

void desenfileirar(Fila *f) {
    if(f->inicio == NULL) {
        printf("A fila está vazia.\n");
        return;
    }

    noFila *temp;
    
    temp = f->inicio;

    printf("%s foi chamado.\n", temp->nome);

    f->inicio = f->inicio->prox;

    if(f->inicio != NULL) {
        f->inicio->ant = NULL;
    } else {
        f->fim = NULL;
    }

    free(temp);
}

void mostrarFila(Fila *f) {
    if(f->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    noFila *aux;
    
    aux = f->inicio;

    printf("Fila de Espera: ");

    while(aux != NULL) {
        printf("%s ", aux->nome);
        aux = aux->prox;
    }
    printf("\n");
}

void liberarFila(Fila *f) {
    noFila *aux;
    noFila *temp;
    
    aux = f->inicio;
    
    while(aux != NULL) {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
    
    f->inicio = NULL;
    f->fim = NULL;
}
