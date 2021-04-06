# -*- MakeFile -*-

all: test

test: charkeyHash.o cdict.o
	gcc charkeyHash.o cdict.o -o test -l m

charkeyHash.o: charkeyHash.c
	gcc -c charkeyHash.c

cdict.o: cdict.c ckhash.h
	gcc -c cdict.c

clean:
	rm -f *.o test
