#include <ncurses.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#include "logger.h"

#define ESC 27
#define INV_SIZE 10 


typedef struct {
    char name[255];
    int count;
    int id;
}Item;

typedef struct{
	Item ItTab[INV_SIZE]; //l'inventaire est un tableau d'objets (a definir)
}Inventory;

typedef struct{
	int hp;
	int xp;
	int lvl;
	Inventory inventory;
	int x;
	int y;
}Joueur;

void initJoueur(Joueur* joueur){
    joueur->hp = 100;
    joueur->xp = 0;
    joueur->lvl = 1;
} 

int main(int argc, char const *argv[])
{
    
    createLog();
    logMessage(INFO, "init ncurses");
	initscr(); //initialise l'ecran
	noecho(); //empeche d'afficher les caracteres saisis dans le terminal
	cbreak(); //permet de quitter le programme avec Ctrl+c
	curs_set(0); //rend le curseur invisible
	int width, height;
	getmaxyx(stdscr,height,width); //recupere la taille du terminal

	WINDOW* mainwin = newwin(height,width,0,0); 
    char msg4[255];
    sprintf(msg4, "window width = %d, height = %d", width, height);
    logMessage(INFO, msg4);
	// creer une fenetre de la taille du terminal ou le coin superieur gauche est a la position (0,0)
	
	box(mainwin,0,0); //creer un rectangle qui represente les bordures de l ecran
	refresh();
	wrefresh(mainwin); 
	//refresh et wrefresh permettent de rafraichir l ecran pour y afficher ce qui est contenu dans la memoire
	keypad(mainwin, true); // active la possibilite de lire certains caracteres commes les fleches du clavier

    Joueur joueur;
    initJoueur(&joueur);

    joueur.x = width/2;
    joueur.y = height/2;

	mvwaddch(mainwin,joueur.y, joueur.x, 'o'); // positionne le curseur au centre de l ecran
	//pour l instant, j ai represente le joueur avec le caractere 'o' pour tester le programme

	int key = wgetch(mainwin);//recupere touche pressee


    logMessage(INFO, "fin init");
	while(key!=ESC){ // BOUCLE DU JEU
        char message[255];
        char message2[255];
        sprintf(message, "key pressed: %d", key);
        logMessage(INFO, message);
		switch(key){
			//change la position du joueur et efface le caractere qui se trouve a sa position actuelle
                
			case KEY_UP:
				mvwaddch(mainwin,joueur.y,joueur.x,' ');
				joueur.y--;
				break;
			case KEY_DOWN:
				mvwaddch(mainwin,joueur.y,joueur.x,' ');
				joueur.y++;
				break;
			case KEY_LEFT:
				mvwaddch(mainwin,joueur.y,joueur.x,' ');
				joueur.x--;
				break;
			case KEY_RIGHT:
				mvwaddch(mainwin,joueur.y,joueur.x,' ');
				joueur.x++;
				break;
            case KEY_BACKSPACE:
                sprintf(message2, "position joueur x = %d, y = %d", joueur.x, joueur.y);
                logMessage(DEBUG, message2);
                break;
			default:
				break;
		}
		mvwaddch(mainwin,joueur.y,joueur.x, 'o'); //deplace le joueur a la nouvelle position
		wrefresh(mainwin);
		key = wgetch(mainwin);
        usleep(100);
	}
    logMessage(INFO, "fin du programme");

	endwin();//ferme la fenetre
    moveLog();
	return 0;
}