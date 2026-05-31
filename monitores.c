#include "monitores.h"
#include "disciplinas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Monitor *inicioMonitores = NULL;

void inicializarMonitores(void) {
    inicioMonitores = NULL;
}

int adicionarMonitor(char nome[100], int id, int id_disciplina) {
    if (buscarMonitorPorId(id) != NULL) {
        printf("Erro: Ja existe um monitor com o ID %d.\n", id);
        return 0;
    }

    Monitor *novo = (Monitor*) malloc(sizeof(Monitor));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria para monitor.\n");
        return 0;
    }

    novo->id = id;
    novo->id_disciplina = id_disciplina;
    strncpy(novo->nome, nome, 99);
    novo->nome[99] = '\0';
    novo->prox = NULL;
    
    inicializarFila(&(novo->filaEspera));

    if (inicioMonitores == NULL) {
        inicioMonitores = novo;
    } else {
        Monitor *aux = inicioMonitores;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    printf("Monitor '%s' cadastrado com sucesso (ID: %d).\n", nome, id);
    return 1;
}

void listarMonitores(void) {
    if (inicioMonitores == NULL) {
        printf("Nenhum monitor cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Monitores ---\n");
    Monitor *aux = inicioMonitores;
    while (aux != NULL) {
        Disciplina *d = buscarDisciplinaPorId(aux->id_disciplina);
        char nomeDisciplina[100] = "Desconhecida";
        if (d != NULL) {
            strcpy(nomeDisciplina, d->nome);
        }
        printf("ID: %d | Nome: %s | Disciplina: %s\n", aux->id, aux->nome, nomeDisciplina);
        aux = aux->prox;
    }
    printf("--------------------------\n");
}

Monitor* buscarMonitorPorId(int id) {
    Monitor *aux = inicioMonitores;
    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void liberarMonitores(void) {
    Monitor *aux = inicioMonitores;
    while (aux != NULL) {
        Monitor *temp = aux;
        aux = aux->prox;
        liberarFila(&(temp->filaEspera));
        free(temp);
    }
    inicioMonitores = NULL;
}
