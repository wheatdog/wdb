CC=gcc
CPP=g++
CFLAGS=-Wall -gdwarf-4 -g3
TARGETS=test array_benchmark

all: $(TARGETS)

%.o: %.c ../wdb.h
	$(CC) $(CFLAGS) -c $< -o $@

test: test.o wdb_arr_test.o wdb_list_test.o wdb_heap_test.o
	$(CC) $(CFLAGS) $^ -o $@

array_benchmark: array_benchmark.cc
	$(CPP) $(CFLAGS) array_benchmark.cc -o array_benchmark

clean:
	rm $(TARGETS) *.o
