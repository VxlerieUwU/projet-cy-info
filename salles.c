#include "logger.h"
#include "CosmicYonder.h"

Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes, int entree, WINDOW* win) {
    for(int i=0;i<taille_verticale;i++){ //boucle qui verifie que l emplacement de la salle est libre
        for(int j=0;j<taille_horizontale;j++){
            if(mvwinch(win,i+y,j+x)!=' '&&mvwinch(win,i+y,j+x)!='o'){
                switch(entree){
                    case 1:
                        return creerSalleProced(x+taille_horizontale+1,y+taille_verticale/2,entree, win);
                        break;
                    case 2:
                        return creerSalleProced(x-taille_horizontale/2,y+taille_verticale+1,entree, win);
                        break;
                    case 3:
                        return creerSalleProced(x-2,y+taille_verticale/2,entree, win);
                        break;
                    case 4:
                        return creerSalleProced(x+taille_horizontale/2,y-2,entree, win);
                        break;
                    default:
                        return creerSalleProced(x,y,entree, win);
                        break;
                }
            }
        }
    }

    Salle * salle = NULL;
    salle = malloc(sizeof(Salle));

    if(salle == NULL) {
        logMessage(CRITICAL, "erreur malloc struct salle");
        exit(1);
    }

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

        if(salle->nportes == 4) { 
            salle->portes[0].x = 0;
            salle->portes[0].y = (rand() % (taille_verticale-1)) + 1;
            salle->portes[1].x = (rand() % (taille_horizontale-1)) + 1;
            salle->portes[1].y = 0;
            salle->portes[2].x = taille_horizontale-1;
            salle->portes[2].y = (rand() % (taille_verticale-1)) + 1;
            salle->portes[3].x = (rand() % (taille_horizontale-1)) + 1;
            salle->portes[3].y = taille_verticale-1;
        } else {
            // TODO:  nportes != 4 / salles de boss?
            switch(entree){
                case 1: //entree a droite
                    salle->portes[0].x = 0;
                    salle->portes[0].y = (rand() % (taille_verticale-1)) + 1;
                    salle->portes[1].x = (rand() % (taille_horizontale-1)) + 1;
                    salle->portes[1].y = 0;
                    salle->portes[2].x = (rand() % (taille_horizontale-1)) + 1;
                    salle->portes[2].y = taille_verticale-1;
                    break;
                case 2: //entree en haut
                    salle->portes[0].x = 0;
                    salle->portes[0].y = (rand() % (taille_verticale-1)) + 1;
                    salle->portes[1].x = (rand() % (taille_horizontale-1)) + 1;
                    salle->portes[1].y = 0;
                    salle->portes[2].x = taille_horizontale-1;
                    salle->portes[2].y = (rand() % (taille_verticale-1)) + 1;
                    break;
                case 3: //entree a gauche
                    salle->portes[0].x = (rand() % (taille_horizontale-1)) + 1;
                    salle->portes[0].y = 0;
                    salle->portes[1].x = taille_horizontale-1;
                    salle->portes[1].y = (rand() % (taille_verticale-1)) + 1;
                    salle->portes[2].x = (rand() % (taille_horizontale-1)) + 1;
                    salle->portes[2].y = taille_verticale-1;
                    break;
                case 4: //entree en bas
                    salle->portes[0].x = 0;
                    salle->portes[0].y = (rand() % (taille_verticale-1)) + 1;
                    salle->portes[1].x = taille_horizontale-1;
                    salle->portes[1].y = (rand() % (taille_verticale-1)) + 1;
                    salle->portes[2].x = (rand() % (taille_horizontale-1)) + 1;
                    salle->portes[2].y = taille_verticale-1;
                    break;
                default:
                    break;
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

    if(salle->nportes != 0) {
        for(int i=0; i<salle->nportes; i++) {
            salle->disp[salle->portes[i].y][salle->portes[i].x] = PORTE;

            //on verifie qu'il y ait l'espace disponible pour generer une salle derriere les portes
            if(salle->portes[i].x==0){ //porte a gauche
                for(int j=1; j<=3; j++){
                    for(int k=-2; k<=2; k++){
                        if(mvwinch(win, y+salle->portes[i].y-k, x+salle->portes[i].x-j)!=' '){
                            salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_HORIZ;
                        }
                    }
                }
            }
            if(salle->portes[i].x==taille_horizontale-1){ //porte a droite
                for(int j=1; j<=3; j++){
                    for(int k=-2; k<=2; k++){
                        if(mvwinch(win, y+salle->portes[i].y-k, x+salle->portes[i].x+j)!=' '){
                            salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_HORIZ;
                        }                  
                    }
                }
            }
            if(salle->portes[i].y==0){ //porte en haut
                for(int j=-2; j<=2; j++){
                    for(int k=1; k<=3; k++){
                        if(mvwinch(win, y+salle->portes[i].y-k, x+salle->portes[i].x+j)!=' '){
                            salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_VERTI;
                        }                         
                    }
                }
            }
            if(salle->portes[i].y==taille_verticale-1){ //porte en bas
                for(int j=-2; j<=2; j++){
                    for(int k=1; k<=3; k++){
                        if(mvwinch(win, y+salle->portes[i].y+k, x+salle->portes[i].x+j)!=' '){
                            salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_VERTI;
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

Salle * creerSalleProced(int x, int y, int dir, WINDOW* win) {
    int v, h;
    v = TAILLE_MAX_V-(rand()%(TAILLE_MAX_V-3));
    h = TAILLE_MAX_H-(rand()%(TAILLE_MAX_H-4));
    char logBuffer[50];
    sprintf(logBuffer, "taille verticale = %d, taille horizontale = %d", v, h);
    logMessage(DEBUG, logBuffer);

    switch(dir){ //gere l'origine de la salle en fonction de la direction de la porte
        case 1: //porte a gauche
            return creerSalle(h, v, x-h-1, y-v/2, 3, dir,win);
            break;
        case 2: //porte en haut
            return creerSalle(h, v, x-h/2, y-v-1, 3, dir,win);
            break;
        case 3: //porte a droite
            return creerSalle(h, v, x+2, y-v/2, 3, dir,win);
            break;
        case 4: //porte en bas
            return creerSalle(h, v, x-h/2, y+2, 3, dir,win);
            break;
        default: 
            return creerSalle(h, v, x, y, 4, dir,win);
            break;
    }
    
}


void dessineSalle(WINDOW * win, Salle * salle) {
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

void libereSalle(Salle * salle) {
    for(int i=0;i<salle->hauteur;i++){
        free(salle->disp[i]);
    }
    free(salle->disp);
    free(salle);
}
