#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

// Contexto do ambiente

GrafoListaPonderado *criar_grafo(int n)
{
    GrafoListaPonderado *grafo = (GrafoListaPonderado *)malloc(sizeof(GrafoListaPonderado));
    grafo->n = n;
    grafo->adj = (Aresta **)malloc(n * sizeof(Aresta *));

    for (int i = 0; i < n; i++)
    {
        grafo->adj[i] = NULL;
    }

    return grafo;
}

void inserir_arco(GrafoListaPonderado *grafo, int u, int v, int peso)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        int sao_adjacentes = 0;
        Aresta *atual = grafo->adj[u];

        while (atual != NULL)
        {
            if (atual->destino == v)
            {
                sao_adjacentes = 1;
                break;
            }

            atual = atual->prox;
        }

        if (sao_adjacentes == 0)
        {
            Aresta *aresta = (Aresta *)malloc(sizeof(Aresta));

            if (!aresta)
            {
                return;
            }

            aresta->destino = v;
            aresta->peso = peso;
            aresta->prox = grafo->adj[u];
            grafo->adj[u] = aresta;
        }
    }
}

void inserir_aresta(GrafoListaPonderado *grafo, int u, int v, int peso)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        inserir_arco(grafo, u, v, peso);
        inserir_arco(grafo, v, u, peso);
    }
}

void remover_arco(GrafoListaPonderado *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        Aresta *atual = grafo->adj[u];
        Aresta *anterior = NULL;

        while (atual != NULL && atual->destino != v)
        {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual != NULL)
        {
            (anterior == NULL) ? (grafo->adj[u] = atual->prox) : (anterior->prox = atual->prox);
            free(atual);
        }
    }
}

void remover_aresta(GrafoListaPonderado *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        remover_arco(grafo, u, v);
        remover_arco(grafo, v, u);
    }
}

void liberar_grafo(GrafoListaPonderado *grafo)
{
    if (grafo == NULL)
        return;

    for (int i = 0; i < grafo->n; i++)
    {
        Aresta *atual = grafo->adj[i];

        while (atual != NULL)
        {
            Aresta *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(grafo->adj);
    free(grafo);
}

// Implementação do código

MinHeap *criar_min_heap(GrafoListaPonderado *grafo, int origem)
{
    if (!grafo || grafo->n < 0)
    {
        return NULL;
    }

    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));

    if (!heap)
    {
        return NULL;
    }

    heap->capacidade = grafo->n;
    heap->tamanho = grafo->n;

    heap->dados = (NoHeap *)malloc(grafo->n * sizeof(NoHeap));

    if (!heap->dados)
    {
        free(heap);
        return NULL;
    }

    heap->posicao = (int *)malloc(grafo->n * sizeof(int));

    if (!heap->posicao)
    {
        free(heap->dados);
        free(heap);
        return NULL;
    }

    for (int i = 0; i < grafo->n; i++)
    {
        heap->dados[i].distancia = INT_MAX;
        heap->dados[i].vertice = i;
        heap->posicao[i] = i;
    }

    heap->dados[origem].distancia = 0;

    diminuir_chave(heap, origem, 0);

    return heap;
}

NoHeap extrair_minimo(MinHeap *heap)
{
    NoHeap vazio = {-1, INT_MAX};

    if (heap == NULL || heap->tamanho <= 0)
    {
        return vazio;
    }

    NoHeap minimo = heap->dados[0];

    heap->posicao[minimo.vertice] = -1;
    heap->tamanho--;

    if (heap->tamanho > 0)
    {
        heap->dados[0] = heap->dados[heap->tamanho];
        heap->posicao[heap->dados[0].vertice] = 0;

        int i = 0;

        while (1)
        {
            int menor = i;
            int esquerda = 2 * i + 1;
            int direita = 2 * i + 2;

            if (esquerda < heap->tamanho && heap->dados[esquerda].distancia < heap->dados[menor].distancia)
                menor = esquerda;

            if (direita < heap->tamanho && heap->dados[direita].distancia < heap->dados[menor].distancia)
                menor = direita;

            if (menor == i)
            {
                break;
            }

            NoHeap aux = heap->dados[i];
            heap->dados[i] = heap->dados[menor];
            heap->dados[menor] = aux;

            heap->posicao[heap->dados[i].vertice] = i;
            heap->posicao[heap->dados[menor].vertice] = menor;

            i = menor;
        }
    }

    return minimo;
}

void diminuir_chave(MinHeap *heap, int vertice, int distancia)
{
    int i = heap->posicao[vertice];

    if (i == -1)
    {
        return;
    }

    heap->dados[i].distancia = distancia;

    while (i > 0 && heap->dados[(i - 1) / 2].distancia > heap->dados[i].distancia)
    {
        int pos_a = heap->posicao[heap->dados[i].vertice];
        int pos_b = heap->posicao[heap->dados[(i - 1) / 2].vertice];

        heap->posicao[heap->dados[i].vertice] = pos_b;
        heap->posicao[heap->dados[(i - 1) / 2].vertice] = pos_a;

        NoHeap aux = heap->dados[i];
        heap->dados[i] = heap->dados[(i - 1) / 2];
        heap->dados[(i - 1) / 2] = aux;

        i = (i - 1) / 2;
    }
}

void liberar_min_heap(MinHeap *heap)
{
    if (!heap)
    {
        return;
    }

    free(heap->posicao);
    free(heap->dados);
    free(heap);
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred)
{
    MinHeap *heap = criar_min_heap(g, origem);

    if (!heap)
    {
        return;
    }

    for (int v = 0; v < g->n; v++)
    {

        dist[v] = INT_MAX;
        pred[v] = -1;
    }

    dist[origem] = 0;

    while (heap->tamanho > 0)
    {
        NoHeap no = extrair_minimo(heap);
        int u = no.vertice;

        if (u == -1 || dist[u] == INT_MAX)
        {
            break;
        }

        Aresta *aresta = g->adj[u];

        while (aresta != NULL)
        {
            int v = aresta->destino;
            int peso = aresta->peso;

            if (heap->posicao[v] != -1 && dist[u] != INT_MAX && dist[v] > dist[u] + peso)
            {
                dist[v] = dist[u] + peso;
                pred[v] = u;

                diminuir_chave(heap, v, dist[v]);
            }

            aresta = aresta->prox;
        }
    }

    liberar_min_heap(heap);
}

void reconstruir_caminho(int origem, int destino, int *pred)
{
    if (origem == destino)
    {
        printf("%d", origem);
        return;
    }

    if (pred[destino] == -1)
    {
        puts("Caminho inexistente\n");
        return;
    }

    reconstruir_caminho(origem, pred[destino], pred);
    printf(" -> %d", destino);
}
