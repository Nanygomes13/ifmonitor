#ifndef DISCIPLINAS_H
#define DISCIPLINAS_H

#define MAX_DISCIPLINAS 100

typedef struct disciplina {
    int id;
    char nome[100];
} Disciplina;

void inicializarDisciplinas(void);
int adicionarDisciplina(char nome[100], int id);
void listarDisciplinas(void);
Disciplina* buscarDisciplinaPorId(int id);
int getQuantidadeDisciplinas(void);

#endif
