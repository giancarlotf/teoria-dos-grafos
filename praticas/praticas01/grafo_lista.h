#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

// Lista de adjacência
typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int n;
    No **adj;
} GrafoLista;

GrafoLista criar_grafo_lista(int n);
void inserir_aresta_(No *u, No *v);
void remover_aresta_(No *u, No *v);
void grau_();
void sao_adjacentes_();
void liberar_grafo_(GrafoLista grafo);

#endif