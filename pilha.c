#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializarPilha(Pilha *p) {
    p->topo = NULL;
}

void push(Pilha *p, char nomeAluno[50]) {
    noPilha *novo;
    
    novo = (noPilha*) malloc(sizeof(noPilha));

    if(novo == NULL) {
        printf("Erro de memória.\n");
        return;
    }

    strncpy(novo->nomeAluno, nomeAluno, 49);
    novo->nomeAluno[49] = '\0';
    
    novo->prox = p->topo;
    p->topo = novo;
}

void pop(Pilha *p) {
    if(p->topo == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    noPilha *temp;
    
    temp = p->topo;

    printf("Acao desfeita: %s\n", temp->nomeAluno);

    p->topo = p->topo->prox;

    free(temp);
}

void mostrarhistorico(Pilha *p) {
    if(p->topo == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    noPilha *aux;
    
    aux = p->topo;

    printf("\n--- Historico de Acoes (Mais recente no topo) ---\n");
    int contador = 1;
    while(aux != NULL) {
        printf("%d. %s\n", contador++, aux->nomeAluno);
        aux = aux->prox;
    }
    printf("-------------------------------------------------\n");
}

void liberarPilha(Pilha *p) {
    noPilha *aux;
    noPilha *temp;
    
    aux = p->topo;
    
    while(aux != NULL) {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
    
    p->topo = NULL;
}
