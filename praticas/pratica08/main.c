#include <stdio.h>
#include "agm.h"

int main()
{
    GrafoListaPonderado *grafo_lp = criar_grafo(6);

    inserir_aresta(grafo_lp, 0, 1, 4);
    inserir_aresta(grafo_lp, 0, 2, 2);
    inserir_aresta(grafo_lp, 1, 2, 1);
    inserir_aresta(grafo_lp, 1, 3, 5);
    inserir_aresta(grafo_lp, 1, 4, 8);
    inserir_aresta(grafo_lp, 2, 3, 4);
    inserir_aresta(grafo_lp, 2, 4, 10);
    inserir_aresta(grafo_lp, 3, 4, 2);
    inserir_aresta(grafo_lp, 3, 5, 1);
    inserir_aresta(grafo_lp, 4, 5, 3);

    int custo = 0;

    Aresta *resultado_kruskal = kruskal(grafo_lp, &custo);

    puts("Resultado do algoritmo de Kruskal:");

    if (resultado_kruskal)
    {
        puts("Arvore Geradora Minima:");

        for (int i = 0; resultado_kruskal[i].u != -1; i++)
        {
            printf("[%d] %d -- %d\n", i, resultado_kruskal[i].u, resultado_kruskal[i].v);
        }

        puts("Custo:");

        for (int i = 0; resultado_kruskal[i].u != -1; i++)
        {
            printf("%d", resultado_kruskal[i].peso);

            if (resultado_kruskal[i + 1].u != -1)
            {
                printf(" + ");
            }
        }

        printf(" = %d\n", custo);
    }
    else
    {
        puts("Nao foi possivel calcular a AGM com Kruskal");
    }

    puts("");

    int origem = 0;
    custo = 0;

    Aresta *resultado_prim = prim(grafo_lp, origem, &custo);

    puts("Resultado do algoritmo de Prim:");

    if (resultado_prim)
    {
        puts("Arvore Geradora Minima:");

        for (int i = 0; resultado_prim[i].u != -1; i++)
        {
            printf("[%d] %d -- %d\n", i, resultado_prim[i].u, resultado_prim[i].v);
        }

        puts("Custo:");

        for (int i = 0; resultado_prim[i].u != -1; i++)
        {
            printf("%d", resultado_prim[i].peso);

            if (resultado_prim[i + 1].u != -1)
            {
                printf(" + ");
            }
        }

        printf(" = %d\n", custo);
    }
    else
    {
        puts("Nao foi possivel calcular a AGM com Prim");
    }

    liberar_grafo(grafo_lp);

    return 0;
}
