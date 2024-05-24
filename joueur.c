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

int maj_niveau(Joueur* joueur){
    /* Gère le gain de niveau du joueur en fonction de son expérience */
    if (joueur == NULL){
        exit(2);
    }
    return joueur-> niv = 1 + joueur->xp/100;
}

void perte_vie_joueur(Joueur* joueur, Ennemi* ennemi){
    /* Le joueur perd de la vie quand un ennemi est sur sa case en fonction de la défense du joueur et de l'attaque de l'ennemi */
    if(joueur==NULL){
       exit(3); 
    }
    if(ennemi==NULL){
       exit(4); 
    }
    joueur-> pv -= ennemi->att;
}