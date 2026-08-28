/**
 * Os exemplos de uso das funções de matriz e de lista de adjacência recebem os
 * mesmos dados de entrada, a fim de facilitar a comparação e demonstrar que
 * ambos os métodos chegam aos mesmos resultados.
 */

#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main()
{
    // Matriz de Adjacência
    puts("\nExemplo grafo_matriz:");

    GrafoMatriz *grafo_m = criar_grafo_matriz(4);

    inserir_aresta_matriz(grafo_m, 0, 1);
    inserir_aresta_matriz(grafo_m, 0, 2);
    inserir_aresta_matriz(grafo_m, 0, 3);

    printf("Grau do vertice 0: %d\n", grau_matriz(grafo_m, 0));
    printf("Grau do vertice 1: %d\n", grau_matriz(grafo_m, 1));

    if (sao_adjacentes_matriz(grafo_m, 0, 1))
    {
        puts("Os vertices 0 e 1 sao adjacentes");
    }
    else
    {
        puts("Os vertices 0 e 1 nao sao adjacentes");
    }

    if (sao_adjacentes_matriz(grafo_m, 1, 2))
    {
        puts("Os vertices 1 e 2 sao adjacentes");
    }
    else
    {
        puts("Os vertices 1 e 2 nao sao adjacentes");
    }

    remover_aresta_matriz(grafo_m, 0, 3);
    puts("Aresta (0, 3) removida");
    printf("Grau do vertice 0: %d\n", grau_matriz(grafo_m, 0));

    liberar_grafo_matriz(grafo_m);

    // Lista de Adjacência
    puts("\nExemplo grafo_lista:");

    GrafoLista *grafo_l = criar_grafo_lista(4);

    inserir_aresta_lista(grafo_l, 0, 1);
    inserir_aresta_lista(grafo_l, 0, 2);
    inserir_aresta_lista(grafo_l, 0, 3);

    printf("Grau do vertice 0: %d\n", grau_lista(grafo_l, 0));
    printf("Grau do vertice 1: %d\n", grau_lista(grafo_l, 1));

    if (sao_adjacentes_lista(grafo_l, 0, 1))
    {
        puts("Os vertices 0 e 1 sao adjacentes");
    }
    else
    {
        puts("Os vertices 0 e 1 nao sao adjacentes");
    }

    if (sao_adjacentes_lista(grafo_l, 1, 2))
    {
        puts("Os vertices 1 e 2 sao adjacentes");
    }
    else
    {
        puts("Os vertices 1 e 2 nao sao adjacentes");
    }

    remover_aresta_lista(grafo_l, 0, 3);
    puts("Aresta (0, 3) removida");
    printf("Grau do vertice 0: %d\n", grau_lista(grafo_l, 0));

    liberar_grafo_lista(grafo_l);

    puts("");
    return 0;
}
