COMPILER = gcc
CFLAGS = -Wall -g -c


hash: hash.o
	$(COMPILER) -o hash.out hash.o
	rm hash.o

hash.o: hash.c
	$(COMPILER) $(CFLAGS) -o hash.o hash.c



fw: fw.o
	$(COMPILER) -o fw.out fw.o
	rm fw.o

fw.o: fw.c
	$(COMPILER) $(CFLAGS) -o fw.o fw.c



sort: sort.o
	$(COMPILER) -o sort.out sort.o
	rm sort.o

compare.o: sort.c
	$(COMPILER) $(CFLAGS) -o sort.o sort.c
