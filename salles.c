#include "logger.h"
#include "CosmicYonder.h"
/*Ce fichier contient les fonctions relatives au fonctionnement des salles*/

Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes, int entree, WINDOW* win, int* sallesrest) {
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
    
    //boucle qui verifie que l emplacement de la salle est libre et la regenere si elle se superpose avec une autre salle
    for(int i=0;i<taille_verticale;i++){ 
        for(int j=0;j<taille_horizontale;j++){
            if(mvwinch(win,i+y,j+x)!=' '){
                creerSalle(taille_horizontale-1, taille_verticale-1, x, y, nportes, entree, win, sallesrest);
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

    if(*sallesrest >= nportes){
       salle->nportes = nportes; 
    }
    else{
        salle->nportes = *sallesrest; 
    }
    
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

        //salle de départ
        if(entree==-1) { 
            salle->portes[0] = initPorte(GAUCHE,taille_verticale,taille_horizontale);
            (*sallesrest)--;

            salle->portes[1] = initPorte(HAUT,taille_verticale,taille_horizontale);
            (*sallesrest)--;

            salle->portes[2] = initPorte(DROITE,taille_verticale,taille_horizontale);
            (*sallesrest)--;
 
            salle->portes[3] = initPorte(BAS,taille_verticale,taille_horizontale);
            (*sallesrest)--;
        } else {
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
                    salle->portes[0].ouvert = 0;
                    break;
                case BAS: 
                    salle->portes[0].x = taille_horizontale/2;
                    salle->portes[0].y = taille_verticale-1;
                    salle->portes[0].ouvert = 0;
                    break;
            }
            //les conditions suivantes creent les autres portes
            switch(salle->nportes){
                case 4: //4 portes
                    if(entree!=DROITE){
                        salle->portes[1] = initPorte(DROITE,taille_verticale,taille_horizontale);
                        (*sallesrest)--;
                    } 
                    else{
                        salle->portes[1] = initPorte(GAUCHE,taille_verticale,taille_horizontale);
                        (*sallesrest)--;  
                    }
                    if(entree!=BAS){
                        salle->portes[2] = initPorte(BAS,taille_verticale,taille_horizontale);
                        (*sallesrest)--;
                    } 
                    else{
                        salle->portes[2] = initPorte(HAUT,taille_verticale,taille_horizontale);
                        (*sallesrest)--;
                    } 
                    if((entree==DROITE||entree==GAUCHE)){
                        salle->portes[3] = initPorte(HAUT,taille_verticale,taille_horizontale);
                        (*sallesrest)--;
                    } 
                    else if((entree==BAS||entree==HAUT)){
                        salle->portes[3] = initPorte(GAUCHE,taille_verticale,taille_horizontale);
                        (*sallesrest)--;  
                    } 
                    break;
                case 3: //3 portes
                    if(entree!=DROITE){
                        salle->portes[1] = initPorte(DROITE,taille_verticale,taille_horizontale);
                        (*sallesrest)--;
                    } 
                    else{
                        salle->portes[1] = initPorte(GAUCHE,taille_verticale,taille_horizontale);
                        (*sallesrest)--;  
                    }
                    if(entree!=BAS){
                        salle->portes[2] = initPorte(BAS,taille_verticale,taille_horizontale);
                        (*sallesrest)--;
                    } 
                    else{
                        salle->portes[2] = initPorte(HAUT,taille_verticale,taille_horizontale);
                        (*sallesrest)--;
                    }  
                    break;
                case 2: //2 portes
                    if(entree!=DROITE){
                        salle->portes[1] = initPorte(DROITE,taille_verticale,taille_horizontale);
                        (*sallesrest)--;
                    } 
                    else{
                        salle->portes[1] = initPorte(GAUCHE,taille_verticale,taille_horizontale);
                        (*sallesrest)--;  
                    }
                    break;
                case 1: //1 porte
                    break;
                default: //si nombre de portes invalide, exit
                    exit(4);
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
    for(int i=0; i<salle->nportes; i++) {
        salle->disp[salle->portes[i].y][salle->portes[i].x] = PORTE;

        /*on verifie qu'il y ait l'espace disponible pour generer une salle derriere les portes
        on verifie dans un espace de 3 en longueur x 4 en largeur 
        s'il n'y a pas la place on remplace la porte par un mur et on met son etat en ouvert*/
        if(salle->portes[i].x==0){ //porte a gauche
            for(int j=1; j<=4; j++){
                for(int k=-2; k<=2; k++){
                    if(mvwinch(win, y+salle->portes[i].y-k, x+salle->portes[i].x-j)!=' '){
                        salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_HORIZ;
                        salle->portes[i].ouvert = 1;
                    }
                }
            }
        }
        if(salle->portes[i].x==taille_horizontale-1){ //porte a droite
            for(int j=1; j<=4; j++){
                for(int k=-2; k<=2; k++){
                    if(mvwinch(win, y+salle->portes[i].y-k, x+salle->portes[i].x+j)!=' '){
                        salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_HORIZ;
                        salle->portes[i].ouvert = 1;
                    }                  
                }
            }
        }
        if(salle->portes[i].y==0){ //porte en haut
            for(int j=-2; j<=2; j++){
                for(int k=1; k<=4; k++){
                    if(mvwinch(win, y+salle->portes[i].y-k, x+salle->portes[i].x+j)!=' '){
                        salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_VERTI;
                        salle->portes[i].ouvert = 1;
                    }                         
                }
            }
        }
        if(salle->portes[i].y==taille_verticale-1){ //porte en bas
            for(int j=-2; j<=2; j++){
                for(int k=1; k<=4; k++){
                    if(mvwinch(win, y+salle->portes[i].y+k, x+salle->portes[i].x+j)!=' '){
                        salle->disp[salle->portes[i].y][salle->portes[i].x] = MUR_VERTI;
                        salle->portes[i].ouvert = 1;
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

Salle * creerSalleProced(int x, int y, int nportes, int dir, WINDOW* win, int* sallesrest) {
    //init attributs salles
    int v, h;
    v = rand()%(TAILLE_MAX_V-2)+3;
    h = rand()%(TAILLE_MAX_H-2)+3;
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
            return creerSalle(h, v, x-h-1, y-v/2, nportes, dir,win,sallesrest); 
            break;
        case BAS: 
            //genere la salle en haut de la salle actuelle
            return creerSalle(h, v, x-h/2, y-v-1, nportes, dir,win,sallesrest);
            break;
        case GAUCHE: 
            //genere la salle a droite de la salle actuelle
            return creerSalle(h, v, x+2, y-v/2, nportes, dir,win,sallesrest);
            break;
        case HAUT: 
            //genere la salle en bas de la salle actuelle
            return creerSalle(h, v, x-h/2, y+2, nportes, dir,win,sallesrest);
            break;
        default: 
            return creerSalle(h, v, x, y, nportes, dir,win,sallesrest);
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