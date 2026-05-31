#ifndef HORARIOS_H
#define HORARIOS_H

#define DIAS 5
#define TURNOS 3

void inicializarHorarios(void);
int alocarHorario(int dia, int turno, int id_monitor);
int liberarHorario(int dia, int turno);
void mostrarHorarios(void);

#endif
