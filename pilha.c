#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void inicializarPilha(Pilha *p){
    p->topo = NULL;
}

void push(Pilha *p, char nomeAluno[50]){
    noPilha *novo;
    novo = (noPilha*) malloc(sizeof(noPilha));
    if(novo == NULL){
        printf("Erro de memória.\n");
        return;
    }
    strcpy(novo->nomeAluno, nomeAluno);
    novo->prox = p->topo;
    p->topo = novo;
    printf("%s entrou na pilha.\n", nomeAluno);
}

void pop(Pilha *p){
    if(p->topo == NULL){
        printf("Historico vazio.\n");
        return;
    }
    noPilha *temp;
    temp = p->topo;
    printf("%s foi chamado.\n", temp->nomeAluno);
    p->topo = p->topo->prox;
    free(temp);
}

void mostrarhistorico(Pilha *p){
    if(p->topo == NULL){
        printf("Historico vazio.\n");
        return;
    }
    noPilha *aux;
    aux = p->topo;
    printf("Historico de Atendimentos: ");
    while(aux != NULL){
        printf("%s ", aux->nomeAluno);
        aux = aux->prox;
    }
    printf("\n");
}

void liberarPilha(Pilha *p) {
    noPilha *aux;
    while(p->topo != NULL) {
        aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }
}
