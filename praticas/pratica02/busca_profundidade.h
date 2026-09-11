#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "../pratica01/grafo_lista.h"

// Pilha (LIFO) para DFS iterativa
typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *tempo_entrada, int *tempo_saida, int *tempo);
int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);

#endif