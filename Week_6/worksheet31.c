#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#ifndef TYPE
#define TYPE int
#endif
# ifndef LT
# define LT(A, B) ((A) < (B))
# endif

struct data {
    int value;
    char* name;
};
struct AVLnode {
    TYPE value;
    struct AVLnode* left; /* Left child. */
    struct AVLnode* right; /* Right child. */
    int height;
};
struct AVLTree { /* Height-Balanced Binary Search Tree. */
    struct AVLnode* root;
    int cnt;
};

struct AVLTree* newAVLTree() {
    struct AVLTree* tree = malloc(sizeof(struct AVLTree));
    assert(tree != 0);
    tree->root = 0;
    tree->cnt = 0;
    return tree;
}
int _h(struct AVLnode* current)
{
    if (current == 0) return -1;  return current->height;
}
void _setHeight(struct AVLnode* current) {
    int lch = _h(current->left);
    int rch = _h(current->right);
    if (lch < rch) current->height = 1 + rch;
    else current->height = 1 + lch;
}
int _bf(struct AVLnode* current)
{
    return _h(current->right) - _h(current->left);
}
struct AVLnode* _rotateLeft(struct AVLnode* current) {
    struct AVLnode* newTop = current->right;
    current->right = newTop->left;
    newTop->left = current;
    _setHeight(current);
    _setHeight(newTop);
    return newTop;
}
struct AVLnode* _rotateRight(struct AVLnode* current) {
    struct AVLnode* newTop = current->left;
    current->left = newTop->right;
    newTop->right = current;
    _setHeight(current);
    _setHeight(newTop);
    return newTop;
}
struct AVLnode* _balance(struct AVLnode* current) {
    int cbf = _bf(current);
    if (cbf < -1) {
        if (_bf(current->left) > 0) // double rotation
            current->left = _rotateLeft(current->left);
        return _rotateRight(current); // single rotation
    }
    else if (cbf > 1) {
        if (_bf(current->right) < 0)
            current->right = _rotateRight(current->right);
        return _rotateLeft(current);
    }
    _setHeight(current);
    return current;
}


struct AVLnode* _AVLnodeAdd(struct AVLnode* current, TYPE newValue) {
    struct AVLnode* newnode;
    if (current == 0) {
        newnode = malloc(sizeof(struct AVLnode));
        assert(newnode != 0);
        newnode->value = newValue;
        newnode->left = newnode->right = 0;
        newnode->height = 0;
        return newnode;  //why don't we balance here ??
    }
    else if (LT(newValue, current->value)) {
        current->left = _AVLnodeAdd(current->left, newValue);
    }
    else {
        current->right = _AVLnodeAdd(current->right, newValue);
    }
    return _balance(current);    /* <-   NEW  the call on balance */
}
struct AVLnode* _removeLeftmost(struct AVLnode* cur) {
    struct AVLnode* temp;
    if (cur->left != 0)
    {
        cur->left = _removeLeftmost(cur->left);
        return _balance(cur);
    }
    temp = cur->right;
    free(cur);
    return temp;
}
int containsAVLTree(struct AVLTree* tree, TYPE val) {
    struct AVLnode* cur;
    cur = tree->root;
    while (cur != 0)
    {
        if (cur->value == val) return 1;
        else if (val < cur->value) cur = cur->left;
        else cur = cur->right;
    }
    return 0;
}
struct AVLnode* _removeNode(struct AVLnode* cur, TYPE val) {
    struct AVLnode* current;
    current = cur;
    while (current != 0)
    {
        if (current->value == val) {
            if (current->right == NULL) {
                return current->left;
            }
            else {
                current->value = _leftMost(current->right);
                current->right = _removeLeftmost(current->right);
            }
        }
        else if (val < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
}
void removeAVLTree(struct AVLTree* tree, TYPE val) {
    if (containsAVLTree(tree, val)) {
        tree->root = _removeNode(tree->root, val);
        tree->cnt--;
    }
}
TYPE _leftMost(struct AVLnode* cur) {
    while (cur->left != 0) {
        cur = cur->left;
    }
    return cur->value;
}
void print2DUtil(struct AVLnode* root, int space)
{
    // Base case 
    if (root == NULL)
        return;
    // Increase distance between levels 
    space += 10;
    // Process right child first 
    print2DUtil(root->right, space);
    // Print current node after space 
    // count 
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
    // Process left child 
    print2DUtil(root->left, space);
}
// Wrapper over print2DUtil() 
void print2D(struct AVLnode* root)
{
    // Pass initial space count as 0 
    print2DUtil(root, 0);
}

void addAVLTree(struct AVLTree* tree, TYPE val) {
    tree->root = _AVLnodeAdd(tree->root, val); /* call the recursive helper function */
    tree->cnt++;
}

int main(int argc, char* argv[])
{
    struct AVLTree* tree = newAVLTree();
    /*Create value of the type of data that you want to store*/

    printf("tree created\n");

    addAVLTree(tree, 1);
    addAVLTree(tree, 2);
    addAVLTree(tree, 3);
    // print2D(tree->root);
    // printTree(tree, printVal);
    printf("\n");
    addAVLTree(tree, 4);
    addAVLTree(tree, 5);
    print2D(tree->root);
    printf("tree->root->value %d", tree->root->value);
    //printf("\n");
    // _AVLnodeAdd(tree->root, &myData5.value);
    // print2D(tree->root);
    printf("\n");
    // _AVLnodeAdd(tree->root, &myData6.value);
    // _AVLnodeAdd(tree->root, &myData7.value);
    // _AVLnodeAdd(tree->root, &myData8.value);
    // print2D(tree->root);
    // printf("\n");
    // removeAVLTree(tree->root, &myData8.value);
    // removeAVLTree(tree->root, &myData4.value);
  //
    // print2D(tree->root);
    //printf("\n");
    return 1;
}