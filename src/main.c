#include <ncurses.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#define ESC 27
#define INV_SIZE 10 

enum level {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

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

int createLog() {
    FILE* file = fopen("latest.log", "w");
    if (file == NULL) {
        return -1;
    }
    fclose(file);
    return 0;
}

int logMessage(char* filename, int level, char* message) {
    
    char instant[51];
    char niveau[10];
    
    
    time_t t = time(NULL);
    tzset();

    strftime(instant, sizeof(instant) - 1, "%a %b %d %T %Z %Y", localtime(&t));
    
    FILE* file = fopen("latest.log", "a");
    if(file == NULL) {
        return -1;
    }
    switch(level) {
        case DEBUG:
            sprintf(niveau, "DEBUG");
            break;
        case INFO:
            sprintf(niveau, "INFO");
            break;
        case WARNING:
            sprintf(niveau, "WARNING");
            break;
        case ERROR:
            sprintf(niveau, "ERROR");
            break;
        case CRITICAL:
            sprintf(niveau, "CRITICAL");
            break;
        default:
            sprintf(niveau, "UNKNOWN");
            break;
    }

    fprintf(file, "[%s] %s %s\n", instant, niveau, message);
    fclose(file);
    return 0;
}


void initJoueur(Joueur* joueur){
    joueur->hp = 100;
    joueur->xp = 0;
    joueur->lvl = 1;
} 

int main(int argc, char const *argv[])
{
    createLog();
    logMessage("latest.log", INFO, "init ncurses");
	initscr(); //initialise l'ecran
	noecho(); //empeche d'afficher les caracteres saisis dans le terminal
	cbreak(); //permet de quitter le programme avec Ctrl+c
	curs_set(0); //rend le curseur invisible
	int width, height;
	getmaxyx(stdscr,height,width); //recupere la taille du terminal

	WINDOW* mainwin = newwin(height,width,0,0); 
    char msg4[255];
    sprintf(msg4, "window width = %d, height = %d", width, height);
    logMessage("latest.log", INFO, msg4);
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


    logMessage("latest.log", INFO, "fin init");
	while(key!=ESC){ // BOUCLE DU JEU
        char message[255];
        char message2[255];
        sprintf(message, "key pressed: %d", key);
        logMessage("latest.log", INFO, message);
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
                logMessage("latest.log", DEBUG, message2);
                break;
			default:
				break;
		}
		mvwaddch(mainwin,joueur.y,joueur.x, 'o'); //deplace le joueur a la nouvelle position
		wrefresh(mainwin);
		key = wgetch(mainwin);
        usleep(100);
	}
    logMessage("latest.log", INFO, "fin du programme");

	endwin();//ferme la fenetre
	return 0;
}