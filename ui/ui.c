#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "../logger.h"



void initCouleur() {
    /* Initialisation des couleurs pour les textes et menus*/
    if(!has_colors()) {
        logMessage(WARNING, "erreur initialisation couleur");
        return;
    }
    start_color();

    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_YELLOW);
}

void renduTexte(WINDOW * win, Texte texte) {
    /* Sert à donner de la couleur aux textes*/
    int i;
    wattron(win, COLOR_PAIR(texte.couleur));
    for(i = 0; i < texte.nbLignes; i++) {
        mvwprintw(win ,texte.y + i, texte.x, "%s", texte.texte[i]);
    }
    wattroff(win, COLOR_PAIR(texte.couleur));
}

void renduBouton(WINDOW * win, Bouton bouton, int sel) {
    /* Sert à donner de la couleur aux boutons du menu*/
    if(!sel) {
        wattron(win, COLOR_PAIR(bouton.couleur));
    }
    mvwprintw(win, bouton.y, bouton.x, "%s", bouton.texte);
    if(sel) {
        //wattroff(win, COLOR_PAIR(bouton.couleurSel));
        mvwchgat(win, bouton.y, bouton.x, strlen(bouton.texte), A_REVERSE, 0, NULL);
    } else {
        wattroff(win, COLOR_PAIR(bouton.couleur));
    }
}

void renduBoutons(WINDOW * win, Bouton ** boutons, int sel, int nbBoutons) {
    /* Affiche les boutons avec cette couleur selon le nombre de bouton.
    Uniformise la couleur des boutons d'un même menu et change la couleur de celui-ci si
    il est sélectionné par le curseur*/
    for(int i = 0; i < nbBoutons; i++) {
        if(i == sel) {
            renduBouton(win, *boutons[i], 1);
        } else {
            renduBouton(win, *boutons[i], 0);
        }
    }
}


void renduMessage(WINDOW * win, MiniMenu message) {
    /* Affiche les messages des boutons avec cette couleur selon la couleur des boutons.
    Uniformise la couleur des textes des boutons d'un même menu et change 
    la couleur du texte de celui-ci s'il est sélectionné par le curseur*/
    int i;
    wattron(win, COLOR_PAIR(message.couleur));
    renduTexte(win, *message.titre);
    if(message.message != NULL) {
        renduTexte(win, *message.message);
    }
    wattroff(win, COLOR_PAIR(message.couleur));
    for(i = 0; i < message.nbBoutons; i++) {
        if(i == message.curseur) {
            renduBouton(win, *message.boutons[i], 1);
        } else {
            renduBouton(win, *message.boutons[i], 0);
        }
    }
}

void renduMenu(WINDOW * win, Menu menu) {
    /* Sert à faire le rendu du menu à partir de la fonction précédente renduBouton*/
    int i;
    
    renduTexte(win, *menu.titre);

    for(i = 0; i < menu.nbBoutons; i++) {
        if(i == menu.selecteur) {
            renduBouton(win, *menu.boutons[i], 1);
        } else {
            renduBouton(win, *menu.boutons[i], 0);
        }
    }
}


Menu * creerMenu(int hauteur, int largeur, Texte * titre, int nbBoutons, int espace, int couleurFond) {
    /* Fonction servant à créer un menu*/
    //Initialisation
    Menu * menu = NULL;
    //Allocation mémoire
    menu = malloc(sizeof(Menu));
    if(menu == NULL) {
        logMessage(CRITICAL, "erreur malloc menu");
        exit(1);
    }
    //Initialisation des membres
    menu->hauteur = hauteur;
    menu->largeur = largeur;
    menu->titre = titre;
    menu->nbBoutons = nbBoutons;
    menu->espace = espace;
    menu->couleurFond = couleurFond;
    menu->selecteur = 0;
    menu->selEtat = 0;
    menu->focus = 1;
    menu->boutons = NULL;
    //Allocation des pointeurs boutons
    menu->boutons = malloc(nbBoutons * sizeof(Bouton*));
    if(menu->boutons == NULL) {
        logMessage(CRITICAL, "erreur malloc boutons menu");
        exit(1);
    }
    return menu;
}

Bouton * creerBouton(int x, int y, int couleur, int couleurSel, char * texte) {
    /* Fonction permettant de créer les pointeurs de bouton du menu*/
    //Initialisation
    Bouton * bouton = NULL;
    //Allocation mémoire
    bouton = malloc(sizeof(Bouton));
    if(bouton == NULL) {
        logMessage(CRITICAL, "erreur malloc bouton");
        exit(1);
    }
    //Initialisation des membres
    bouton->x = x;
    bouton->y = y;
    bouton->couleur = couleur;
    bouton->couleurSel = couleurSel;
    bouton->texte = texte;
    return bouton;
}

MiniMenu * creerMessage(int x, int y, int hauteur, int largeur, int couleur, Texte * titre, int nbBoutons, Texte * texte) {
    /* Fonction permettant de créer les sous-menus*/
    //Initialisation
    MiniMenu * message = NULL;
    //Allocation mémoire
    message = malloc(sizeof(MiniMenu));
    if(message == NULL) {
        logMessage(CRITICAL, "erreur malloc message");
        exit(1);
    }
    //Initialisation des membres
    message->x = x;
    message->y = y;
    message->hauteur = hauteur;
    message->largeur = largeur;
    message->couleur = couleur;
    message->titre = titre;
    message->boutons = NULL;
    message->boutons = malloc(nbBoutons * sizeof(Bouton*));
    if(message->boutons == NULL) {
        logMessage(CRITICAL, "erreur malloc boutons menu");
        exit(1);
    }
    message->nbBoutons = nbBoutons;
    message->message = texte;
    message->curseur = 0;
    message->selEtat = 0;
    return message;
}

InvMenu * creerInvMenu(int x, int y, int hauteur, int largeur, int couleur, Texte * titre, int nbBoutCol, int nbBoutLig) {
    /* Fonction permettant de créer les menus d'inventaire*/
    //Initialisation
    InvMenu * invMenu = NULL;
    //Allocation mémoire
    invMenu = malloc(sizeof(InvMenu));
    if(invMenu == NULL) {
        logMessage(CRITICAL, "erreur malloc initInvMenu");
        exit(1);
    }
    //Initialisation des membres
    invMenu->x = x;
    invMenu->y = y;
    invMenu->hauteur = hauteur;
    invMenu->largeur = largeur;
    invMenu->couleur = couleur;
    invMenu->titre = titre;
    invMenu->nbBoutCol = nbBoutCol;
    invMenu->nbBoutLig = nbBoutLig;
    invMenu->boutons = NULL;
    invMenu->boutons = malloc(nbBoutCol * sizeof(Bouton**));
    if(invMenu->boutons == NULL) {
        logMessage(CRITICAL, "erreur malloc boutons initInvMenu");
        exit(1);
    }
    invMenu->reprendre = NULL;
    invMenu->message = NULL;
    invMenu->curseurCol = 0;
    invMenu->curseurLig = 0;
    invMenu->curseurObj = 0;
    invMenu->selEtat = 0;
    invMenu->montrerMsg = 0;
    invMenu->selRetour = 0;
    return invMenu;
}

Texte * creerTexte(int x, int y, char ** texte, int nbLignes, int couleur) {
    /* Message servant à créer le texte des boutons*/
    //Initialisation
    Texte * t = NULL;
    //Allocation mémoire
    t = malloc(sizeof(Texte));
    if(t == NULL) {
        logMessage(CRITICAL, "erreur malloc texte");
        exit(1);
    }
    //Initialisation des membres
    t->x = x;
    t->y = y;
    t->texte = texte;
    t->nbLignes = nbLignes;
    t->couleur = couleur;
    return t;
}

EntreeTexte * creerEntreeTexte(int x, int y, int taille, int couleur, Texte * titre) {
    /* Fonction permettant de créer une entrée de texte (comme pour la création de la graine par exemple)*/
    //Initialisation
    EntreeTexte * entree = NULL;
    //Allocation mémoire
    entree = malloc(sizeof(EntreeTexte));
    if(entree == NULL) {
        logMessage(CRITICAL, "erreur malloc entree texte");
        exit(1);
    }
    //Initialisation des membres
    entree->x = x;
    entree->y = y;
    entree->curseur = 0;
    entree->taille = taille;
    entree->buffer = NULL; //buffer
    //Allocation buffer
    entree->buffer = malloc(sizeof(char) * (taille + 1));
    if(entree->buffer == NULL) {
        logMessage(CRITICAL, "erreur malloc buffer entree texte");
        exit(1);
    }
    entree->affichage = NULL;
    entree->affichage = malloc(sizeof(char) * (taille + 1));
    if(entree->affichage == NULL) {
        logMessage(CRITICAL, "erreur malloc affichage buffer");
        exit(1);
    }

    for(int i = 0; i < taille; i++) {
        entree->affichage[i] = '_';
    }
    entree->affichage[taille] = '\0';

    entree->buffer[0] = '\0'; // initialisation du buffer
    entree->titre = titre;
    entree->couleur = couleur;
    entree->valide = 0; //Sert à savoir si l'entrée est valide
    return entree;
}

void renduEntreeTexte(WINDOW * win, EntreeTexte * entree) {
    /* Sert à afficher l'entrée texte sur le terminal en fonction des paramètres de celui-ci*/
    renduTexte(win, *entree->titre);
    for(int i = 0; i < entree->taille; i++) {
        mvwprintw(win, entree->y, entree->x + i," ");
    }
    wattron(win, COLOR_PAIR(entree->couleur));
    mvwprintw(win, entree->y, entree->x, "%s", entree->affichage);
    mvwchgat(win, entree->y, entree->x, entree->taille, A_REVERSE,entree->couleur, NULL);
    mvwchgat(win, entree->y, entree->x + entree->curseur, 1, A_UNDERLINE, entree->couleur, NULL);
    wattroff(win, COLOR_PAIR(entree->couleur));
}

void freeMenu(Menu * menu) {
    /* Fonction servant à ce qu'une fois que le menu n'est plus utilisé on libère l'espace*/
    free(menu->titre);
    for(int i = 0; i < menu->nbBoutons; i++) {
        free(menu->boutons[i]);
    }
    free(menu->boutons);
    free(menu);
}

StatusBar * creerStatusBar(int x, int y, int size, int color, int cursor) {
    /* Fonction permettant de créer les barres de status*/
    StatusBar * sb = NULL;
    sb = malloc(sizeof(StatusBar));
    if(sb == NULL) {
        logMessage(CRITICAL, "erreur malloc status bar");
        exit(1);
    }
    sb->x = x;
    sb->y = y;
    sb->size = size;
    sb->color = color;
    sb->cursor = cursor;
    return sb;
}

void renduStatusBar(WINDOW * win, StatusBar * sb) {
    /* Fonction permettant le rendu sur le terminal de ces barres de statut*/
    wattron(win, COLOR_PAIR(sb->color));
    for(int i = 0; i < sb->cursor; i++) {
        mvwprintw(win, sb->y, sb->x + i, "█");
    }
    for(int i = sb->cursor; i < sb->size; i++) {
        mvwprintw(win, sb->y, sb->x + i, "░");
    }
    wattroff(win, COLOR_PAIR(sb->color));
}

HUD * creerHUD(int x, int y, int hauteur, int largeur, int outlineColor, int nbText, int nbStatBar) {
    //Fonction permettant d'initialiser la HUD
    //Initialisation
    HUD * hud = NULL;
    //Allocation mémoire
    hud = malloc(sizeof(HUD));
    if(hud == NULL) {
        logMessage(CRITICAL, "erreur malloc hud");
        exit(1);
    }
    //Initialisation des membres de la HUD
    hud->x = x;
    hud->y = y;
    hud->hauteur = hauteur;
    hud->largeur = largeur;
    hud->outlineColor = outlineColor;
    hud->nbText = nbText;
    hud->nbStatBar = nbStatBar;
    hud->textWidgets = NULL;
    hud->textWidgets = malloc(nbText * sizeof(Texte*));
    if(hud->textWidgets == NULL) {
        logMessage(CRITICAL, "erreur malloc texte hud");
        exit(1);
    }
    hud->statBarWidgets = NULL;
    hud->statBarWidgets = malloc(nbStatBar * sizeof(StatusBar*));
    if(hud->statBarWidgets == NULL) {
        logMessage(CRITICAL, "erreur malloc barre de statut hud");
        exit(1);
    }
    return hud;
}

void freeEntreeTexte(EntreeTexte * entree) {
    /* Fonction permettant de libérer l'espace mémoire pris par l'affichage de l'entrée texte
    quand le menu se ferme*/
    free(entree->buffer);
    free(entree->affichage);
    free(entree);
}

void freeTexte(Texte * texte) {
    /* Fonction permettant de libérer l'espace mémoire pris par l'affichage du texte du menu
    quand le menu se ferme*/
    for(int i = 0; i < texte->nbLignes; i++) {
        free(texte->texte[i]);
    }
    free(texte->texte);
    free(texte);
}

