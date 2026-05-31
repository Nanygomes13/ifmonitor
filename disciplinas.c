#include "disciplinas.h"
#include <stdio.h>
#include <string.h>

Disciplina disciplinas[MAX_DISCIPLINAS];
int quantidadeDisciplinas = 0;

void inicializarDisciplinas(void) {
    quantidadeDisciplinas = 0;
}

int adicionarDisciplina(char nome[100], int id) {
    if(quantidadeDisciplinas >= MAX_DISCIPLINAS) {
        printf("Limite maximo de disciplinas atingido!\n");
        return 0;
    }
    
    if(buscarDisciplinaPorId(id) != NULL) {
        printf("Erro: Ja existe uma disciplina com o ID %d.\n", id);
        return 0;
    }

    disciplinas[quantidadeDisciplinas].id = id;
    strncpy(disciplinas[quantidadeDisciplinas].nome, nome, 99);
    disciplinas[quantidadeDisciplinas].nome[99] = '\0';
    
    quantidadeDisciplinas++;
    printf("Disciplina '%s' cadastrada com sucesso (ID: %d).\n", nome, id);
    return 1;
}

void listarDisciplinas(void) {
    if(quantidadeDisciplinas == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }
    
    printf("\n--- Lista de Disciplinas ---\n");
    for(int i = 0; i < quantidadeDisciplinas; i++) {
        printf("ID: %d | Nome: %s\n", disciplinas[i].id, disciplinas[i].nome);
    }
    printf("----------------------------\n");
}

Disciplina* buscarDisciplinaPorId(int id) {
    for(int i = 0; i < quantidadeDisciplinas; i++) {
        if(disciplinas[i].id == id) {
            return &disciplinas[i];
        }
    }
    return NULL;
}

int getQuantidadeDisciplinas(void) {
    return quantidadeDisciplinas;
}
