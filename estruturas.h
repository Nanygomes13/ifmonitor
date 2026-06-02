#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct curso {
    int id;
    char nome[50];
    struct curso *prox;
} Curso;

typedef struct disciplina {
    int id;
    char nome[50];
    int id_curso;
    struct disciplina *prox;
} Disciplina;

typedef struct nofila {
    char nome[50];
    struct nofila *ant;
    struct nofila *prox;
} noFila;

typedef struct fila {
    noFila *inicio;
    noFila *fim;
} Fila;

typedef struct monitor {
    int id;
    char nome[50];
    int id_disciplina;
    char horario[20];
    Fila fila_espera;
    struct monitor *prox;
} Monitor;

typedef struct aluno {
    int matricula;
    char nome[50];
    int id_curso;
    struct aluno *prox;
} Aluno;



typedef struct nopilha {
    char nomeAluno[50];
    struct nopilha *prox;
} noPilha;

typedef struct pilha {
    noPilha *topo;
} Pilha;

#endif
