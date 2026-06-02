#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "curso.h"
#include "disciplina.h"
#include "monitor.h"
#include "fila.h"
#include "pilha.h"

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

void menuAluno(Pilha *historico, Monitor *listaMonitores, Disciplina *listaDisciplinas) {
    int opcao;
    char nome[50];
    int idMonitor;

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
                
                printf("Digite o ID do monitor desejado: ");
                if (scanf("%d", &idMonitor) == 1) {
                    getchar();
                    Monitor *m = buscarMonitorPorId(listaMonitores, idMonitor);
                    if (m) {
                        enfileirar(&m->fila_espera, nome);
                    } else {
                        printf("Erro: Monitor com ID %d nao existe.\n", idMonitor);
                    }
                } else {
                    getchar();
                    printf("ID invalido.\n");
                }
                break;

            case 2:
                printf("Digite o ID do monitor: ");
                if (scanf("%d", &idMonitor) == 1) {
                    getchar();
                    Monitor *m = buscarMonitorPorId(listaMonitores, idMonitor);
                    if (m) {
                        mostrarFila(&m->fila_espera);
                    } else {
                        printf("Erro: Monitor com ID %d nao existe.\n", idMonitor);
                    }
                } else {
                    getchar();
                    printf("ID invalido.\n");
                }
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

void menuMonitor(Monitor *listaMonitores, Pilha *historico) {
    int opcao;
    char nomeAluno[50];
    int idMonitor;

    printf("\nDigite seu ID de Monitor: ");
    if (scanf("%d", &idMonitor) != 1) {
        getchar();
        printf("ID invalido.\n");
        return;
    }
    getchar();

    Monitor *m = buscarMonitorPorId(listaMonitores, idMonitor);
    if (!m) {
        printf("Erro: Monitor com ID %d nao existe.\n", idMonitor);
        return;
    }

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
                if(m->fila_espera.inicio != NULL){
                    sprintf(nomeAluno, "%s foi chamado", m->fila_espera.inicio->nome);
                    push(historico, nomeAluno);
                }
                desenfileirar(&m->fila_espera);
                break;

            case 2:
                mostrarFila(&m->fila_espera);
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
    Pilha historico;
    Curso *listaCursos = NULL;
    Disciplina *listaDisciplinas = NULL;
    Monitor *listaMonitores = NULL;

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
                menuAluno(&historico, listaMonitores, listaDisciplinas);
                break;

            case 2:
                menuMonitor(listaMonitores, &historico);
                break;

            case 3:
                menuAdministrador(&listaCursos, &listaDisciplinas, &listaMonitores);
                break;

            case 0:
                printf("Liberando memoria e encerrando o sistema...\n");
                liberarCursos(listaCursos);
                liberarDisciplinas(listaDisciplinas);
                liberarMonitores(listaMonitores);
                liberarPilha(&historico);
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(opcao != 0);

    return 0;
}