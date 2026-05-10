#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->tree_node = tree_node;
    node->next = NULL;
    if (q->rear) {
        q->rear->next = node;
    } else {
        q->front = node;
    }
    q->rear = node;
}

TreeNode* dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    QueueNode *front = q->front;
    TreeNode *tn = front->tree_node;
    q->front = front->next;
    if (q->front == NULL) q->rear = NULL;
    free(front);
    return tn;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    if (size <= 0 || level_order[0] == INT_MIN) return NULL;

    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = level_order[0];
    root->left = NULL;
    root->right = NULL;

    Queue *q = create_queue();
    enqueue(q, root);

    int i = 1;
    while (!is_empty(q) && i < size) {
        TreeNode *cur = dequeue(q);

        // 左孩子
        if (i < size && level_order[i] != INT_MIN) {
            cur->left = (TreeNode*)malloc(sizeof(TreeNode));
            cur->left->val = level_order[i];
            cur->left->left = NULL;
            cur->left->right = NULL;
            enqueue(q, cur->left);
        }
        i++;

        // 右孩子
        if (i < size && level_order[i] != INT_MIN) {
            cur->right = (TreeNode*)malloc(sizeof(TreeNode));
            cur->right->val = level_order[i];
            cur->right->left = NULL;
            cur->right->right = NULL;
            enqueue(q, cur->right);
        }
        i++;
    }

    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    if (root) {
        printf("%d ", root->val);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void preorder_traversal_iterative(TreeNode *root) {
    // 使用简单的数组作为栈
    if (!root) return;

    TreeNode *stack[256];
    int top = 0;
    stack[top++] = root;

    while (top > 0) {
        TreeNode *cur = stack[--top];
        printf("%d ", cur->val);

        // 先右后左（栈是 LIFO）
        if (cur->right)
            stack[top++] = cur->right;
        if (cur->left)
            stack[top++] = cur->left;
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
