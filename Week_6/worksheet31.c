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

//worksheet 31 question
struct AVLnode* _rotateLeft(struct AVLnode* current) {
    struct AVLnode* newTop = current->right;
    current->right = newTop->left;
    newTop->left = current;
    _setHeight(current);
    _setHeight(newTop);
    return newTop;
}

//worksheet 31 question
struct AVLnode* _rotateRight(struct AVLnode* current) {
    struct AVLnode* newTop = current->left;
    current->left = newTop->right;
    newTop->right = current;
    _setHeight(current);
    _setHeight(newTop);
    return newTop;
}

//provided by worksheet 31
struct AVLnode* _balance(struct AVLnode* current) {
    
    printf("Trying to balance %d\n", current->value);
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

//provided by worksheet 31
TYPE _leftMost(struct AVLnode* cur) {
    while (cur->left != 0) {
        cur = cur->left;
    }
    return cur->value;
}

//referenced worksheet 29
//containsAVL tree will check to make sure this is not an empty tree
//after addition or removal of nodes, program needs to traverse up
// to the root node while balancing
struct AVLnode* _removeNode(struct AVLnode* current, TYPE val) {

    struct AVLnode * temp;
    
    if (current->value == val) { //base case, value found
        if (current->right == NULL) { //no right child so free current node, and return left child
            temp = current->left;
            free(current);
            return temp;
        }
        else { //has right child
            current->value = _leftMost(current->right);
            current->right = _removeLeftmost(current->right);
        }
    }
    else if (val < current->value) {
        current->left  = _removeNode(current->left,val);
    }
    else {
        current->right  = _removeNode(current->right,val);
    }
    
    printf("traversing up parent node, current->value: %d\n",current->value);
    return _balance(current);
}


//provided by AVL walk through lecture
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

//provided by worksheet 31
void removeAVLTree(struct AVLTree* tree, TYPE val) {
    if (containsAVLTree(tree, val)) {
        tree->root = _removeNode(tree->root, val);
        tree->cnt--;
    }
}

void addAVLTree(struct AVLTree* tree, TYPE val) {
    tree->root = _AVLnodeAdd(tree->root, val); /* call the recursive helper function */
    tree->cnt++;
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


int main(int argc, char* argv[])
{
    struct AVLTree* tree = newAVLTree();
    /*Create value of the type of data that you want to store*/

    printf("Tree created with keys:\n75,70,100,60,80,105,77,120\n");

    addAVLTree(tree, 75);
    addAVLTree(tree, 70);
    addAVLTree(tree, 100);
    addAVLTree(tree, 60);
    addAVLTree(tree, 80);
    addAVLTree(tree, 105);
    addAVLTree(tree, 77);
    addAVLTree(tree, 120);
    print2D(tree->root);
    printf("Current root: %d\n", tree->root->value);
    printf("=======================\n\n");
    

    printf("Removing key: 60\n");
    removeAVLTree(tree, 60);
    print2D(tree->root);
    printf("Current root: %d\n", tree->root->value);
    printf("=======================\n\n");
    
    printf("Adding key: 60\n");
    addAVLTree(tree, 60);
    print2D(tree->root);
    printf("Current root: %d\n", tree->root->value);
    printf("=======================\n\n");
    
    printf("Removing keys: 120, 60\n");
    removeAVLTree(tree, 120);
    removeAVLTree(tree, 60);
    print2D(tree->root);
    printf("Current root: %d\n", tree->root->value);
    printf("=======================\n\n");
    removeAVLTree(tree, 80);
    removeAVLTree(tree, 75);
    removeAVLTree(tree, 100);
    removeAVLTree(tree, 70);
    removeAVLTree(tree, 77);
    removeAVLTree(tree, 105);
    return 1;
}
