# ifndef DYARRAYDICTH
# define DYARRAYDICTH
 
/*
   dynamic array dictionary interface file
*/
 
# ifndef KEYTYPE
# define KEYTYPE char *
# endif
 
# ifndef VALUETYPE
# define VALUETYPE double
# endif
 
struct association {
   KEYTYPE key;
   VALUETYPE value;
};
 
# define TYPE struct association *
 
# include "dynamicArray.h"
 
/* dictionary */
void dyArrayDictionaryGet (struct dynArray *da, KEYTYPE key, VALUETYPE *valptr)
void dyArrayDictionaryPut (struct dynArray * da, KEYTYPE key, VALUETYPE val);
int dyArrayDictionaryContainsKey (struct dynArray * da, KEYTYPE key);
void dyArrayDictionaryRemoveKey (struct dynArray * da, KEYTYPE key);
 
# endif
