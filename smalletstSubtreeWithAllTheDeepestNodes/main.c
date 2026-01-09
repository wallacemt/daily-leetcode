struct Pair {
    int depth;
    struct TreeNode* node;
};

struct Pair dfs(struct TreeNode* root) {

    if (!root) return (struct Pair){0, NULL};
    
    struct Pair left = dfs(root->left);
    struct Pair right = dfs(root->right);
    
    int leftDepth = left.depth;
    int rightDepth = right.depth;
    
    if (leftDepth > rightDepth) {
        return (struct Pair){leftDepth + 1, left.node};
    } else if (rightDepth > leftDepth) {
        return (struct Pair){rightDepth + 1, right.node};
    } else {
      
        return (struct Pair){leftDepth + 1, root};
    }
}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    return dfs(root).node;
}