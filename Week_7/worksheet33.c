#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
# define TYPE int
# define EQ(a, b) (a == b)
# define LT(a, b) (a < b)

/* from Week 2 worksheets */
struct DynArr
{
    TYPE *data;    /* pointer to the data array */
    int size;        /* Number of elements in the array */
    int capacity;    /* capacity of the array */
};


void initDynArr(struct DynArr *v, int capacity)
{
    v->data = malloc(sizeof(TYPE) * capacity);
    assert(v->data != 0);
    
    v->size = 0;
    v->capacity = capacity;
    // printf("The current capacity is %i\n", v->capacity);
}


void freeDynArr(struct DynArr *v)
{
    if(v->data != 0)
    {
        free(v->data);     /* free the space on the heap */
        v->data = 0;       /* make it point to null */
    }
    v->size = 0;
    v->capacity = 0;
}


int dyArraySize( struct DynArr *v)
{
	printf("SIZE ----> %d\n\n", v->size);
    return v->size;
}


void _setCapacityDynArr(struct DynArr *v, int newCap)
{
    assert(v != 0);
    /* Allocate new temporary dynamic array with given cap */
    TYPE *temp = malloc(sizeof(TYPE) * newCap);
    assert(temp != 0);
    /* Copy elements from old array to new array */
    for (int i = 0; i < v->size; i++) {
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


void dyArrayAdd(struct DynArr *v, TYPE val)
{
    /* Check to see if a resize is necessary */
    if(v->size >= v->capacity)
        _setCapacityDynArr(v, 2 * v->capacity);
    
    v->data[v->size] = val;
    v->size++;
	// printf("dyArrayAdd size: %d\n\n", v->size);
}


TYPE dyArrayGet (struct DynArr * da, int position){
    
    assert(da->size>0);
    assert(position>=0&&position<=da->size);
    
    return da->data[position];

}


void dyArrayPut (struct DynArr * da, int position, TYPE value){
    
    assert(da->size>0);
    assert(position>=0&&position<=da->size);
    
    da->data[position] = value;
    
}

void swapDynArr (struct DynArr * da, int i, int j){
    
    assert(da->size>0);
    assert(i>=0&&i<=da->size);
    assert(j>=0&&j<=da->size);
    
    //storing i in temp
    TYPE temp = dyArrayGet(da, i);
    
    //move value in j to i
    dyArrayPut(da, i, dyArrayGet(da, j));
    
    //move temp to j
    dyArrayPut(da, j, temp);
    
}

void removeAtDynArr (struct DynArr * da, int index){
    
    assert(da->size>0);
    assert(index>=0&&index<=da->size);
    
    for(int i = index; i<=da->size-1; i++){
        
        swapDynArr(da, i, i+1);
    }
    
    dyArrayPut(da,da->size-1,0);
    
    da->size--;
    
}


void dynArrayPush(struct DynArr * da, TYPE e){
    
    assert(da!=0); //check to see not null
    
    dyArrayAdd(da, e);
    
    
}


TYPE dynArrayTop(struct DynArr * da){
   
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

int containsDynArr(struct DynArr * da, TYPE e){
    
    assert(!dynArrayIsEmpty(da));

    for(int i = 0; i<da->size;i++){
        
        if(EQ(e,da->data[i])) return 1;

    }
    
    return 0;
}

/*=======================*/
/* Starting Worksheet 33 */
/*=======================*/

void swap (struct DynArr * v, int i, int j) {  /* swap elements i j */
      TYPE temp = dyArrayGet(v, i);
      dyArrayPut(v, i, dyArrayGet(v, j));
      dyArrayPut(v, j, temp);
   }

int indexSmallest (struct DynArr * v, int i, int j) {
      /* return index of smallest element */
    if (LT(dyArrayGet(v, i), dyArrayGet(v, j))) return i;
        
    return j;
}
        
TYPE heapGetFirst (struct DynArr *heap) {
    assert(dyArraySize(heap) > 0);
    return dyArrayGet(heap, 0);
}


void adjustHeap(struct DynArr * heap, int max, int pos) {
	int leftChild = 2 * pos + 1; 
	int rightChild = 2 * pos + 2;
	if (rightChild < max) { /* we have two children */
        int smallestChild = indexSmallest(heap, leftChild, rightChild);
		// if value at pos > value of smallest child
		if (heap->data[pos] > heap->data[smallestChild]) {
			// swap with smallest child,  call adjustHeap (max, index of smallest child)
			swap(heap, pos, smallestChild);
			adjustHeap(heap, dyArraySize(heap)-1, smallestChild);
		}
	}
	// else if (leftchild < max) { /* we have one child */
	else if (leftChild < max) {
		// if value at pos > value of child
		if (heap->data[pos] > heap->data[leftChild]) {
			// swap with smallest child, call adjustHeap (max, index of left child)
			swap(heap, pos, leftChild);
			adjustHeap(heap,dyArraySize(heap)-1, leftChild);
		}
	}
   /* else no children, done */
	return;
}


void heapRemoveFirst(struct DynArr *heap) {
    int last = dyArraySize(heap)-1;
    assert(dyArraySize(heap) > 0);    /* make sure we have at least one element */
	printf("heapRemoveFirst ----> last %d, heap->size %d\n\n", last, heap->size);
    /* Copy the last element to the first  position */
    dyArrayPut(heap, 0, dyArrayGet(heap, last));
    removeAtDynArr(heap, last);       /* Remove last element.*/
    adjustHeap(heap, last, 0);/* Rebuild heap */
}


void heapAdd(struct DynArr * heap, TYPE newValue) {
	int parent;
	int pos = dyArraySize(heap);
	dyArrayAdd(heap, newValue); /* adds to end – now need to adjust position */

	while(pos != 0) {
		parent = (pos - 1)/2;
		// printf("heapAdd, pos: %d, parent: %d \n\n", pos, parent);
		if (dyArrayGet(heap, pos) < dyArrayGet(heap, parent)) {
			swapDynArr(heap, parent, pos);
			pos = parent;
		} else {
			return;
		}
	}
}

void printArray(struct DynArr * heap) {
	for (int i = 0; i < heap->size; i++) {
		printf("%d ", heap->data[i]);
	}
	printf("\n\n");
	// printf("printArr, heap cap: %d, size: %d \n\n", heap->capacity, heap->size);
}

int main(int argc, const char * argv[]) {
	struct DynArr heap;
	initDynArr(&heap, 5);
// 2, 3, 5, 9, 10, 7, 8, 12, 14, 11, 16
	heapAdd(&heap, 2);
	heapAdd(&heap, 3);
	heapAdd(&heap, 5);
	heapAdd(&heap, 9);
	heapAdd(&heap, 10);
	printArray(&heap);
	heapAdd(&heap, 7);
	heapAdd(&heap, 8);
	heapAdd(&heap, 12);
	heapAdd(&heap, 14);
	heapAdd(&heap, 11);
	heapAdd(&heap, 16);
	heapRemoveFirst(&heap);

	printArray(&heap);

    heapRemoveFirst(&heap);
    heapRemoveFirst(&heap);
    heapRemoveFirst(&heap);
    heapRemoveFirst(&heap);
    heapRemoveFirst(&heap);
    heapRemoveFirst(&heap);
    heapRemoveFirst(&heap);
    heapRemoveFirst(&heap);
    heapRemoveFirst(&heap);
    printArray(&heap);

	freeDynArr(&heap);
    return 0;
}
