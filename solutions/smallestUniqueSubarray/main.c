#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint64_t key;
    int8_t state; // 0: vazio, 1: visto uma vez, 2: duplicado
} HashEntry;

// Função de hash robusta para as chaves (Rolling Hash já é disperso, mas isso ajuda)
static inline uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

int smallestUniqueSubarray(int* nums, int numsSize) {
    int low = 1, high = numsSize;
    int ans = -1;

    // Usaremos um módulo de 64 bits para evitar colisões (Mersenne Prime 2^61 - 1)
    const __int128 mod = (1ULL << 61) - 1;
    const __int128 base = 100019; // Primo maior que o range de nums

    int capacity = 1;
    while (capacity < 2.5 * numsSize) capacity <<= 1;
    HashEntry* table = malloc(capacity * sizeof(HashEntry));

    while (low <= high) {
        int mid = low + (high - low) / 2;
        memset(table, 0, capacity * sizeof(HashEntry));
        
        int unique_count = 0;
        __int128 current_hash = 0;
        __int128 p_mid = 1;

        // Pré-calcula base^(mid-1) % mod
        for (int i = 0; i < mid - 1; i++) p_mid = (p_mid * base) % mod;

        for (int i = 0; i < numsSize; i++) {
            // Rolling Hash: Adiciona novo elemento
            current_hash = (current_hash * base + nums[i]) % mod;
            
            if (i >= mid) {
                // Remove elemento que saiu da janela
                __int128 term = (nums[i - mid] * (p_mid * base % mod)) % mod;
                current_hash = (current_hash - term + mod) % mod;
            }

            if (i >= mid - 1) {
                uint64_t key = (uint64_t)current_hash;
                uint64_t h = splitmix64(key);
                int idx = h & (capacity - 1);

                while (table[idx].state != 0 && table[idx].key != key) {
                    idx = (idx + 1) & (capacity - 1);
                }

                if (table[idx].state == 0) {
                    table[idx].key = key;
                    table[idx].state = 1;
                    unique_count++;
                } else if (table[idx].state == 1) {
                    table[idx].state = 2;
                    unique_count--;
                }
            }
        }

        if (unique_count > 0) {
            ans = mid;
            high = mid - 1; // Tenta um comprimento menor
        } else {
            low = mid + 1;
        }
    }

    free(table);
    return ans;
}