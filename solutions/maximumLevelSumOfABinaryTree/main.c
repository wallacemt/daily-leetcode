#include <stdlib.h>
#include <limits.h>

int maxLevelSum(struct TreeNode* root) {
    if (root == NULL) return 0;

    
    int queueCapacity = 1024; // Começa com 1024
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * queueCapacity);
    
    if (queue == NULL) return 0;

    int front = 0, rear = 0;
    queue[rear++] = root;

    int level = 1;
    int maxSum = root->val; // Primeira soma como base
    int maxLevel = 1;

    while (front < rear) {
        int size = rear - front;
        long levelSum = 0; // Usar long para evitar overflow

        for (int i = 0; i < size; i++) {
            struct TreeNode* node = queue[front++];
            levelSum += node->val;

            if (node->left) {
                if (rear >= queueCapacity) {
                    queueCapacity *= 2;
                    struct TreeNode** temp = (struct TreeNode**)realloc(queue, sizeof(struct TreeNode*) * queueCapacity);
                    if (temp == NULL) {
                        free(queue);
                        return 0;
                    }
                    queue = temp;
                }
                queue[rear++] = node->left;
            }

            if (node->right) {
                if (rear >= queueCapacity) {
                    queueCapacity *= 2;
                    struct TreeNode** temp = (struct TreeNode**)realloc(queue, sizeof(struct TreeNode*) * queueCapacity);
                    if (temp == NULL) {
                        free(queue);
                        return 0;
                    }
                    queue = temp;
                }
                queue[rear++] = node->right;
            }
        }

        if (levelSum > maxSum) {
            maxSum = levelSum;
            maxLevel = level;
        }

        level++;
    }

    free(queue);
    return maxLevel;
}