#include "CosmicYonder.h"

int main(int argc, char const *argv[])
{
	char logBuffer[255];

	setlocale(LC_ALL,""); // nécessaire pour UTF-8

    createLog();
    logMessage(INFO, "init ncurses");
	srand(time(NULL)); //init rand 
	initscr(); //initialise l'ecran
	noecho(); //empeche d'afficher les caracteres saisis dans le terminal
	cbreak(); //permet de quitter le programme avec Ctrl+c
	curs_set(0); //rend le curseur invisible
	int hauteur, longueur;
	getmaxyx(stdscr,hauteur,longueur); //recupere la taille du terminal

	WINDOW* mainwin = newwin(height,width,0,0); 

    sprintf(logBuffer, "window longueur = %d, hauteur = %d", longueur, hauteur);
    logMessage(INFO, logBuffer);
	clearBuf(logBuffer);

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
	Salle * salle = creerSalleProced(joueur.x, joueur.y);

	mvwaddch(mainwin,joueur.y, joueur.x, 'o'); // positionne le curseur au centre de l ecran
	//pour l instant, j ai represente le joueur avec le caractere 'o' pour tester le programme

	int cle = wgetch(mainwin);//recupere touche pressee

    logMessage(INFO, "fin init");
	while(cle!=ESC){ // BOUCLE DU JEU
		switch(cle){
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
                sprintf(logBuffer, "position joueur x = %d, y = %d", joueur.x, joueur.y);
                logMessage(DEBUG, logBuffer);
				clearBuf(logBuffer);
				if(salle != NULL) {
					libereSalle(salle);
				}
				salle = creerSalleProced(joueur.x, joueur.y);
                break;
			default:
				break;
		}
		mvwaddch(mainwin,joueur.y,joueur.x, 'o'); //deplace le joueur a la nouvelle position
		if(salle != NULL) {
			dessineSalle(mainwin, salle);
		}
		wrefresh(mainwin);
		key = wgetch(mainwin);
        usleep(100);
	}
    logMessage(INFO, "fin du programme");
	libereSalle(salle);
	endwin();//ferme la fenetre
    moveLog();
	return 0;
}
