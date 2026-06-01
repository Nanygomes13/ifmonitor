#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplina.h"
#include "curso.h"
#include "monitor.h"

Disciplina* buscarDisciplinaPorId(Disciplina *topo, int id) {
    Disciplina *aux = topo;
    while(aux != NULL) {
        if(aux->id == id) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void cadastrarDisciplina(Disciplina **topo, Curso *listaCursos) {
    int id, id_curso;
    char nome[50];

    if (listaCursos == NULL) {
        printf("\nErro: Nenhum curso cadastrado. Cadastre um curso primeiro!\n");
        return;
    }

    printf("\n--- CADASTRAR DISCIPLINA ---\n");
    printf("Digite o ID da Disciplina: ");
    if (scanf("%d", &id) != 1) {
        printf("ID invalido.\n");
        getchar();
        return;
    }
    getchar();

    if(buscarDisciplinaPorId(*topo, id) != NULL) {
        printf("Erro: Ja existe uma disciplina cadastrada com o ID %d.\n", id);
        return;
    }

    printf("Digite o Nome da Disciplina: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite o ID do Curso vinculado: ");
    if (scanf("%d", &id_curso) != 1) {
        printf("ID invalido.\n");
        getchar();
        return;
    }
    getchar();

    Curso *curso = buscarCursoPorId(listaCursos, id_curso);
    if(curso == NULL) {
        printf("Erro: Curso com ID %d nao encontrado. Cadastro cancelado.\n", id_curso);
        return;
    }

    Disciplina *nova = (Disciplina*) malloc(sizeof(Disciplina));
    if(nova == NULL) {
        printf("Erro ao alocar memoria para a disciplina.\n");
        return;
    }

    nova->id = id;
    strcpy(nova->nome, nome);
    nova->id_curso = id_curso;
    nova->prox = *topo;
    *topo = nova;

    printf("Disciplina '%s' vinculada ao curso '%s' com sucesso!\n", nome, curso->nome);
}

void listarDisciplinas(Disciplina *topo, Curso *listaCursos) {
    if(topo == NULL) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }
    printf("\n=== LISTA DE DISCIPLINAS ===\n");
    Disciplina *aux = topo;
    while(aux != NULL) {
        Curso *c = buscarCursoPorId(listaCursos, aux->id_curso);
        printf("ID: %d | Nome: %s | Curso: %s (ID: %d)\n", 
               aux->id, aux->nome, c ? c->nome : "Nao encontrado", aux->id_curso);
        aux = aux->prox;
    }
}

void removerDisciplina(Disciplina **topo, int id, Monitor *listaMonitores) {
    Monitor *m_aux = listaMonitores;
    while(m_aux != NULL) {
        if(m_aux->id_disciplina == id) {
            printf("Erro: Nao e possivel remover a disciplina. O monitor '%s' (ID: %d) esta vinculado a ela.\n", m_aux->nome, m_aux->id);
            return;
        }
        m_aux = m_aux->prox;
    }

    Disciplina *atual = *topo;
    Disciplina *anterior = NULL;

    while(atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL) {
        printf("Disciplina com ID %d nao encontrada.\n", id);
        return;
    }

    if(anterior == NULL) {
        *topo = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    printf("Disciplina '%s' (ID: %d) removida com sucesso.\n", atual->nome, atual->id);
    free(atual);
}

void liberarDisciplinas(Disciplina *topo) {
    Disciplina *aux;
    while(topo != NULL) {
        aux = topo;
        topo = topo->prox;
        free(aux);
    }
}
