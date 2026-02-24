void dfs(struct TreeNode* node, int current, int* ans) {
    if (!node) return;
    
    current = (current << 1) | node->val;
    if (!node->left && !node->right) {
        *ans += current;
        return;
    }
    
    dfs(node->left, current, ans);
    dfs(node->right, current, ans);
}

int sumRootToLeaf(struct TreeNode* root) {
    int ans = 0;
    dfs(root, 0, &ans);
    return ans;
}