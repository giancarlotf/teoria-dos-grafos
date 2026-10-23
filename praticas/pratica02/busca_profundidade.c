#include <stdlib.h>
#include "busca_profundidade.h"

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *tempo_entrada, int *tempo_saida, int *tempo)
{
    visitado[u] = 1;
    tempo_entrada[u] = ++(*tempo);
    No *no = g->adj[u];

    while (no)
    {
        int v = no->destino;

        if (!visitado[v])
        {
            dfs_recursiva(g, v, visitado, tempo_entrada, tempo_saida, tempo);
        }

        no = no->prox;
    }

    tempo_saida[u] = ++(*tempo);
}

int contar_componentes(GrafoLista *g)
{
    int componentes = 0;
    int *visitado = (int *)calloc(g->n, sizeof(int));
    int *tempo_entrada = (int *)malloc(g->n * sizeof(int));
    int *tempo_saida = (int *)malloc(g->n * sizeof(int));
    int tempo = 0;

    for (int i = 0; i < g->n; i++)
    {
        if (!visitado[i])
        {
            componentes++;
            dfs_recursiva(g, i, visitado, tempo_entrada, tempo_saida, &tempo);
        }
    }

    free(visitado);
    free(tempo_entrada);
    free(tempo_saida);
    return componentes;
}

int dfs_ciclo(GrafoLista *g, int u, int *pilha)
{
    pilha[u] = 1;
    No *no = g->adj[u];

    while (no)
    {
        int v = no->destino;
        if (pilha[v] == 1)
        {
            return 1;
        }
        if (pilha[v] == 0)
        {
            if (dfs_ciclo(g, v, pilha))
            {
                return 1;
            }
        }
        no = no->prox;
    }

    pilha[u] = 2;
    return 0;
}

int tem_ciclo(GrafoLista *g)
{
    int *pilha = (int *)calloc(g->n, sizeof(int));

    for (int i = 0; i < g->n; i++)
    {
        if (pilha[i] == 0)
        {
            if (dfs_ciclo(g, i, pilha))
            {
                free(pilha);
                return 1;
            }
        }
    }

    free(pilha);
    return 0;
}
