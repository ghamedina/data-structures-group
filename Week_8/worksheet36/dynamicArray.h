/* 	dynamicArray_a1.h : Dynamic Array implementation. */
#ifndef DYNAMIC_ARRAY_INCLUDED
#define DYNAMIC_ARRAY_INCLUDED 1

#ifndef __TYPE
#define __TYPE
// # define TYPE      char
// # define TYPE_SIZE sizeof(char)
# endif

# ifndef LT
# define LT(A, B) ((A) < (B))
# endif

# ifndef EQ
# define EQ(A, B) ((A) == (B))
# endif
# define TYPE struct association *
typedef struct dynArray dynArray;

struct dynArray
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};

/* Dynamic Array Functions */
void initDynArr(dynArray *v, int capacity);	
dynArray *newDynArr(int cap);

void freeDynArr(dynArray *v);
void deleteDynArr(dynArray *v);

int sizeDynArr(dynArray *v);

void dyArrayAdd(dynArray *v, TYPE val);
TYPE getDynArr(dynArray *v, int pos); //returns value stored at position
void putDynArr(dynArray *v, int pos, TYPE val);
void swapDynArr(dynArray *v, int i, int  j);
void removeAtDynArr(dynArray *v, int idx);

// /* Stack interface. */
int isEmptyDynArr(dynArray *v);
// void pushDynArr(dynArray *v, TYPE val);
// TYPE topDynArr(dynArray *v);
// void popDynArr(dynArray *v);

// /* Bag Interface */	
// /* Note addDynArr is already declared above*/
// int containsDynArr(dynArray *v, TYPE val);
// void removeDynArr(dynArray *v, TYPE val);

// void printDynArr(dynArray *v);
#endif
