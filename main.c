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
	int nsalles = MAX_SALLES;
	int i = 1;
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

    Salle** carte;
    carte = malloc(MAX_SALLES * sizeof(Salle));
    if(carte == NULL) {
    	logMessage(CRITICAL, "erreur malloc portes salle");
    	exit(2);
    }   

	carte[0] = creerSalleProced(joueur.x-2, joueur.y-2,-1,mainwin, &nsalles);
	dessineSalle(mainwin, carte[0]);
	
	mvwaddch(mainwin,joueur.y, joueur.x, 'o'); // positionne le curseur au centre de l ecran
	//pour l instant, j ai represente le joueur avec le caractere 'o' pour tester le programme

	int touche = wgetch(mainwin);//recupere touche pressee

    logMessage(INFO, "fin init");
	while(touche!=ESC){ // BOUCLE DU JEU
		interactions(touche, &joueur, carte, i, mainwin);

		/*conditions servent a creer une salle quand le joueur passe devant une porte, 
		en fonction de la position de la porte par rapport au joueur*/
		if(mvwinch(mainwin, joueur.y-1, joueur.x)=='P'){ //porte en haut
			if(carte[i] != NULL) {  
				libereSalle(carte[i]);
			}
			mvwaddch(mainwin,joueur.y-1,joueur.x,' ');
			carte[i] = creerSalleProced(joueur.x, joueur.y,HAUT,mainwin, &nsalles);
			mvwaddch(mainwin,joueur.y-2,joueur.x,' ');
			i = MAX_SALLES - nsalles - 1;
		}
		if(mvwinch(mainwin, joueur.y+1, joueur.x)=='P'){ //porte en bas
			if(carte[i] != NULL) {
				libereSalle(carte[i]);
			}
			mvwaddch(mainwin,joueur.y+1,joueur.x,' ');
			carte[i] = creerSalleProced(joueur.x, joueur.y,BAS,mainwin,&nsalles);
			mvwaddch(mainwin,joueur.y+2,joueur.x,' ');
			i = MAX_SALLES - nsalles - 1;

		}
		if(mvwinch(mainwin, joueur.y, joueur.x-1)=='P'){ //porte a gauche
			if(carte[i] != NULL) {
				libereSalle(carte[i]);
			}
			mvwaddch(mainwin,joueur.y,joueur.x-1,' ');
			carte[i] = creerSalleProced(joueur.x, joueur.y,GAUCHE,mainwin,&nsalles);
			mvwaddch(mainwin,joueur.y,joueur.x-2,' ');
			i = MAX_SALLES - nsalles - 1;
		}
		if(mvwinch(mainwin, joueur.y, joueur.x+1)=='P'){ //porte a droite
			if(carte[i] != NULL) {e
				libereSalle(carte[i]);
			}
			mvwaddch(mainwin,joueur.y,joueur.x+1,' ');
			carte[i] = creerSalleProced(joueur.x, joueur.y,DROITE,mainwin,&nsalles);
			mvwaddch(mainwin,joueur.y,joueur.x+2,' ');
			i = MAX_SALLES - nsalles - 1;
		}	
		wclear(mainwin);
		mvwaddch(mainwin,joueur.y,joueur.x, 'o'); //deplace le joueur a la nouvelle position
		dessineSalles(mainwin, carte, i);
		wrefresh(mainwin);
		touche = wgetch(mainwin);
   		usleep(100);
	}
    logMessage(INFO, "fin du programme");
    for(int i=0;i<nsalles;i++){
    	libereSalle(carte[i]);
    }
	endwin();//ferme la fenetre
    moveLog();
	return 0;
}
