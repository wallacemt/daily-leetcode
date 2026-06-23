struct TreeNode* createNode(int val) {
    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* createBinaryTree(
    int** descriptions,
    int descriptionsSize,
    int* descriptionsColSize
) {
    if (descriptionsSize == 0) return NULL;
    
    struct TreeNode* nodes[100001] = {0};
    bool children[100001] = {0};
    
    int root_val = descriptions[0][0];
    
    for (int i = 0; i < descriptionsSize; i++) {
        int parent = descriptions[i][0];
        int child = descriptions[i][1];
        int isLeft = descriptions[i][2];
        
        if (nodes[parent] == NULL)
            nodes[parent] = createNode(parent);
        if (nodes[child] == NULL)
            nodes[child] = createNode(child);
        
        children[child] = true;
        root_val = parent; 
        
        if (isLeft)
            nodes[parent]->left = nodes[child];
        else
            nodes[parent]->right = nodes[child];
    }
    
    struct TreeNode* root = NULL;
    for (int i = 0; i < descriptionsSize; i++) {
        int parent = descriptions[i][0];
        if (!children[parent]) {
            root = nodes[parent];
            break;
        }
    }
    
    return root;
}