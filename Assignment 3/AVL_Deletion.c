#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int getHeight(struct Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

struct Node *createNode(int key) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

void displayTree(struct Node* root, int space) {
    int i;

    if (root == NULL)
        return;

    space += 10;

    displayTree(root->right, space);

    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    displayTree(root->left, space);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalanceFactor(struct Node *n) {
    if (n == NULL)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return y;
}

struct Node *insert(struct Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    if (bf > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    if (bf < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    if (bf > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (bf < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

struct Node* delete(struct Node* root, int k) {
    if (root == NULL)
        return root;
    //finds where element is in tree recursively
    if (k < root->key)
        root->left = delete(root->left, k);
    else if (k > root->key)
        root->right = delete(root->right, k);
    else {
        //if element is found
        //if one of the children is empty, then shift left or right child up to be parent
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        //both children are present
        struct Node* succParent = root;
        struct Node* succ = root->right;
        //find the inorder successor
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }
        //if the successor exists, then delete it by replacing it with its right child
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
        //put successor's data into root, thereby deleting the value that was in the root
        root->key = succ->key;
        free(succ);
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int isbal = getBalanceFactor(root);
    //for left left case, the tree needs to be right rotated once
    if (isbal > 1 && getBalanceFactor(root->left) > 0) {
        return rightRotate(root);
    }
    //for right right case, the tree needs to be left rotated once
    if (isbal < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }
    //for left right case, the tree needs to be rotated left then right
    if (isbal > 1 && getBalanceFactor(root->left) <= 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //for right left case, the tree needs to be rotated right then left
    if (isbal < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    //this is similar to the insert function
    return root;
}

int main()
{
    struct Node * root = NULL, *temp;
    int elm, menu;

    while(1){
      printf("\n0. exit, 1. initialize, 2. insert, 3. delete, 4. display. \n ");
      printf("Input Choice: ");
          scanf("%d", &menu);

          switch(menu){
           case 0: exit(0);

           case 1: root = NULL;
                   break;

           case 2: printf("Give element to insert: ");
                   scanf("%d", &elm);
                   root = insert(root, elm);
                   break;

           case 3: printf("Give element to delete: ");
                   scanf("%d", &elm);
                   delete(root, elm);
                   break;

           case 4:  if (root == NULL) printf("Tree empty\n");
	                displayTree(root, 15);
                    printf("\n\n");
                    break;

           default: printf("Wrong choice\n");
         }
        }

    return 0;
}
