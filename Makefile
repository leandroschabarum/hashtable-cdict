# -*- MakeFile -*-

all: test

binaries:
	mkdir $(PWD)/$@

test: binaries binaries/charkeyHash.o binaries/cdict.o
	gcc binaries/charkeyHash.o binaries/cdict.o -o test -l m

binaries/charkeyHash.o: charkeyHash.c
	gcc -c charkeyHash.c -o $@

binaries/cdict.o: cdict.c ckhash.h
	gcc -c cdict.c -o $@

clean:
	rm -rf test $(PWD)/binaries
