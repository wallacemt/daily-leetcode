int cmp(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);  // Ordem decrescente
}

int minimumCost(int* cost, int costSize) {
    qsort(cost, costSize, sizeof(int), cmp);
    
    int total = 0;
    
    // Iteração forward com step de 3
    for (int i = 0; i < costSize; i += 3) {
        total += cost[i];
        if (i + 1 < costSize) {
            total += cost[i + 1];
        }
        // Pula o terceiro (gratuito)
    }
    
    return total;
}