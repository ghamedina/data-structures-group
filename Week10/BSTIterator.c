//
//  BSTIterator.c
//  bstIterator
//
//  Created by Shirley Chan on 3/5/20.
//  Copyright © 2020 Shirley Chan. All rights reserved.
//

#include "BSTIterator.h"

//Create an empty stack
void BSTIteratorInit (struct BinarySearchTree *tree, struct BSTIterator *itr){
    
    /*Fix me please*/
    assert(tree!=0);
    assert(itr!=0);
    
    itr->tree = tree;
    
    //create an empty stack
    struct DynArr * newDynArr = (struct DynArr*)malloc(sizeof(struct DynArr));
    initDynArr(newDynArr, 10);
    itr->stk = newDynArr;

}


int BSTIteratorHasNext (struct BSTIterator * itr){
    
    /*Fix me*/

    //if stack is empty, perform slideLeft on root
    if(dyArraySize(itr->stk)==0) {
        _slideLeft(itr->tree->root, itr);
        
    } else {
        //left n be the top of the stack
        struct Node n = dynArrayTop(itr->stk);
        //pop topmost element
        dynArrayPop(itr->stk);
        //slideLeft on the right child of n
        _slideLeft(n.right, itr);
    }
    
    //return true if stack is not empty
    if(dyArraySize(itr->stk)!=0) return 1;
    else return 0;
}

//Returns the top of the stack
TYPE BSTIteratorNext (struct BSTIterator *itr) {
    
    /*Fix me*/
    
    struct Node temp = dynArrayTop(itr->stk);
    
    return temp.value;
}


void _slideLeft(struct Node *cur, struct BSTIterator *itr) {
    
    while(cur != NULL) {
        dynArrayPush(itr->stk, cur);
        cur = cur->left;
    }
}

