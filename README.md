# Hash table data structure
## **cdict**
----

### Compiling with make

```shell
# builds directory structure and compiles program
make build && make

# runs compiled program
bin/main

# cleans directory structure
make clean
```


### Compiling directly with GCC

```shell
# assemble cdict.o and charKeyHash.o objects
gcc -c cdict.c -o cdict.o
gcc -c charKeyHash.c -o charKeyHash.o

# link objects and compile executable program
gcc cdict.o charKeyHash.o -o main -l m

#runs compiled program
./main
```

