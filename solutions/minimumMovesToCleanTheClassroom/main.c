#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int r, c, e, mask;
} State;

int minMoves(char** classroom, int classroomSize, int energy) {
    if (!classroom || classroomSize <= 0) {
        return -1;
    }

    int m = classroomSize;
    int n = strlen(classroom[0]);

    if (n <= 0) {
        return -1;
    }

    int sr = -1, sc = -1;
    int litR[10], litC[10], numL = 0;

    // Encontrar posição inicial e lixo
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c = classroom[i][j];
            if (c == 'S') {
                sr = i;
                sc = j;
            } else if (c == 'L' && numL < 10) {
                litR[numL] = i;
                litC[numL] = j;
                numL++;
            }
        }
    }

    if (numL == 0) {
        return 0;
    }

    if (sr == -1) {
        return -1;
    }

    int fullMask = (1 << numL) - 1;
    int maskCount = 1 << numL;

    // Mapear índices de lixo
    int litIdx[20][20];
    memset(litIdx, -1, sizeof(litIdx));
    for (int i = 0; i < numL; i++) {
        litIdx[litR[i]][litC[i]] = i;
    }
 
    long long maxStates = (long long)m * n * (energy + 1) * maskCount;
    
    // Limitar alocação se muito grande
    if (maxStates > 100000000LL) {
        return -1;
    }

    char* visited = (char*)calloc(maxStates, sizeof(char));
    if (!visited) {
        return -1;
    }

    State* queue = (State*)malloc(sizeof(State) * maxStates);
    if (!queue) {
        free(visited);
        return -1;
    }

    int qHead = 0, qTail = 0;

    // Macro para calcular índice
    #define IDX(r, c, e, mask) \
        ((long long)(((long long)(r) * n + (c)) * (energy + 1) + (e)) * maskCount + (mask))

    visited[IDX(sr, sc, energy, 0)] = 1;
    queue[qTail++] = (State){sr, sc, energy, 0};

    int dr[4] = {0, 0, 1, -1};
    int dc[4] = {1, -1, 0, 0};
    int moves = 0;

    while (qHead < qTail) {
        int sz = qTail - qHead;
        moves++;

        for (int k = 0; k < sz; k++) {
            State cur = queue[qHead++];
            int r = cur.r, c = cur.c, e = cur.e, mask = cur.mask;

            if (e == 0) {
                continue;
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                    continue;
                }

                char ch = classroom[nr][nc];
                if (ch == 'X') {
                    continue;
                }

                int ne = e - 1;
                int nmask = mask;

                if (litIdx[nr][nc] != -1) {
                    nmask |= (1 << litIdx[nr][nc]);
                }

                if (ch == 'R') {
                    ne = energy;
                }

                if (nmask == fullMask) {
                    free(visited);
                    free(queue);
                    return moves;
                }

                long long id = IDX(nr, nc, ne, nmask);
                if (!visited[id]) {
                    visited[id] = 1;
                    queue[qTail++] = (State){nr, nc, ne, nmask};
                }
            }
        }
    }

    free(visited);
    free(queue);
    return -1;
}