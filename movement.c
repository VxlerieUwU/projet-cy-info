#include <ncurses.h>
#define ESC 27

int main(int argc, char const *argv[])
{
	initscr(); //initialise l'ecran
	noecho(); //empeche d'afficher les caracteres saisis dans le terminal
	cbreak(); //permet de quitter le programme avec Ctrl+c
	curs_set(0); //rend le curseur invisible

	int width, height;
	getmaxyx(stdscr,height,width); //recupere la taille du terminal

	WINDOW* mainwin = newwin(height,width,0,0); 
	// creer une fenetre de la taille du terminal ou le coin superieur gauche est a la position (0,0)
	
	box(mainwin,0,0); //creer un rectangle qui represente les bordures de l ecran
	refresh();
	wrefresh(mainwin); 
	//refresh et wrefresh permettent de rafraichir l ecran pour y afficher ce qui est contenu dans la memoire

	keypad(mainwin, true); // active la possibilite de lire certains caracteres commes les fleches du clavier

	int x =width/2;
	int y =height/2;
	mvwaddch(mainwin,y,x,'o'); // positionne le curseur au centre de l ecran
	//pour l instant, j ai represente le joueur avec le caractere 'o' pour tester le programme

	int key = wgetch(mainwin);//recupere touche pressee

	while(key!=ESC){ //boucle tant que la touche echap n est pas pressee
		switch(key){
			//change la position du joueur et efface le caractere qui se trouve a sa position actuelle
			case KEY_UP:
				mvwaddch(mainwin,y,x,' ');
				y--;
				break;
			case KEY_DOWN:
				mvwaddch(mainwin,y,x,' ');
				y++;
				break;
			case KEY_LEFT:
				mvwaddch(mainwin,y,x,' ');
				x--;
				break;
			case KEY_RIGHT:
				mvwaddch(mainwin,y,x,' ');
				x++;
				break;
			default:
				break;
		}
		mvwaddch(mainwin,y,x,'o'); //deplace le joueur a la nouvelle position
		wrefresh(mainwin);
		key = wgetch(mainwin);
	}

	endwin();//ferme la fenetre

	return 0;
}