#include "CosmicYonder.h"
#include "logger.h"

void interactions(int touche, Joueur* joueur, WINDOW* mainwin, char* logBuffer, Salle* salle){
	switch(touche){
			//change la position du joueur et efface le caractere qui se trouve a sa position actuelle
			case KEY_UP:
				mvwaddch(mainwin,joueur->y,joueur->x,' ');
				joueur->y--;
				break;
			case KEY_DOWN:
				mvwaddch(mainwin,joueur->y,joueur->x,' ');
				joueur->y++;
				break;
			case KEY_LEFT:
				mvwaddch(mainwin,joueur->y,joueur->x,' ');
				joueur->x--;
				break;
			case KEY_RIGHT:
				mvwaddch(mainwin,joueur->y,joueur->x,' ');
				joueur->x++;
				break;
            case KEY_BACKSPACE:
                sprintf(logBuffer, "position joueur x = %d, y = %d", joueur->x, joueur->y);
                logMessage(DEBUG, logBuffer);
				clearBuf(logBuffer);
				if(salle != NULL) {
					libereSalle(salle);
				}
				salle = creerSalleProced(joueur->x, joueur->y);
                break;
			default:
				break;
	}
}