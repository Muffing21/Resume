CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
LFLAGS = -lm

all: banhammer

banhammer: banhammer.o speck.o ht.o bst.o node.o bf.o bv.o parser.o
	$(CC) $(LFLAGS) -o banhammer banhammer.o ht.o bst.o node.o bf.o bv.o parser.o

banhammer.o: banhammer.c 
	$(CC) $(CFLAGS) -c banhammer.c

ht.o: ht.c ht.h
	$(CC) $(CFLAGS) -c ht.c

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

bf.o: bf.c bf.h
	$(CC) $(CFLAGS) -c bf.c

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c

parser.o: parser.c parser.h
	$(CC) $(LFLAGS) -c parser.c

clean:
	rm -f banhammer banhammer.o ht.o bst.o node.o bf.o bv.o parser.o

format:
	clang-format -i -style=file *.[ch]

