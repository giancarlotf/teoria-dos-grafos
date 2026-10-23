#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

int main()
{
    int n = 6;
    GrafoLista *grafo_l = criar_grafo(n);

    inserir_arco(grafo_l, 0, 1);
    inserir_arco(grafo_l, 0, 2);
    inserir_arco(grafo_l, 1, 3);
    inserir_arco(grafo_l, 2, 3);
    inserir_arco(grafo_l, 3, 4);

    // Verificação de DAG
    puts("\nExemplo eh_dag:");
    if (eh_dag(grafo_l))
    {
        puts("O grafo e um DAG (Direcionado Aciclico).");
    }
    else
    {
        puts("O grafo NAO e um DAG (contem ciclos).");
    }

    // Algoritmo de Kahn
    puts("\nExemplo ordenacao_topologica_kahn:");
    int tamanho_kahn = 0;
    int *ordem_kahn = ordenacao_topologica_kahn(grafo_l, &tamanho_kahn);

    if (ordem_kahn != NULL)
    {
        printf("Ordem Topologica (Kahn): ");
        for (int i = 0; i < tamanho_kahn; i++)
        {
            printf("%d ", ordem_kahn[i]);
        }
        puts("");
        free(ordem_kahn);
    }
    else
    {
        puts("Nao foi possivel ordenar: o grafo contem ciclos.");
    }

    // Variante DFS
    puts("\nExemplo ordenacao_topologica_dfs:");
    int tamanho_dfs = 0;
    int *ordem_dfs = ordenacao_topologica_dfs(grafo_l, &tamanho_dfs);

    if (ordem_dfs != NULL)
    {
        printf("Ordem Topologica (DFS): ");
        for (int i = 0; i < tamanho_dfs; i++)
        {
            printf("%d ", ordem_dfs[i]);
        }
        puts("");
        free(ordem_dfs);
    }
    else
    {
        puts("Nao foi possivel ordenar: o grafo contem ciclos.");
    }

    liberar_grafo(grafo_l);

    puts("");
    return 0;
}