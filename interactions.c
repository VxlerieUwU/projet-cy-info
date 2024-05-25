#include "CosmicYonder.h"
#include "logger.h"

void interactions(int touche, Joueur* joueur, Salle ** carte, int salles_existantes, WINDOW* mainwin, int* nb_obj_inv, int* nb_obj_spe_inv){
	if (joueur == NULL){
		exit(1);
	}
	if(carte == NULL){
		exit(2);
	}
	if(joueur->pv<=0){
		reapparition_joueur(joueur, carte,salles_existantes);
	}
	int mouv; //Stocke le mouvement voulu par le joueur
	switch(touche){
		/*change la position du joueur et efface le caractere qui se trouve a sa position actuelle
		Les conditions verifient que le caractere d a cote est un espace ou une porte, pour les collisions
		si l'espace est libre, l'ensemble des salles est deplace dans la direction opposee a la fleche pressee*/
		case KEY_UP:
			mouv = mvwinch(mainwin, joueur->y-1, joueur->x); //Le mouvement est vers le haut
			//Si la case est un objet ou une porte ou est vide le carte se déplace relativement au joueur selon le sens opposé de mouv
			if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){ 
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->y++;
					//modifie la position des objets de la salle
					for(int j=0;j<3;j++){
						if(&(carte[i]->objets[j])!=NULL){
							carte[i]->objets[j].y++;					
						}	
					}
				}
			}
			else{
				//Sinon si la case à l'arrivée du mouv est un ennemi : l'ennemi perd des pvs et le joueur reste à sa place
				for(int i = 0; i < salles_existantes; i++) {
					if(carte[i]->ennemi!=NULL && carte[i]->ennemi->xGlobal == joueur->x && carte[i]->ennemi->yGlobal == joueur->y-1){
						perte_vie_ennemi(carte[i]->ennemi, joueur);
					}
				}
			}
			break;
		case KEY_DOWN:
			mouv = mvwinch(mainwin, joueur->y+1, joueur->x); //Le mouvement est vers le bas
			//Si la case est un objet ou une porte ou est vide le carte se déplace relativement au joueur selon le sens opposé de mouv
			if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->y--;
					//modifie la position des objets de la salle
					for(int j=0;j<3;j++){
						if(&(carte[i]->objets[j])!=NULL){
							carte[i]->objets[j].y--;					
						}	
					}
				}
			}
			else{
				//Sinon si la case à l'arrivée du mouv est un ennemi : l'ennemi perd des pvs et le joueur reste à sa place
				for(int i = 0; i < salles_existantes; i++) {
					if(carte[i]->ennemi!=NULL && carte[i]->ennemi->xGlobal == joueur->x && carte[i]->ennemi->yGlobal == joueur->y+1){
						perte_vie_ennemi(carte[i]->ennemi, joueur);
					}
				}
			}
			break;
		case KEY_LEFT:
			mouv = mvwinch(mainwin, joueur->y, joueur->x-1); //Le mouvement est à gauche
			//Si la case est un objet ou une porte ou est vide le carte se déplace relativement au joueur selon le sens opposé de mouv
			if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->x++;
					//modifie la position des objets de la salle
					for(int j=0;j<3;j++){
						if(&(carte[i]->objets[j])!=NULL){
							carte[i]->objets[j].x++;					
						}	
					}
				}
			}
			else{
				//Sinon si la case à l'arrivée du mouv est un ennemi : l'ennemi perd des pvs et le joueur reste à sa place
				for(int i = 0; i < salles_existantes; i++) {
					if(carte[i]->ennemi!=NULL && carte[i]->ennemi->xGlobal == joueur->x-1 && carte[i]->ennemi->yGlobal == joueur->y){
						perte_vie_ennemi(carte[i]->ennemi, joueur);
					}
				}
			}
			break;
		case KEY_RIGHT:
			mouv = mvwinch(mainwin, joueur->y, joueur->x+1); //Le mouvement est à droite
			//Si la case est un objet ou une porte ou est vide le carte se déplace relativement au joueur selon le sens opposé de mouv
			if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
				for(int i = 0; i < salles_existantes; i++) {
					carte[i]->x--;				
					//modifie la position des objets de la salle
					for(int j=0;j<3;j++){
						if(&(carte[i]->objets[j])!=NULL){
							carte[i]->objets[j].x--;					
						}	
					}
				}
			}
			else{
				//Sinon si la case à l'arrivée du mouv est un ennemi : l'ennemi perd des pvs et le joueur reste à sa place
				for(int i = 0; i < salles_existantes; i++) {
					if(carte[i]->ennemi!=NULL && carte[i]->ennemi->xGlobal == joueur->x+1 && carte[i]->ennemi->yGlobal == joueur->y){
						perte_vie_ennemi(carte[i]->ennemi, joueur);
					}
				}
			}
			break;
		case 'e':
			//parcours chaque objet de la carte et appelle la fonction recup_objet si l objet existe
			for(int i=0;i < salles_existantes; i++){
				for(int j=0;j<3;j++){
					if(&(carte[i]->objets[j])!=NULL){
						if(carte[i]->objets[j].x == joueur->x && carte[i]->objets[j].y == joueur->y){
							recup_objet(joueur,carte[i],&(carte[i]->objets[j]),nb_obj_inv,nb_obj_spe_inv);
							desapparition_objet(&(carte[i]->objets[j]), carte[i], joueur, mainwin);
						}						
					}	
				}
			}
			break;
		default:
			break;
	}
}