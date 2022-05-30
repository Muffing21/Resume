CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
LFLAGS = -lm

all: tsp

tsp: tsp.o graph.o stack.o path.o
	$(CC) $(LFLAGS) -o tsp tsp.o graph.o stack.o path.o

tsp.o: tsp.c graph.h stack.h path.h
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c graph.h vertices.h
	$(CC) $(CFLAGS) -c graph.c

path.o: path.c path.h 
	$(CC) $(CFLAGS) -c path.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f tsp tsp.o graph.o path.o stack.o

format:
	clang-format -i -style=file *.[ch]

