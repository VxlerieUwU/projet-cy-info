CC=gcc
CFLAGS=-W -Wall -ggdb -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600
LDFLAGS=-lncursesw
EXEC=jeu

all: jeu

jeu: logger.o graphics.o salles.o joueur.o main.o interactions.o
	$(CC) -o $@ $^ $(LDFLAGS)

logger.o: logger.c
	$(CC) -o $@ -c $< $(CFLAGS)

graphics.o: graphics.c
	$(CC) -o $@ -c $< $(CFLAGS)

salles.o: salles.c
	$(CC) -o $@ -c $< $(CFLAGS)

joueur.o: joueur.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
interactions.o: interactions.c
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c logger.c graphics.c salles.c joueur.c interactions.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
