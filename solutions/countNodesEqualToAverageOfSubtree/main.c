#include <stdlib.h>

typedef struct {
    long long sum;
    int count;
} SubtreeInfo;

SubtreeInfo dfs(struct TreeNode* node, int* ans) {
    SubtreeInfo result = {0, 0};
    
    if (!node) {
        return result;
    }
     
    SubtreeInfo left = dfs(node->left, ans);
     
    SubtreeInfo right = dfs(node->right, ans);
     
    long long sum = left.sum + right.sum + node->val;
    int cnt = left.count + right.count + 1;
     
    if (sum / cnt == node->val) {
        (*ans)++;
    }
    
    result.sum = sum;
    result.count = cnt;
    
    return result;
}

int averageOfSubtree(struct TreeNode* root) {
    int ans = 0;
    dfs(root, &ans);
    return ans;
}