#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monitor.h"
#include "disciplina.h"

Monitor* buscarMonitorPorId(Monitor *topo, int id) {
    Monitor *aux = topo;
    while(aux != NULL) {
        if(aux->id == id) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void cadastrarMonitor(Monitor **topo, Disciplina *listaDisciplinas) {
    int id, id_disciplina;
    char nome[50];
    char horario[20];

    if (listaDisciplinas == NULL) {
        printf("\nErro: Nenhuma disciplina cadastrada. Cadastre uma disciplina primeiro!\n");
        return;
    }

    printf("\n--- CADASTRAR MONITOR ---\n");
    printf("Digite o ID do Monitor: ");
    if (scanf("%d", &id) != 1) {
        printf("ID invalido.\n");
        getchar();
        return;
    }
    getchar();

    if(buscarMonitorPorId(*topo, id) != NULL) {
        printf("Erro: Ja existe um monitor cadastrado com o ID %d.\n", id);
        return;
    }

    printf("Digite o Nome do Monitor: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite o ID da Disciplina vinculada: ");
    if (scanf("%d", &id_disciplina) != 1) {
        printf("ID invalido.\n");
        getchar();
        return;
    }
    getchar();

    Disciplina *disc = buscarDisciplinaPorId(listaDisciplinas, id_disciplina);
    if(disc == NULL) {
        printf("Erro: Disciplina com ID %d nao encontrada. Cadastro cancelado.\n", id_disciplina);
        return;
    }

    printf("Digite o Horario de Atendimento (ex: Seg 14h): ");
    fgets(horario, sizeof(horario), stdin);
    horario[strcspn(horario, "\n")] = '\0';

    Monitor *novo = (Monitor*) malloc(sizeof(Monitor));
    if(novo == NULL) {
        printf("Erro ao alocar memoria para o monitor.\n");
        return;
    }

    novo->id = id;
    strcpy(novo->nome, nome);
    novo->id_disciplina = id_disciplina;
    strcpy(novo->horario, horario);
    novo->prox = *topo;
    *topo = novo;

    printf("Monitor '%s' cadastrado na disciplina '%s' (%s) com sucesso!\n", nome, disc->nome, horario);
}

void listarMonitores(Monitor *topo, Disciplina *listaDisciplinas) {
    if(topo == NULL) {
        printf("Nenhum monitor cadastrado.\n");
        return;
    }
    printf("\n=== LISTA DE MONITORES ===\n");
    Monitor *aux = topo;
    while(aux != NULL) {
        Disciplina *d = buscarDisciplinaPorId(listaDisciplinas, aux->id_disciplina);
        printf("ID: %d | Nome: %s | Disciplina: %s (ID: %d) | Horario: %s\n", 
               aux->id, aux->nome, d ? d->nome : "Nao encontrada", aux->id_disciplina, aux->horario);
        aux = aux->prox;
    }
}

void removerMonitor(Monitor **topo, int id) {
    Monitor *atual = *topo;
    Monitor *anterior = NULL;

    while(atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL) {
        printf("Monitor com ID %d nao encontrado.\n", id);
        return;
    }

    if(anterior == NULL) {
        *topo = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    printf("Monitor '%s' (ID: %d) removido com sucesso.\n", atual->nome, atual->id);
    free(atual);
}

void liberarMonitores(Monitor *topo) {
    Monitor *aux;
    while(topo != NULL) {
        aux = topo;
        topo = topo->prox;
        free(aux);
    }
}
