#include <stdlib.h>
#include <string.h>

typedef struct {
    int right;
    int left;
    int weight;
    int index;
} Interval;

typedef struct {
    long long score;
    int indices[4];
    int size;
} State;

int compareInterval(const void* a, const void* b) {
    Interval* x = (Interval*)a;
    Interval* y = (Interval*)b;

    if (x->right != y->right) {
        return x->right - y->right;
    }
    if (x->left != y->left) {
        return x->left - y->left;
    }
    return x->index - y->index;
}

// Verifica se a é lexicograficamente menor que b
int lexSmaller(State* a, State* b) {
    int limit = a->size < b->size ? a->size : b->size;

    for (int i = 0; i < limit; i++) {
        if (a->indices[i] != b->indices[i]) {
            return a->indices[i] < b->indices[i];
        }
    }

    return a->size < b->size;
}

// Retorna o melhor estado: maior score, ou lexicograficamente menor se empate
State better(State a, State b) {
    if (a.score > b.score) {
        return a;
    }
    if (b.score > a.score) {
        return b;
    }
    return lexSmaller(&a, &b) ? a : b;
}

// Insere valor mantendo ordem crescente
void insertSorted(State* state, int value) {
    int i = state->size;
    while (i > 0 && state->indices[i - 1] > value) {
        state->indices[i] = state->indices[i - 1];
        i--;
    }
    state->indices[i] = value;
    state->size++;
}

// Binary search: encontra primeiro elemento >= target
int lowerBound(int* arr, int end, int target) {
    int left = 0, right = end;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int* maximumWeight(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize) {
    int n = intervalsSize;

    // Cria array de intervalos com índices originais
    Interval* arr = malloc(sizeof(Interval) * n);
    for (int i = 0; i < n; i++) {
        arr[i].left = intervals[i][0];
        arr[i].right = intervals[i][1];
        arr[i].weight = intervals[i][2];
        arr[i].index = i;
    }

    // Ordena por ponto final (right)
    qsort(arr, n, sizeof(Interval), compareInterval);

    // Extrai pontos finais para binary search
    int* rightEnds = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        rightEnds[i] = arr[i].right;
    }

    // DP: previous[i] = melhor estado com i intervalos
    State* previous = calloc(n + 1, sizeof(State));

    // Itera para cada quantidade de intervalos selecionados (1 a 4)
    for (int selectedCount = 1; selectedCount <= 4; selectedCount++) {
        State* current = calloc(n + 1, sizeof(State));

        // DP: current[i] = melhor estado considerando primeiros i intervalos
        for (int i = 1; i <= n; i++) {
            // Opção 1: Skip o intervalo i-1
            State skip = current[i - 1];

            // Opção 2: Take o intervalo i-1
            // Encontra último intervalo que não sobrepõe
            int previousCount = lowerBound(rightEnds, i - 1, arr[i - 1].left);
            State take = previous[previousCount];
            take.score += arr[i - 1].weight;
            insertSorted(&take, arr[i - 1].index);

            // Escolhe melhor opção
            current[i] = better(skip, take);
        }

        free(previous);
        previous = current;
    }

    // Extrai resultado
    *returnSize = previous[n].size;
    int* result = malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        result[i] = previous[n].indices[i];
    }

    // Libera memória
    free(arr);
    free(rightEnds);
    free(previous);

    return result;
}