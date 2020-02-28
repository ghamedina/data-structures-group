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
void print(struct hashTable *ht);

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


//Does this go into more depth?
void hashTableAdd (struct hashTable *ht, TYPE newValue) {
    
    //compute hash value to find the correct bucket
    int hashIndex = HASH(newValue) % ht->tablesize;
    if (hashIndex < 0) hashIndex += ht->tablesize;

    //Creating a new link
    struct hlink * newLink = malloc(sizeof(struct hlink));
    assert(newLink);
    newLink->value = newValue;
    newLink->next = NULL;
    
    //Finding the bucket
    struct hlink * iterator = ht->table[hashIndex];
    
    //First link in a bucket
    if(iterator == NULL){
        
        //allocating space for first link in bucket?
//        ht->table[hashIndex] = malloc(sizeof(struct hlink));
        
        //placing the new link in the bucket
        ht->table[hashIndex] = newLink;
        
    } else {

        //searching the rest of the buckets for an empty space
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
    struct hlink * previous;

    //search bucket
    while(current!=NULL) {
        
        previous = current;
    
        if(*(current->value) == *testElement && current->next == NULL) {
            
            current = current->next;
            free(current);
            free(ht->table[hashIndex]);
            ht->count--;
            break;
            
        } else if(*(current->value) == *testElement){
            
            previous->next = current->next;
            free(current);
            ht->count--;
            break;
        }

        current = current->next;
    }
}

void resizeTable (struct hashTable *ht) {

    /* Fix me please*/
    struct hashTable newHT;
    initHashTable(&newHT, ht->tablesize*2);
    
    printf("===Resizing from %i to %i\n",ht->tablesize, newHT.tablesize);
    
    for(int i = 0; i<ht->tablesize; i++){

        struct hlink * iterator = ht->table[i];
        
        while(iterator!=NULL) {

            struct hlink * temp = iterator->next;
            hashTableAdd(&newHT,iterator->value);
            printf("Freeing buckets inside of resize\n");
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
     
        if(ht->table[i]!=NULL){ //check to see if it was allocated before freeing
            
            struct hlink * iterator = ht->table[i];
            printf("\nBucket number %i: ",i);

            while(iterator!=NULL){
                
                printf("%c ",*iterator->value);
                
                struct hlink * temp = iterator->next;
                free(iterator);
                iterator = temp;
                
                printf("Freed ");
            }
            
//            free(ht->table[i]);

        }
        
    }
    printf("\n");
    //freeing table
    free(ht->table);
}


void print(struct hashTable *ht) {
    
    printf("==PRINTING HASH TABLE==\n");
    
    
    for(int i = 0; i < ht->tablesize; i++) {
        
        printf("\nkey %i: ",i);
        
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
    
    struct hashTable bucket;
    initHashTable(&bucket, 2);

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

    print(&bucket);
    
//    hashTableRemove(&bucket, string1);
    
    print(&bucket);
    
    freeHashTable(&bucket);
    
    return 0;
}
