#include "logger.h"
#include "CosmicYonder.h"
/*Ce fichier contient les fonctions relatives au fonctionnement des portes*/

Porte initPorte(int dir,int v,int h){
    /*initialise la porte en prenant en parametres sa direction et les dimensions de la salle*/
    Porte porte;
    switch(dir){
        case GAUCHE:
            porte.x = 0;
            porte.y = (rand() % (v-2)) + 1;
            porte.ouvert = 0;
            break;
        case DROITE:
            porte.x = h-1;
            porte.y = (rand() % (v-2)) + 1;
            porte.ouvert = 0;
            break;
        case HAUT:
            porte.x = (rand() % (h-2)) + 1;
            porte.y = 0;
            porte.ouvert = 0;
            break;
        case BAS:
            porte.x = (rand() % (h-2)) + 1;
            porte.y = v-1;
            porte.ouvert = 0;
            break;
        default:
            porte.x = -1;
            porte.y = -1;
            porte.ouvert = 1;
            break;
    }
    return porte;
}

void ouvrirPorte(Salle ** carte, int indexSalleAct,int indexNouvSalle, int indexPorte, int dir) {
    /*permet de gerer l'ouverture des portes pour la creation de salles*/
    if(carte==NULL){
        exit(1);
    }
    //ouvre la porte de la salle ou le joueur se trouve
    carte[indexSalleAct]->portes[indexPorte].ouvert = 1;
    carte[indexSalleAct]->disp[carte[indexSalleAct]->portes[indexPorte].y][carte[indexSalleAct]->portes[indexPorte].x] = VIDE; // TODO: caractère porte ouverte

    //ouvre la porte de la salle generee en fonction de la direction de la porte d'entree
    switch(dir){
        case GAUCHE:
            carte[indexNouvSalle]->disp[carte[indexNouvSalle]->portes[0].y][carte[indexNouvSalle]->portes[0].x] = VIDE;
            carte[indexNouvSalle]->portes[0].ouvert = 1;
            break;
        case DROITE:
            carte[indexNouvSalle]->disp[carte[indexNouvSalle]->portes[0].y][carte[indexNouvSalle]->portes[0].x] = VIDE;
            carte[indexNouvSalle]->portes[0].ouvert = 1;
            break;
        case HAUT:
            carte[indexNouvSalle]->disp[carte[indexNouvSalle]->portes[0].y][carte[indexNouvSalle]->portes[0].x] = VIDE;
            carte[indexNouvSalle]->portes[0].ouvert = 1;
            break;
        case BAS:
            carte[indexNouvSalle]->disp[carte[indexNouvSalle]->portes[0].y][carte[indexNouvSalle]->portes[0].x] = VIDE;
            carte[indexNouvSalle]->portes[0].ouvert = 1;
            break;
    }
}

void creationPortes(Salle* salle, int entree, int* sallesrest){
    /*cree les portes d'une salle (hors porte d'entree)*/
    if(salle==NULL){
        exit(2);
    }
    if(sallesrest==NULL){
        exit(3);
    }
    switch(salle->nportes){
        case 4: //4 portes
            if(entree!=DROITE){
                salle->portes[1] = initPorte(DROITE,salle->hauteur,salle->longueur);
                (*sallesrest)--;
            } 
            else{
                salle->portes[1] = initPorte(GAUCHE,salle->hauteur,salle->longueur);
                (*sallesrest)--;  
            }
            if(entree!=BAS){
                salle->portes[2] = initPorte(BAS,salle->hauteur,salle->longueur);
                (*sallesrest)--;
            } 
            else{
                salle->portes[2] = initPorte(HAUT,salle->hauteur,salle->longueur);
                (*sallesrest)--;
            } 
            if((entree==DROITE||entree==GAUCHE)){
                salle->portes[3] = initPorte(HAUT,salle->hauteur,salle->longueur);
                (*sallesrest)--;
            } 
            else if((entree==BAS||entree==HAUT)){
                salle->portes[3] = initPorte(GAUCHE,salle->hauteur,salle->longueur);
                (*sallesrest)--;  
            } 
            break;
        case 3: //3 portes
            if(entree!=DROITE){
                salle->portes[1] = initPorte(DROITE,salle->hauteur,salle->longueur);
                (*sallesrest)--;
            } 
            else{
                salle->portes[1] = initPorte(GAUCHE,salle->hauteur,salle->longueur);
                        (*sallesrest)--;  
                }
                if(entree!=BAS){
                    salle->portes[2] = initPorte(BAS,salle->hauteur,salle->longueur);
                    (*sallesrest)--;
                } 
                else{
                    salle->portes[2] = initPorte(HAUT,salle->hauteur,salle->longueur);
                    (*sallesrest)--;
                }  
                break;
        case 2: //2 portes
            if(entree!=DROITE){
                salle->portes[1] = initPorte(DROITE,salle->hauteur,salle->longueur);
                (*sallesrest)--;
            } 
            else{
                salle->portes[1] = initPorte(GAUCHE,salle->hauteur,salle->longueur);
                (*sallesrest)--;  
            }
            break;
        case 1: //1 porte
            break;
        default: //si nombre de portes invalide, exit
            exit(4);
        }
    }