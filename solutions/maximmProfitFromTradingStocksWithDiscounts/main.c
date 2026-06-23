#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_NODES 165
#define INVALID_PROFIT -1000000000

typedef struct {
    int* present_prices;
    int* future_prices;
    int max_budget;
} StockData;

typedef struct {
    int head[MAX_NODES];
    int next[MAX_NODES];
    int target[MAX_NODES];
    int count;
} AdjacencyList;

static StockData g_stock_data;
static AdjacencyList g_graph;

static inline int max_int(int a, int b) {
    return a > b ? a : b;
}

static void initialize_profit_array(int* profit_array, int size) {
    for (int i = 0; i <= size; i++) {
        profit_array[i] = INVALID_PROFIT;
    }
}

static void add_tree_edge(int parent, int child) {
    g_graph.target[g_graph.count] = child;
    g_graph.next[g_graph.count] = g_graph.head[parent];
    g_graph.head[parent] = g_graph.count++;
}

static void combine_child_profits(int* accumulated, int* child_result, int* temp_buffer) {
    initialize_profit_array(temp_buffer, g_stock_data.max_budget);

    for (int budget1 = 0; budget1 <= g_stock_data.max_budget; budget1++) {
        if (accumulated[budget1] == INVALID_PROFIT) continue;
        
        int remaining_budget = g_stock_data.max_budget - budget1;
        for (int budget2 = 0; budget2 <= remaining_budget; budget2++) {
            if (child_result[budget2] == INVALID_PROFIT) continue;
            
            int combined_budget = budget1 + budget2;
            int combined_profit = accumulated[budget1] + child_result[budget2];
            
            if (combined_profit > temp_buffer[combined_budget]) {
                temp_buffer[combined_budget] = combined_profit;
            }
        }
    }
    
    memcpy(accumulated, temp_buffer, (g_stock_data.max_budget + 1) * sizeof(int));
}

static void apply_stock_purchase(int* result, int* base_profits, int stock_idx, int discount_percent) {
    int original_price = g_stock_data.present_prices[stock_idx];
    int purchase_price = (discount_percent == 50) ? original_price / 2 : original_price;
    int profit = g_stock_data.future_prices[stock_idx] - purchase_price;
    
    if (purchase_price > g_stock_data.max_budget) return;
    
    for (int budget = 0; budget <= g_stock_data.max_budget - purchase_price; budget++) {
        if (base_profits[budget] == INVALID_PROFIT) continue;
        
        int new_budget = budget + purchase_price;
        int total_profit = base_profits[budget] + profit;
        
        if (total_profit > result[new_budget]) {
            result[new_budget] = total_profit;
        }
    }
}

static void compute_subtree_profits(int node, int* profit_without_purchase, int* profit_with_discount) {
    int no_purchase_acc[MAX_NODES];
    int with_discount_acc[MAX_NODES];
    int temp_buffer[MAX_NODES];
    
    initialize_profit_array(no_purchase_acc, g_stock_data.max_budget);
    initialize_profit_array(with_discount_acc, g_stock_data.max_budget);
    no_purchase_acc[0] = 0;
    with_discount_acc[0] = 0;

    for (int edge = g_graph.head[node]; edge != -1; edge = g_graph.next[edge]) {
        int child = g_graph.target[edge];
        
        int child_no_purchase[MAX_NODES];
        int child_with_discount[MAX_NODES];
        
        compute_subtree_profits(child, child_no_purchase, child_with_discount);
        
        combine_child_profits(no_purchase_acc, child_no_purchase, temp_buffer);
        combine_child_profits(with_discount_acc, child_with_discount, temp_buffer);
    }

    memcpy(profit_without_purchase, no_purchase_acc, (g_stock_data.max_budget + 1) * sizeof(int));
    memcpy(profit_with_discount, no_purchase_acc, (g_stock_data.max_budget + 1) * sizeof(int));

    apply_stock_purchase(profit_without_purchase, with_discount_acc, node, 0);
    apply_stock_purchase(profit_with_discount, with_discount_acc, node, 50);
}

int maxProfit(int n, int* present, int presentSize, int* future, int futureSize, 
              int** hierarchy, int hierarchySize, int* hierarchyColSize, int budget) {
    
    g_stock_data.present_prices = present;
    g_stock_data.future_prices = future;
    g_stock_data.max_budget = budget;
    
    g_graph.count = 0;
    memset(g_graph.head, -1, sizeof(g_graph.head));
    
    for (int i = 0; i < hierarchySize; i++) {
        add_tree_edge(hierarchy[i][0] - 1, hierarchy[i][1] - 1);
    }
    
    int root_profit_no_purchase[MAX_NODES];
    int root_profit_with_discount[MAX_NODES];
    
    compute_subtree_profits(0, root_profit_no_purchase, root_profit_with_discount);
    
    int max_profit = 0;
    for (int i = 0; i <= budget; i++) {
        max_profit = max_int(max_profit, root_profit_no_purchase[i]);
    }
    
    return max_profit;
}