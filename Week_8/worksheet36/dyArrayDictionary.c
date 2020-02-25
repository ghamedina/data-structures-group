# include "dyArrayDictionary.h"
# include <stdlib.h>
# include <assert.h>

/*finds and places the value associated with key in valptr */
void dyArrayDictionaryGet (struct dynArray *da, KEYTYPE key, VALUETYPE *valptr){        
    /* FIXME: You will write this function */

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

}

int main() {

    return 0;
}

