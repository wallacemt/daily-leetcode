#include <stdint.h>

/**
 * Calcula o custo mínimo para satisfazer as necessidades de dois itens.
 * cost1, cost2: custos individuais.
 * costBoth: custo para um de cada.
 */
long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
    
    if ((long long)cost1 + cost2 <= costBoth) {
        return (long long)need1 * cost1 + (long long)need2 * cost2;
    } 
    int common = (need1 < need2) ? need1 : need2;
    long long totalCost = (long long)common * costBoth;
 
    int remain1 = need1 - common;
    int remain2 = need2 - common;
 
    int effectiveCost1 = (cost1 < costBoth) ? cost1 : costBoth;
    int effectiveCost2 = (cost2 < costBoth) ? cost2 : costBoth;

    totalCost += (long long)remain1 * effectiveCost1;
    totalCost += (long long)remain2 * effectiveCost2;

    return totalCost;
}