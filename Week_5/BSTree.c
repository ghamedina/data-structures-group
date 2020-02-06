#include "BSTree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#define COUNT 10

void initBST(struct BinarySearchTree *tree)
{
    tree->size = 0;
    tree->root = 0;
}
/*
 * ===  FUNCTION  ==========================================================
 *         Name:  _leftMostChild
 *  Description:  Internal function. Takes current node as arg and returns
 *                the leftmost child's value of current node
 * =========================================================================
 */
TYPE _leftMostChild(struct Node* current)
{
    assert(current != 0);
    current = current->left;
    while(current->left != NULL) current = current->left;
    return current->value;
}
/*
 * ===  FUNCTION  ==========================================================
 *         Name:  _removeLeftMostChild(struct Node* current)
 *  Description:  Takes current node as arg and returns tree with leftmost
 *                child removed
 * =========================================================================
 */
struct Node* _removeLeftMostChild(struct Node *current)
{
    assert(current != 0);
    struct Node * parent = current;         //keep track of parent node
    struct Node * leftMost = current->left;
    while(leftMost->left != NULL) {
        parent = parent->left;
        leftMost = leftMost->left;
    }
    if(leftMost->right != NULL) { //right child of left most subtree will always be less than parent
        parent->left = leftMost->right; //linking parent node to to be deleted's right node
        leftMost->right = NULL; //erasing previous link
    } else {
        parent->left = NULL;
    }
    free(leftMost);
    return current;
}

struct Node* _nodeRemoveBST(struct Node* current, TYPE d)
{
    if(d == current->value)
    {
        if(current->right == NULL)
        {
            return current->left;
        }
        else
        {
            //replace value with leftmost child of right child
            current->value = _leftMostChild(current->right);
            //set right child to result of removeLeftMost(right)
            current->right = _removeLeftMostChild(current->right);
        }
    }
    else if(d < current->value)
    {
        current->left = _nodeRemoveBST(current->left, d);
    }
    else
    {
        current->right = _nodeRemoveBST(current->right, d);
    }
    return current;
}

struct Node* _nodeAddBST(struct Node *current, TYPE val)
{
    struct Node *newNode;
    //if current is null, return new node with value
    if(current == NULL)
    {
        newNode = malloc(sizeof(struct Node));
        assert(newNode != 0);
        newNode->value = val;
        newNode->left = newNode->right = 0;
        return newNode;
    }
    //otherwise if new value is less than value at start then set left child to
    //value returned by add(left child, newvalue)
    if(val < current->value)
    {
        current->left = _nodeAddBST(current->left, val);
    }
    else
    {
        current->right = _nodeAddBST(current->right, val);
    }
    return current;
}

void addBST(struct BinarySearchTree *tree, TYPE val)
{
    tree->root = _nodeAddBST(tree->root, val);
    tree->size++;
}

int containsBST(struct BinarySearchTree *tree, TYPE val)
{
    //start at root
    struct Node* current = tree->root;
    while(current != NULL)
    {
        if(val == current->value)
        {
            return 1;
        }
        if(val < current->value)
        {
            current = current->left;
        }
        else //greater than
        {
            current = current->right;
        }
    }
    return 0;
}

void removeBST(struct BinarySearchTree *tree, TYPE val)
{
    if(containsBST(tree, val))
    {
        tree->root = _nodeRemoveBST(tree->root,val);
        tree->size--;
    }
}

int sizeBST(struct BinarySearchTree *tree)
{
    return tree->size;
}
void print(struct BinarySearchTree* tree, struct Node* current)
{
    printf("Node value: %d\n", current->value);
    // printf("Node right value: %d\n", current->right->value);
    // printf("Node left value: %d\n", current->left->value);
}
void print2DUtil(struct Node *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
    // Increase distance between levels 
    space += COUNT; 
    // Process right child first 
    print2DUtil(root->right, space); 
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->value); 
    // Process left child 
    print2DUtil(root->left, space); 
} 
// Wrapper over print2DUtil() 
void print2D(struct Node *root) 
{ 
   // Pass initial space count as 0 
   print2DUtil(root, 0); 
}
void freeTree(struct Node* current)
{
    if(current == NULL) return;
    freeTree(current->left);
    freeTree(current->right);
    free(current);
}
int main()
{
    struct BinarySearchTree bst;
    initBST(&bst);
    addBST(&bst, 45);
    addBST(&bst, 67);
    addBST(&bst, 22);
    addBST(&bst, 100);
    addBST(&bst, 75);
    addBST(&bst, 13);
    addBST(&bst, 11);
    addBST(&bst, 64);
    addBST(&bst, 30);
    addBST(&bst, 21);
    addBST(&bst, 63);
    addBST(&bst, 65);
    addBST(&bst, 101);
    addBST(&bst, 31);
    addBST(&bst, 29);
    printf("Size: %d\n", sizeBST(&bst));
    print2D(bst.root);
    printf("Contains 30: %d\n", containsBST(&bst, 30));
    printf("Contains 11: %d\n", containsBST(&bst, 11));
    printf("Contains 200: %d\n", containsBST(&bst, 200));
    printf("Removing 67..\n");
    removeBST(&bst, 67);
    printf("Contains 67: %d\n", containsBST(&bst, 67));
    printf("Removing 0..\n");
    print2D(bst.root);
    freeTree(bst.root);
    return 0;
}