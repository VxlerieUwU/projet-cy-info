#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

Menu *cosmicMenu(int thauteur, int tlargeur) {
    int titreLignes, titreX, titreY; // nombre de lignes et padding vertical du titre
    Menu *menu;
    Texte *titre;

    Bouton *commencer;
    Bouton *charger;
    Bouton *parametres;
    Bouton *quitter;
    char **titreTexte = NULL;

    if (tlargeur >= ASCII_TAILLEMIN) {
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

    if (titreTexte == NULL) {
        exit(1);
    }

    if (tlargeur >= ASCII_TAILLEMIN) {
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

MiniMenu *options(int x, int y, int hauteur, int largeur) {
    MiniMenu *parametres;

    Bouton *quitter;
    Bouton *sauvegarder;

    Texte *titre;
    char **titreTexte = NULL;
    titreTexte = (char **) malloc(sizeof(char) * 8);
    titreTexte[0] = "Options";

    titre = creerTexte(largeur/2 + x/2 - 4, hauteur/2, titreTexte, 1, 6);

    sauvegarder = creerBouton(x - 5, y + 2, 5, 2, "Sauvegarder");
    quitter = creerBouton(x - 3, y + 4, 5, 2, "Retour");

    parametres = creerMessage(largeur / 2, hauteur / 2, hauteur, largeur, 6, titre, 2, NULL);

    parametres->boutons[0] = sauvegarder;
    parametres->boutons[1] = quitter;

    return parametres;
}


MiniMenu *pauseMenu(int x, int y, int hauteur, int largeur) {
    MiniMenu *pause;

    Bouton *retour;
    Bouton *quitter;
    Bouton *reprendre;

    Texte *titre;
    char **titreTexte = NULL;
    titreTexte = (char **) malloc(sizeof(char) * 8);
    titreTexte[0] = "Pause";

    titre = creerTexte(largeur/2 + x/2 - 4, hauteur/2, titreTexte, 1, 6);

    reprendre = creerBouton(x - 5, y + 2, 5, 2, "Reprendre");
    retour = creerBouton(x - 3, y + 4, 5, 2, "Retour au menu");
    quitter = creerBouton(x - 3, y + 6, 5, 2, "Quitter");

    pause = creerMessage(largeur / 2, hauteur / 2, hauteur, largeur, 6, titre, 3, NULL);

    pause->boutons[0] = reprendre;
    pause->boutons[1] = retour;
    pause->boutons[2] = quitter;

    return pause;
}

MiniMenu * sauvegardeMenu(int x, int y, int hauteur, int largeur) {

}

EntreeTexte * graineMenu(int x, int y, int hauteur, int largeur) {
    Texte * titre;
    EntreeTexte *graine;
    char **titreTexte = NULL;
    titreTexte = (char **) malloc(sizeof(char) * (43 + 34));
    titreTexte[0] = "Entrez une graine (nombre entier)";
    titreTexte[1] = "Laisser vide pour la générer aléatoirement";

    titre = creerTexte(largeur/2 + x - 20, y + hauteur/2 - 4, titreTexte, 2, 6);

    graine = creerEntreeTexte(x - 10 + largeur/2, y + hauteur/2 + 2, 18, 4, titre);
    return graine;
}

EntreeTexte * sauvegardeEntree(int x, int y, int hauteur, int largeur) {
    Texte * titre;
    EntreeTexte *sauvegarde;
    char **titreTexte = NULL;
    titreTexte = (char **) malloc(sizeof(char) * (43 + 34));
    titreTexte[0] = "Nom de la sauvegarde";
    titreTexte[1] = "";

    titre = creerTexte(largeur/2 + x - 20, y + hauteur/2 - 4, titreTexte, 2, 6);

    sauvegarde = creerEntreeTexte(x - 10 + largeur/2, y + hauteur/2 + 2, 18, 4, titre);
    return sauvegarde;
}



void renduFenetreMenu(WINDOW *win, Menu menu, int thauteur, int tlargeur) {
    wattron(win, COLOR_PAIR(5));

    mvwhline(win, 0, 0, ACS_HLINE, tlargeur);
    mvwhline(win, thauteur - 1, 0, ACS_HLINE, tlargeur);
    mvwvline(win, 0, 0, ACS_VLINE, thauteur);
    mvwvline(win, 0, tlargeur - 1, ACS_VLINE, thauteur);
    mvwaddch(win, 0, 0, ACS_ULCORNER);
    mvwaddch(win, 0, tlargeur - 1, ACS_URCORNER);
    mvwaddch(win, thauteur - 1, 0, ACS_LLCORNER);
    mvwaddch(win, thauteur - 1, tlargeur - 1, ACS_LRCORNER);
    wattroff(win, COLOR_PAIR(5));


    renduMenu(win, menu);
}

void renduFenetreOptions(WINDOW *win, MiniMenu options) {
    for(int i = options.y; i < options.y + options.hauteur - 1; i++) {
        for(int j = options.x; j < options.x + options.largeur - 1; j++) {
            mvwaddch(win, i, j, ' ');
        }
    }

    wattron(win, COLOR_PAIR(7));

    mvwhline(win, options.y, options.x, ACS_HLINE, options.largeur);
    mvwhline(win, options.y + options.hauteur - 1, options.x, ACS_HLINE, options.largeur);
    mvwvline(win, options.y, options.x, ACS_VLINE, options.hauteur);
    mvwvline(win, options.y, options.x + options.largeur - 1, ACS_VLINE, options.hauteur);
    mvwaddch(win, options.y, options.x, ACS_ULCORNER);
    mvwaddch(win, options.y, options.x + options.largeur - 1, ACS_URCORNER);
    mvwaddch(win, options.y + options.hauteur - 1, options.x, ACS_LLCORNER);
    mvwaddch(win, options.y + options.hauteur - 1, options.x + options.largeur - 1, ACS_LRCORNER);
    wattroff(win, COLOR_PAIR(7));



    renduMessage(win, options);

}

void renduFenetreEntree(WINDOW *win, EntreeTexte * entree, int x, int y, int hauteur, int largeur) {
    for(int i = y; i < y + largeur; i++) {
        for(int j = x; j < x + hauteur - 1; j++) {
            mvwaddch(win, i, j, ' ');
        }
    }

    wattron(win, COLOR_PAIR(7));

    mvwhline(win, y, x, ACS_HLINE, largeur);
    mvwhline(win, y + hauteur - 1, x, ACS_HLINE, largeur);
    mvwvline(win, y, x, ACS_VLINE, hauteur);
    mvwvline(win, y, x + largeur - 1, ACS_VLINE, hauteur);
    mvwaddch(win, y, x, ACS_ULCORNER);
    mvwaddch(win, y, x + largeur - 1, ACS_URCORNER);
    mvwaddch(win, y + hauteur - 1, x, ACS_LLCORNER);
    mvwaddch(win, y + hauteur - 1, x + largeur - 1, ACS_LRCORNER);

    wattroff(win, COLOR_PAIR(7));

    renduEntreeTexte(win, entree);
}

void entreeMenu(Menu *menu, int touche) {
    switch (touche) {
        case KEY_UP:
            if (menu->selecteur != 0) {
                menu->selecteur--;
            }
            break;
        case KEY_DOWN:
            if (menu->selecteur != menu->nbBoutons - 1) {
                menu->selecteur++;
            }
            break;
        case 10:
            menu->selEtat = 1;
            break;
    }
}

void entreeTexte(EntreeTexte *entree, int touche) {
    switch (touche) {
        case ERR:
            break;
        case KEY_BACKSPACE:
            if(strlen(entree->buffer) > 0) {
                entree->buffer[entree->curseur - 1] = '\0';
                entree->affichage[entree->curseur - 1] = '_';
                entree->curseur--;
            }
            break;

        case 10:
            entree->valide = 1;
            break;
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (entree->taille > entree->curseur+1) {
                entree->buffer[entree->curseur] = (char) touche;
                entree->affichage[entree->curseur] = (char) touche;
                entree->buffer[entree->curseur+1] = '\0';
                entree->curseur++;
            }
            break;
        default:
            break;
    }
}

void entreeMessage(MiniMenu *message, int touche) {
    switch (touche) {
        case ERR:
            break;
        case KEY_UP:
            if (message->curseur != 0) {
                message->curseur--;
            }
            break;
        case KEY_DOWN:
            if (message->curseur != message->nbBoutons - 1) {
                message->curseur++;
            }
            break;
        case 10:
            message->selEtat = 1;
            break;
    }
}

void pauseBoucle(WINDOW *mainwin, int *touche, MiniMenu *pause, int *jeuEtat) {
    while (!pause->selEtat) {
        wrefresh(mainwin);
        *touche = wgetch(mainwin);
        renduFenetreOptions(mainwin, *pause);
        entreeMessage(pause, *touche);
    }
    switch (pause->curseur) {
        case 0: //continuer
            pause->selEtat = 0;
            pause->curseur = 0;
            break;
        case 1: // BROKEN
            pause->selEtat = 0;
            pause->curseur = 0;

            break;
        case 2: //quitter
            *jeuEtat = 0;
            break;
    }
}