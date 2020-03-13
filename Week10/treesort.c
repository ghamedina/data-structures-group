#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "DynArray.h"

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

struct AVLTree { /* Height-Balanced Binary Search Tree. */
    struct  Node* root;
    int cnt;
};

struct AVLTree* newAVLTree() {
    struct AVLTree* tree = (struct AVLTree*)malloc(sizeof(struct AVLTree));
    assert(tree != 0);
    tree->root = 0;
    tree->cnt = 0;
    return tree;
}

int _h(struct Node* current)
{
    if (current == 0) return -1;  return current->height;
}

void _setHeight(struct Node* current) {
    int lch = _h(current->left);
    int rch = _h(current->right);
    if (lch < rch) current->height = 1 + rch;
    else current->height = 1 + lch;
}

int _bf(struct Node* current)
{
    return _h(current->right) - _h(current->left);
}

//worksheet 31 question
struct Node* _rotateLeft(struct Node* current) {
    struct Node* newTop = current->right;
    current->right = newTop->left;
    newTop->left = current;
    _setHeight(current);
    _setHeight(newTop);
    return newTop;
}

//worksheet 31 question
struct Node* _rotateRight(struct Node* current) {
    struct Node* newTop = current->left;
    current->left = newTop->right;
    newTop->right = current;
    _setHeight(current);
    _setHeight(newTop);
    return newTop;
}

//provided by worksheet 31
struct Node* _balance(struct Node* current) {
    
    //printf("Trying to balance %d\n", current->value);
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


struct Node* _AVLnodeAdd(struct Node* current, TYPE newValue) {
    struct Node* newnode;
    if (current == 0) {
        newnode = (struct Node*)malloc(sizeof(struct Node));
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

struct Node* _removeLeftmost(struct Node* cur) {
    struct Node* temp;
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
TYPE _leftMost(struct Node* cur) {
    while (cur->left != 0) {
        cur = cur->left;
    }
    return cur->value;
}

//referenced worksheet 29
//containsAVL tree will check to make sure this is not an empty tree
//after addition or removal of nodes, program needs to traverse up
//to the root node while balancing
struct Node* _removeNode(struct Node* current, TYPE val) {

    struct Node * temp;
    
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
    struct Node* cur;
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

void freeAVLTree(struct Node* current)
{
    if (current == NULL) return;
    freeAVLTree(current->left);
    freeAVLTree(current->right);
    free(current);
}




struct AVLIterator {
    struct DynArr *stk;
    struct AVLTree *tree;
};


//Create an empty stack
void AVLIteratorInit (struct AVLTree *tree, struct AVLIterator *itr){
    
    /*Fix me please*/
    assert(tree!=0);
    assert(itr!=0);
    
    itr->tree = tree;
    
    //create an empty stack
    struct DynArr * newDynArr = (struct DynArr*)malloc(sizeof(struct DynArr));
    initDynArr(newDynArr, 10);
    itr->stk = newDynArr;

}


//Returns the top of the stack
TYPE AVLIteratorNext (struct AVLIterator *itr) {
    
    /*Fix me*/
    
    struct Node temp = dynArrayTop(itr->stk);
    
    return temp.value;
}


void _AVLslideLeft(struct Node *cur, struct AVLIterator *itr) {
    
    while(cur != NULL) {
        dynArrayPush(itr->stk, cur);
        cur = cur->left;
    }
}


int AVLIteratorHasNext (struct AVLIterator * itr){
    
    /*Fix me*/

    //if stack is empty, perform slideLeft on root
    if(dyArraySize(itr->stk)==0) {
        _AVLslideLeft(itr->tree->root, itr);
        
    } else {
        //left n be the top of the stack
        struct Node n = dynArrayTop(itr->stk);
        //pop topmost element
        dynArrayPop(itr->stk);
        //slideLeft on the right child of n
        _AVLslideLeft(n.right, itr);
    }
    
    //return true if stack is not empty
    if(dyArraySize(itr->stk)!=0) return 1;
    else return 0;
}








void treesort(TYPE * data,int n){/*sort values into array data*/
    
    struct AVLTree * tree;
    tree = newAVLTree();
    
    //step 1: copy each element from A into an AVL tree
    for(int i = 0; i<n; i++){
        addAVLTree(tree, data[i]);
    }
    
    //step 2: copy each element from the AVL tree back into the array
    struct AVLIterator iter;
    AVLIteratorInit(tree, &iter);
    
    int count = 0;
    
    printf("during sort\n");
    while(AVLIteratorHasNext(&iter)!=0){
        
        data[count] = AVLIteratorNext(&iter);
        printf("%i ",data[count]);
        count++;
    }
    
    printf("\n");

    
}







int main(int argc, char* argv[])
{
    
    int array[] = {10,11,24,6,7,8,2,11,98,8};
    int count = 10;
    
    printf("before sort\n");
    for(int i = 0; i<count;i++){
        printf("%i ",array[i]);
    }
    printf("\n");
    treesort(array, count);
    
    printf("after sort\n");
    for(int i = 0; i<count;i++){
        printf("%i ",array[i]);
    }
    
    
    
    return 0;
}
