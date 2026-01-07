long long total, best;
const int MOD = 1000000007;

long long dfs(struct TreeNode* node) {
    if (!node) return 0;
    
    long long leftSum = dfs(node->left);
    long long rightSum = dfs(node->right);
    long long s = node->val + leftSum + rightSum;
    long long prod = s * (total - s);
    if (prod > best) best = prod;
    
    return s;
}

int maxProduct(struct TreeNode* root) {
    total = dfs(root); 
    best = 0;
    dfs(root);        
    return best % MOD;
}