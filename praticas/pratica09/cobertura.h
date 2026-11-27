#ifndef COBERTURA_H
#define COBERTURA_H 1

// Contexto do ambiente

#ifndef MAX_VERTICES
#define MAX_VERTICES 512
#endif

#ifndef MAX_ARESTAS
#define MAX_ARESTAS 2048
#endif

typedef struct
{
    int u;
    int v;
} Aresta;

// Implementação do código

// Backtracking com poda por limite.
int cobertura_minima_bt(Aresta arestas[], int n, int m, int cobertura[]);

// Seleciona vértice de maior grau restante.
int cobertura_gulosa(Aresta arestas[], int n, int m, int cobertura[]);

// Verifica se todas as arestas estão cobertas.
int eh_cobertura(Aresta arestas[], int m, int cobertura[]);

#endif // COBERTURA_H
