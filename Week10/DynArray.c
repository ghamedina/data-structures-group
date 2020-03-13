#include "DynArray.h"

void initDynArr(struct DynArr *v, int capacity)
{
    v->data = malloc(sizeof(struct Node) * capacity);
    assert(v->data != 0);
    
    v->size = 0;
    v->capacity = capacity;
}


void freeDynArr(struct DynArr *v)
{
    if(v->data != 0)
    {
        free(v->data);     /* free the space on the heap */
        //v->data = 0;       /* make it point to null */
    }
    v->size = 0;
    v->capacity = 0;
}


int dyArraySize( struct DynArr *v)
{
    return v->size;
}


void _setCapacityDynArr(struct DynArr *v, int newCap)
{
    assert(v != 0);
    
    /* Allocate new temporary dynamic array with given cap */
    struct Node *temp = (struct Node*)malloc((sizeof(struct Node))* (newCap));
    assert(temp != 0);
    
    /* Copy elements from old array to new array */
    for (int i = 0; i < v->size; i++) {
        assert(i < newCap);
        temp[i] = v->data[i];
    }
    
    /* Free the old array */
    free(v->data);
    
    /* Set pointer v to new array */
    v->data = temp;
    temp = 0;
    
    /* Update the capacity*/
    v->capacity=newCap;
}


void dyArrayAdd(struct DynArr *v, Node * newNode)
{
    /* Check to see if a resize is necessary */
    if(v->size >= v->capacity)
        _setCapacityDynArr(v, 2 * v->capacity);
    
    v->data[v->size].value = newNode->value;
    v->data[v->size].left = newNode->left;
    v->data[v->size].right = newNode->right;
    v->size++;

}


Node * dyArrayGet (struct DynArr * da, int position){
    
    assert(da->size>0);
    assert(position>=0&&position<=da->size);
    
    return &da->data[position];

}


void dyArrayPut (struct DynArr * da, int position, Node newNode ){
    
    assert(da->size>0);
    assert(position>=0&&position<=da->size);
    
    da->data[position] = newNode;
    
}

void swapDynArr (struct DynArr * da, int i, int j){
    
    assert(da->size>0);
    assert(i>=0&&i<=da->size);
    assert(j>=0&&j<=da->size);
    
    //storing i in temp
    Node temp = *dyArrayGet(da, i);
    
    //move value in j to i
    dyArrayPut(da, i, *dyArrayGet(da, j));
    
    //move temp to j
    dyArrayPut(da, j, temp);
    
}

void removeAtDynArr (struct DynArr * da, int index){
    
    assert(da->size>0);
    assert(index>=0&&index<=da->size);
    
    for(int i = index; i<da->size-1; i++){
        
        swapDynArr(da, i, i+1);
    }
    
    da->size--;
    
}


void dynArrayPush(struct DynArr * da, Node * newNode){
    
    assert(da!=0); //check to see not null
    
    dyArrayAdd(da, newNode);
    
    
}


Node dynArrayTop(struct DynArr * da){
   
    assert(da!=0);
    assert(dyArraySize(da)>=1);
    
    return da->data[dyArraySize(da)-1];
    
}


void dynArrayPop(struct DynArr * da){

    assert(da!=0&&dyArraySize(da)>=1);
    
    removeAtDynArr(da, da->size-1);
    
}


int dynArrayIsEmpty(struct DynArr * da){
    
    if(da->size==0) return 1; //is empty
    
    return 0; //not empty
}

int containsDynArr(struct DynArr * da, Node * n){
    
    assert(!dynArrayIsEmpty(da));

    for(int i = 0; i<da->size;i++){
        
        if(EQ(n->value,da->data[i].value)) return 1;

    }
    
    return 0;
}
