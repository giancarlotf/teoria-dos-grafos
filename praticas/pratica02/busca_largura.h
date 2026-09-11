#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include "../pratica01/grafo_lista.h"

// Fila (FIFO) para BFS
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

Fila* criar_fila(int capacidade);
void enfileirar(Fila *f, int v);
int desenfileirar(Fila *f);
int fila_vazia(Fila *f);
void liberar_fila(Fila *f);

void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);

#endif