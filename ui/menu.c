#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

Menu * cosmicMenu(int thauteur, int tlargeur) {
    int titreLignes, titreX, titreY; // nombre de lignes et padding vertical du titre
    Menu * menu;
    Texte * titre;

    Bouton * commencer;
    Bouton * charger;
    Bouton * parametres;
    Bouton * quitter;
    char ** titreTexte = NULL;

    if(tlargeur >= ASCII_TAILLEMIN) {
        titreTexte = (char **) malloc(sizeof(char) * 8 * 131);
        titreLignes = 8;
        titreX = tlargeur / 2 - 65;
        titreY = thauteur / 2 - 10;
    } else {
        titreTexte = (char **) malloc(sizeof(char) * 2 * 24);
        titreLignes = 2;
        titreX = tlargeur / 2 - 11;
        titreY = thauteur / 2 - 2;
    }

    if(titreTexte == NULL) {
        exit(1);
    }
    
    if(tlargeur >= ASCII_TAILLEMIN) {
        // Nécessite l'extension GNU du standard C (gnu11 ou gnu99)
        titreTexte[0] = "________  ________  ________  _____ ______   ___  ________           ___    ___ ________  ________   ________  _______   ________";
        titreTexte[1] = R"(|\   ____\|\   __  \|\   ____\|\   _ \  _   \|\  \|\   ____\         |\  \  /  /|\   __  \|\   ___  \|\   ___ \|\  ___ \ |\   __  \)";
        titreTexte[2] = R"(\ \  \___|\ \  \|\  \ \  \___|\ \  \\\__\ \  \ \  \ \  \___|         \ \  \/  / | \  \|\  \ \  \\ \  \ \  \_|\ \ \   __/|\ \  \|\  \   )";
        titreTexte[3] = R"( \ \  \    \ \  \\\  \ \_____  \ \  \\|__| \  \ \  \ \  \             \ \    / / \ \  \\\  \ \  \\ \  \ \  \ \\ \ \  \_|/_\ \   _  _\  )";
        titreTexte[4] = R"(  \ \  \____\ \  \\\  \|____|\  \ \  \    \ \  \ \  \ \  \____         \/  /  /   \ \  \\\  \ \  \\ \  \ \  \_\\ \ \  \_|\ \ \  \\  \| )";
        titreTexte[5] = R"(   \ \_______\ \_______\____\_\  \ \__\    \ \__\ \__\ \_______\     __/  / /      \ \_______\ \__\\ \__\ \_______\ \_______\ \__\\ _\ )";
        titreTexte[6] = R"(    \|_______|\|_______|\_________\|__|     \|__|\|__|\|_______|    |\___/ /        \|_______|\|__| \|__|\|_______|\|_______|\|__|\|__|)";
        titreTexte[7] = R"(                       \|_________|                                 \|___|/)";
    } else {
        titreTexte[0] = "Cosmic Yonder";
        titreTexte[1] = "Agrandis ton terminal!";
    }



    titre = creerTexte(titreX, titreY, titreTexte, titreLignes, 6);
    commencer = creerBouton(tlargeur / 2 - 2, thauteur / 2 + 2, 5, 2, "Nouvelle partie");
    charger = creerBouton(tlargeur / 2 - 2, thauteur / 2 + 4, 5, 2, "Charger sauvegarde");
    parametres = creerBouton(tlargeur / 2 - 2, thauteur / 2 + 6, 5, 2, "Options");
    quitter = creerBouton(tlargeur / 2 - 2, thauteur / 2 + 8, 5, 2, "Quitter");

    

    menu = creerMenu(thauteur, tlargeur, titre, 4, 1, 6);
    menu->boutons[0] = commencer;
    menu->boutons[1] = charger;
    menu->boutons[2] = parametres;
    menu->boutons[3] = quitter;


    return menu;
}

void renduFenetreMenu(WINDOW * win, Menu menu, int thauteur, int tlargeur) {
    wattron(win, COLOR_PAIR(5));
    
    mvwhline(win, 0, 0, ACS_HLINE, tlargeur);
    mvwhline(win, thauteur - 1, 0, ACS_HLINE, tlargeur);
    mvwvline(win, 0, 0, ACS_VLINE, thauteur);
    mvwvline(win, 0, tlargeur - 1, ACS_VLINE, thauteur);
    mvwaddch(win, 0, 0, ACS_ULCORNER);
    mvwaddch(win, 0 ,tlargeur - 1, ACS_URCORNER);
    mvwaddch(win, thauteur - 1, 0, ACS_LLCORNER);
    mvwaddch(win, thauteur - 1, tlargeur - 1, ACS_LRCORNER);
    wattroff(win, COLOR_PAIR(5));


    renduMenu(win, menu);
}

void entrees(Menu * menu, int touche) {
    switch(touche) {
        case KEY_UP:
            if(menu->selecteur != 0) {
                menu->selecteur--;
            }
            break;
        case KEY_DOWN:
            if(menu->selecteur != menu->nbBoutons - 1) {
                menu->selecteur++;
            }
            break;
        case 10:
            menu->selEtat = 1;
            break;
    }
}