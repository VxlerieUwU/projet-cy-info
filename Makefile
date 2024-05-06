CC=gcc
CFLAGS=-W -Wall -ggdb 
LDFLAGS=-lncurses -fsanitize=address
EXEC=jeu

all: main

main: logger.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

logger.o: logger.c
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c logger.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
