#include "logger.h"
#include "CosmicYonder.h"

Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes) {
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

Salle * creerSalleProced(int x, int y, int dir) {
    int v, h;
    v = TAILLE_MAX_V-(rand()%(TAILLE_MAX_V-3));
    h = TAILLE_MAX_H-(rand()%(TAILLE_MAX_H-4));
    char logBuffer[50];
    sprintf(logBuffer, "taille verticale = %d, taille horizontale = %d", v, h);
    logMessage(DEBUG, logBuffer);

    switch(dir){
        case 1:
            return creerSalle(h, v, x-h-1, y-v/2, 4);
        case 2:
            return creerSalle(h, v, x-h/2, y-v-1, 4);
        case 3:
            return creerSalle(h, v, x+2, y-v/2, 4);
        case 4:
            return creerSalle(h, v, x-h/2, y+2, 4);
        default:
            return creerSalle(h, v, x, y, 4);
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
                    mvwaddch(win, salle->y+i, salle->x+j, 'P');
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
