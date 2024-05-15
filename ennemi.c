#include "CosmicYonder.h"
//ce fichier contient les fonctions nécessaires au fonctionnement des ennemis

Ennemi initEnnemi(int x, int y, int pv, int att, int def){
    Ennemi ennemi;
    ennemi.x = x;
    ennemi.y = y;
    ennemi.pv = pv;
    ennemi.att = att;
    ennemi.def = def;
    return ennemi;
} 