#include "CosmicYonder.h"


Objet apparition_objet(Salle* salle, int* objets_speciaux_apparus, int sallesrest, int portesNonOuvertes){
    /*Décide quel objet sera l'objet à faire apparaitre en fonction du numéro de la salle
    et fait apparaitre un objet Objet dans une salle Salle*/

    if(salle == NULL){
        exit(1);
    }
    if(objets_speciaux_apparus==NULL){
        exit(2);
    }

    int x,y; //Coordonnées relatives de l'objet
    //Sert à compter le nombre de fois qu'un objet est replacé à cause d'un objet déjà présent sur la case allouée
    int compteur = 0;
    Objet objet;

    //Initialisation objet
    objet.id = 0;
    objet.x = -1;
    objet.y = -1;
    
    /* Si le nombre de salles restantes à générer est identique aux nombres d'objets
    à récupérer pour gagner non apparues, on force l'apparition d'un de ces objets dans chacune
    des salles restantes*/
    if(sallesrest <= 1 && portesNonOuvertes == 4-(*objets_speciaux_apparus)){
        objet.id = 11 + (*objets_speciaux_apparus);
        (*objets_speciaux_apparus)++;
    }

    /*Condition pour faire apparaitre les objets à récupérer pour gagner le jeu
    dans les salles sans portes supplémentaires et si tous les objets à récupérer ne sont pas
    encore tous apparus*/
    else if(salle->nportes <= 1 && (*objets_speciaux_apparus) < 4){  
        /* 4 est le nombre d'objets communs (3) de l'énumération Id + 1 : ce + 1
        sert à faire apparaitre les objets à récupérer pour gagner le jeu.  
        8 est le nombre d'éléments possibles de la salle avant l'apparition des objets (murs, vide
        et portes)*/
        objet.id = 8 + rand()%4;
        
        
        /*Si l'objet est un objet à récupérer pour gagner,l'objet devient  le x+1 ème objet 
        à récupérer pour gagner selon les x objets à récupérer déjà apparus*/
        if(objet.id == 11){ //
            
            objet.id = 11 + (*objets_speciaux_apparus);  
            (*objets_speciaux_apparus)++;
        }
    }

    else{ //Sinon ne fait apparaitre que les objets communs (3)
        objet.id = 8 + rand()%3;
    }

	do{
        x = 1 + rand()%((salle->longueur)-2); //Abscisse objet relative à la salle
        y = 1 + rand()%((salle->hauteur)-2); //Ordonnée objet relative à la salle
        compteur++;
    }while(salle->disp[y][x]!=VIDE && compteur < 3); //Condition pour ne pas écraser un objet ou un monstre de la salle

    if(compteur >= 3){
        return objet; //L'objet est dans le tableau de la salle mais on ne peut pas interagir avec
    }
    else{
    salle->disp[y][x] = objet.id;

    //Coordonnées absolues de l'objet pour collision joueur-objets
    objet.x = salle->x + x;
    objet.y = salle->y + y;

    return objet;
    }
    
}

void recup_objet(Joueur* joueur, Salle* salle, Objet objet, int* nb_obj_inv, int* nb_obj_spe_inv){ 
    /*place l'objet dans l'inventaire du joueur et augmente son xp*/
    if(joueur == NULL || salle == NULL || nb_obj_inv == NULL || nb_obj_spe_inv == NULL){
        exit(3);
    }
    if(objet.id>=11 && *nb_obj_spe_inv<4){ //objets speciaux
        joueur->xp += 20;
        joueur->inventaire.obTab[*nb_obj_spe_inv] = objet;
        (*nb_obj_spe_inv)++;
    }
    else if(*nb_obj_inv+4 < INV_TAILLE){ //objets communs
        joueur->xp += 20;
        joueur->inventaire.obTab[*nb_obj_inv+4] = objet;
        (*nb_obj_inv)++;
    }
}

void utiliser_objet(Joueur* joueur, Objet objet, int* minuteur){
    switch(objet.id){
        case BANDAGE:
            if(joueur->pv <= (100+joueur->niv*20)-20){
                joueur->pv = 100+joueur->niv*20;
            }
            else{
                joueur->pv += 20;
            }
            objet.id = VIDE_OBJ;
            break;
        case BOUTEILLE_O2:
            *minuteur += 2;
            objet.id = VIDE_OBJ;
            break;
        case CLE:
            joueur->xp += 5;
            objet.id = VIDE_OBJ;
            break;
        default:
            break;
    }
}

void disparition_objet(Objet* objet, Salle* salle, WINDOW* win){
    /*libere le pointeur sur l'ennemi et assigne l'attribut ennemi_existant a 0*/
    if(objet==NULL){
        exit(4);
    }
    if(salle==NULL){
        exit(5);
    }
    if(win==NULL){
        exit(6);
    }
    //calcule la position relative de l'objet
    int x = objet->x-salle->x;
    int y = objet->y-salle->y;
    //enleve l'objet de la salle
    salle->disp[y][x] = VIDE;
    //met ses coordonnees a -1 et son id a 0
    objet->x=-1;
    objet->y=-1;
    objet->id=VIDE_OBJ;
}