COMPILER = gcc
CFLAGS = -Wall -g -c


DEFAULT: hash.o
	$(COMPILER) -o hash.out hash.o
	rm hash.o

clean:
	rm hash.o

uniq: hash.o
	$(COMPILER) -o hash.out hash.o