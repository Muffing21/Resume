CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: sorting

sorting: sorting.o insert.o heap.o quick.o stats.o shell.o
	$(CC) $(LFLAGS) -o sorting sorting.o insert.o heap.o quick.o stats.o shell.o

sorting.o: sorting.c heap.h insert.h quick.h set.h shell.h stats.h
	$(CC) $(CFLAGS) -c sorting.c

insert.o: insert.c insert.h
	$(CC) $(CFLAGS) -c insert.c

heap.o: heap.c heap.h 
	$(CC) $(CFLAGS) -c heap.c

quick.o: quick.c quick.h
	$(CC) $(CFLAGS) -c quick.c

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f sorting sorting.o insert.o heap.o quick.o shell.o

format:
	clang-format -i -style=file *.[ch]

