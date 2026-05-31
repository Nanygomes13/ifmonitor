# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct curso{
    int id;
    char nome[50];
    struct curso *prox;
};

typedef struct curso Curso;

struct disciplina{
    int id;
    char nome[50];
    int id_curso;
    struct disciplina *prox;
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
}

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

void gerenciarSistema(Curso **listaCursos, Disciplina **listaDisciplinas, Monitor **listaMonitores) {
    int opcao;
    int id;

    do {
        printf("\n=== GERENCIAR SISTEMA ===\n");
        printf("1. Listar Cursos\n");
        printf("2. Listar Disciplinas\n");
        printf("3. Listar Monitores\n");
        printf("4. Remover Curso\n");
        printf("5. Remover Disciplina\n");
        printf("6. Remover Monitor\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");
            getchar();
            continue;
        }
        getchar();

        switch(opcao) {
            case 1:
                listarCursos(*listaCursos);
                break;
            case 2:
                listarDisciplinas(*listaDisciplinas, *listaCursos);
                break;
            case 3:
                listarMonitores(*listaMonitores, *listaDisciplinas);
                break;
            case 4:
                printf("Digite o ID do Curso a remover: ");
                if (scanf("%d", &id) == 1) {
                    getchar();
                    removerCurso(listaCursos, id, *listaDisciplinas);
                } else {
                    getchar();
                    printf("ID invalido.\n");
                }
                break;
            case 5:
                printf("Digite o ID da Disciplina a remover: ");
                if (scanf("%d", &id) == 1) {
                    getchar();
                    removerDisciplina(listaDisciplinas, id, *listaMonitores);
                } else {
                    getchar();
                    printf("ID invalido.\n");
                }
                break;
            case 6:
                printf("Digite o ID do Monitor a remover: ");
                if (scanf("%d", &id) == 1) {
                    getchar();
                    removerMonitor(listaMonitores, id);
                } else {
                    getchar();
                    printf("ID invalido.\n");
                }
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
}

void liberarCursos(Curso *topo) {
    Curso *aux;
    while(topo != NULL) {
        aux = topo;
        topo = topo->prox;
        free(aux);
    }
}

void liberarDisciplinas(Disciplina *topo) {
    Disciplina *aux;
    while(topo != NULL) {
        aux = topo;
        topo = topo->prox;
        free(aux);
    }
}

void liberarMonitores(Monitor *topo) {
    Monitor *aux;
    while(topo != NULL) {
        aux = topo;
        topo = topo->prox;
        free(aux);
    }
}

void liberarFila(Fila *f) {
    noFila *aux;
    while(f->inicio != NULL) {
        aux = f->inicio;
        f->inicio = f->inicio->prox;
        free(aux);
    }
    f->fim = NULL;
}

void liberarPilha(Pilha *p) {
    noPilha *aux;
    while(p->topo != NULL) {
        aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }
}

void menuAdministrador(Curso **listaCursos, Disciplina **listaDisciplinas, Monitor **listaMonitores) {
    int opcao;
    do {
        printf("\n=== MENU ADMINISTRADOR ===\n");
        printf("1. Cadastrar Curso\n");
        printf("2. Cadastrar Disciplina\n");
        printf("3. Cadastrar Monitor\n");
        printf("4. Gerenciar Sistema (Listar/Remover)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");
            getchar();
            continue;
        }
        getchar();

        switch(opcao) {
            case 1:
                cadastrarCurso(listaCursos);
                break;
            case 2:
                cadastrarDisciplina(listaDisciplinas, *listaCursos);
                break;
            case 3:
                cadastrarMonitor(listaMonitores, *listaDisciplinas);
                break;
            case 4:
                gerenciarSistema(listaCursos, listaDisciplinas, listaMonitores);
                break;
            case 0:
                printf("Retornando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
}

void menuAluno(Fila *fila, Pilha *historico, Monitor *listaMonitores, Disciplina *listaDisciplinas) {
    int opcao;
    char nome[50];

    do {
        printf("\n=== MENU ALUNO ===\n");
        printf("1. Entrar na Fila de Espera\n");
        printf("2. Mostrar Fila de Espera\n");
        printf("3. Visualizar Monitores e Horarios\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");
            getchar();
            continue;
        }
        getchar();

        switch(opcao) {
            case 1:
                printf("Digite o nome do aluno: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                enfileirar(fila, nome);
                push(historico, nome);
                break;

            case 2:
                mostrarFila(fila);
                printf("\n");
                break;

            case 3:
                listarMonitores(listaMonitores, listaDisciplinas);
                break;

            case 0:
                printf("Retornando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
}

void menuMonitor(Fila *fila, Pilha *historico) {
    int opcao;
    char nomeAluno[50];

    do {
        printf("\n=== MENU MONITOR ===\n");
        printf("1. Chamar Proximo Aluno\n");
        printf("2. Mostrar Fila de Espera\n");
        printf("3. Mostrar Historico de Atendimentos\n");
        printf("4. Desfazer Ultima Acao\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");
            getchar();
            continue;
        }
        getchar();

        switch(opcao) {
            case 1:
                if(fila->inicio != NULL){
                    sprintf(nomeAluno, "%s foi chamado", fila->inicio->nome);
                    push(historico, nomeAluno);
                }
                desenfileirar(fila);
                break;

            case 2:
                mostrarFila(fila);
                printf("\n");
                break;

            case 3:
                mostrarhistorico(historico);
                printf("\n");
                break;

            case 4:
                pop(historico);
                break;

            case 0:
                printf("Retornando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
}

int main(){

    Fila fila;
    Pilha historico;
    Curso *listaCursos = NULL;
    Disciplina *listaDisciplinas = NULL;
    Monitor *listaMonitores = NULL;

    inicializarFila(&fila);
    inicializarPilha(&historico);

    int opcao;

    do{
        printf("\n=== IFMONITOR - MENU PRINCIPAL ===\n");
        printf("1. Acesso Aluno\n");
        printf("2. Acesso Monitor\n");
        printf("3. Acesso Administrador\n");
        printf("0. Sair\n");

        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");
            getchar();
            continue;
        }
        getchar();

        switch(opcao){
            case 1:
                menuAluno(&fila, &historico, listaMonitores, listaDisciplinas);
                break;

            case 2:
                menuMonitor(&fila, &historico);
                break;

            case 3:
                menuAdministrador(&listaCursos, &listaDisciplinas, &listaMonitores);
                break;

            case 0:
                printf("Liberando memoria e encerrando o sistema...\n");
                liberarCursos(listaCursos);
                liberarDisciplinas(listaDisciplinas);
                liberarMonitores(listaMonitores);
                liberarFila(&fila);
                liberarPilha(&historico);
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(opcao != 0);

    return 0;
}