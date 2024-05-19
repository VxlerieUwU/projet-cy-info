#include "CosmicYonder.h"
#include "logger.h"

void interactions(int touche, Joueur* joueur, Salle ** carte, int salles_existantes, WINDOW* mainwin){
	switch(touche){
		/*change la position du joueur et efface le caractere qui se trouve a sa position actuelle
		Les conditions verifient que le caractere d a cote est un espace ou une porte, pour les collisions
		si l'espace est libre, l'ensemble des salles est deplace dans la direction opposee a la fleche pressee*/
		case KEY_UP:
			if(mvwinch(mainwin, joueur->y-1, joueur->x)==' '){ 
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->y++;
				}
			}
			break;
		case KEY_DOWN:
			if(mvwinch(mainwin, joueur->y+1, joueur->x)==' '){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->y--;

				}
			}
			break;
		case KEY_LEFT:
			if(mvwinch(mainwin, joueur->y, joueur->x-1)==' '){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->x++;
				}
			}
			break;
		case KEY_RIGHT:
			if(mvwinch(mainwin, joueur->y, joueur->x+1)==' '){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->x--;
				}
			}
			break;
		default:
			break;
	}
}