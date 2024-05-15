#include "CosmicYonder.h"
#include "logger.h"

void interactions(int touche, Joueur* joueur, Salle ** carte, int salles_existantes, WINDOW* mainwin){
	switch(touche){
		//change la position du joueur et efface le caractere qui se trouve a sa position actuelle
		case KEY_UP:
			if(mvwinch(mainwin, joueur->y-1, joueur->x)==' '||mvwinch(mainwin, joueur->y-1, joueur->x)=='P'){ /*verifie que le caractere d a cote 
				est un espace ou une porte, pour les collisions*/
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->y++;
				}
			}
			break;
		case KEY_DOWN:
			if(mvwinch(mainwin, joueur->y+1, joueur->x)==' '||mvwinch(mainwin, joueur->y+1, joueur->x)=='P'){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->y--;

				}
			}
			break;
		case KEY_LEFT:
			if(mvwinch(mainwin, joueur->y, joueur->x-1)==' '||mvwinch(mainwin, joueur->y, joueur->x-1)=='P'){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->x++;
				}
			}
			break;
		case KEY_RIGHT:
			if(mvwinch(mainwin, joueur->y, joueur->x+1)==' '||mvwinch(mainwin, joueur->y, joueur->x+1)=='P'){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->x--;
				}
			}
			break;
		default:
			break;
	}
}