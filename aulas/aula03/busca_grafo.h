#ifndef BUSCA_GRAFO_H
#define BUSCA_GRAFO_H

#include "grafo_lista.h"

void dfs(GrafoLista *grafo, int u, int *visitado);
void bfs(GrafoLista *grafo, int u, int *visitado);

#endif