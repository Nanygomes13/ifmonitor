#include "horarios.h"
#include "monitores.h"
#include <stdio.h>


int matrizHorarios[DIAS][TURNOS];

void inicializarHorarios(void) {
    for (int i = 0; i < DIAS; i++) {
        for (int j = 0; j < TURNOS; j++) {
            matrizHorarios[i][j] = 0; 
        }
    }
}

int alocarHorario(int dia, int turno, int id_monitor) {
    if (dia < 0 || dia >= DIAS || turno < 0 || turno >= TURNOS) {
        printf("Dia ou turno invalido.\n");
        return 0;
    }

    if (matrizHorarios[dia][turno] != 0) {
        printf("Horario ja esta ocupado pelo monitor ID %d.\n", matrizHorarios[dia][turno]);
        return 0;
    }

    matrizHorarios[dia][turno] = id_monitor;
    printf("Horario alocado com sucesso para o monitor %d.\n", id_monitor);
    return 1;
}

int liberarHorario(int dia, int turno) {
    if (dia < 0 || dia >= DIAS || turno < 0 || turno >= TURNOS) {
        printf("Dia ou turno invalido.\n");
        return 0;
    }

    if (matrizHorarios[dia][turno] == 0) {
        printf("O horario ja esta livre.\n");
        return 0;
    }

    matrizHorarios[dia][turno] = 0;
    printf("Horario liberado com sucesso.\n");
    return 1;
}

void mostrarHorarios(void) {
    const char *nomesDias[] = {"Seg", "Ter", "Qua", "Qui", "Sex"};

    printf("\n--- Grade de Horarios (Nome do Monitor) ---\n");
    printf("%-7s | %-12s | %-12s | %-12s\n", "Dia", "Manha", "Tarde", "Noite");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < DIAS; i++) {
        printf("%-7s | ", nomesDias[i]);
        for (int j = 0; j < TURNOS; j++) {
            if (matrizHorarios[i][j] == 0) {
                printf("%-12s | ", "Livre");
            } else {
                Monitor *m = buscarMonitorPorId(matrizHorarios[i][j]);
                if (m != NULL) {
                    printf("%-12.12s | ", m->nome);
                } else {
                    char temp[20];
                    sprintf(temp, "Mon.%d", matrizHorarios[i][j]);
                    printf("%-12s | ", temp);
                }
            }
        }
        printf("\n");
    }
    printf("------------------------------------------------------\n");
}
