#include "CosmicYonder.h"
//ce fichier contient les fonctions nécessaires au fonctionnement des ennemis

Ennemi initEnnemi(int x, int y, int pv, int att, int def){
    Ennemi ennemi;
    ennemi.xRelatif = x;
    ennemi.yRelatif = y;
    ennemi.pv = pv;
    ennemi.att = att;
    ennemi.def = def;
    return ennemi;
} 

void ennemimv(Ennemi* ennemi,Salle* salle, Joueur* joueur, WINDOW* mainwin){
    //calcule la position de l'ennemi sur l'ecran en fonction de sa position dans la salle
    ennemi->xGlobal=salle->x+ennemi->xRelatif;
    ennemi->yGlobal=salle->y+ennemi->yRelatif;
    /*ces conditions permettent a l'ennemi de se deplacer
    compare la position de l'ennemi et du joueur et modifie la position de l'ennemi afin qu'il se rapproche du joueur*/
    if(ennemi->xGlobal>joueur->x && mvwinch(mainwin, ennemi->yGlobal, ennemi->xGlobal-1)==' '){
        ennemi->xRelatif--;
    }
    else if(ennemi->xGlobal<joueur->x && mvwinch(mainwin, ennemi->yGlobal, ennemi->xGlobal+1)==' '){
        ennemi->xRelatif++;
    }
    if(ennemi->yGlobal>joueur->y && mvwinch(mainwin, ennemi->yGlobal-1, ennemi->xGlobal)==' '){
        ennemi->yRelatif--;
    }
    else if(ennemi->yGlobal<joueur->y && mvwinch(mainwin, ennemi->yGlobal+1, ennemi->xGlobal)==' '){
        ennemi->yRelatif++;
    }
}

void afficheEnnemi(Ennemi* ennemi, WINDOW* mainwin){
    mvwaddstr(mainwin, ennemi->yGlobal, ennemi->xGlobal, "M");
}