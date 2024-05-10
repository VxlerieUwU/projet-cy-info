#include "CosmicYonder.h"
#include "logger.h"

int main()
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

	WINDOW* mainwin = newwin(hauteur,longueur,0,0); 

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

    joueur.x = longueur/2;
    joueur.y = hauteur/2;

	Salle * salle = creerSalleProced(joueur.x-2, joueur.y-2,0,mainwin);
	dessineSalle(mainwin, salle);
	
	mvwaddch(mainwin,joueur.y, joueur.x, 'o'); // positionne le curseur au centre de l ecran
	//pour l instant, j ai represente le joueur avec le caractere 'o' pour tester le programme

	int touche = wgetch(mainwin);//recupere touche pressee

    logMessage(INFO, "fin init");
	while(touche!=ESC){ // BOUCLE DU JEU
		interactions(touche, &joueur, mainwin, logBuffer, salle);

		if(mvwinch(mainwin, joueur.y-1, joueur.x)=='P'){ /*l50 a 77 :
		conditions servent a creer une salle quand le joueur passe devant une porte*/
			if(salle != NULL) {
				libereSalle(salle);
			}
			mvwaddch(mainwin,joueur.y-1,joueur.x,' ');
			salle = creerSalleProced(joueur.x, joueur.y,2,mainwin);
			dessineSalle(mainwin, salle);
			mvwaddch(mainwin,joueur.y-2,joueur.x,' ');
		}
		if(mvwinch(mainwin, joueur.y+1, joueur.x)=='P'){
			if(salle != NULL) {
				libereSalle(salle);
			}
			mvwaddch(mainwin,joueur.y+1,joueur.x,' ');
			salle = creerSalleProced(joueur.x, joueur.y,4,mainwin);
			dessineSalle(mainwin, salle);
			mvwaddch(mainwin,joueur.y+2,joueur.x,' ');
		}
		if(mvwinch(mainwin, joueur.y, joueur.x-1)=='P'){
			if(salle != NULL) {
				libereSalle(salle);
			}
			mvwaddch(mainwin,joueur.y,joueur.x-1,' ');
			salle = creerSalleProced(joueur.x, joueur.y,1,mainwin);
			dessineSalle(mainwin, salle);
			mvwaddch(mainwin,joueur.y,joueur.x-2,' ');
		}
		if(mvwinch(mainwin, joueur.y, joueur.x+1)=='P'){
			if(salle != NULL) {
				libereSalle(salle);
			}
			mvwaddch(mainwin,joueur.y,joueur.x+1,' ');
			salle = creerSalleProced(joueur.x, joueur.y,3,mainwin);
			dessineSalle(mainwin, salle);
			mvwaddch(mainwin,joueur.y,joueur.x+2,' ');
		}

		mvwaddch(mainwin,joueur.y,joueur.x, 'o'); //deplace le joueur a la nouvelle position

		wrefresh(mainwin);
		touche = wgetch(mainwin);
   		usleep(100);
	}
    logMessage(INFO, "fin du programme");
	libereSalle(salle);
	endwin();//ferme la fenetre
    moveLog();
	return 0;
}
