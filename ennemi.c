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
void ennemipos(Ennemi* ennemi,Salle* salle){
    //calcule la position de l'ennemi sur l'ecran en fonction de sa position dans la salle
    ennemi->xGlobal=salle->x+ennemi->xRelatif;
    ennemi->yGlobal=salle->y+ennemi->yRelatif;
}

void ennemimv(Ennemi* ennemi,Salle* salle, Joueur* joueur, WINDOW* mainwin){
    if(ennemi==NULL){
        exit(1);
    }
    if(salle == NULL){
        exit(2);
    }
    if(joueur==NULL){
       exit(3); 
    }
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
    if(ennemi==NULL){
        exit(4);
    }
    mvwaddstr(mainwin, ennemi->yGlobal, ennemi->xGlobal, "M");
}

Ennemi* apparition_ennemi(Salle* salle){
    /* Fait apparaitre un ennemi Ennemi dans une salle Salle*/

    //Vérification allocation salle
    if(salle == NULL){
        exit(5);
    }

    int x,y; //Coordonnées absolues de l'ennemi

    Ennemi* ennemi;
    //Vérification allocation ennemi
    ennemi = malloc(sizeof(Ennemi));
    if(ennemi==NULL){
        exit(6);
    }
    do{
        x = 1 + rand()%((salle->hauteur)-2); //Abscisse objet relative à la salle
        y = 1 + rand()%((salle->longueur)-2); //Ordonnée objet relative à la salle
    }while(salle->disp[x][y]!=VIDE); //Condition pour ne pas écraser un objet ou un monstre de la salle

    *ennemi = initEnnemi(x, y, 10, 10, 10); //Type et création de l'ennemi

    return ennemi;
}