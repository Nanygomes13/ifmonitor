#ifndef MONITORES_H
#define MONITORES_H

#include "fila.h"

typedef struct monitor {
    int id;
    char nome[100];
    int id_disciplina;
    Fila filaEspera;
    struct monitor *prox;
} Monitor;

extern Monitor *inicioMonitores;

void inicializarMonitores(void);
int adicionarMonitor(char nome[100], int id, int id_disciplina);
void listarMonitores(void);
Monitor* buscarMonitorPorId(int id);
void liberarMonitores(void);

#endif
