//
//  BSTIterator.h
//  bstIterator
//
//  Created by Shirley Chan on 3/5/20.
//  Copyright © 2020 Shirley Chan. All rights reserved.
//

#ifndef BSTIterator_h
#define BSTIterator_h

#include "BSTree.h"
#include "DynArray.h"

//Internal stack will represent the current path that has been traversed
//First element produced should be the left most child of the root
struct BSTIterator {
    struct DynArr *stk;
    struct BinarySearchTree *tree;
};


void BSTIteratorInit (struct BinarySearchTree *tree, struct BSTIterator *itr);

//hasnext and next has to be called subsequently
int BSTIteratorHasNext (struct BSTIterator * itr);
void _slideLeft(struct Node *cur, struct BSTIterator *itr);
TYPE BSTIteratorNext (struct BSTIterator *itr);


#endif /* BSTIterator_h */
