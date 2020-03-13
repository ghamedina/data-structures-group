//
//  DynArray.h
//  bstIterator
//
//  Created by Shirley Chan on 3/6/20.
//  Copyright © 2020 Shirley Chan. All rights reserved.
//

#ifndef DynArray_h
#define DynArray_h

#ifndef __TYPE
#define __TYPE
#define TYPE int
#define TYPE_SIZE sizeof(int)
#endif

# define EQ(a, b) (a == b)

#include "BSTree.h"

struct DynArr
{
    Node *data;    /* pointer to the Node data array */
    int size;        /* Number of elements in the array */
    int capacity;    /* capacity of the array */
};


void initDynArr(struct DynArr *v, int capacity);


void freeDynArr(struct DynArr *v);


int dyArraySize( struct DynArr *v);


void _setCapacityDynArr(struct DynArr *v, int newCap);


void dyArrayAdd(struct DynArr *v, Node * newNode);

Node * dyArrayGet (struct DynArr * da, int position);

void dyArrayPut (struct DynArr * da, int position, Node newNode );

void swapDynArr (struct DynArr * da, int i, int j);

void removeAtDynArr (struct DynArr * da, int index);

void dynArrayPush(struct DynArr * da, Node * newNode);

Node dynArrayTop(struct DynArr * da);

void dynArrayPop(struct DynArr * da);

int dynArrayIsEmpty(struct DynArr * da);

int containsDynArr(struct DynArr * da, Node * n);




#endif /* DynArray_h */
