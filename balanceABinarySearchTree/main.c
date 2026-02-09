int* vals;
int size = 0;
int capacity = 0;

void inorder(struct TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    if (size >= capacity) {
        capacity = capacity == 0 ? 10 : capacity * 2;
        vals = (int*)realloc(vals, capacity * sizeof(int));
    }
    vals[size++] = root->val;
    inorder(root->right);
}

struct TreeNode* build(int left, int right) {
    if (left > right) return NULL;

    int mid = (left + right) / 2;
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = vals[mid];

    root->left = build(left, mid - 1);
    root->right = build(mid + 1, right);

    return root;
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    vals = NULL;
    size = 0;
    capacity = 0;
    
    inorder(root);
    return build(0, size - 1);
}