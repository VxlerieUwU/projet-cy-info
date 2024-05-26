#include "logger.h"
#include "CosmicYonder.h"
/*Ce fichier contient les fonctions relatives au fonctionnement des salles*/

Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes, 
int entree, int posEntree, WINDOW* win, int* sallesrest, int* objets_speciaux_apparus,int portesNonOuvertes) {
    //verif win
    if(win == NULL){
        exit(1);
    }
    //verif sallesrest
    if(sallesrest == NULL){
        exit(2);
    }
    if(objets_speciaux_apparus==NULL){
        exit(3);
    }
    //verif taille
    if(taille_horizontale<3 || taille_verticale<3){
        exit(4);
    }

    //enleve le marquage de caracteres invisibles
    enleve_marquage(entree, x, y, taille_horizontale, taille_verticale, posEntree, win);

    //verif superposition
    verif_superposition(entree, &posEntree, &x, &y, &taille_horizontale, &taille_verticale, win);

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
                    salle->portes[0].y = posEntree;
                    salle->portes[0].ouvert = 0;
                    break;
                case DROITE:
                    salle->portes[0].x = taille_horizontale-1;
                    salle->portes[0].y = posEntree;
                    salle->portes[0].ouvert = 0;
                    break;
                case HAUT:
                    salle->portes[0].x = posEntree;
                    salle->portes[0].y = 0;
                    salle->portes[0].ouvert = 0;
                    break;
                case BAS: 
                    salle->portes[0].x = posEntree;
                    salle->portes[0].y = taille_verticale-1;
                    salle->portes[0].ouvert = 0;
                    break;
            }
            //cree les autres portes
            creationPortes(salle, entree, sallesrest);   
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

    //pour la premiere salle, on affiche manuellement la premiere porte
    if(entree==-1){
        salle->disp[salle->portes[0].y][salle->portes[0].x] = PORTE;
    }

    for(int i=1; i<salle->nportes; i++) {
        salle->disp[salle->portes[i].y][salle->portes[i].x] = PORTE;

        //verifie qu'une salle ait la place de se generer derriere la porte
        verifPorte(salle,i, win);
        
        //si la porte n'a pas pu se generer, on reincremente le nombre de salles restantes
        if(salle->disp[salle->portes[i].y][salle->portes[i].x] == MUR_HORIZ || salle->disp[salle->portes[i].y][salle->portes[i].x] == MUR_VERTI){
            (*sallesrest)++;
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

    //ALLOCATION OBJETS
    int objets_existants = 0; //Objets existants dans la salle à sa création soit 0
    for(int i = 0; i<4;i++){ //Il peut y avoir jusqu'à 4 objets par salle
        /* Si le nombre de salles restantes à générer est identique aux nombres d'objets
        à récupérer pour gagner non apparues, on force l'apparition d'un de ces objets dans chacune
        des salles restantes*/
        if(*sallesrest==1 &&  portesNonOuvertes == 4-(*objets_speciaux_apparus)){
            salle->objets[objets_existants] = apparition_objet(salle, objets_speciaux_apparus,*sallesrest,portesNonOuvertes);
            objets_existants++;
        }
        
        /* Le pourcentage de chance d'apparition d'objets diminue en fonction du nombre
        d'objets dans la salle (30% si 0, 15% si 1, 7% si 2, 3% si 3)*/
        else if(rand()%100 <= (30/(objets_existants+1))){ 
            salle->objets[objets_existants] = apparition_objet(salle, objets_speciaux_apparus,*sallesrest,portesNonOuvertes);
            objets_existants++;
        }
    } 
    //ALLOCATION ENNEMI
    //Il peut y avoir jusqu'à 1 ennemi par salle
    /* Le pourcentage de chance d'apparition d'ennemi diminue en fonction du nombre
    d'objets dans la salle (60% si 0, 30% si 1, 20% si 2)*/
    if(rand()%100 <= 20){ 
        salle->ennemi = apparition_ennemi(salle);
    }
    else{
        salle->ennemi = NULL;
        salle->ennemi_existant=0;
    }
    
    return salle;
}

Salle * creerSalleProced(int x, int y, int nportes, int dir, WINDOW* win, 
int* sallesrest, int* objets_speciaux_apparus, int portesNonOuvertes) {
    if(win==NULL){
        exit(5);
    }
    if(sallesrest==NULL){
        exit(6);
    }
    if(objets_speciaux_apparus==NULL){
        exit(7);
    }
    //init attributs salles
    int v, h;
    v = rand()%(TAILLE_MAX_V-2)+3;
    h = rand()%(TAILLE_MAX_H-2)+3;
    int posEntree=0;
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
            posEntree = rand()%(v-2)+1; 
            return creerSalle(h, v, x-h-1, y-posEntree, nportes, dir, posEntree, win, sallesrest, objets_speciaux_apparus, portesNonOuvertes); 
            break;
        case BAS: 
            //genere la salle en haut de la salle actuelle
            posEntree = rand()%(h-2)+1; 
            return creerSalle(h, v, x-posEntree, y-v-1, nportes, dir,posEntree,win,sallesrest, objets_speciaux_apparus, portesNonOuvertes);
            break;
        case GAUCHE: 
            //genere la salle a droite de la salle actuelle
            posEntree = rand()%(v-2)+1; 
            return creerSalle(h, v, x+2, y-posEntree, nportes, dir, posEntree, win,sallesrest, objets_speciaux_apparus, portesNonOuvertes);
            break;
        case HAUT: 
            //genere la salle en bas de la salle actuelle
            posEntree = rand()%(h-2)+1; 
            return creerSalle(h, v, x-posEntree, y+2, nportes, dir,posEntree,win,sallesrest,objets_speciaux_apparus, portesNonOuvertes);
            break;
        default: 
            //permet de creer la salle de depart
            return creerSalle(h, v, x, y, nportes, dir,posEntree,win,sallesrest,objets_speciaux_apparus, portesNonOuvertes);
            break;
    }
}


void dessineSalle(WINDOW * win, Salle * salle) {
    /* affiche la salle sur la fenetre en parcourant la salle*/
    if(win==NULL){
        exit(8);
    }
    if(salle==NULL){
        exit(9);
    }
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
                    mvwaddstr(win, salle->y+i, salle->x+j, PORTE_CHR);
                    //conditions placent des caracteres invisibles dans un espace 3*3 devant la salle afin de 'marquer' l'espace pour une future salle
                    if(j==0){ //porte a gauche
                        for(int k=1; k<4; k++){
                            for(int l=-1; l<=1; l++){
                                mvwaddstr(win, salle->y+i+l, salle->x+j-k, MARQUAGE_CHR);
                            }
                        }
                    }
                    else if(j==salle->longueur-1){ //porte a droite
                        for(int k=1; k<4; k++){
                            for(int l=-1; l<=1; l++){
                                mvwaddstr(win, salle->y+i+l, salle->x+j+k, MARQUAGE_CHR);
                            }
                        }
                    }
                    else if(i==0){ //porte en haut
                        for(int k=1; k<4; k++){
                            for(int l=-1; l<=1; l++){
                                mvwaddstr(win, salle->y+i-k, salle->x+j+l, MARQUAGE_CHR);
                            }
                        }
                    }
                    else if(i==salle->hauteur-1){ //porte en bas
                        for(int k=1; k<4; k++){
                            for(int l=-1; l<=1; l++){
                                mvwaddstr(win, salle->y+i+k, salle->x+j+l, MARQUAGE_CHR);
                            }
                        }
                    }
                    break;

                //affiche les objets
                case BOUTEILLE_O2:
                    mvwaddstr(win, salle->y+i, salle->x+j, BOUTEILLE_O2_CHR);
                    break;
                case BANDAGE:
                    mvwaddstr(win, salle->y+i, salle->x+j, BANDAGE_CHR);
                    break;
                case XP:
                    mvwaddstr(win, salle->y+i, salle->x+j, XP_CHR);
                    break;
                case GENERATEUR:
                    mvwaddstr(win, salle->y+i, salle->x+j, GENERATEUR_CHR);
                    break;
                case REACTEUR_1:
                    mvwaddstr(win, salle->y+i, salle->x+j, REACTEUR_CHR);
                    break;
                case REACTEUR_2:
                    mvwaddstr(win, salle->y+i, salle->x+j, REACTEUR_CHR);
                    break;
                case PC:
                    mvwaddstr(win, salle->y+i, salle->x+j, PC_CHR);
                    break;
                default:
                    break;
            }
        }
    }
}

void dessineSalles(WINDOW * win, Salle ** carte, int salles_existantes) {
    /*affiche l'ensemble des salles*/
    if(win==NULL){
        exit(10);
    }
    if(carte==NULL){
        exit(11);
    }
    for(int i = 0; i<salles_existantes; i++) {
        dessineSalle(win, carte[i]);
    }
}

void libereSalle(Salle * salle) {
    /*libere l'emplacement memoire de la salle*/
    if(salle==NULL){
        exit(12);
    }
    for(int i=0;i<salle->hauteur;i++){
        free(salle->disp[i]);
    }
    free(salle->disp);
    free(salle);
}

int compteurPortesNonOuvertes(Salle ** carte, int salles_existantes){
    /* Compte le nombre de portes non ouvertes sur la carte (sert à
    forcer l'apparition des objets à récupérer s'ils ne sont pas apparus)*/
    if(carte==NULL){
        exit(13);
    }
    int compteur = 0;
    for(int i=0; i<salles_existantes;i++){
      for(int j=0; j<carte[i]->nportes;j++){
        if(carte[i]->portes[j].ouvert == 0){
            compteur += 1;
            }  
        }
    }
    return compteur;
}

void enleve_marquage(int entree, int x, int y, int taille_horizontale, int taille_verticale, int posEntree, WINDOW* win){
    /*enleve le marquage de caracteres invisibles afin que la salle puisse etre cree sans problemes*/
    if(win==NULL){
        exit(14);
    }
    switch(entree){
        case GAUCHE:
            for(int i=0;i<3;i++){
                for(int j=-1;j<=1;j++){
                    mvwaddch(win, y+posEntree+j, x+i, ' ');
                }
            }
            break;
        case DROITE:
            for(int i=0;i<3;i++){
                for(int j=-1;j<=1;j++){
                    mvwaddch(win, y+posEntree+j, x+taille_horizontale-1-i, ' ');
                }
            }
            break;
        case HAUT:
            for(int i=0;i<3;i++){
                for(int j=-1;j<=1;j++){
                    mvwaddch(win, y+i, x+posEntree+j, ' ');
                }
            }
            break;
        case BAS:
            for(int i=0;i<3;i++){
                for(int j=-1;j<=1;j++){
                    mvwaddch(win, y+taille_verticale-1-i, x+posEntree+j, ' ');
                }
            }
            break; 
        default:
            break;
    }
}

void verif_superposition(int entree, int* posEntree, int* x, int* y, int* taille_horizontale, int* taille_verticale, WINDOW* win){
    /*Cette fonction permet de verifier qu'il n'y a pas de superposition lors de la generation de salle*/
    if(posEntree==NULL){
        exit(15);
    }
    if(x==NULL || y==NULL){
        exit(16);
    }
    if(taille_horizontale==NULL || taille_verticale==NULL){
        exit(17);
    }
    if(win==NULL){
        exit(18);
    }
    int i; //compteur
    int se_superpose; //variable qui determine si la salle se superpose

    /*boucle verifie que la salle ne se superpose pas, et reduit les dims de la salle si c'est le cas
    se finit quand la salle ne se superpose plus avec une autre salle*/
    do{
        //on initialise le compteur et la var de verif a 0
        i=0;
        se_superpose=0;
        if(entree==GAUCHE || entree==DROITE){
            while(i<*taille_horizontale || i<*taille_verticale){
                if(i<*taille_horizontale && *taille_horizontale>3){
                    /*on verifie que les murs horizontaux ne rencontrent pas d'autres salles
                    si c'est le cas on reduit la taille horizontale*/
                    if(mvwinch(win,*y,*x+i)!=' '||mvwinch(win,*y+*taille_verticale-1,*x+i)!=' '){
                        if(entree==DROITE){ //si l'entree est a droite, on change l'origine pour que la salle soit toujours collee a la salle precedente
                            (*x)++;
                        }
                        (*taille_horizontale)--;
                        se_superpose=1;
                    }
                }
                if(i<*taille_verticale && *taille_verticale>3){
                    /*on verifie que les murs verticaux ne rencontrent pas d'autres salles
                    si c'est le cas on reduit la taille verticale*/
                    if(mvwinch(win,*y+i,*x)!=' '||mvwinch(win,*y+i,*x+*taille_horizontale-1)!=' '){
                        //si la superposition est en haut de la porte on change l'origine et on replace la position de l'entree
                        if(i<*posEntree-1){
                            (*y)++;
                            (*posEntree)--;
                        }
                        //sinon on reduit la taille verticale
                        else if(i>*posEntree+1){
                            (*taille_verticale)--;
                        }
                        se_superpose=1;
                    }
                }
                i++;
            }
        }
        if(entree==HAUT || entree==BAS){
            while(i<*taille_horizontale || i<*taille_verticale){
                if(i<*taille_horizontale && *taille_horizontale>3){
                    /*on verifie que les murs horizontaux ne rencontrent pas d'autres salles
                    si c'est le cas on reduit la taille horizontale*/
                    if(mvwinch(win,*y,*x+i)!=' '||mvwinch(win,*y+*taille_verticale-1,*x+i)!=' '){
                        //si la superposition est a gauche de la porte on change l'origine et on replace la position de l'entree
                        if(i<*posEntree-1){
                            (*x)++;
                            (*posEntree)--;
                        }
                        //sinon on reduit la taille horizontale
                        else if(i>*posEntree+1){
                            (*taille_horizontale)--;
                        }
                        se_superpose=1;
                    }
                }
                if(i<*taille_verticale && *taille_verticale>3){
                    /*on verifie que les murs verticaux ne rencontrent pas d'autres salles
                    si c'est le cas on reduit la taille verticale*/
                    if(mvwinch(win,*y+i,*x)!=' '||mvwinch(win,*y+i,*x+*taille_horizontale-1)!=' '){
                        if(entree==BAS){ //si l'entree est en bas, on change l'origine pour que la salle soit toujours collee a la salle precedente
                            (*y)++;
                        }
                        (*taille_verticale)--;
                        se_superpose=1;
                    }
                }
                i++;
            }
        }
    }while(se_superpose==1);
}