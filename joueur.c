#include "CosmicYonder.h"

void initJoueur(Joueur* joueur){
    /* Initialise les stats du joueur au début du jeu */
    if(joueur==NULL){
       exit(1); 
    }
    joueur->pv = 100;
    joueur->xp = 0;
    joueur->niv = 1;
    joueur->att = 10;
    joueur->def = 5;
} 

void maj_niveau(Joueur* joueur){
    /* Gère le gain de niveau du joueur en fonction de son expérience */
    if (joueur == NULL){
        exit(2);
    }
    joueur->niv = 1 + joueur->xp/100;
    joueur->pv = 100 + joueur->niv*20;
    joueur->att = 10 + joueur->niv*1;
    joueur->def = 5 + joueur->niv*1;
}

void perte_vie_joueur(Joueur* joueur, Ennemi* ennemi){
    /* Le joueur perd de la vie quand un ennemi est sur sa case en fonction 
    de la défense du joueur et de l'attaque de l'ennemi */
    if(joueur==NULL){
       exit(3); 
    }
    if(ennemi==NULL){
       exit(4); 
    }
    joueur-> pv -= ennemi->att -joueur->def;
}

void reapparition_joueur(Joueur* joueur, Salle** carte, int salles_existantes){
    /*calcule la distance entre le joueur et le point de depart et deplace la carte afin que le joueur soit de retour au centre de la premiere salle
    divise l'xp du joueur par 2 puis actualise son niveau et ses stats*/
    if(joueur==NULL){
        exit(5);
    }
    if(carte==NULL){
        exit(6);
    }
    int distx = carte[0]->x - joueur->x + carte[0]->longueur/2;
    int disty = carte[0]->y - joueur->y + carte[0]->hauteur/2;
    for(int i = 0; i < salles_existantes; i++) {
        carte[i]->x -= distx;
        carte[i]->y -= disty;
    }
    joueur->xp /= 2;
    maj_niveau(joueur);
}