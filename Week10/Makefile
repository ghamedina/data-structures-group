
output: BSTmain.o BSTIterator.o BSTree.o DynArray.o
	g++ -std=c++11 BSTmain.o BSTIterator.o BSTree.o DynArray.o -o output

BSTmain.o: BSTmain.c
	g++ -std=c++11 -c BSTmain.c

BSTIterator.o: BSTIterator.c BSTIterator.h
	g++ -std=c++11 -c BSTIterator.c

BSTree.o: BSTree.c BSTree.h
	g++ -std=c++11 -c BSTree.c

DynArray.o: DynArray.c DynArray.h
	g++ -std=c++11 -c DynArray.c

clean:
	rm *.o output