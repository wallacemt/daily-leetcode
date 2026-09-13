#include <stdlib.h>

int largestOverlap(int** img1, int img1Size, int* img1ColSize, 
                   int** img2, int img2Size, int* img2ColSize) {
    int n = img1Size;
    
    // Extrai coordenadas dos 1s (máximo n²)
    int* i1arr = (int*)malloc(n * n * sizeof(int));
    int* j1arr = (int*)malloc(n * n * sizeof(int));
    int* i2arr = (int*)malloc(n * n * sizeof(int));
    int* j2arr = (int*)malloc(n * n * sizeof(int));
    
    int k1 = 0, k2 = 0;
    
    // Primeira passagem: extrai coordenadas
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (img1[i][j] == 1) {
                i1arr[k1] = i;
                j1arr[k1] = j;
                k1++;
            }
            if (img2[i][j] == 1) {
                i2arr[k2] = i;
                j2arr[k2] = j;
                k2++;
            }
        }
    }
    
    // Se uma imagem não tem 1s, não há overlap
    if (k1 == 0 || k2 == 0) {
        free(i1arr);
        free(j1arr);
        free(i2arr);
        free(j2arr);
        return 0;
    }
    
    // Array 2D para contar translações
    // Offset = n-1 para centralizar (translações variam de -(n-1) a +(n-1))
    int offset = n - 1;
    int size = 2 * n - 1;
    int* count = (int*)calloc(size * size, sizeof(int));
    
    int best = 0;
    
    // Segunda passagem: calcula translações (O(k1 * k2))
    for (int a = 0; a < k1; a++) {
        for (int b = 0; b < k2; b++) {
            // Translação: quanto img2 precisa se mover
            int dx = i2arr[b] - i1arr[a] + offset;
            int dy = j2arr[b] - j1arr[a] + offset;
            
            // Acesso direto O(1)
            int idx = dx * size + dy;
            count[idx]++;
            
            if (count[idx] > best) {
                best = count[idx];
            }
        }
    }
    
    // Libera memória
    free(i1arr);
    free(j1arr);
    free(i2arr);
    free(j2arr);
    free(count);
    
    return best;
}