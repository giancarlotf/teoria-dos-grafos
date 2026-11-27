#include "cobertura.h"

int cobertura_minima_bt(Aresta arestas[], int n, int m, int cobertura[])
{
    if (!arestas || n < 0 || n > MAX_VERTICES || m < 0 || m > MAX_ARESTAS || !cobertura)
    {
        return -1;
    }

    int atual[MAX_VERTICES];
    int melhor[MAX_VERTICES];
    int estado[MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++)
    {
        atual[i] = 0;
        melhor[i] = 0;
        estado[i] = 0;
    }

    int tamanho_atual = 0;
    int tamanho_melhor = n + 1;
    int i = 0;

    while (i >= 0)
    {
        if (tamanho_atual >= tamanho_melhor || i == n)
        {
            if (i < n)
            {
                estado[i] = 0;
            }

            i--;

            continue;
        }

        if (eh_cobertura(arestas, m, atual))
        {
            tamanho_melhor = tamanho_atual;

            for (int v = 0; v < n; v++)
            {
                melhor[v] = atual[v];
            }

            estado[i] = 0;
            i--;

            continue;
        }

        if (estado[i] == 0)
        {
            estado[i] = 1;
            atual[i] = 1;
            tamanho_atual++;
            i++;

            if (i < n)
            {
                estado[i] = 0;
            }
        }
        else if (estado[i] == 1)
        {
            estado[i] = 2;
            atual[i] = 0;
            tamanho_atual--;
            i++;

            if (i < n)
            {
                estado[i] = 0;
            }
        }
        else
        {
            estado[i] = 0;
            i--;
        }
    }

    int quantidade = 0;

    for (int v = 0; v < n; v++)
    {
        if (melhor[v])
        {
            cobertura[quantidade++] = v;
        }
    }

    return quantidade;
}

int cobertura_gulosa(Aresta arestas[], int n, int m, int cobertura[])
{
    if (!arestas || n < 0 || n > MAX_VERTICES || m < 0 || m > MAX_ARESTAS || !cobertura)
    {
        return -1;
    }

    int removida[MAX_ARESTAS];

    for (int i = 0; i < m; i++)
    {
        removida[i] = 0;
    }

    int tamanho = 0;

    while (1)
    {
        int grau[MAX_VERTICES];

        for (int i = 0; i < MAX_VERTICES; i++)
        {
            grau[i] = 0;
        }

        int arestas_restantes = 0;

        for (int i = 0; i < m; i++)
        {
            if (!removida[i])
            {
                grau[arestas[i].u]++;
                grau[arestas[i].v]++;
                arestas_restantes++;
            }
        }

        if (arestas_restantes == 0)
        {
            break;
        }

        int melhor_v = -1;
        int maior_grau = 0;

        for (int v = 0; v < n; v++)
        {
            if (grau[v] > maior_grau)
            {
                maior_grau = grau[v];
                melhor_v = v;
            }
        }

        if (melhor_v == -1)
        {
            break;
        }

        cobertura[tamanho++] = melhor_v;

        for (int i = 0; i < m; i++)
        {
            if (!removida[i] && (arestas[i].u == melhor_v || arestas[i].v == melhor_v))
            {
                removida[i] = 1;
            }
        }
    }

    return tamanho;
}

int eh_cobertura(Aresta arestas[], int m, int cobertura[])
{
    if (!arestas || m < 0 || m > MAX_ARESTAS || !cobertura)
    {
        return -1;
    }

    for (int i = 0; i < m; i++)
    {
        if (arestas[i].u < 0 || arestas[i].u >= MAX_VERTICES || arestas[i].v < 0 || arestas[i].v >= MAX_VERTICES)
        {
            return -1;
        }

        if (!cobertura[arestas[i].u] && !cobertura[arestas[i].v])
        {
            return 0;
        }
    }

    return 1;
}
