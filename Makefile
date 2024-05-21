CC=gcc
CFLAGS=-W -Wall -ggdb -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -std=gnu11
LDFLAGS=-lncursesw
EXEC=jeu

all: jeu

<<<<<<< HEAD
jeu: logger.o graphics.o objet.o salles.o joueur.o main.o interactions.o graine.o ennemi.o porte.o ui/menu.o ui/ui.o
=======
jeu: logger.o graphics.o salles.o joueur.o main.o interactions.o graine.o ennemi.o porte.o ui/menu.o ui/ui.o json/json.o
>>>>>>> 56e101d7af19962534155725c990427775db4e29
	$(CC) -o $@ $^ $(LDFLAGS)

ui/menu.o: ui/menu.c
	$(CC) -o $@ -c $< $(CFLAGS)

ui/ui.o: ui/ui.c
	$(CC) -o $@ -c $< $(CFLAGS)

logger.o: logger.c
	$(CC) -o $@ -c $< $(CFLAGS)

graphics.o: graphics.c
	$(CC) -o $@ -c $< $(CFLAGS)

graine.o: graine.c
	$(CC) -o $@ -c $< $(CFLAGS)

objet.o: objet.c
	$(CC) -o $@ -c $< $(CFLAGS)

salles.o: salles.c
	$(CC) -o $@ -c $< $(CFLAGS)

joueur.o: joueur.c
	$(CC) -o $@ -c $< $(CFLAGS)

interactions.o: interactions.c
	$(CC) -o $@ -c $< $(CFLAGS)

ennemi.o: ennemi.c
	$(CC) -o $@ -c $< $(CFLAGS)

porte.o: porte.c
	$(CC) -o $@ -c $< $(CFLAGS)

<<<<<<< HEAD
main.o: main.c logger.c graphics.c objet.c salles.c joueur.c  interactions.c ennemi.c graine.c porte.c ui/menu.c ui/ui.c
=======
json/json.o: json/json.c
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c logger.c graphics.c salles.c joueur.c interactions.c ennemi.c graine.c porte.c ui/menu.c ui/ui.c json/json.c
>>>>>>> 56e101d7af19962534155725c990427775db4e29
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf ui/*.o
	rm -rf json/*.o

mrproper: clean
	rm -rf $(EXEC)
