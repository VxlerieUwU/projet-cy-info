#include "logger.h"
#include "CosmicYonder.h"

Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes, int entree, WINDOW* win, int* sallesrest) {
    //boucle qui verifie que l emplacement de la salle est libre et la regenere si elle se superpose avec une autre salle
    //verif win
    if(win == NULL){
        exit(1);
    }
    //verif sallesrest
    if(sallesrest == NULL){
        exit(2);
    }
    //verif taille
    if(taille_horizontale<3 || taille_verticale<3){
        exit(3);
    }

    for(int i=0;i<taille_verticale;i++){ 
        for(int j=0;j<taille_horizontale;j++){
            if(mvwinch(win,i+y,j+x)!=' '&&mvwinch(win,i+y,j+x)!='o'){
                creerSalle(taille_horizontale-j, taille_verticale-i, x, y, nportes, entree, win, sallesrest);
            }
        }
    }

    //allocation salle
    Salle * salle = NULL;
    salle = malloc(sizeof(Salle));

    if(salle == NULL) {
        logMessage(CRITICAL, "erreur malloc struct salle");
        exit(1);
    }

    //init attributs salle
    salle->longueur = taille_horizontale;
    salle->hauteur = taille_verticale;
    salle->x = x;
    salle->y = y;
    salle->nportes = nportes;

    // ALLOCATION PORTES
    if(salle->nportes == 0) {
        salle->portes = NULL;
    } else {
        salle->portes = malloc(sizeof(Porte) * salle->nportes);
        if(salle->portes == NULL) {
            logMessage(CRITICAL, "erreur malloc portes salle");
            exit(2);
        };

        /*verifie si il reste au moins une salle a generer et genere une porte si c'est le cas
        si la porte ne dois pas se generer, j'ai mis ses coordonnees a -1*/
        if(entree==-1) { //4 portes, salle de départ
            if(*sallesrest>0){
                salle->portes[0].x = 0;
                salle->portes[0].y = (rand() % (taille_verticale-2)) + 1;
                salle->portes[0].ouvert = 0;
                (*sallesrest)--;
            }
            else{
                salle->portes[0].x = -1;
                salle->portes[0].y = -1;
            }
            if(*sallesrest>0){
                salle->portes[1].x = (rand() % (taille_horizontale-2)) + 1;
                salle->portes[1].y = 0;
                salle->portes[1].ouvert = 0;
                (*sallesrest)--;
            }
            else{
                salle->portes[1].x = -1;
                salle->portes[1].y = -1;
            }
            if(*sallesrest>0){
                salle->portes[2].x = taille_horizontale-1;
                salle->portes[2].y = (rand() % (taille_verticale-2)) + 1;
                salle->portes[2].ouvert = 0;
                (*sallesrest)--;
            }
            else{
                salle->portes[2].x = -1;
                salle->portes[2].y = -1;
            }
            if(*sallesrest>0){
                salle->portes[3].x = (rand() % (taille_horizontale-2)) + 1;
                salle->portes[3].y = taille_verticale-1;
                salle->portes[3].ouvert = 0;
                (*sallesrest)--;
            }
            else{
                salle->portes[3].x = -1;
                salle->portes[3].y = -1;
            }
        } else {
            // TODO:  nportes != 4 / salles de boss?

            // cree la porte d'entree, ici porte[0] = porte d'entree
            switch(entree){
                case GAUCHE:
                    salle->portes[0].x = 0;
                    salle->portes[0].y = taille_verticale/2;
                    salle->portes[0].ouvert = 0;
                    break;
                case DROITE:
                    salle->portes[0].x = taille_horizontale-1;
                    salle->portes[0].y = taille_verticale/2;
                    salle->portes[0].ouvert = 0;
                    break;
                case HAUT:
                    salle->portes[0].x = taille_horizontale/2;
                    salle->portes[0].y = 0;
                    break;
                case BAS: 
                    salle->portes[0].x = taille_horizontale/2;
                    salle->portes[0].y = taille_verticale-1;
                    salle->portes[0].ouvert = 0;
                    break;
            }
            //les conditions suivantes creent les autres portes
            if(entree!=DROITE && *sallesrest>0){
                salle->portes[1].x = taille_horizontale-1;
                salle->portes[1].y = (rand() % (taille_verticale-2)) + 1;
                salle->portes[1].ouvert = 0;
                (*sallesrest)--;
            } 
            else if(*sallesrest>0){
                salle->portes[1].x = 0;
                salle->portes[1].y = (rand() % (taille_verticale-2)) + 1;
                salle->portes[1].ouvert = 0;
                (*sallesrest)--;  
            }
            else{
                salle->portes[1].x = -1;
                salle->portes[1].y = -1;
            }

            if(entree!=BAS && *sallesrest>0){
                salle->portes[2].x = (rand() % (taille_horizontale-2)) + 1;
                salle->portes[2].y = taille_verticale-1;
                salle->portes[2].ouvert = 0;
                (*sallesrest)--;
            } 
            else if(*sallesrest>0){
                salle->portes[2].x = (rand() % (taille_horizontale-2)) + 1;
                salle->portes[2].y = 0;
                salle->portes[2].ouvert = 0;
                (*sallesrest)--;
            } 
            else{
                salle->portes[2].x = -1;
                salle->portes[2].y = -1;
            } 

            if((entree==DROITE||entree==GAUCHE) && *sallesrest>0){
                salle->portes[3].x = (rand() % (taille_horizontale-2)) + 1;
                salle->portes[3].y = 0;
                salle->portes[3].ouvert = 0;
                (*sallesrest)--;
            } 
            else if((entree==BAS||entree==HAUT) && *sallesrest>0){
                salle->portes[3].x = 0;
                salle->portes[3].y = (rand() % (taille_verticale-2)) + 1;
                salle->portes[3].ouvert = 0;
                (*sallesrest)--;  
            } 
            else{
                salle->portes[3].x = -1;
                salle->portes[3].y = -1;
            }
        }
    }

    // ALLOCATION MURS 
    salle->disp = malloc(sizeof(int*) * taille_verticale);

    if(salle->disp == NULL) {
        logMessage(CRITICAL, "erreur malloc tableau salle");
        exit(2);
    }

    for(int i=0;i<taille_verticale;i++){
        salle->disp[i] = malloc(sizeof(int) * taille_horizontale);
        //Vérification allocation
        if(salle->disp[i] == NULL){
            logMessage(CRITICAL, "erreur malloc ligne salle");
            exit(2);
        }

        for(int j=0;j<taille_horizontale;j++){
            //Vérification allocation

            salle->disp[i][j] = VIDE;
            
            if(i==0 || i==taille_verticale-1){
                salle->disp[i][j] = MUR_VERTI;//Affichage bordure droite et gauche
            }
            else if(j==0 || j==taille_horizontale-1){
                salle->disp[i][j] = MUR_HORIZ; //Affichage bordure haut et bas
            }   
        }
    }
    //affichage des portes
    if(salle->nportes != 0) {
        for(int i=0; i<salle->nportes; i++) {
            if(salle->portes[i].x!=-1 && salle->portes[i].y!=-1){//verifie que la porte existe

                salle->disp[salle->portes[i].y][salle->portes[i].x] = PORTE;

                /*on verifie qu'il y ait l'espace disponible pour generer une salle derriere les portes
                on verifie dans un espace de 3 en longueur x 4 en largeur 
                s'il n'y a pas la place on remplace la porte par un mur*/

                if(salle->portes[i].x==0){ //porte a gauche
                    for(int j=1; j<=4; j++){
                        for(int k=-2; k<=2; k++){
                            if(mvwinch(win, y+salle->portes[i].y-k, x+salle->portes[i].x-j)!=' '){
                                salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_HORIZ;
                            }
                        }
                    }
                }
                if(salle->portes[i].x==taille_horizontale-1){ //porte a droite
                    for(int j=1; j<=4; j++){
                        for(int k=-2; k<=2; k++){
                            if(mvwinch(win, y+salle->portes[i].y-k, x+salle->portes[i].x+j)!=' '){
                                salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_HORIZ;
                            }                  
                        }
                    }
                }
                if(salle->portes[i].y==0){ //porte en haut
                    for(int j=-2; j<=2; j++){
                        for(int k=1; k<=4; k++){
                            if(mvwinch(win, y+salle->portes[i].y-k, x+salle->portes[i].x+j)!=' '){
                                salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_VERTI;
                            }                         
                        }
                    }
                }
                if(salle->portes[i].y==taille_verticale-1){ //porte en bas
                    for(int j=-2; j<=2; j++){
                        for(int k=1; k<=4; k++){
                            if(mvwinch(win, y+salle->portes[i].y+k, x+salle->portes[i].x+j)!=' '){
                                salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_VERTI;
                            }                      
                        }
                    }
                }    
            }        
        }
    }
    //Bord supérieur gauche
    salle->disp[0][taille_horizontale-1] = MUR_SUPG;

    //Bord supérieur droit
    salle->disp[0][0] = MUR_SUPD;

    //Bord inférieur gauche
    salle->disp[taille_verticale-1][taille_horizontale-1] = MUR_INFG;
    //Bord inférieur droit
    salle->disp[taille_verticale-1][0] = MUR_INFD;

    return salle;
}

Salle * creerSalleProced(int x, int y, int dir, WINDOW* win, int* sallesrest) {
    //init attributs salles
    int v, h;
    v = TAILLE_MAX_V-(rand()%(TAILLE_MAX_V-3));
    h = TAILLE_MAX_H-(rand()%(TAILLE_MAX_H-4));
    //logs
    char logBuffer[50];
    sprintf(logBuffer, "taille verticale = %d, taille horizontale = %d", v, h);
    logMessage(DEBUG, logBuffer);

    /*gere l'origine de la salle en fonction de la direction de l'entree de la salle
    pour l'instant place l'entree de la salle generee au milieu
    il faudrait changer la boucle qui empeche la superposition afin d'eviter ce probleme*/

    switch(dir){ 
        case DROITE: 
            //genere la salle a gauche de la salle actuelle
            return creerSalle(h, v, x-h-1, y-v/2, 4, dir,win,sallesrest); 
            break;
        case BAS: 
            //genere la salle en haut de la salle actuelle
            return creerSalle(h, v, x-h/2, y-v-1, 4, dir,win,sallesrest);
            break;
        case GAUCHE: 
            //genere la salle a droite de la salle actuelle
            return creerSalle(h, v, x+2, y-v/2, 4, dir,win,sallesrest);
            break;
        case HAUT: 
            //genere la salle en bas de la salle actuelle
            return creerSalle(h, v, x-h/2, y+2, 4, dir,win,sallesrest);
            break;
        default: 
            return creerSalle(h, v, x, y, 4, dir,win,sallesrest);
            break;
    }
    
}


void dessineSalle(WINDOW * win, Salle * salle) {
    /* affiche la salle sur la fenetre en parcourant la salle*/
    int i, j;
    for(i=0; i < salle->hauteur; i++){
        for(j=0; j < salle->longueur; j++){
            switch(salle->disp[i][j]){
                case MUR_VERTI:
                    mvwaddstr(win, salle->y+i, salle->x+j, MUR_VERTI_CHR);
                    break;
                case MUR_HORIZ:
                    mvwaddstr(win, salle->y+i, salle->x+j, MUR_HORIZ_CHR);
                    break;
                case MUR_SUPG:
                    mvwaddstr(win, salle->y+i, salle->x+j, MUR_SUPG_CHR);
                    break;
                case MUR_SUPD:
                    mvwaddstr(win, salle->y+i, salle->x+j, MUR_SUPD_CHR);
                    break;
                case MUR_INFG:
                    mvwaddstr(win, salle->y+i, salle->x+j, MUR_INFG_CHR);
                    break;
                case MUR_INFD:
                    mvwaddstr(win, salle->y+i, salle->x+j, MUR_INFD_CHR);
                    break;
                case PORTE:
                    mvwaddch(win, salle->y+i, salle->x+j, 'P'); /*modifie temporairement
                    car je n'ai pas trouve de moyen de detecter les caracteres unicodes affiches sur l'ecran*/
                    break;
                case VIDE:
                    //mvwaddstr(win, salle->y+i, salle->x+j, " ");
                    break;
            }
        }
    }
}

void dessineSalles(WINDOW * win, Salle ** carte, int salles_existantes) {
    /*affiche l'ensemble des salles*/
    for(int i = 0; i<salles_existantes; i++) {
        dessineSalle(win, carte[i]);
    }
}

void libereSalle(Salle * salle) {
    /*libere l'emplacement memoire de la salle*/
    for(int i=0;i<salle->hauteur;i++){
        free(salle->disp[i]);
    }
    free(salle->disp);
    free(salle);
}

void ouvrirPorte(Salle ** carte, int indexSalleAct,int indexNouvSalle, int indexPorte, int dir) {
    /*permet de gerer l'ouverture des portes pour la creation de salles*/

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