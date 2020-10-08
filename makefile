COMPILER = gcc
CFLAGS = -Wall -g -pedantic -c


all: hash fw

hash: hash.o
	$(COMPILER) -o hash.out hash.o
	rm hash.o

hash.o: hash.c
	$(COMPILER) $(CFLAGS) -o hash.o hash.c

fw: fw.o hash.o
	$(COMPILER) -o fw.out fw.o hash.o
	rm fw.o hash.o

fw.o: fw.c
	$(COMPILER) $(CFLAGS) -o fw.o fw.c

sort: sort.o
	$(COMPILER) -o sort.out sort.o
	rm sort.o

compare.o: sort.c
	$(COMPILER) $(CFLAGS) -o sort.o sort.c

clean:
	rm -f fw.o hash.o *~
