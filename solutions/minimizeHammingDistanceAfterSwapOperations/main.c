#include <stdlib.h>
#include <string.h>

typedef struct {
    int index;
    int root;
} IndexRoot;

int find(int* parent, int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent, parent[x]); // Path compression recursivo
    }
    return parent[x];
}

void unite(int* parent, int* rank, int a, int b)
{
    int pa = find(parent, a);
    int pb = find(parent, b);

    if (pa == pb) return;

    if (rank[pa] < rank[pb])
    {
        parent[pa] = pb;
    }
    else if (rank[pa] > rank[pb])
    {
        parent[pb] = pa;
    }
    else
    {
        parent[pb] = pa;
        rank[pa]++;
    }
}

int cmp(const void* a, const void* b)
{
    return ((IndexRoot*)a)->root - ((IndexRoot*)b)->root;
}

int minimumHammingDistance(int* source, int sourceSize, int* target, int targetSize, 
                           int** allowedSwaps, int allowedSwapsSize, int* allowedSwapsColSize)
{
    int* parent = (int*)malloc(sizeof(int) * sourceSize);
    int* rank = (int*)malloc(sizeof(int) * sourceSize);
    
    memset(rank, 0, sizeof(int) * sourceSize);
    for (int i = 0; i < sourceSize; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < allowedSwapsSize; i++)
    {
        unite(parent, rank, allowedSwaps[i][0], allowedSwaps[i][1]);
    }

    // Usar struct para evitar variável global
    IndexRoot* indexRoots = (IndexRoot*)malloc(sizeof(IndexRoot) * sourceSize);
    for (int i = 0; i < sourceSize; i++)
    {
        indexRoots[i].index = i;
        indexRoots[i].root = find(parent, i);
    }

    qsort(indexRoots, sourceSize, sizeof(IndexRoot), cmp);

    int retval = 0;
    
    // Encontrar valor máximo dinamicamente
    int maxVal = 0;
    for (int i = 0; i < sourceSize; i++)
    {
        if (source[i] > maxVal) maxVal = source[i];
        if (target[i] > maxVal) maxVal = target[i];
    }

    int* count = (int*)calloc(maxVal + 1, sizeof(int));

    int start = 0;
    while (start < sourceSize)
    {
        int root = indexRoots[start].root;
        int end = start;

        // Encontrar fim do grupo
        while (end < sourceSize && indexRoots[end].root == root)
        {
            end++;
        }

        // Contar valores de source
        for (int i = start; i < end; i++)
        {
            count[source[indexRoots[i].index]]++;
        }

        for (int i = start; i < end; i++)
        {
            int targetVal = target[indexRoots[i].index];
            if (count[targetVal] > 0)
            {
                count[targetVal]--;
            }
            else
            {
                retval++;
            }
        }

        for (int i = start; i < end; i++)
        {
            count[source[indexRoots[i].index]] = 0;
        }

        start = end;
    }

    free(parent);
    free(rank);
    free(indexRoots);
    free(count);

    return retval;
}