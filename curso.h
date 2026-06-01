#ifndef CURSO_H
#define CURSO_H
#include "estruturas.h"

Curso* buscarCursoPorId(Curso *topo, int id);
void cadastrarCurso(Curso **topo);
void listarCursos(Curso *topo);
void removerCurso(Curso **topo, int id, Disciplina *listaDisciplinas);
void liberarCursos(Curso *topo);

#endif
