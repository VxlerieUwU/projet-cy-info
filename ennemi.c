#include "CosmicYonder.h"
//ce fichier contient les fonctions nécessaires au fonctionnement des ennemis

Ennemi initEnnemi(int x, int y, int pv, int att, int def){
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
    ennemi.xRelatif = x;
    ennemi.yRelatif = y;
    ennemi.pv = pv;
    ennemi.att = att;
    ennemi.def = def;
    return ennemi;
} 
void ennemietat(Ennemi* ennemi,Salle* salle, Joueur* joueur, WINDOW* win){
    //calcule la position de l'ennemi sur l'ecran en fonction de sa position dans la salle
    if(ennemi==NULL){
        exit(1);
    }
    if(salle==NULL){
        exit(2);
    }
    ennemi->xGlobal=salle->x+ennemi->xRelatif;
    ennemi->yGlobal=salle->y+ennemi->yRelatif;    
    if(ennemi->pv<=0){
        desapparition_ennemi(ennemi,salle,joueur, win);
    }  
}

void ennemimv(Ennemi* ennemi,Salle* salle, Joueur* joueur, WINDOW* mainwin){
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
    
    if(ennemi->xGlobal>joueur->x){
        mouv = mvwinch(mainwin, ennemi->yGlobal, ennemi->xGlobal-1);
        if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
            ennemi->xRelatif--;  
        } 
        else if(mouv=='o'){
            perte_vie_joueur(joueur, ennemi);
        }
    }
    else if(ennemi->xGlobal<joueur->x){
        mouv = mvwinch(mainwin, ennemi->yGlobal, ennemi->xGlobal+1);
        if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
            ennemi->xRelatif++;
        }   
        else if(mouv=='o'){
            perte_vie_joueur(joueur, ennemi);
        }
    }
    else if(ennemi->yGlobal>joueur->y){
        mouv = mvwinch(mainwin, ennemi->yGlobal-1, ennemi->xGlobal);
        if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
            ennemi->yRelatif--;
        }  
        else if(mouv=='o'){
            perte_vie_joueur(joueur, ennemi);
        }  
    }
    else if(ennemi->yGlobal<joueur->y){
        mouv = mvwinch(mainwin, ennemi->yGlobal+1, ennemi->xGlobal);
        if(mouv==' '||mouv==*BOUTEILLE_O2_CHR || mouv==*BANDAGE_CHR ||mouv==*CLE_CHR
			||mouv==*GENERATEUR_CHR || mouv==*REACTEUR_CHR ||mouv==*PC_CHR){
            ennemi->yRelatif++;
        }
        else if(mouv=='o'){
            perte_vie_joueur(joueur, ennemi);
        }

    }        
}  

void afficheEnnemi(Ennemi* ennemi, WINDOW* mainwin){
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
    *ennemi = initEnnemi(x, y, 20, 10, 10); //Type et création de l'ennemi
    salle->ennemi_existant = 1;
    return ennemi;
}

void perte_vie_ennemi(Ennemi* ennemi, Joueur* joueur, WINDOW* win){
    /* L'ennemi perd de la vie quand le joueur avance vers lui */
    if(joueur==NULL){
       exit(11); 
    }
    if(ennemi==NULL){
       exit(12); 
    }
    ennemi->pv -= joueur->att;
}

void desapparition_ennemi(Ennemi* ennemi, Salle* salle, Joueur* joueur, WINDOW* win){
    /*libere le pointeur sur l'ennemi et assigne l'attribut ennemi_existant a 0*/
    if(ennemi==NULL){
        exit(13);
    }
    if(win==NULL){
        exit(14);
    }
    mvwaddch(win, ennemi->yGlobal, ennemi->xGlobal, ' ');
    free(ennemi);
    salle->ennemi_existant=0;

    joueur->xp+=50;
}