#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "pilha.h"
#include "utils.h"
#include "disciplinas.h"
#include "monitores.h"
#include "horarios.h"

int main() {
    Pilha historico;

    int opcao;
    char nome[100];
    char nomeAluno[100];
    int id_disciplina, id_monitor, dia, turno;

    inicializarPilha(&historico);
    inicializarDisciplinas();
    inicializarMonitores();
    inicializarHorarios();

    do {
        printf("\n=========================================\n");
        printf("      SISTEMA DE MONITORIAS (IFAL)       \n");
        printf("=========================================\n");
        printf(" 1. Cadastrar Disciplina\n");
        printf(" 2. Cadastrar Monitor e Horario\n");
        printf(" 3. Ver Grade de Horarios e Monitores\n");
        printf(" 4. Entrar na Fila de Espera (Aluno)\n");
        printf(" 5. Atender Proximo Aluno\n");
        printf(" 6. Ver Filas e Historico\n");
        printf(" 7. Desfazer Ultima Acao (Pilha)\n");
        printf(" 0. Sair\n");
        printf("=========================================\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                printf("Digite o ID da disciplina: ");
                scanf("%d", &id_disciplina);
                limparBufferEntrada();
                printf("Digite o nome da disciplina: ");
                lerStringSegura(nome, sizeof(nome));
                
                if (adicionarDisciplina(nome, id_disciplina)) {
                    sprintf(nomeAluno, "Cadastrou Disciplina %d", id_disciplina);
                    push(&historico, nomeAluno);
                }
                break;
                
            case 2:
                printf("\n--- Disciplinas Disponiveis ---\n");
                listarDisciplinas();
                printf("-------------------------------\n\n");
                
                printf("Digite o ID do monitor: ");
                scanf("%d", &id_monitor);
                limparBufferEntrada();
                printf("Digite o nome do monitor: ");
                lerStringSegura(nome, sizeof(nome));
                printf("Digite o ID da disciplina: ");
                scanf("%d", &id_disciplina);
                limparBufferEntrada();
                
                if (buscarDisciplinaPorId(id_disciplina) == NULL) {
                    printf("Erro: Disciplina nao existe.\n");
                } else {
                    if (adicionarMonitor(nome, id_monitor, id_disciplina)) {
                        printf("Digite o dia para alocar (0=Seg, 1=Ter, 2=Qua, 3=Qui, 4=Sex): ");
                        scanf("%d", &dia);
                        printf("Digite o turno (0=Manha, 1=Tarde, 2=Noite): ");
                        scanf("%d", &turno);
                        limparBufferEntrada();
                        
                        if (alocarHorario(dia, turno, id_monitor)) {
                            sprintf(nomeAluno, "Mon.%d alocado", id_monitor);
                            push(&historico, nomeAluno);
                        } else {
                            sprintf(nomeAluno, "Cadastrou Mon.%d (Sem Horario)", id_monitor);
                            push(&historico, nomeAluno);
                        }
                    }
                }
                break;
                
            case 3:
                listarDisciplinas();
                listarMonitores();
                mostrarHorarios();
                break;
                
            case 4:
                printf("\n--- Monitores Disponiveis ---\n");
                listarMonitores();
                printf("-----------------------------\n\n");
                
                printf("Digite o ID do monitor que deseja atendimento: ");
                scanf("%d", &id_monitor);
                limparBufferEntrada();
                
                Monitor *m_entrar = buscarMonitorPorId(id_monitor);
                if (m_entrar == NULL) {
                    printf("Monitor nao encontrado.\n");
                } else {
                    printf("Digite o nome do aluno: ");
                    lerStringSegura(nome, sizeof(nome));
                    enfileirar(&(m_entrar->filaEspera), nome);
                    sprintf(nomeAluno, "Aluno %s na fila do Mon.%d", nome, id_monitor);
                    push(&historico, nomeAluno);
                }
                break;

            case 5:
                printf("Digite o ID do monitor que vai atender: ");
                scanf("%d", &id_monitor);
                limparBufferEntrada();
                
                Monitor *m_atender = buscarMonitorPorId(id_monitor);
                if (m_atender == NULL) {
                    printf("Monitor nao encontrado.\n");
                } else {
                    if (m_atender->filaEspera.inicio != NULL) {
                        sprintf(nomeAluno, "Aluno %s atendido pelo Mon.%d", m_atender->filaEspera.inicio->nome, id_monitor);
                        push(&historico, nomeAluno);
                        desenfileirar(&(m_atender->filaEspera));
                    } else {
                        printf("A fila deste monitor esta vazia.\n");
                    }
                }
                break;

            case 6:
                printf("\n--- Filas de Espera por Monitor ---\n");
                Monitor *aux = inicioMonitores;
                int temFila = 0;
                while (aux != NULL) {
                    printf("\n> Fila do Monitor %s:\n", aux->nome);
                    mostrarFila(&(aux->filaEspera));
                    aux = aux->prox;
                    temFila = 1;
                }
                if (!temFila) printf("Nenhum monitor cadastrado ainda.\n");
                
                mostrarhistorico(&historico);
                break;
                
            case 7:
                pop(&historico);
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

        if (opcao != 0) {
            printf("\n[Pressione ENTER para voltar ao menu...]");
            getchar();
        }

    } while (opcao != 0);

    liberarPilha(&historico);
    liberarMonitores();

    return 0;
}