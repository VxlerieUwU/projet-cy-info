#include "CosmicYonder.h"
#include "logger.h"

void interactions(int touche, Joueur* joueur, WINDOW* mainwin, char* logBuffer, Salle* salle){
	switch(touche){
		//change la position du joueur et efface le caractere qui se trouve a sa position actuelle
		case KEY_UP:
			if(mvwinch(mainwin, joueur->y-1, joueur->x)==' '||mvwinch(mainwin, joueur->y-1, joueur->x)=='P'){ /*verifie que le caractere d a cote 
				est un espace ou une porte, pour les collisions*/
				mvwaddch(mainwin,joueur->y,joueur->x,' ');
				joueur->y--;
			}
			break;
		case KEY_DOWN:
			if(mvwinch(mainwin, joueur->y+1, joueur->x)==' '||mvwinch(mainwin, joueur->y+1, joueur->x)=='P'){
				mvwaddch(mainwin,joueur->y,joueur->x,' ');
				joueur->y++;
			}
			break;
		case KEY_LEFT:
			if(mvwinch(mainwin, joueur->y, joueur->x-1)==' '||mvwinch(mainwin, joueur->y, joueur->x-1)=='P'){
				mvwaddch(mainwin,joueur->y,joueur->x,' ');
				joueur->x--;
			}
			break;
		case KEY_RIGHT:
			if(mvwinch(mainwin, joueur->y, joueur->x+1)==' '||mvwinch(mainwin, joueur->y, joueur->x+1)=='P'){
				mvwaddch(mainwin,joueur->y,joueur->x,' ');
				joueur->x++;
			}
			break;
		case KEY_BACKSPACE:
			sprintf(logBuffer, "position joueur x = %d, y = %d", joueur->x, joueur->y);
			logMessage(DEBUG, logBuffer);
			clearBuf(logBuffer);
			if(salle != NULL) {
				libereSalle(salle);
			}
			salle = creerSalleProced(joueur->x, joueur->y,0);
			break;
		default:
			break;
	}
}