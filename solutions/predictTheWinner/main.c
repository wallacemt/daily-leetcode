#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 21

 
int memo[MAX_SIZE][MAX_SIZE][2];
bool computed[MAX_SIZE][MAX_SIZE][2];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}
 
int getMaxDifference(int start, int end, int* nums, bool turn) {

    if (start > end)
        return 0;

    // Verificar cache
    if (computed[start][end][turn])
        return memo[start][end][turn];

    int result;

    if (turn) {
 
        int left = nums[start] + getMaxDifference(start + 1, end, nums, false);
        int right = nums[end] + getMaxDifference(start, end - 1, nums, false);
        result = max(left, right);
    } else {
    
        int left = getMaxDifference(start + 1, end, nums, true) - nums[start];
        int right = getMaxDifference(start, end - 1, nums, true) - nums[end];
        result = min(left, right);
    }
 
    memo[start][end][turn] = result;
    computed[start][end][turn] = true;

    return result;
}

bool predictTheWinner(int* nums, int numsSize) {
 
    memset(computed, false, sizeof(computed));
    memset(memo, 0, sizeof(memo));

    // Se a diferença for >= 0, Player 1 vence ou empata
    int difference = getMaxDifference(0, numsSize - 1, nums, true);
    return difference >= 0;
}