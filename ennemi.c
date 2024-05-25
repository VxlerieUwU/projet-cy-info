#include "CosmicYonder.h"
//ce fichier contient les fonctions nécessaires au fonctionnement des ennemis

Ennemi initEnnemi(int x, int y, int pv, int att, int def){
    /* Initialise les stats et la position de l'ennemi à sa création*/
    if(pv<1){
        pv=1;
    }
    if(att<1){
        att=1;
    }
    if(def<1){
        def=1;
    }
    Ennemi ennemi;
    ennemi.xRelatif = x; //abscisse relative par rapport à l'origine de la salle
    ennemi.yRelatif = y; //ordonnée relative par rapport à l'origine de la salle
    ennemi.pv = pv;
    ennemi.att = att;
    ennemi.def = def;
    return ennemi;
} 
void ennemipos(Ennemi* ennemi,Salle* salle){
    //calcule la position de l'ennemi sur l'ecran en fonction de sa position dans la salle
    if(ennemi==NULL){
        exit(1);
    }
    if(salle==NULL){
        exit(2);
    }
    ennemi->xGlobal=salle->x+ennemi->xRelatif; //abscisse du point d'apparition du monstre
    ennemi->yGlobal=salle->y+ennemi->yRelatif; //ordonnée du point d'apparition du monstre
}

void ennemimv(Ennemi* ennemi,Salle* salle, Joueur* joueur, WINDOW* mainwin){
    /* Fonction qui gère les déplacements de l'ennemi par rapport à sa position par
    rapport au joueur*/
    if(ennemi==NULL){
        exit(3);
    }
    if(salle == NULL){
        exit(4);
    }
    if(joueur==NULL){
       exit(5); 
    }
    if(mainwin==NULL){
        exit(6);
    }
    int mouv = 0;
    /*ces conditions permettent a l'ennemi de se deplacer
    compare la position de l'ennemi et du joueur et modifie la position de l'ennemi afin qu'il se rapproche du joueur*/
    
    if(ennemi->xGlobal>joueur->x){ //ennemi en bas du joueur
        mouv = mvwinch(mainwin, ennemi->yGlobal, ennemi->xGlobal-1); //mouvement vers le haut
        //L'ennemi se déplace si la case d'arrivée du mouv est un objet ou du vide
        if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
            ennemi->xRelatif--;  
        } 
        else if(mouv=='o'){ 
            //Sinon si la case d'arrivée est le joueur, le joueur perd des pvs et le monstre reste à sa place.
            perte_vie_joueur(joueur, ennemi);
        }
    }
    else if(ennemi->xGlobal<joueur->x){ //ennemi en haut du joueur
        mouv = mvwinch(mainwin, ennemi->yGlobal, ennemi->xGlobal+1); //mouv vers le bas
        //L'ennemi se déplace si la case d'arrivée du mouv est un objet ou du vide
        if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
            ennemi->xRelatif++;
        }   
        else if(mouv=='o'){ 
            //Sinon si la case d'arrivée est le joueur, le joueur perd des pvs et le monstre reste à sa place.
            perte_vie_joueur(joueur, ennemi);
        }
    }
    else if(ennemi->yGlobal>joueur->y){ //ennemi à droite du joueur
        mouv = mvwinch(mainwin, ennemi->yGlobal-1, ennemi->xGlobal); //mouv vers la gauche
        //L'ennemi se déplace si la case d'arrivée du mouv est un objet ou du vide
        if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
            ennemi->yRelatif--;
        }  
        else if(mouv=='o'){ 
            //Sinon si la case d'arrivée est le joueur, le joueur perd des pvs et le monstre reste à sa place.
            perte_vie_joueur(joueur, ennemi);
        }  
    }
    else if(ennemi->yGlobal<joueur->y){ //ennemi à gauche du joueur
        mouv = mvwinch(mainwin, ennemi->yGlobal+1, ennemi->xGlobal); //mouv vers la droite
        //L'ennemi se déplace si la case d'arrivée du mouv est un objet ou du vide
        if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
            ennemi->yRelatif++;
        }
        else if(mouv=='o'){ 
            //Sinon si la case d'arrivée est le joueur, le joueur perd des pvs et le monstre reste à sa place.
            perte_vie_joueur(joueur, ennemi);
        }

    }        
}  

void afficheEnnemi(Ennemi* ennemi, WINDOW* mainwin){
    /* Affiche l'ennemi sur l'écran de ncurses*/
    if(ennemi==NULL){
        exit(7);
    }
    if(mainwin==NULL){
        exit(8);
    }
    mvwaddstr(mainwin, ennemi->yGlobal, ennemi->xGlobal, "M");
}

Ennemi* apparition_ennemi(Salle* salle){
    /* Fait apparaitre un ennemi Ennemi dans une salle Salle*/

    //Vérification allocation salle
    if(salle == NULL){
        exit(9);
    }

    int x,y; //Coordonnées absolues de l'ennemi

    Ennemi* ennemi;
    //Vérification allocation ennemi
    ennemi = malloc(sizeof(Ennemi));
    if(ennemi==NULL){
        exit(10);
    }
    do{
        x = 1 + rand()%((salle->longueur)-2); //Abscisse objet relative à la salle
        y = 1 + rand()%((salle->hauteur)-2); //Ordonnée objet relative à la salle
    }while(salle->disp[y][x]!=VIDE); //Condition pour ne pas écraser un objet ou un monstre de la salle
    *ennemi = initEnnemi(x, y, 10, 10, 10); //Type et création de l'ennemi

    return ennemi;
}

void perte_vie_ennemi(Ennemi* ennemi, Joueur* joueur){
    /* Le joueur perd de la vie quand un ennemi est sur sa case en fonction de la défense du joueur et de l'attaque de l'ennemi) */
    if(joueur==NULL){
       exit(11); 
    }
    if(ennemi==NULL){
       exit(12); 
    }
    ennemi-> pv -= joueur->att - ennemi->def;
}