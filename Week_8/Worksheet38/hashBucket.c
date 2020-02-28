#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __TYPE
#define __TYPE
#define TYPE char*
#endif

struct hlink {
    TYPE value;
    struct hlink *next;
};

struct hashTable {
    struct hlink ** table;
    int tablesize; //buckets
    int count;
};

int HASH(TYPE key)
{

    return key[0];
}

void resizeTable (struct hashTable *ht);

void initHashTable (struct hashTable * ht, int size) {

    /* Fix me please*/
    assert(ht!=NULL && size>0);
    
    ht->tablesize = size;
    ht->count = 0;
    ht->table = malloc(sizeof(struct hlink*) * size);
    
    for(int i = 0; i<ht->tablesize; i++) {
        ht->table[i] = NULL;
    }
}


int hashTableSize (struct hashTable * ht) {
    return ht->count;
}



void hashTableAdd (struct hashTable *ht, TYPE newValue) {
    
    //compute hash value to find the correct bucket
    int hashIndex = HASH(newValue) % ht->tablesize;
    if (hashIndex < 0) hashIndex += ht->tablesize;
    
    struct hlink * newLink = (struct hlink *) malloc(sizeof(struct hlink));
    assert(newLink);
    newLink->value = newValue;
    newLink->next = NULL;
    
    if(ht->table[hashIndex]==NULL){

//        ht->table[hashIndex] = malloc(sizeof(struct hlink));
        ht->table[hashIndex] = newLink; /* add to bucket */

    } else {
        
        struct hlink * iterator = ht->table[hashIndex];

        while(iterator->next!=NULL) {

            iterator=iterator->next;
        }
        
        iterator->next = newLink;

    }

    ht->count++;
    
    if ((ht->count / (double) ht->tablesize) > 2.0) {

        resizeTable(ht);
    }

}





int hashTableContains (struct hashTable * ht, TYPE testElement) {

    /* Fix me please*/
    
    assert(ht!=NULL && testElement!=NULL);
    
    //compute hash value to find the correct bucket
    int hashIndex = HASH(testElement) % ht->tablesize;
    if (hashIndex < 0) hashIndex += ht->tablesize;
    
    //bucket location
    struct hlink * iterator = ht->table[hashIndex];
    
    //search bucket
    while(iterator!=NULL) {
        
        if(*(iterator->value) == *testElement) return 1;
        
        iterator = iterator->next;
    }

    return 0;

}
 





void hashTableRemove (struct hashTable * ht, TYPE testElement) {
    
    /* Fix me please*/
    
    assert(ht!=NULL && testElement!=NULL);
    
    //compute hash value to find the correct bucket
    int hashIndex = HASH(testElement) % ht->tablesize;
    if (hashIndex < 0) hashIndex += ht->tablesize;
    
    //bucket location
    struct hlink * current = ht->table[hashIndex];
    struct hlink * previous = current;

    //search bucket
    while(current!=NULL) {
 
        //Test element is the only element in a bucket
        if(*(current->value) == *testElement && current->next==NULL) {
           
            free(current);
            ht->table[hashIndex] = NULL;
            ht->count--;
            return;
            
            //Test element is the first element in a bucket of more than 1
        } else if(*(current->value) == *testElement && current->next!=NULL) {
            
            ht->table[hashIndex] = current->next;
            free(current);
            ht->count--;
            return;
            
            //Test element is not the first and only element in bucket
        } else if(*(current->value) == *testElement){
            
            previous->next = current->next;
            free(current);
            ht->count--;
            return;
            
        }
        
        current = current->next;
    }

}

void resizeTable (struct hashTable *ht) {

    /* Fix me please*/
    struct hashTable newHT;
 
    initHashTable(&newHT, ht->tablesize*2);

    for(int i = 0; i<ht->tablesize; i++){

        struct hlink * iterator = ht->table[i];
        
        while(iterator!=NULL) {

            hashTableAdd(&newHT,iterator->value);
            struct hlink * temp = iterator->next;
            free(iterator);
            iterator = temp;

        }
    }
    
    free(ht->table);
    
    ht->table = newHT.table;
    ht->tablesize = newHT.tablesize;
}


void freeHashTable(struct hashTable * ht){
    
    //freeing individual pointers
    for(int i = 0; i<ht->tablesize; i++) {
        
        struct hlink * current = ht->table[i];
        
        while(current!=NULL){
            
            struct hlink * temp = current->next;
            free(current);
            current = temp;
        }
    }
    //freeing table
    free(ht->table);
}


void print(struct hashTable *ht) {
    
    printf("==PRINTING HASH TABLE==\n");
    
    
    for(int i = 0; i < ht->tablesize; i++) {
        
        printf("\nIndex %i: ",i);
        
        if(ht->table[i]!=NULL) {
            
            struct hlink * iterator = ht->table[i];
            
            while(iterator!=NULL) {
                
                printf("%c ", *(iterator->value));
                iterator=iterator->next;
            }
        }
    }
    printf("\n\n");
}

int main(){
    
    char string1[] = "Tanya";
    char string2[] = "Andrew";
    char string3[] = "Noor";
    char string4[] = "Melisa";
    char string5[] = "Shirley";
    char string6[] = "Pikachu";
    char string7[] = "Bulbasaur";
    char string8[] = "Blastoise";
    char string9[] = "Geodude";
    char string10[] = "Starmie";
    char string11[] = "Squirtle";
    char string12[] = "Burmy";
    
    struct hashTable bucket;
    initHashTable(&bucket, 5);

    hashTableAdd(&bucket, string1);
    hashTableAdd(&bucket, string2);
    hashTableAdd(&bucket, string3);
    hashTableAdd(&bucket, string4);
    hashTableAdd(&bucket, string5);

    print(&bucket);

    hashTableAdd(&bucket, string6);
    hashTableAdd(&bucket, string7);
    hashTableAdd(&bucket, string8);
    hashTableAdd(&bucket, string9);
    hashTableAdd(&bucket, string10);
    hashTableAdd(&bucket, string11);
    hashTableAdd(&bucket, string12);

    print(&bucket);
    
    if(hashTableContains(&bucket, string7)){
        printf("Found %s\n", string7);
    } else {
        printf("Can't find %s\n", string7);
    }
    
    hashTableRemove(&bucket, string7);
    hashTableRemove(&bucket, string8);
    
    print(&bucket);
    printf("Removed %s\n",string7);
    printf("Removed %s\n",string8);
    
    if(hashTableContains(&bucket, string7)){
        printf("Found %s\n", string7);
    } else {
        printf("Can't find %s\n", string7);
    }
    
    freeHashTable(&bucket);
    
    return 0;
}
