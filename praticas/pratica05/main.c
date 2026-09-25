#include <stdio.h>
#include <stdlib.h>
#include "../pratica01/grafo_lista.h"
#include "coloracao.h"

int main()
{
    int n = 4;
    GrafoLista *grafo_l = criar_grafo_lista(n);

    inserir_aresta_lista(grafo_l, 0, 1);
    inserir_aresta_lista(grafo_l, 1, 2);
    inserir_aresta_lista(grafo_l, 2, 3);
    inserir_aresta_lista(grafo_l, 3, 0);

    // Coloração Gulosa
    puts("\nExemplo coloracao_gulosa:");
    int num_cores_gulosa = 0;
    int *cores_gulosa = coloracao_gulosa(grafo_l, &num_cores_gulosa);

    if (cores_gulosa != NULL)
    {
        printf("Numero de cores utilizadas (Guloso): %d\n", num_cores_gulosa);

        for (int i = 0; i < n; i++)
        {
            printf("Vertice [%d] -> Cor: %d\n", i, cores_gulosa[i]);
        }

        free(cores_gulosa);
    }

    // Coloração Welsh-Powell
    puts("\nExemplo coloracao_welsh_powell:");
    int num_cores_wp = 0;
    int *cores_wp = coloracao_welsh_powell(grafo_l, &num_cores_wp);

    if (cores_wp != NULL)
    {
        printf("Numero de cores utilizadas (Welsh-Powell): %d\n", num_cores_wp);

        for (int i = 0; i < n; i++)
        {
            printf("Vertice [%d] -> Cor: %d\n", i, cores_wp[i]);
        }

        free(cores_wp);
    }

    // Detecção de Bipartição
    puts("\nExemplo eh_bipartido:");

    if (eh_bipartido(grafo_l))
    {
        puts("O grafo e bipartido.");
    }
    else
    {
        puts("O grafo nao e bipartido.");
    }

    liberar_grafo_lista(grafo_l);
    puts("");

    return 0;
}
