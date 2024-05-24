#include "CosmicYonder.h"
#include "logger.h"

void interactions(int touche, Joueur* joueur, Salle ** carte, int salles_existantes, WINDOW* mainwin){
	int mouv; //Stocke le mouvement voulu par le joueur
	switch(touche){
		/*change la position du joueur et efface le caractere qui se trouve a sa position actuelle
		Les conditions verifient que le caractere d a cote est un espace ou une porte, pour les collisions
		si l'espace est libre, l'ensemble des salles est deplace dans la direction opposee a la fleche pressee*/
		case KEY_UP:
			mouv = mvwinch(mainwin, joueur->y-1, joueur->x); //Le mouvement est vers le bas
			if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){ 
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->y++;
				}
			}
			break;
		case KEY_DOWN:
			mouv = mvwinch(mainwin, joueur->y+1, joueur->x); //Le mouvement est vers le haut
			if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->y--;

				}
			}
			break;
		case KEY_LEFT:
			mouv = mvwinch(mainwin, joueur->y, joueur->x-1); //Le mouvement est à gauche
			if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->x++;
				}
			}
			break;
		case KEY_RIGHT:
			mouv = mvwinch(mainwin, joueur->y, joueur->x+1); //Le mouvement est à droite
			if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->x--;
				}
			}
			break;
		default:
			break;
	}
}

void collisions_objet(Joueur* joueur, Salle* salle, Objet objet, int* nb_obj_inv, int* nb_obj_spe_inv){
	
	if(joueur == NULL || salle == NULL || nb_obj_inv == NULL || nb_obj_spe_inv == NULL){
		exit(1);
	}

	if(objet.id<11 && nb_obj_inv <= INV_TAILLE - 1){
		joueur->xp += 20;
		joueur->inventaire[nb_obj_inv+4] = objet;
		salle->disp[objet.y-salle->y][objet.x-salle->x] = VIDE;
		(*nb_obj_inv)++;
	}
	else{
		joueur->xp += 20;
		joueur->inventaire[nb_obj_spe_inv] = objet;
		salle->disp[objet.y-salle->y][objet.x-salle->x] = VIDE;
		(*nb_obj_spe_inv)++;
	}
}