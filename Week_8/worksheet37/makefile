all: prog

prog: hashTable.o
	gcc -g -Wall -std=c99 -o prog hashTable.o

hashTable.o: hashTable.c 
	gcc -g -Wall -std=c99 -c hashTable.c

clean:
	rm hashTable.o
	rm prog