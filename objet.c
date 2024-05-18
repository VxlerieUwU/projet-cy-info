#include "CosmicYonder.h"

void apparition_objet(Salle* salle, Objet* objet){
    /* Fait apparaitre un objet Objet dans une salle Salle*/
    int x,y;

    //Vérification allocation salle
    if(salle == NULL){
        exit(2);
    }
	do{
        x = 1 + rand()%(((*salle).hauteur)-2); //Abscisse objet relative à la salle
        y = 1 + rand()%(((*salle).longueur)-2); //Ordonnée objet relative à la salle
        salle->disp[x][y];
    }while(salle->disp[x][y]!=VIDE); //Condition pour ne pas écraser un objet ou un monstre de la salle

    //Coordonnées absolues de l'objet pour collision joueur-objets
    objet->x = salle.x + x;
    objet->y = salle.y + y;
}

