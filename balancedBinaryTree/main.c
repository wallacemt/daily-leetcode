/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * struct TreeNode *left;
 * struct TreeNode *right;
 * };
 */

#include <stdlib.h>
#include <stdbool.h>

/**
 * Calcula a altura da árvore e verifica se está balanceada.
 * 
 * Retorna:
 *   - A altura da subárvore se balanceada
 *   - -1 se desbalanceada
 */
int dfs(struct TreeNode* node) {
    // Caso base: nó nulo tem altura 0
    if (node == NULL) {
        return 0;
    }

    // Calcula altura das subárvores esquerda e direita
    int leftHeight = dfs(node->left);
    int rightHeight = dfs(node->right);

    // Se alguma subárvore está desbalanceada, propaga -1
    if (leftHeight == -1 || rightHeight == -1) {
        return -1;
    }

    // Verifica se a diferença de altura excede 1
    if (abs(leftHeight - rightHeight) > 1) {
        return -1;
    }

    // Retorna a altura do nó atual
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

/**
 * Verifica se uma árvore binária está balanceada.
 * Uma árvore está balanceada se a diferença de altura entre
 * as subárvores esquerda e direita de qualquer nó é no máximo 1.
 */
bool isBalanced(struct TreeNode* root) {
    return dfs(root) != -1;
}