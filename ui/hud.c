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


HUD * hudJeu(int x, int y, int hauteur, int largeur, Joueur * joueur) {
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
    minuteurStr[0] = malloc(sizeof(char) * 200);
    if(minuteurStr == NULL){
        logMessage(ERROR, "Erreur d'allocation de mémoire pour le minuteur");
        exit(1);
    }

    *nivStr = strcpy(*nivStr, "Niveau : ");
    *xpStr = strcpy(*xpStr, "XP : ");
    *pvStr = strcpy(*pvStr, "PV : ");
    *minuteurStr = strcpy(*minuteurStr, "Minuteur : ");


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

    sprintf(*nameStr, "Nom : %s", joueur->nom);
    sprintf(*atkStr, "Attaque : %d", joueur->att);
    sprintf(*defStr, "Défense : %d", joueur->def);
    sprintf(*minuteurStr, "Minuteur : %d", 300);

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
    

    pv = creerStatusBar(x + 11, y + hauteur/2, 10, 2, joueur->pv/10);
    xp = creerStatusBar(x + 11, y + hauteur/2 + 1, 10, 3, joueur->xp/10);
    niv = creerStatusBar(x + 11, y + hauteur/2 + 2, 10, 4, joueur->niv);

    pvText = creerTexte(x + 1, y + hauteur/2, pvStr, 1, 7);
    xpText = creerTexte(x + 1, y + hauteur/2 + 1, xpStr, 1, 7);
    nivText = creerTexte(x + 1, y + hauteur/2 + 2, nivStr, 1, 7);
    nameText = creerTexte(x + 1, y + hauteur/2 - 2, nameStr, 1, 7);
    attText = creerTexte(x + largeur/3 - 10, y + hauteur/2, atkStr, 1, 7);
    defText = creerTexte(x + largeur/3 - 10, y + hauteur/2 + 1, defStr, 1, 7);
    minuteurTexte = creerTexte(x + 2*largeur/3 - 10,y+hauteur/2 + 3,minuteurStr,1,7);

    hud = creerHUD(x, y, hauteur, largeur, 1, 7, 3);

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
