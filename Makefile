
output: BSTmain.o BSTIterator.o BSTree.o DynArray.o
	g++ -std=c++11 BSTmain.o BSTIterator.o BSTree.o DynArray.o -o output

BSTmain.o: BSTmain.cpp
	g++ -std=c++11 -c BSTmain.cpp

BSTIterator.o: BSTIterator.cpp BSTIterator.hpp
	g++ -std=c++11 -c BSTIterator.cpp

BSTree.o: BSTree.cpp BSTree.hpp
	g++ -std=c++11 -c BSTree.cpp

DynArray.o: DynArray.cpp DynArray.hpp
	g++ -std=c++11 -c DynArray.cpp

clean:
	rm *.o output