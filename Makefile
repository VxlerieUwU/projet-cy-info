CC=gcc
CFLAGS=-W -Wall -ggdb -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600
LDFLAGS=-lncursesw
EXEC=jeu

all: jeu

jeu: logger.o main.o graphics.o salles.o
	$(CC) -o $@ $^ $(LDFLAGS)

logger.o: logger.c
	$(CC) -o $@ -c $< $(CFLAGS)

graphics.o: graphics.c
	$(CC) -o $@ -c $< $(CFLAGS)

salles.o: salles.c
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c logger.c graphics.c salles.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
