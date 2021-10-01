all: pig

pig : pig.o
	$(CC) -o pig pig.o

pig.o: pig.c names.h
	$(CC) $(CFLAGS) -c pig.c

clean:
	rm -f pig pig.o

format:
	clang-format -i -style=pig *.[c,h]
