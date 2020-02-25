all: prog

prog: dynamicArray.o dyArrayDictionary.o
	gcc -g -Wall -std=c99 -o prog dynamicArray.o dyArrayDictionary.o

dynamicArray.o: dynamicArray.c dynamicArray.h
	gcc -g -Wall -std=c99 -c dynamicArray.c

dyArrayDictionary.o: dyArrayDictionary.c dyArrayDictionary.h
	gcc -g -Wall -std=c99 -c dyArrayDictionary.c

clean:
	rm dyArrayDictionary.o
	rm dynamicArray.o
	rm prog