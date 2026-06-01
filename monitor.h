#ifndef MONITOR_H
#define MONITOR_H
#include "estruturas.h"

Monitor* buscarMonitorPorId(Monitor *topo, int id);
void cadastrarMonitor(Monitor **topo, Disciplina *listaDisciplinas);
void listarMonitores(Monitor *topo, Disciplina *listaDisciplinas);
void removerMonitor(Monitor **topo, int id);
void liberarMonitores(Monitor *topo);

#endif
