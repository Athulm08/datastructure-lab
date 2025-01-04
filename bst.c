#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *left;
    struct node *right;
    int data;
};

struct node *root = NULL; // Initialize root to NULL

struct node *newnode(int value) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

struct node *insert(struct node *root, int value) {
    if (root == NULL) {
        return newnode(value); // Create root node if root is NULL
    } else if (value == root->data) {
        printf("Same data can't be stored\n");
        return root;
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        root->left = insert(root->left, value);
    }
    return root;
}

void inorderTraversal(struct node *root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d->", root->data);
    inorderTraversal(root->right);
}

void preorderTraversal(struct node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d->", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(struct node *root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d->", root->data);
}

struct node *search(struct node *root, int key) {
    if (root == NULL) {
        printf("\nNOT FOUND\n");
        return NULL;
    } else if (root->data == key) {
        printf("\nFOUND\n");
        return root;
    } else if (root->data < key) {
        return search(root->right, key);
    } else {
        return search(root->left, key);
    }
}

struct node *minValueNode(struct node *root) {
    struct node *current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct node *deleteNode(struct node *root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main() {
    int opt;
    int value, searchv, key;
    do {
        printf("\n1) Insert Node \n2) Search\n3) Inorder Traversal\n4) Preorder Traversal\n5) Postorder Traversal\n6) Delete\n7) Exit\n");
        printf("Choose an option: ");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                printf("\nEnter a number: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("\nEnter a number to search: ");
                scanf("%d", &searchv);
                search(root, searchv);
                break;
            case 3:
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                preorderTraversal(root);
                printf("\n");
                break;
            case 5:
                postorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("\nEnter a number to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option!\n");
        }
    } while (opt != 7);
    return 0;
}
