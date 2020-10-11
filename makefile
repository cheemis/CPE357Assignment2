COMPILER = gcc
CFLAGS = -Wall -g -pedantic -c


hash: hash.o
	$(COMPILER) -o hash.out hash.o
	rm hash.o

hash.o: hash.c
	$(COMPILER) $(CFLAGS) -o hash.o hash.c

fw: fw.o hash.o sort.o
	$(COMPILER) -o fw fw.o hash.o sort.o
	rm fw.o hash.o sort.o

fw.o: fw.c
	$(COMPILER) $(CFLAGS) -o fw.o fw.c

sort: sort.o
	$(COMPILER) -o sort.out sort.o
	rm sort.o

compare.o: sort.c
	$(COMPILER) $(CFLAGS) -o sort.o sort.c

