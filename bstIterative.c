#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Stack {
    struct Node* node;
    struct Stack* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

void push(struct Stack** top, struct Node* node) {
    struct Stack* newStack = (struct Stack*)malloc(sizeof(struct Stack));
    newStack->node = node;
    newStack->next = *top;
    *top = newStack;
}

struct Node* pop(struct Stack** top) {
    if (*top == NULL) return NULL;
    struct Stack* temp = *top;
    struct Node* node = temp->node;
    *top = temp->next;
    free(temp);
    return node;
}

int isEmpty(struct Stack* top) {
    return top == NULL;
}

void inorderIterative(struct Node* root) {
    struct Stack* stack = NULL;
    struct Node* curr = root;
    while (curr != NULL || !isEmpty(stack)) {
        while (curr != NULL) {
            push(&stack, curr);
            curr = curr->left;
        }
        curr = pop(&stack);
        printf("%d ", curr->data);
        curr = curr->right;
    }
}

void preorderIterative(struct Node* root) {
    if (root == NULL) return;
    struct Stack* stack = NULL;
    push(&stack, root);
    while (!isEmpty(stack)) {
        struct Node* curr = pop(&stack);
        printf("%d ", curr->data);
        if (curr->right) push(&stack, curr->right);
        if (curr->left) push(&stack, curr->left);
    }
}

void postorderIterative(struct Node* root) {
    if (root == NULL) return;
    struct Stack* stack1 = NULL;
    struct Stack* stack2 = NULL;
    push(&stack1, root);
    while (!isEmpty(stack1)) {
        struct Node* curr = pop(&stack1);
        push(&stack2, curr);
        if (curr->left) push(&stack1, curr->left);
        if (curr->right) push(&stack1, curr->right);
    }
    while (!isEmpty(stack2)) {
        struct Node* node = pop(&stack2);
        printf("%d ", node->data);
    }
}

int main() {
    struct Node* root = NULL;
    int n, value;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter %d values: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }
    printf("\nInorder Traversal (Iterative): ");
    inorderIterative(root);
    printf("\nPreorder Traversal (Iterative): ");
    preorderIterative(root);
    printf("\nPostorder Traversal (Iterative): ");
    postorderIterative(root);
    printf("\n");
    return 0;
}
