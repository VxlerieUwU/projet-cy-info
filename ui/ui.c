#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "../logger.h"

// TODO: libérer la mémoire mdrrrr

void initCouleur() {
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
    int i;
    wattron(win, COLOR_PAIR(texte.couleur));
    for(i = 0; i < texte.nbLignes; i++) {
        mvwprintw(win ,texte.y + i, texte.x, "%s", texte.texte[i]);
    }
    wattroff(win, COLOR_PAIR(texte.couleur));
}

void renduBouton(WINDOW * win, Bouton bouton, int sel) {
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
    for(int i = 0; i < nbBoutons; i++) {
        if(i == sel) {
            renduBouton(win, *boutons[i], 1);
        } else {
            renduBouton(win, *boutons[i], 0);
        }
    }
}


void renduMessage(WINDOW * win, MiniMenu message) {
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
    Menu * menu = NULL;
    menu = malloc(sizeof(Menu));
    if(menu == NULL) {
        logMessage(CRITICAL, "erreur malloc menu");
        exit(1);
    }
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
    menu->boutons = malloc(nbBoutons * sizeof(Bouton*));
    if(menu->boutons == NULL) {
        logMessage(CRITICAL, "erreur malloc boutons menu");
        exit(1);
    }
    return menu;
}

Bouton * creerBouton(int x, int y, int couleur, int couleurSel, char * texte) {
    Bouton * bouton = NULL;
    bouton = malloc(sizeof(Bouton));
    if(bouton == NULL) {
        logMessage(CRITICAL, "erreur malloc bouton");
        exit(1);
    }
    bouton->x = x;
    bouton->y = y;
    bouton->couleur = couleur;
    bouton->couleurSel = couleurSel;
    bouton->texte = texte;
    return bouton;
}

MiniMenu * creerMessage(int x, int y, int hauteur, int largeur, int couleur, Texte * titre, int nbBoutons, Texte * texte) {
    MiniMenu * message = NULL;
    message = malloc(sizeof(MiniMenu));
    if(message == NULL) {
        logMessage(CRITICAL, "erreur malloc message");
        exit(1);
    }
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

Texte * creerTexte(int x, int y, char ** texte, int nbLignes, int couleur) {
    Texte * t = NULL;
    t = malloc(sizeof(Texte));
    if(t == NULL) {
        logMessage(CRITICAL, "erreur malloc texte");
        exit(1);
    }
    t->x = x;
    t->y = y;
    t->texte = texte;
    t->nbLignes = nbLignes;
    t->couleur = couleur;
    return t;
}

EntreeTexte * creerEntreeTexte(int x, int y, int taille, int couleur, Texte * titre) {
    EntreeTexte * entree = NULL;
    entree = malloc(sizeof(EntreeTexte));
    if(entree == NULL) {
        logMessage(CRITICAL, "erreur malloc entree texte");
        exit(1);
    }
    entree->x = x;
    entree->y = y;
    entree->curseur = 0;
    entree->taille = taille;
    entree->buffer = NULL;
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
    entree->valide = 0;
    return entree;
}

void renduEntreeTexte(WINDOW * win, EntreeTexte * entree) {
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
    free(menu->titre);
    for(int i = 0; i < menu->nbBoutons; i++) {
        free(menu->boutons[i]);
    }
    free(menu->boutons);
    free(menu);
}

StatusBar * creerStatusBar(int x, int y, int size, int color, int cursor) {
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
    HUD * hud = NULL;
    hud = malloc(sizeof(HUD));
    if(hud == NULL) {
        logMessage(CRITICAL, "erreur malloc hud");
        exit(1);
    }
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

void renduHUD(WINDOW * win, HUD * hud, int minuteur) {
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
}

void freeEntreeTexte(EntreeTexte * entree) {
    free(entree->buffer);
    free(entree->affichage);
    free(entree);
}

void freeTexte(Texte * texte) {
    for(int i = 0; i < texte->nbLignes; i++) {
        free(texte->texte[i]);
    }
    free(texte->texte);
    free(texte);
}

