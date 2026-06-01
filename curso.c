#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.h"
#include "disciplina.h"

Curso* buscarCursoPorId(Curso *topo, int id) {
    Curso *aux = topo;
    while(aux != NULL) {
        if(aux->id == id) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void cadastrarCurso(Curso **topo) {
    int id;
    char nome[50];

    printf("\n--- CADASTRAR CURSO ---\n");
    printf("Digite o ID do Curso: ");
    if (scanf("%d", &id) != 1) {
        printf("ID invalido.\n");
        getchar();
        return;
    }
    getchar(); // limpar buffer

    if(buscarCursoPorId(*topo, id) != NULL) {
        printf("Erro: Ja existe um curso cadastrado com o ID %d.\n", id);
        return;
    }

    printf("Digite o Nome do Curso: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // remover newline

    Curso *novo = (Curso*) malloc(sizeof(Curso));
    if(novo == NULL) {
        printf("Erro ao alocar memoria para o curso.\n");
        return;
    }

    novo->id = id;
    strcpy(novo->nome, nome);
    novo->prox = *topo;
    *topo = novo;

    printf("Curso '%s' (ID: %d) cadastrado com sucesso!\n", nome, id);
}

void listarCursos(Curso *topo) {
    if(topo == NULL) {
        printf("Nenhum curso cadastrado.\n");
        return;
    }
    printf("\n=== LISTA DE CURSOS ===\n");
    Curso *aux = topo;
    while(aux != NULL) {
        printf("ID: %d | Nome: %s\n", aux->id, aux->nome);
        aux = aux->prox;
    }
}

void removerCurso(Curso **topo, int id, Disciplina *listaDisciplinas) {
    Disciplina *d_aux = listaDisciplinas;
    while(d_aux != NULL) {
        if(d_aux->id_curso == id) {
            printf("Erro: Nao e possivel remover o curso. A disciplina '%s' (ID: %d) esta vinculada a ele.\n", d_aux->nome, d_aux->id);
            return;
        }
        d_aux = d_aux->prox;
    }

    Curso *atual = *topo;
    Curso *anterior = NULL;

    while(atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL) {
        printf("Curso com ID %d nao encontrado.\n", id);
        return;
    }

    if(anterior == NULL) {
        *topo = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    printf("Curso '%s' (ID: %d) removido com sucesso.\n", atual->nome, atual->id);
    free(atual);
}

void liberarCursos(Curso *topo) {
    Curso *aux;
    while(topo != NULL) {
        aux = topo;
        topo = topo->prox;
        free(aux);
    }
}
