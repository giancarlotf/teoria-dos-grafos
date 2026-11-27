#include <stdio.h>
#include "cobertura.h"

int main()
{
    int lista_n[] = {5, 8, 10, 12, 15};

    for (int t = 0; t < 5; t++)
    {
        int n = lista_n[t];
        Aresta arestas[MAX_ARESTAS];
        int m = 0;

        for (int v = 0; v < n - 1; v++)
        {
            arestas[m].u = v;
            arestas[m].v = v + 1;
            m++;
        }

        for (int v = 0; v + 2 < n; v += 2)
        {
            arestas[m].u = v;
            arestas[m].v = v + 2;
            m++;
        }

        if (n >= 5)
        {
            arestas[m].u = 0;
            arestas[m].v = n - 1;
            m++;
        }

        int resposta_gulosa[MAX_VERTICES] = {0};
        int tamanho_gulosa = cobertura_gulosa(arestas, n, m, resposta_gulosa);

        puts("Resultado de cobertura_gulosa:");

        if (tamanho_gulosa >= 0)
        {
            int marcado_gulosa[MAX_VERTICES] = {0};

            for (int i = 0; i < tamanho_gulosa; i++)
            {
                marcado_gulosa[resposta_gulosa[i]] = 1;
            }

            int valida_gulosa = eh_cobertura(arestas, m, marcado_gulosa);

            printf("Grafo com n = %d e m = %d (tamanho = %d; valida = %d):\n", n, m, tamanho_gulosa, valida_gulosa);

            for (int i = 0; i < tamanho_gulosa; i++)
            {
                printf("[%d] vertice %d\n", i, resposta_gulosa[i]);
            }
        }
        else
        {
            puts("Nao foi possivel calcular a cobertura gulosa");
        }

        puts("");

        int resposta_bt[MAX_VERTICES] = {0};
        int tamanho_bt = cobertura_minima_bt(arestas, n, m, resposta_bt);

        puts("Resultado de cobertura_minima_bt:");

        if (tamanho_bt >= 0)
        {
            int marcado_bt[MAX_VERTICES] = {0};

            for (int i = 0; i < tamanho_bt; i++)
            {
                marcado_bt[resposta_bt[i]] = 1;
            }

            int valida_bt = eh_cobertura(arestas, m, marcado_bt);

            printf("Grafo com n = %d e m = %d (tamanho = %d; valida = %d):\n", n, m, tamanho_bt, valida_bt);

            for (int i = 0; i < tamanho_bt; i++)
            {
                printf("[%d] vertice %d\n", i, resposta_bt[i]);
            }
        }
        else
        {
            puts("Nao foi possivel calcular a cobertura minima com backtracking");
        }

        puts("");
    }

    return 0;
}
