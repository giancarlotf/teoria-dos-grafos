#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#define LIMITE 10

// Matriz de adjacência
typedef struct {
    int n;
    int **adj;
} GrafoMatriz;

GrafoMatriz criar_grafo_matriz(int n);
void liberar_grafo_(GrafoMatriz grafo);

#endif