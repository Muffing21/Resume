CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g $(shell pkg-config --cflags gmp)
LDFLAGS = $(shell pkg-config --libs gmp)
COMMON_OBJS = rsa.o randstate.o numtheory.o
LFLAGS = -lm

all: encrypt decrypt keygen

encrypt: encrypt.o numtheory.o randstate.o rsa.o
	$(CC) $(LDFLAGS) -o encrypt encrypt.o numtheory.o randstate.o rsa.o

decrypt: decrypt.o numtheory.o randstate.o rsa.o
	$(CC) $(LDFLAGS) -o decrypt decrypt.o numtheory.o randstate.o rsa.o

keygen: keygen.o numtheory.o randstate.o rsa.o
	$(CC) $(LDFLAGS) -o keygen keygen.o numtheory.o randstate.o rsa.o

encrypt.o: encrypt.c randstate.h numtheory.h
	$(CC) $(CFLAGS) -c encrypt.c

decrypt.o: decrypt.c randstate.h numtheory.h
	$(CC) $(CFLAGS) -c decrypt.c

keygen.o: keygen.c randstate.h numtheory.h
	$(CC) $(CFLAGS) -c keygen.c

numtheory.o: numtheory.c numtheory.h 
	$(CC) $(CFLAGS) -c numtheory.c

randstate.o: randstate.c randstate.h
	$(CC) $(CFLAGS) -c randstate.c

clean:
	rm -f decrypt decrypt.o encrypt encrypt.o keygen keygen.o numtheory.o randstate.o rsa.o

format:
	clang-format -i -style=file *.[ch]

