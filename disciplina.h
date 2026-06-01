#ifndef DISCIPLINA_H
#define DISCIPLINA_H
#include "estruturas.h"

Disciplina* buscarDisciplinaPorId(Disciplina *topo, int id);
void cadastrarDisciplina(Disciplina **topo, Curso *listaCursos);
void listarDisciplinas(Disciplina *topo, Curso *listaCursos);
void removerDisciplina(Disciplina **topo, int id, Monitor *listaMonitores);
void liberarDisciplinas(Disciplina *topo);

#endif
