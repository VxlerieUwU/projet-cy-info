all: main

main: logger.o main.o
	gcc -o jeu -lncurses logger.o main.o

logger.o: logger.c
	gcc -o logger.o -c logger.c -W -Wall -pedantic

main.o: main.c logger.c
	gcc -o main.o -c main.c -W -Wall -pedantic

clean:
	rm -rf *.o

mrproper: clean
	rm -rf jeu
