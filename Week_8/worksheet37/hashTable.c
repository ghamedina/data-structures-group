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
    printf("Count: %d, Size: %d, Load factor: %g\n", ht->count, ht->tablesize, ht->count / (double) ht->tablesize);
    if ((ht->count / (double) ht->tablesize) > 0.75) 
    {
        printf("Inside openHashTable - resizing\n");
        int temp = ht->tablesize;
        _resizeOpenHashTable(ht);
        printf("New table size: %d\n", ht->tablesize);
        // assert(ht->tablesize = temp * 2);
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
    // printf("%s\n", *ht->table[idx]);
    TYPE* temp = (TYPE*)malloc(sizeof(TYPE*));
    *temp = newValue;
    ht->table[idx] = temp; //
    printf("Inside openHastableAdd %s added to index %d\n", *temp, idx);
}


int openHashTableBagContains (struct openHashTable *ht, TYPE newValue) {
    int idx; 
    idx = HASH(newValue) % ht->tablesize;
    if (idx < 0) idx += ht->tablesize;
    //write this part
    while(ht->table[idx] != &newValue && ht->table[idx] != 0) {
        idx = (idx +1) % ht->tablesize; //move it to beginning if > tbsize
        //will break out when it either finds value or reaches next null
    }
    if(ht->table[idx] == &newValue) {
        return 1;
    }
    return 0;
}

void _resizeOpenHashTable (struct openHashTable *ht) {
    //write this
    printf("\n\n------ RESIZE ------ \n\n");
    struct openHashTable newHT;
    initOpenHashTable(&newHT, ht->tablesize * 2);
    int temp = ht->tablesize;
    // newHT.tablesize = ht->tablesize * 2;
    for(int i = 0; i < ht->tablesize; i++) {
        if(ht->table[i] != 0)
        {
            printf("Inside of resize...    ");
            openHashTableAdd(&newHT, *(ht->table[i]));
        }
    }
    // int x = ht->tablesize;
    //free ht somehow
    free(ht->table);
    ht = &newHT;
    newHT.tablesize = temp * 2;
    printf("\n--- END RESIZE -----\n\n");

}

void print(struct openHashTable *ht) {
    for(int i = 0; i < ht->tablesize; i++) {
        if(ht->table[i]!= 0)
        printf("Index %d: %s\n", i, *ht->table[i]);
    }
}

int main() {

    struct openHashTable table;
    initOpenHashTable(&table, 5);
    printf("Hash table size: %d\n", table.tablesize);
    openHashTableAdd(&table, "tanya");

    openHashTableAdd(&table, "shirley");
    openHashTableAdd(&table,"Melisa");
    openHashTableAdd(&table,"Noor");
    openHashTableAdd(&table,"Andrew");
    openHashTableAdd(&table,"Alex");
    // printf("Index at 5: %s\n", **(&table.table[5]));
    print(&table);
    // printf("Index at 4: %s\n", *table.table[4]);
    return 0;
}
