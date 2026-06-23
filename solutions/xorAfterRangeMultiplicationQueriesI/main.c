int xorAfterQueries(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    const int mod = 1000000007;
    int res = 0;

    // Pré-calcular XOR inicial
    for (int i = 0; i < numsSize; i++) {
        res ^= nums[i];
    }

    // Processar queries
    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        int k = queries[i][2];
        long long v = queries[i][3]; // Converter para long long aqui

        for (int idx = l; idx <= r; idx += k) {
            // Remover XOR antigo
            res ^= nums[idx];
            
            // Atualizar valor
            nums[idx] = (nums[idx] * v) % mod;
            
            // Adicionar XOR novo
            res ^= nums[idx];
        }
    }

    return res;
}