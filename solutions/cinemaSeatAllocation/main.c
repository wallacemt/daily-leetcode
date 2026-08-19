#include <stdlib.h>

// Comparador corrigido: retorna -1, 0, 1
int cmpFunc(const void* a, const void* b) {
    int **aa = (int**)a, **bb = (int**)b;
    
    if ((*aa)[0] != (*bb)[0]) {
        return (*aa)[0] < (*bb)[0] ? -1 : 1;
    }
    return (*aa)[1] < (*bb)[1] ? -1 : 1;
}

int maxNumberOfFamilies(
    int n, int** reserved, int reservedSize, int* reservedColSize
) {
    int result = 0;
    
    if (reservedSize == 0) {
        return (n / 2) * 2;
    }

    // Máscaras pré-calculadas (constantes)
    const int MASK_ALL = 0b1111111111;      // Todos os 10 assentos
    const int MASK_2345 = 0b0000011110;     // Assentos 2,3,4,5
    const int MASK_4567 = 0b0001111000;     // Assentos 4,5,6,7
    const int MASK_6789 = 0b0111100000;     // Assentos 6,7,8,9
    const int MASK_VALID = 0b0111111110;    // Assentos 2-9 (válidos)

    // Sort the reserved seats
    qsort(reserved, reservedSize, sizeof(int*), cmpFunc);

    int last_row = 0;
    int i = 0;

    while (i < reservedSize) {
        int curr_row = reserved[i][0];

        // Contar linhas vazias desde last_row até curr_row
        if (curr_row > last_row + 1) {
            result += (curr_row - last_row - 1) * 2;
        } 
        int mark = MASK_ALL;
        while (i < reservedSize && reserved[i][0] == curr_row) {
            mark &= ~(1 << (reserved[i][1] - 1));
            i++;
        }
 
        if ((mark & MASK_2345) == MASK_2345 && (mark & MASK_6789) == MASK_6789) {
            result += 2;
        } else if ((mark & MASK_2345) == MASK_2345 || 
                   (mark & MASK_4567) == MASK_4567 || 
                   (mark & MASK_6789) == MASK_6789) {
            result += 1;
        }

        last_row = curr_row;
    }
 
    result += (n - last_row) * 2;

    return result;
}