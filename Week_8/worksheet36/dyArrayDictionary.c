# include "dyArrayDictionary.h"
# include <stdlib.h>
# include <assert.h>
# include <stdio.h>

/*finds and places the value associated with key in valptr */
void dyArrayDictionaryGet (struct dynArray *da, KEYTYPE key, VALUETYPE *valptr){        
    /* FIXME: You will write this function */
    if(dyArrayDictionaryContainsKey(da, key)) {
        for(int i= 0; i < da->size; i++) {
            if(((struct association*)(da->data[i]))->key == key) {
                //point to the address
                *valptr = da->data[i]->value;
            }
        }
    }
    //what happens if it's not there?
}

void dyArrayDictionaryPut (struct dynArray *da, KEYTYPE key, VALUETYPE val) {
        struct association * ap;
        if (dyArrayDictionaryContainsKey(da, key))
        {
            dyArrayDictionaryRemoveKey(da, key);
        }
        ap = (struct association *) malloc(sizeof(struct association));
        assert(ap != 0);
        ap->key = key;
        ap->value = val;
        dyArrayAdd(da, ap);
}

int dyArrayDictionaryContainsKey (struct dynArray *da, KEYTYPE key) {
    /* FIXME: You will write this function */
    for(int i = 0; i < da->size; i++) {
        //cast data to association type and then compare key
        if(((struct association*)(da->data[i]))->key == key) {
            return 1;
        }
    }
    return 0;
}

void dyArrayDictionaryRemoveKey (struct  dynArray *da, KEYTYPE key) {
    /* FIXME: You will write this function */
    for(int i = 0; i < da->size; i++) {
        //cast data to association type and then compare key
        if(((struct association*)(da->data[i]))->key == key) {
            removeAtDynArr(da, i);
            return;
        }
    }

}


int main() {

    struct dynArray* dictionary = newDynArr(5);
    struct association term1;
    term1.key = "Tanya";
    term1.value = 4.0;
    struct association term2;
    term2.key = "Noor";
    term2.value = 5;
    struct association term3;
    term3.key = "Andrew";
    term3.value = 6;
    struct association term4;
    term4.key = "Melisa";
    term4.value = 1;
    struct association term5;
    term5.key = "Shirley";
    term5.value = 2;
    struct association term6;
    term6.key = "test";
    term6.value = 100;
    dyArrayDictionaryPut(dictionary, term1.key, term1.value);
    dyArrayDictionaryPut(dictionary, term2.key, term1.value);
    dyArrayDictionaryPut(dictionary, term3.key, term1.value);
    dyArrayDictionaryPut(dictionary, term4.key, term1.value);
    // printf("Capacity of dynamic array is: %d\n", dictionary->capacity);
    dyArrayDictionaryPut(dictionary, term5.key, term1.value);
    dyArrayDictionaryPut(dictionary, term6.key, term1.value);
    // printf("Capacity of dynamic array is: %d\n", dictionary->capacity);  //cap doubling properly
    printf("Does it contain Tanya: %d\n", dyArrayDictionaryContainsKey(dictionary, "Tanya"));
    
    VALUETYPE x = 0;
    dyArrayDictionaryGet(dictionary, "Tanya", &x);
    printf("Value associated with Tanya: %g\n", x); 

    VALUETYPE y = -1;
    printf("Does it contain key 0: %d\n", dyArrayDictionaryContainsKey(dictionary, "0"));
    
    dyArrayDictionaryGet(dictionary, "0", &y);
    printf("Value associated with 0: %g\n", y); 

    printf("Removing Tanya..\n");
    dyArrayDictionaryRemoveKey(dictionary,"Tanya");
    printf("Does it contain Tanya: %d\n", dyArrayDictionaryContainsKey(dictionary, "Tanya"));
    freeDynArr(dictionary);
    return 0;
}

