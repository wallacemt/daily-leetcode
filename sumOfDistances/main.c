#define MOD 1000000007 
#define HTMOD 100000049 

enum {VAL,INDEX,NEXT};
#define ESIZE 3

void insertht(int *ht, int htSize, int (*nodes)[ESIZE], int node);
int hash(int n, int size);

long long* distance(int* nums, int numsSize, int* returnSize) {
    int n = numsSize, htSize = (n << 1) + 1;
    int *ht = (int *) malloc(htSize * sizeof(int));
    int (*nodes)[ESIZE] = (int (*)[ESIZE]) malloc((n + 1) * ESIZE * sizeof(int));
    
    memset(ht, -1, htSize * sizeof(int));
    
    // Pré-alocar espaço para prefixSum reutilizável
    long long *prefSum = (long long *) malloc((n + 1) * sizeof(long long));
    long long *ans = (long long *) malloc(n * sizeof(long long));
    
    // Inicializar ans com -1 corretamente
    for (int i = 0; i < n; ++i) {
        ans[i] = -1;
    }
    
    // Construir hash table
    for (int node = 0; node < n; ++node) {
        nodes[node][VAL] = nums[node];
        nodes[node][INDEX] = node;
        insertht(ht, htSize, nodes, node);
    }
    
    int *arr = (int *) malloc(n * sizeof(int));
    
    for (int i = 0; i < n; ++i) {
        if (ans[i] < 0) {
            int e = n, sz = 0;
            int node = ht[hash(nums[i], htSize)];
            
            // Coletar índices
            while (node >= 0) {
                if (nodes[node][VAL] == nums[i]) {
                    int j = nodes[node][INDEX];
                    arr[--e] = j;
                    ++sz;
                }
                node = nodes[node][NEXT];
            }
            
            int *indexes = &arr[e];
            
            // Calcular prefix sum
            prefSum[0] = 0;
            for (int j = 0; j < sz; ++j) {
                prefSum[j + 1] = prefSum[j] + indexes[j];
            }
            
            // Calcular distâncias
            long long totalSum = prefSum[sz];
            for (int j = 0; j < sz; ++j) {
                long long k = indexes[j];
                long long val = k * j - prefSum[j];
                val += (totalSum - prefSum[j + 1] - k * (sz - j - 1));
                ans[k] = val;
            }
        }
    }
    
    free(arr);
    free(prefSum);
    free(nodes);
    free(ht);
    
    *returnSize = n;
    return ans;
}

int hash(int n, int size) {
    long long h = ((long long) n + MOD) % HTMOD;
    return h % size;
}

void insertht(int *ht, int htSize, int (*nodes)[ESIZE], int node) {
    int index = hash(nodes[node][VAL], htSize);
    nodes[node][NEXT] = ht[index];
    ht[index] = node;
}