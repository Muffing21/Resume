CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
LFLAGS = -lm

all: encode decode

encode: encode.o code.o io.o pq.o node.o huffman.o stack.o
	$(CC) $(LFLAGS) -o encode encode.o code.o io.o pq.o node.o huffman.o stack.o

decode: decode.o code.o io.o pq.o node.o huffman.o stack.o
	$(CC) $(LFLAGS) -o decode decode.o code.o io.o pq.o node.o huffman.o stack.o


encode.o: encode.c code.h io.h pq.h node.h huffman.h stack.h defines.h header.h
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c code.o io.h pq.h node.h huffman.h stack.h defines.h header.h
	$(CC) $(CFLAGS) -c decode.c

code.o: code.c code.h 
	$(CC) $(CFLAGS) -c code.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

pq.o: pq.c pq.h
	$(CC) $(CFLAGS) -c pq.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -c huffman.c

clean:
	rm -f decode decode.o encode encode.o code.o io.o pq.o node.o huffman.o stack.o

format:
	clang-format -i -style=file *.[ch]

