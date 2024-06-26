CC=gcc
CFLAGS=-W -Wall -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -std=gnu11
LDFLAGS=-lncursesw
EXEC=jeu

all: jeu

jeu: logger.o objet.o salles.o joueur.o main.o interactions.o graine.o ennemi.o porte.o partie.o ui/menu.o ui/ui.o ui/hud.o json/json.o sauvegarde.o
	$(CC) -o $@ $^ $(LDFLAGS)

sauvegarde.o: sauvegarde.c
	$(CC) -o $@ -c $< $(CFLAGS)

json/json.o: json/json.c
	$(CC) -o $@ -c $< $(CFLAGS)

ui/menu.o: ui/menu.c
	$(CC) -o $@ -c $< $(CFLAGS)

ui/ui.o: ui/ui.c
	$(CC) -o $@ -c $< $(CFLAGS)

ui/hud.o: ui/hud.c
	$(CC) -o $@ -c $< $(CFLAGS)

logger.o: logger.c
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

partie.o: partie.c
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c logger.c objet.c salles.c joueur.c  interactions.c ennemi.c graine.c porte.c ui/menu.c ui/ui.c ui/hud.c json/json.c sauvegarde.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf ui/*.o
	rm -rf json/*.o

mrproper: clean
	rm -rf $(EXEC)
