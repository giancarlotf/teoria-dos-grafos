#include "agm.h"
#include <stdlib.h>

// Contexto do ambiente

GrafoListaPonderado *criar_grafo(int n)
{
    GrafoListaPonderado *grafo = (GrafoListaPonderado *)malloc(sizeof(GrafoListaPonderado));

    if (!grafo)
    {
        return NULL;
    }

    grafo->n = n;
    grafo->adj = (No **)malloc(n * sizeof(No *));

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
        No *atual = grafo->adj[u];

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
            No *no = (No *)malloc(sizeof(No));

            if (!no)
            {
                return;
            }

            no->destino = v;
            no->peso = peso;
            no->prox = grafo->adj[u];
            grafo->adj[u] = no;
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
        No *atual = grafo->adj[u];
        No *anterior = NULL;

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
        No *atual = grafo->adj[i];

        while (atual != NULL)
        {
            No *temp = atual;
            atual = atual->prox;

            free(temp);
        }
    }

    free(grafo->adj);
    free(grafo);
}

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
            {
                menor = esquerda;
            }

            if (direita < heap->tamanho && heap->dados[direita].distancia < heap->dados[menor].distancia)
            {
                menor = direita;
            }

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

// Implementação do código

int find(DSU *d, int x)
{
    if (d->pai[x] != x)
    {
        d->pai[x] = find(d, d->pai[x]);
    }

    return d->pai[x];
}

int unir(DSU *d, int x, int y)
{
    int raiz_x = find(d, x);
    int raiz_y = find(d, y);

    if (raiz_x == raiz_y)
    {
        return 0;
    }

    if (d->rank[raiz_x] < d->rank[raiz_y])
    {
        d->pai[raiz_x] = raiz_y;
    }
    else if (d->rank[raiz_x] > d->rank[raiz_y])
    {
        d->pai[raiz_y] = raiz_x;
    }
    else
    {
        d->pai[raiz_y] = raiz_x;
        d->rank[raiz_x]++;
    }

    return 1;
}

int comparar(const void *a, const void *b)
{
    Aresta *x = (Aresta *)a;
    Aresta *y = (Aresta *)b;
    return x->peso - y->peso;
}

Aresta *kruskal(GrafoListaPonderado *g, int *custo)
{
    if (!g || g->n <= 0)
    {
        return NULL;
    }

    int n = g->n;
    int m = 0;

    for (int i = 0; i < n; i++)
    {
        No *no = g->adj[i];

        while (no)
        {
            if (i < no->destino)
            {
                m++;
            }

            no = no->prox;
        }
    }

    if (m == 0)
    {
        return NULL;
    }

    Aresta *arestas = (Aresta *)malloc(m * sizeof(Aresta));

    if (!arestas)
    {
        return NULL;
    }

    int k = 0;

    for (int i = 0; i < n; i++)
    {
        No *no = g->adj[i];

        while (no)
        {
            if (i < no->destino)
            {
                arestas[k].u = i;
                arestas[k].v = no->destino;
                arestas[k].peso = no->peso;

                k++;
            }

            no = no->prox;
        }
    }

    qsort(arestas, k, sizeof(Aresta), comparar);

    Aresta *agm = (Aresta *)malloc(n * sizeof(Aresta));

    if (!agm)
    {
        free(arestas);
        return NULL;
    }

    DSU uf;
    uf.pai = (int *)malloc(n * sizeof(int));

    if (!uf.pai)
    {
        free(agm);
        free(arestas);
        return NULL;
    }

    uf.rank = (int *)calloc(n, sizeof(int));

    if (!uf.rank)
    {
        free(uf.pai);
        free(agm);
        free(arestas);
        return NULL;
    }

    uf.n = n;

    for (int i = 0; i < uf.n; i++)
    {
        uf.pai[i] = i;
    }

    int qtd_agm = 0;
    int custo_total = 0;

    for (int i = 0; i < k && qtd_agm < n - 1; i++)
    {
        if (unir(&uf, arestas[i].u, arestas[i].v))
        {
            agm[qtd_agm++] = arestas[i];
            custo_total += arestas[i].peso;
        }
    }

    if (qtd_agm != n - 1)
    {
        free(uf.rank);
        free(uf.pai);
        free(agm);
        free(arestas);
        return NULL;
    }

    agm[qtd_agm].u = -1;

    if (custo)
    {
        *custo = custo_total;
    }

    free(uf.rank);
    free(uf.pai);
    free(arestas);

    return agm;
}

Aresta *prim(GrafoListaPonderado *g, int origem, int *custo)
{
    if (custo)
    {
        *custo = 0;
    }

    if (!g || g->n <= 0 || g->n > MAX_VERTICES || origem < 0 || origem >= g->n)
    {
        return NULL;
    }

    int chave[MAX_VERTICES] = {0};
    int pai[MAX_VERTICES] = {0};

    for (int i = 0; i < g->n; i++)
    {
        chave[i] = INT_MAX;
        pai[i] = -1;
    }

    chave[origem] = 0;

    MinHeap *heap = criar_min_heap(g, origem);

    if (!heap)
    {
        return NULL;
    }

    while (heap->tamanho > 0)
    {
        NoHeap minimo = extrair_minimo(heap);
        int u = minimo.vertice;

        if (u == -1 || minimo.distancia == INT_MAX)
        {
            break;
        }

        No *no = g->adj[u];

        while (no != NULL)
        {
            int v = no->destino;
            int peso = no->peso;

            if (heap->posicao[v] != -1 && chave[v] > peso)
            {
                chave[v] = peso;
                pai[v] = u;

                diminuir_chave(heap, v, peso);
            }

            no = no->prox;
        }
    }

    liberar_min_heap(heap);

    for (int i = 0; i < g->n; i++)
    {
        if (i != origem && pai[i] == -1)
        {
            return NULL;
        }
    }

    Aresta *agm = (Aresta *)malloc(g->n * sizeof(Aresta));

    if (!agm)
    {
        return NULL;
    }

    int qtd_agm = 0;
    int custo_total = 0;

    for (int i = 0; i < g->n; i++)
    {
        if (pai[i] != -1)
        {
            agm[qtd_agm].u = pai[i];
            agm[qtd_agm].v = i;
            agm[qtd_agm].peso = chave[i];

            custo_total += chave[i];
            qtd_agm++;
        }
    }

    agm[qtd_agm].u = -1;

    if (custo)
    {
        *custo = custo_total;
    }

    return agm;
}
