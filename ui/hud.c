//
// Created by valerie on 22/05/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "ui.h"
#include "../logger.h"
#include "../CosmicYonder.h"
#include "../json/json.h"


HUD * hudJeu(int x, int y, int hauteur, int largeur, Joueur * joueur, int minuteur) {
    /* Fonction gérant la création des informations comme les barres de vie et 
    les valeurs tels que le minuteur ou les stats du joueur de la hud en jeu*/

    //Initialisation des variables nécessaires à la création de la hud
    HUD * hud = NULL;

    StatusBar * pv = NULL;
    StatusBar * xp = NULL;
    StatusBar * niv = NULL;

    Texte * pvText = NULL;
    Texte * xpText = NULL;
    Texte * nivText = NULL;
    Texte * nameText = NULL;
    Texte * attText = NULL;
    Texte * defText = NULL;
    Texte * minuteurTexte = NULL;

    char ** atkStr = NULL;
    char ** defStr = NULL;
    char ** nivStr = NULL;
    char ** xpStr = NULL;
    char ** pvStr = NULL;
    char ** minuteurStr = NULL;

    char ** nameStr = NULL;

    //Allocation de des variables de texte et des infos de la partie dynamiquement
    atkStr = malloc(sizeof(char*));
    if(atkStr == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour l'attaque du joueur");
        exit(1);
    }
    atkStr[0] = malloc(sizeof(char) * 200);
    if(atkStr[0] == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour l'attaque du joueur");
        exit(1);
    }

    defStr = malloc(sizeof(char*));
    if(defStr == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour la défense du joueur");
        exit(1);
    }
    defStr[0] = malloc(sizeof(char) * 200);
    if(defStr[0] == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour la défense du joueur");
        exit(1);
    }

    nivStr = malloc(sizeof(char*));
    if(nivStr == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le niveau du joueur");
        exit(1);
    }
    nivStr[0] = malloc(sizeof(char) * 200);
    if(nivStr[0] == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le niveau du joueur");
        exit(1);
    }

    xpStr = malloc(sizeof(char*));
    if(xpStr == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour l'expérience du joueur");
        exit(1);
    }
    xpStr[0] = malloc(sizeof(char) * 200);
    if(xpStr[0] == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour l'expérience du joueur");
        exit(1);
    }

    pvStr = malloc(sizeof(char*));
    if(pvStr == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour les points de vie du joueur");
        exit(1);
    }
    pvStr[0] = malloc(sizeof(char) * 200);
    if(pvStr[0] == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour les points de vie du joueur");
        exit(1);
    }
    
    minuteurStr = malloc(sizeof(char*));
    if(minuteurStr == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le minuteur");
        exit(1);
    
    }
    minuteurStr[0] = malloc(sizeof(char) * 10);
    if(minuteurStr[0] == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le minuteur");
        exit(1);
    }

    minuteurStr = malloc(sizeof(char*));
    if(minuteurStr == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le minuteur");
        exit(1);

    }
    minuteurStr[0] = malloc(sizeof(char) * 10);
    if(minuteurStr[0] == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le minuteur");
        exit(1);
    }

    *nivStr = strcpy(*nivStr, "Niveau : ");
    *xpStr = strcpy(*xpStr, "XP : ");
    *pvStr = strcpy(*pvStr, "PV : ");

    nameStr = malloc(sizeof(char*));
    if(nameStr == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le nom du joueur");
        exit(1);
    }
    nameStr[0] = malloc(sizeof(char) * 200);
    if(nameStr[0] == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le nom du joueur");
        exit(1);
    }

    /*Création des chaines de caractères pour le nom, l'attaque, la défense et le minuteur
    Celles-ci s'afficheront dans la hud*/
    sprintf(*nameStr, "Nom : %s", joueur->nom);
    sprintf(*atkStr, "Attaque : %d", joueur->att);
    sprintf(*defStr, "Défense : %d", joueur->def);
    sprintf(*minuteurStr, "Minuteur : %d", minuteur);

    //Allocation mémoire des textes et barres de la hud
    pv = malloc(sizeof(StatusBar));
    if(pv == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour la barre de vie");
        exit(1);
    }
    xp = malloc(sizeof(StatusBar));
    if(xp == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour la barre d'expérience");
        exit(1);
    }
    niv = malloc(sizeof(StatusBar));
    if(niv == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour la barre de niveau");
        exit(1);
    }

    pvText = malloc(sizeof(Texte));
    if(pvText == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le texte de la barre de vie");
        exit(1);
    }
    xpText = malloc(sizeof(Texte));
    if(xpText == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le texte de la barre d'expérience");
        exit(1);
    }
    nivText = malloc(sizeof(Texte));
    if(nivText == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le texte de la barre de niveau");
        exit(1);
    }
    nameText = malloc(sizeof(Texte));
    if(nameText == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le texte du nom");
        exit(1);
    }
    attText = malloc(sizeof(Texte));
    if(attText == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le texte de l'attaque");
        exit(1);
    }
    defText = malloc(sizeof(Texte));
    if(defText == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le texte de la défense");
        exit(1);
    }
    minuteurTexte = malloc(sizeof(Texte));
    if(minuteurTexte == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le texte du minuteur");
        exit(1);
    }

    //Création des barres et des textes de la hud  selon une abscisse et une ordonnée
    pv = creerStatusBar(x + 11, y + hauteur/2, 10, 2, joueur->pv/10);
    xp = creerStatusBar(x + 11, y + hauteur/2 + 1, 10, 3, joueur->xp/10);
    niv = creerStatusBar(x + 11, y + hauteur/2 + 2, 10, 4, joueur->niv);

    pvText = creerTexte(x + 1, y + hauteur/2, pvStr, 1, 7);
    xpText = creerTexte(x + 1, y + hauteur/2 + 1, xpStr, 1, 7);
    nivText = creerTexte(x + 1, y + hauteur/2 + 2, nivStr, 1, 7);
    nameText = creerTexte(x + 1, y + hauteur/2 - 2, nameStr, 1, 7);
    attText = creerTexte(x + largeur/3 - 10, y + hauteur/2, atkStr, 1, 7);
    defText = creerTexte(x + largeur/3 - 10, y + hauteur/2 + 1, defStr, 1, 7);
    minuteurTexte = creerTexte(x + largeur/3 - 10,y+hauteur/2 + 2,minuteurStr,1,7);

    //Création de la hud
    hud = creerHUD(x, y, hauteur, largeur, 1, 7, 3);
    //Placement des barres et des textes dans la hud
    hud->textWidgets[0] = pvText;
    hud->textWidgets[1] = xpText;
    hud->textWidgets[2] = nivText;
    hud->textWidgets[3] = nameText;
    hud->textWidgets[4] = attText;
    hud->textWidgets[5] = defText;
    hud->textWidgets[6] = minuteurTexte;

    hud->statBarWidgets[0] = pv;
    hud->statBarWidgets[1] = xp;
    hud->statBarWidgets[2] = niv;

    hud->x = x;
    hud->y = y;
    hud->hauteur = hauteur;
    hud->largeur = largeur;
    return hud;
}

void renderInventaire(WINDOW * win, int y, int x, Inventaire inventaire, int nb_obj_inv, int nb_obj_spe_inv) {
    int xTmp; // calcul des coordonnees
    mvwhline(win, y, x, ACS_HLINE, INV_TAILLE*2);
    mvwhline(win, y + 2, x + 1, ACS_HLINE, INV_TAILLE*2);
    for(int i = 0; i < INV_TAILLE + 1; i++) {
        mvwvline(win, y, x + 2*i, ACS_VLINE, 2);
    }
    for(int i = 0; i < INV_TAILLE; i++) {
        mvwaddch(win, y + 2, x + 2*i, ACS_BTEE);
        mvwaddch(win, y, x + 2*i, ACS_TTEE);
    }
    mvwaddch(win, y + 2, x + 2*INV_TAILLE, ACS_LRCORNER);
    mvwaddch(win, y, x + 2*INV_TAILLE, ACS_URCORNER);

    mvwvline(win, y, x, ACS_VLINE, 2);
    mvwvline(win, y, x + INV_TAILLE, ACS_VLINE, 2);
    mvwaddch(win, y, x, ACS_ULCORNER);
    mvwaddch(win, y, x + INV_TAILLE, ACS_TTEE);
    mvwaddch(win, y + 2, x, ACS_LLCORNER);



    for(int i = 0; i < INV_TAILLE; i++) { // OBJETS SPECIAUX
        switch(inventaire.obTab[i].id) {
            case BOUTEILLE_O2:
                mvwaddstr(win,  y + 1, x + 2*i + 1, BOUTEILLE_O2_CHR);
                break;
            case BANDAGE:
                mvwaddstr(win, y + 1, x + 2*i + 1, BANDAGE_CHR);
                break;
            case CLE:
                mvwaddstr(win, y + 1,x + 2*i + 1, CLE_CHR);
                break;
            case GENERATEUR:
                mvwaddstr(win, y + 1, x + 2*i + 1, GENERATEUR_CHR);
                break;
            case REACTEUR_1:
                mvwaddstr(win, y + 1,x + 2*i + 1, REACTEUR_CHR);
                break;
            case REACTEUR_2:
                mvwaddstr(win, y + 1,x + 2*i + 1, REACTEUR_CHR);
                break;
            case PC:
                mvwaddstr(win, y + 1, x + 2*i + 1, PC_CHR);
                break;
            case VIDE_OBJ:
                mvwaddstr(win, y + 1, x + 2*i + 1, " ");
                break;
        }
    }
}

void renduHUD(WINDOW * win, HUD * hud, int minuteur, Joueur * jou, int nb_obj_inv, int nb_obj_spe_inv) {
    // mise à jour des donnees de la hud
    hud->statBarWidgets[0]->cursor = jou->pv/10;
    hud->statBarWidgets[1]->cursor = jou->xp/10;
    hud->statBarWidgets[2]->cursor = jou->niv;


    // nettoyage de la zone
    for(int i = 0; i < hud->hauteur; i++) {
        for(int j = 0; j < hud->largeur; j++) {
            mvwprintw(win, hud->y + i, hud->x + j, " ");
        }
    }

    // bordures
    wattron(win, COLOR_PAIR(hud->outlineColor));
    mvwhline(win, hud->y, hud->x, ACS_HLINE, hud->largeur);
    mvwhline(win, hud->y + hud->hauteur - 1, hud->x, ACS_HLINE, hud->largeur);
    mvwvline(win, hud->y, hud->x, ACS_VLINE, hud->hauteur);
    mvwvline(win, hud->y, hud->x + hud->largeur - 1, ACS_VLINE, hud->hauteur);
    mvwaddch(win, hud->y, hud->x, ACS_ULCORNER);
    mvwaddch(win, hud->y, hud->x + hud->largeur - 1, ACS_URCORNER);
    mvwaddch(win, hud->y + hud->hauteur - 1, hud->x, ACS_LLCORNER);
    mvwaddch(win, hud->y + hud->hauteur - 1, hud->x + hud->largeur - 1, ACS_LRCORNER);
    wattroff(win, COLOR_PAIR(hud->outlineColor));

    sprintf(hud->textWidgets[6]->texte[0], "Minuteur : %d", minuteur);


    for(int i = 0; i < hud->nbText; i++) {
        renduTexte(win, *hud->textWidgets[i]);
    }
    for(int i = 0; i < hud->nbStatBar; i++) {
        renduStatusBar(win, hud->statBarWidgets[i]);
    }
    renderInventaire(win,hud->y + hud->hauteur/2 - 3,hud->x + hud->largeur/3 - 11, jou->inventaire, nb_obj_inv, nb_obj_spe_inv);
}

void renduInvDial(WINDOW * win, InvMenu * invMenu, Inventaire inventaire) {
    for(int i = 0; i < invMenu->hauteur; i++) {
        for(int j = 0; j < invMenu->largeur; j++) {
            mvwaddch(win, invMenu->y + i, invMenu->x + j, ' ');
        }
    }
    /* Dessin des bordures*/
    wattron(win, COLOR_PAIR(7));
    mvwhline(win, invMenu->message->y, invMenu->message->x, ACS_HLINE, invMenu->message->largeur);
    mvwhline(win, invMenu->message->y + invMenu->message->hauteur - 1, invMenu->message->x, ACS_HLINE, invMenu->message->largeur);
    mvwvline(win, invMenu->message->y, invMenu->message->x, ACS_VLINE, invMenu->message->hauteur);
    mvwvline(win, invMenu->message->y, invMenu->message->x + invMenu->message->largeur - 1, ACS_VLINE, invMenu->message->hauteur);
    mvwaddch(win, invMenu->message->y, invMenu->message->x, ACS_ULCORNER);
    mvwaddch(win, invMenu->message->y, invMenu->message->x + invMenu->message->largeur - 1, ACS_URCORNER);
    mvwaddch(win, invMenu->message->y + invMenu->message->hauteur - 1, invMenu->message->x, ACS_LLCORNER);
    mvwaddch(win, invMenu->message->y + invMenu->message->hauteur - 1, invMenu->message->x + invMenu->message->largeur - 1, ACS_LRCORNER);
    wattroff(win, COLOR_PAIR(7));
    switch(inventaire.obTab[invMenu->curseurObj].id) {
        case BOUTEILLE_O2:
            invMenu->message->titre->texte[0] = "Bouteille O2";
            break;
        case BANDAGE:
            invMenu->message->titre->texte[0] = "Bandage";
            break;
        case CLE:
            invMenu->message->titre->texte[0] = "Clef";
            break;
        case GENERATEUR:
            invMenu->message->titre->texte[0] = "Generateur";
            break;
        case REACTEUR_1:
            invMenu->message->titre->texte[0] = "Reacteur 1";
            break;
        case REACTEUR_2:
            invMenu->message->titre->texte[0] = "Reacteur 2";
            break;
        case PC:
            invMenu->message->titre->texte[0] = "PC";
            break;
        case VIDE_OBJ:
            invMenu->message->titre->texte[0] = "Vide";
            break;
    }

    renduMessage(win, *invMenu->message);
}

void renduInvMenu(WINDOW * win, InvMenu * invMenu, Inventaire inventaire) {
    short k = 0;
    // efface le texte sous la fenetre
    for(int i = 0; i < invMenu->hauteur; i++) {
        for(int j = 0; j < invMenu->largeur; j++) {
            mvwaddch(win, invMenu->y + i, invMenu->x + j, ' ');
        }
    }
    /* Dessin des bordures*/
    wattron(win, COLOR_PAIR(7));
    mvwhline(win, invMenu->y, invMenu->x, ACS_HLINE, invMenu->largeur);
    mvwhline(win, invMenu->y + invMenu->hauteur - 1, invMenu->x, ACS_HLINE, invMenu->largeur);
    mvwvline(win, invMenu->y, invMenu->x, ACS_VLINE, invMenu->hauteur);
    mvwvline(win, invMenu->y, invMenu->x + invMenu->largeur - 1, ACS_VLINE, invMenu->hauteur);
    mvwaddch(win, invMenu->y, invMenu->x, ACS_ULCORNER);
    mvwaddch(win, invMenu->y, invMenu->x + invMenu->largeur - 1, ACS_URCORNER);
    mvwaddch(win, invMenu->y + invMenu->hauteur - 1, invMenu->x, ACS_LLCORNER);
    mvwaddch(win, invMenu->y + invMenu->hauteur - 1, invMenu->x + invMenu->largeur - 1, ACS_LRCORNER);
    wattroff(win, COLOR_PAIR(7));

    renduTexte(win, *invMenu->titre);
    renduBouton(win, *invMenu->reprendre, 0);
    for(int i = 0; i < invMenu->nbBoutLig; i++) {
        for(int j = 0; j < invMenu->nbBoutCol; j++) {
            switch(inventaire.obTab[k].id) {
                case BOUTEILLE_O2:
                    invMenu->boutons[j][i]->texte = "Bouteille O2";
                    break;
                case BANDAGE:
                    invMenu->boutons[j][i]->texte = "Bandage";
                    break;
                case CLE:
                    invMenu->boutons[j][i]->texte = "Clef";
                    break;
                case GENERATEUR:
                    invMenu->boutons[j][i]->texte = "Generateur";
                    break;
                case REACTEUR_1:
                    invMenu->boutons[j][i]->texte = "Reacteur 1";
                    break;
                case REACTEUR_2:
                    invMenu->boutons[j][i]->texte = "Reacteur 2";
                    break;
                case PC:
                    invMenu->boutons[j][i]->texte = "PC";
                    break;
                case VIDE_OBJ:
                    invMenu->boutons[j][i]->texte = "Vide";
                    break;
            }
            if(invMenu->curseurCol == j && invMenu->curseurLig == i) {
                invMenu->curseurObj = k;
                renduBouton(win, *invMenu->boutons[j][i], 1);
            } else {
                renduBouton(win, *invMenu->boutons[j][i], 0);
            }
            k++;
        }
    }


}



void invBoucle(WINDOW *mainwin, int *touche, InvMenu *invMenu, Inventaire inventaire) {
    /* Fonction qui fait une boucle infini tant qu'on a pas choisi une option
    pour arrêter le jeu quand on fait pause*/
    while (!invMenu->selEtat) { //Tant qu'on ne sélectionne rien le jeu est arrêté
        wrefresh(mainwin);
        *touche = wgetch(mainwin);
        entreeInv(invMenu, touche);

        while(invMenu->montrerMsg) {
            wrefresh(mainwin);
            *touche = wgetch(mainwin);
            entreeMessage(invMenu->message, *touche);
            if(invMenu->message->selEtat) {
                switch(invMenu->message->curseur) {
                    case 0:
                        // UTILISER L'OBJET;
                        invMenu->montrerMsg = 0;
                        invMenu->message->selEtat = 0;
                        break;
                    case 1:
                        // JETER L'OBJET
                        inventaire.obTab[invMenu->curseurObj].id = VIDE_OBJ;
                        invMenu->montrerMsg = 0;
                        invMenu->message->selEtat = 0;
                        
                        break;
                    case 2:
                        // QUITTER
                        invMenu->montrerMsg = 0;
                        invMenu->message->selEtat = 0;

                        break;

                }
            
            
            }
            renduInvDial(mainwin, invMenu, inventaire);
        }
        renduInvMenu(mainwin, invMenu, inventaire);
        
    }
    invMenu -> montrerMsg = 0; 
    invMenu-> selEtat = 0;
}