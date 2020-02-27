#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __TYPE
#define __TYPE 
#define TYPE char*
#endif


struct openHashTable {
   TYPE ** table;
   int tablesize;
   int count;
};
void _resizeOpenHashTable (struct openHashTable *ht);

int HASH(TYPE key)
{

    return key[0];
}

void initOpenHashTable (struct openHashTable* ht, int size) {
    int i;
    assert (size > 0);
    ht->table = (TYPE **) malloc(size * sizeof(TYPE *));
    assert(ht->table != 0);
    for (i = 0; i < size; i++)
    {
        ht->table[i] = 0; /* initialize empty */
    }
    ht->tablesize = size;
    ht->count = 0;
}

int openHashTableSize (struct openHashTable *ht) { 
    return ht->count; 
}

void openHashTableAdd (struct openHashTable * ht, TYPE newValue) {
    int idx; 

    /* Make sure we have space and under the load factor threshold*/ 
    if ((ht->count / (double) ht->tablesize) > 0.75) 
    {
        _resizeOpenHashTable(ht);
    }
    ht->count++;
    
    idx = HASH(newValue) % ht->tablesize;
    
   /* To be safe, use only positive arithmetic.  % may behave very differently on diff	 
      implementations or diff languages .  However, you can do the following to deal with a 
      negative result from HASH  */

    if (idx < 0) idx += ht->tablesize;
    //write this
    while(ht->table[idx] != 0) {
        idx = (idx +1) % ht->tablesize;
    }
    
    //dereference pointer at the index so we can assign to the newvalue pointer
    //because table[idx] is a double pointer
    
    if(ht->table[idx]!=NULL) {
        *(ht->table[idx]) = newValue;
    } else {
        ht->table[idx] = malloc(sizeof(TYPE *));
        *(ht->table[idx]) = newValue;
    }
}


int openHashTableBagContains (struct openHashTable *ht, TYPE newValue) {
    int idx; 
    idx = HASH(newValue) % ht->tablesize;
    if (idx < 0) idx += ht->tablesize;
    //write this part
    while(*(ht->table[idx]) != newValue && ht->table[idx] != 0) {
        idx = (idx +1) % ht->tablesize; //move it to beginning if > tbsize
        //will break out when it either finds value or reaches next null
    }
    if(*(ht->table[idx]) == newValue) {
        return 1;
    }
    return 0;
}

void _resizeOpenHashTable (struct openHashTable *ht) {
    //write this
    struct openHashTable newHT;
    initOpenHashTable(&newHT, ht->tablesize * 2);
    for(int i = 0; i < ht->tablesize; i++) {
        openHashTableAdd(&newHT, *(ht->table[i]));
    }
    //free ht somehow
    free(ht->table);
    
    ht = &newHT;
    // newHT = 0;
}

void print(struct openHashTable *ht) {
    for(int i = 0; i < ht->tablesize; i++) {
        printf("%s\n", *(ht->table[i]));
    }
}

int main() {

    return 0;
}
