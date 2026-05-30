# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct curso{
    int id;
    char nome[50];
};

typedef struct curso Curso;

struct disciplina{
    int id;
    char nome[50];
    int id_curso;
};

typedef struct disciplina Disciplina;

struct monitor{
    int id;
    char nome[50];
    int id_disciplina;
    char horario[20];

    struct monitor *prox;
};

typedef struct monitor Monitor;

struct aluno{
    int matricula;
    char nome[50];
    int id_curso;

    struct aluno *prox;
};

typedef struct aluno Aluno;

struct nofila{
    char nome[50];

    struct nofila *ant;
    struct nofila *prox;
};

typedef struct nofila noFila;

struct fila{
    noFila *inicio;
    noFila *fim;
};

typedef struct fila Fila;

struct nopilha{
    char nomeAluno[50];

    struct nopilha *prox;
};

typedef struct nopilha noPilha;

struct pilha{
    noPilha *topo;
};

typedef struct pilha Pilha;

void inicializarFila(Fila *f){
    f->inicio = NULL;
    f->fim = NULL;
}

void enfileirar(Fila *f, char nome[50]){

    noFila *novo;
    
    novo = (noFila*) malloc(sizeof(noFila));

    if(novo == NULL){
        printf("Erro ao alocar memória.\n");
        return;
    }

    strcpy(novo->nome, nome);
    
    novo->ant = NULL;
    novo->prox = NULL;

    if(f->fim == NULL){
        f->inicio = novo;
        f->fim = novo;

    } else {
        novo->ant = f->fim;
        f->fim->prox = novo;
        f->fim = novo;

    }

    printf("%s entrou na fila.\n", nome);
}

void desenfileirar(Fila *f){

    if(f->inicio == NULL){
        printf("A fila está vazia.\n");
        return;
    }

    noFila *temp;
    
    temp = f->inicio;

    printf("%s foi chamado.\n", temp->nome);

    f->inicio = f->inicio->prox;

    if(f->inicio != NULL){
        f->inicio->ant = NULL;
    } else {
        f->fim = NULL;
    }

    free(temp);
}

void mostrarFila(Fila *f){
    if(f->inicio == NULL){
        printf("Fila vazia.\n");
        return;
    }

    noFila *aux;
    
    aux = f->inicio;

    printf("Fila de Espera: ");

    while(aux != NULL){
        printf("%s ", aux->nome);
        aux = aux->prox;
    }
    //printf("\n");
}

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

    //printf("\n");
}

int main(){

    Fila fila;
    Pilha historico;

    int opcao;

    char nome[50];
    char nomeAluno[50];

    inicializarFila(&fila);
    inicializarPilha(&historico);

    do{
        printf("\nMenu Monitoria:\n");
        printf("1. Adicionar aluno\n");
        printf("2. Chamar proximo aluno\n");
        printf("3. Mostrar fila de espera\n");
        printf("4. Mostrar historico\n");
        printf("5. Desfazer ultima acao\n");
        printf("0. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        getchar();

        switch(opcao){
            case 1:
                printf("Digite o nome do aluno: ");
                scanf("%s", nome);

                enfileirar(&fila, nome);

                push(&historico, nome);
                break;

            case 2:

                if(fila.inicio != NULL){
                    sprintf(nomeAluno, "%s foi chamado", fila.inicio->nome);
                    push(&historico, nomeAluno);
                }

                desenfileirar(&fila);
                break;

            case 3:
                mostrarFila(&fila);
                break;

            case 4:
                mostrarhistorico(&historico);
                break;
            
            case 5:
                pop(&historico);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(opcao != 0);

    return 0;
}