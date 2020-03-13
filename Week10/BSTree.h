#ifndef BSTree
#define BSTree

#ifndef __TYPE
#define __TYPE
#define TYPE int
#define TYPE_SIZE sizeof(int)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct BinarySearchTree BinarySearchTree;
typedef struct Node Node;

struct BinarySearchTree
{
    struct Node *root;
    int size;
};

struct Node
{
    TYPE value;
    struct Node *left;
    struct Node *right;
    int height;
};

void initBST(struct BinarySearchTree *tree);
void addBST(struct BinarySearchTree *tree, TYPE val);
int containsBST(struct BinarySearchTree *tree, TYPE val);
void removeBST(struct BinarySearchTree *tree, TYPE val);
int sizeBST(struct BinarySearchTree *tree);

void print2D(struct Node *root);

#endif
