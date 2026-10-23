#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

static int colorir_vertices(GrafoLista *g, const int *ordem, int *cores)
{
    int n = g->n;
    int max_cor = -1;
    int *cores_disponiveis = (int *)calloc(n, sizeof(int));

    if (!cores_disponiveis)
        return -1;

    for (int i = 0; i < n; i++)
    {
        int u = ordem[i];
        No *atual = g->adj[u];

        while (atual != NULL)
        {
            int v = atual->destino;

            if (v >= 0 && v < n && cores[v] != -1)
                cores_disponiveis[cores[v]] = 1;

            atual = atual->prox;
        }

        int cor_escolhida = 0;

        while (cor_escolhida < n && cores_disponiveis[cor_escolhida] == 1)
        {
            cor_escolhida++;
        }

        cores[u] = cor_escolhida;

        if (cor_escolhida > max_cor)
            max_cor = cor_escolhida;

        atual = g->adj[u];

        while (atual != NULL)
        {
            int v = atual->destino;
            if (v >= 0 && v < n && cores[v] != -1)
            {
                cores_disponiveis[cores[v]] = 0;
            }
            atual = atual->prox;
        }
    }

    free(cores_disponiveis);
    return max_cor;
}

int *coloracao_gulosa(GrafoLista *g, int *num_cores)
{
    if (g == NULL || g->n <= 0)
    {
        *num_cores = 0;
        return NULL;
    }

    int n = g->n;
    int *cores = (int *)malloc(n * sizeof(int));
    int *ordem = (int *)malloc(n * sizeof(int));

    if (!cores || !ordem)
    {
        free(cores);
        free(ordem);
        *num_cores = 0;
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        cores[i] = -1;
        ordem[i] = i;
    }

    int max_cor = colorir_vertices(g, ordem, cores);
    free(ordem);

    *num_cores = (max_cor >= 0) ? max_cor + 1 : 0;
    return cores;
}

typedef struct
{
    int vertice;
    int grau;
} VerticeGrau;

int comparar_grau_vertices(const void *a, const void *b)
{
    VerticeGrau *vg1 = (VerticeGrau *)a;
    VerticeGrau *vg2 = (VerticeGrau *)b;
    return vg2->grau - vg1->grau;
}

int *coloracao_welsh_powell(GrafoLista *g, int *num_cores)
{
    if (g == NULL || g->n <= 0)
    {
        *num_cores = 0;
        return NULL;
    }

    int n = g->n;
    VerticeGrau *vgs = (VerticeGrau *)malloc(n * sizeof(VerticeGrau));
    int *cores = (int *)malloc(n * sizeof(int));
    int *ordem = (int *)malloc(n * sizeof(int));

    if (!vgs || !cores || !ordem)
    {
        free(vgs);
        free(cores);
        free(ordem);
        *num_cores = 0;
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        vgs[i].vertice = i;
        vgs[i].grau = grau_lista(g, i);
        cores[i] = -1;
    }

    qsort(vgs, n, sizeof(VerticeGrau), comparar_grau_vertices);

    for (int i = 0; i < n; i++)
    {
        ordem[i] = vgs[i].vertice;
    }

    int max_cor = colorir_vertices(g, ordem, cores);
    free(vgs);
    free(ordem);
    *num_cores = (max_cor >= 0) ? max_cor + 1 : 0;

    return cores;
}

int eh_bipartido(GrafoLista *g)
{
    if (g == NULL || g->n <= 0)
        return 1;

    int n = g->n;
    int *cores = (int *)malloc(n * sizeof(int));
    int *fila = (int *)malloc(n * sizeof(int));

    if (!cores || !fila)
    {
        free(cores);
        free(fila);
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        cores[i] = -1;
    }

    int inicio = 0, fim = 0;
    int bipartido = 1;

    for (int i = 0; i < n && bipartido; i++)
    {
        if (cores[i] == -1)
        {
            cores[i] = 0;
            fila[fim++] = i;

            while (inicio < fim && bipartido)
            {
                int u = fila[inicio++];
                No *atual = g->adj[u];

                while (atual != NULL)
                {
                    int v = atual->destino;

                    if (cores[v] == -1)
                    {
                        cores[v] = 1 - cores[u];
                        fila[fim++] = v;
                    }
                    else if (cores[v] == cores[u])
                    {
                        bipartido = 0;
                        break;
                    }

                    atual = atual->prox;
                }
            }
        }
    }

    free(cores);
    free(fila);

    return bipartido;
}
