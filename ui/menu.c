#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "../logger.h"

Menu *cosmicMenu(int thauteur, int tlargeur) {
    /* Fonction servant à afficher le menu de cosmic yonder selon la largeur et hauteur
    du terminal.*/
    int titreLignes, titreX, titreY; // nombre de lignes et padding vertical du titre
    Menu *menu;
    Texte *titre;

    Bouton *commencer;
    Bouton *charger;
    Bouton *quitter;
    char **titreTexte = NULL;


    if (tlargeur >= ASCII_TAILLEMIN) {
        titreTexte = (char **) malloc(sizeof(char) * 8 * 131);
        titreLignes = 8;
        titreX = tlargeur / 2 - 65;
        titreY = thauteur / 2 - 10;
    } else {
        titreTexte = (char **) malloc(sizeof(char) * 2 * 54);
        titreLignes = 2;
        titreX = tlargeur / 2 - 11;
        titreY = thauteur / 2 - 2;
    }

    if (titreTexte == NULL) {
        exit(1);
    }

    //Si la largeur du terminal n'est pas assez grande : le texte COSMIC YONDER ne s'affiche pas en ASCII
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
        titreTexte[1] = "Active le plein-écran pour ne pas rencontrer de bugs!";
    }

    //Création éléments menu
    titre = creerTexte(titreX, titreY, titreTexte, titreLignes, 6);
    commencer = creerBouton(tlargeur / 2 - 2, thauteur / 2 + 2, 5, 2, "Nouvelle partie");
    charger = creerBouton(tlargeur / 2 - 2, thauteur / 2 + 4, 5, 2, "Charger sauvegarde");
    quitter = creerBouton(tlargeur / 2 - 2, thauteur / 2 + 6, 5, 2, "Quitter");

    //Création menu et assignation des éléments au menu
    menu = creerMenu(thauteur, tlargeur, titre, 3, 1, 6);
    menu->boutons[0] = commencer;
    menu->boutons[1] = charger;
    menu->boutons[2] = quitter;


    return menu;
}



Texte * respawnTexte(int x, int y, int largeur) {
    /* Fonction servant à créer le texte de réapparition quand le joueur meurt*/
    Texte * respawnTxt = NULL;
    respawnTxt = malloc(sizeof(Texte));
    if(respawnTxt == NULL) {
        logMessage(CRITICAL, "erreur malloc texte respawn");
        exit(1);
    }
    char **respawnTexte = NULL;
    if(largeur >= 82) {
        respawnTexte = malloc(sizeof(char*) * 8);
        if(respawnTexte == NULL) {
            logMessage(CRITICAL, "erreur malloc char** texte respawn");
            exit(1);
        }
        for(int i = 0; i < 8; i++) {
            respawnTexte[i] = NULL;
            respawnTexte[i] = malloc(sizeof(char) * 82);
            if(respawnTexte[i] == NULL) {
                logMessage(CRITICAL, "erreur malloc char* texte respawn");
                exit(1);
            }
        }
        respawnTexte[0] = " ________  _______   ________  ________  ________  ___       __   ________      ";
        respawnTexte[1] = R"(|\   __  \|\  ___ \ |\   ____\|\   __  \|\   __  \|\  \     |\  \|\   ___  \    )";
        respawnTexte[2] = R"(\ \  \|\  \ \   __/|\ \  \___|\ \  \|\  \ \  \|\  \ \  \    \ \  \ \  \\ \  \   )";
        respawnTexte[3] = R"( \ \   _  _\ \  \_|/_\ \_____  \ \   ____\ \   __  \ \  \  __\ \  \ \  \\ \  \  )";
        respawnTexte[4] = R"(  \ \  \\  \\ \  \_|\ \|____|\  \ \  \___|\ \  \ \  \ \  \|\__\_\  \ \  \\ \  \ )";
        respawnTexte[5] = R"(   \ \__\\ _\\ \_______\____\_\  \ \__\    \ \__\ \__\ \____________\ \__\\ \__\)";
        respawnTexte[6] = R"(    \|__|\|__|\|_______|\_________\|__|     \|__|\|__|\|____________|\|__| \|__|)";
        respawnTexte[7] = R"(                       \|_________|                                             )";
        respawnTxt = creerTexte(x, y, respawnTexte, 8, 4);
    } else {
        respawnTexte = malloc(sizeof(char*));
        if(respawnTexte == NULL) {
            logMessage(CRITICAL, "erreur malloc char** texte respawn");
            exit(1);
        }
        respawnTexte[0] = malloc(sizeof(char) * 8);
        if(respawnTexte[0] == NULL) {
            logMessage(CRITICAL, "erreur malloc char* texte respawn");
            exit(1);
        }
        respawnTexte[0] = "RESPAWN";
        respawnTxt = creerTexte(x, y, respawnTexte, 1, 4);

    }
    return respawnTxt;
}

void renderRespawn(WINDOW * win, Texte * respawn) {
    /* Rendu du texte de réapparition sur le terminal quand le joueur meurt*/
    wattron(win, COLOR_PAIR(5));

    mvwhline(win, respawn->y - 1, respawn->x - 1, ACS_HLINE, 82);
    mvwhline(win, respawn->y + 9, respawn->x - 1, ACS_HLINE, 82);
    mvwvline(win, respawn->y - 1, respawn->x - 1, ACS_VLINE, 9);
    mvwvline(win, respawn->y - 1, respawn->x + 81, ACS_VLINE, 9);
    mvwaddch(win, respawn->y - 1, respawn->x - 1, ACS_ULCORNER);
    mvwaddch(win, respawn->y - 1, respawn->x + 81, ACS_URCORNER);
    mvwaddch(win, respawn->y + 9, respawn->x - 1, ACS_LLCORNER);
    mvwaddch(win, respawn->y + 9, respawn->x + 81, ACS_LRCORNER);
    wattroff(win, COLOR_PAIR(5));

    renduTexte(win, *respawn);
}






MiniMenu *options(int x, int y, int hauteur, int largeur) {
    /* Fonction gérant le sous-menu des options dans le menu de début de partie*/
    //Initialisation
    MiniMenu *parametres;

    Bouton *quitter;
    Bouton *sauvegarder;

    Texte *titre;
    char **titreTexte = NULL;
    //Allocation mémoire
    titreTexte = (char **) malloc(sizeof(char) * 8);
    titreTexte[0] = "Options";

    titre = creerTexte(largeur/2 + x/2 - 4, hauteur/2, titreTexte, 1, 6);

    //Bouton du menu
    sauvegarder = creerBouton(x - 5, y + 2, 5, 2, "Sauvegarder");
    quitter = creerBouton(x - 3, y + 4, 5, 2, "Retour");

    parametres = creerMessage(largeur / 2, hauteur / 2, hauteur, largeur, 6, titre, 2, NULL);
    //Assignation des boutons au menu
    parametres->boutons[0] = sauvegarder;
    parametres->boutons[1] = quitter;

    return parametres;
}


MiniMenu *pauseMenu(int x, int y, int hauteur, int largeur) {
    /* Fonction créant le menu de pause */

    //Initialisation
    MiniMenu *pause;

    Bouton *retour;
    Bouton *quitter;
    Bouton *reprendre;
    Bouton *sauvegarder;

    Texte *titre;
    char **titreTexte = NULL;
    //Allocation
    titreTexte = (char **) malloc(sizeof(char) * 8);
    titreTexte[0] = "Pause";

    titre = creerTexte(largeur/2 + x/2 - 4, hauteur/2, titreTexte, 1, 6);
    //Boutons du menu
    reprendre = creerBouton(x - 5, y, 5, 2, "Reprendre");
    sauvegarder = creerBouton(x - 5, y + 2, 5, 2, "Sauvegarder");
    retour = creerBouton(x - 5, y + 4, 5, 2, "Retour au menu");
    quitter = creerBouton(x - 5, y + 6, 5, 2, "Quitter");


    pause = creerMessage(largeur / 2, hauteur / 2, hauteur, largeur, 6, titre, 4, NULL);
    //Assignation des boutons au menu
    pause->boutons[0] = reprendre;
    pause->boutons[1] = sauvegarder;
    pause->boutons[2] = retour;
    pause->boutons[3] = quitter;

    return pause;
}

InvMenu *initInvMenu(int x, int y, int hauteur, int largeur) {
    /* Fonction créant le menu de l'inventaire */

    //Initialisation
    InvMenu * invMenu1;

    Bouton ** col1;
    Bouton ** col2;
    col1 = malloc(sizeof(Bouton*) * 5);
    col2 = malloc(sizeof(Bouton*) * 5);
    if(col1 == NULL) {
        logMessage(CRITICAL, "erreur malloc col1 initInvMenu");
        exit(1);
    }
    if(col2 == NULL) {
        logMessage(CRITICAL, "erreur malloc col2 initInvMenu");
        exit(1);
    }

    for(int i = 0; i < 5; i++) {
        col1[i] = creerBouton(x - 11, y - 8 + i * 2, 5, 2, "Vide");
        col2[i] = creerBouton(x + 5, y - 8 + i * 2, 5, 2, "Vide");
    }
    col1[0]->couleur = 1;
    col2[0]->couleur = 1;
    col1[1]->couleur = 1;
    col2[1]->couleur = 1;


    Texte *titre;
    char **titreTexte = NULL;
    //Allocation
    titreTexte = (char **) malloc(sizeof(char) * 11);
    titreTexte[0] = "Inventaire";

    Texte *titreMsg;
    char **titreTexteMsg = NULL;
    //Allocation
    titreTexteMsg = (char **) malloc(sizeof(char) * 20);
    titreTexteMsg[0] = "Nom objet";

    titre = creerTexte(largeur/2 + x/2 - 4, hauteur/2, titreTexte, 1, 6);
    titreMsg = creerTexte(largeur/2 + x/2 - 3, hauteur/2 + hauteur/4, titreTexteMsg, 1, 6);


    //Boutons du menu


    invMenu1 = creerInvMenu(largeur / 2, hauteur / 2, hauteur, largeur, 6, titre, 2, 5);
    //Assignation des boutons au menu
    invMenu1->boutons[0] = col1;
    invMenu1->boutons[1] = col2;
    invMenu1->message = creerMessage(largeur / 2 + largeur/4, hauteur / 2 + hauteur/4, hauteur/2, largeur/2, 6, titreMsg, 3, NULL);
    invMenu1->message->boutons[0] = creerBouton(x - 4, y - 1, 5, 2, "Utiliser");
    invMenu1->message->boutons[1] = creerBouton(x - 4, y + 1, 5, 2, "Jeter");
    invMenu1->message->boutons[2] = creerBouton(x - 4, y + 3, 5, 2, "Retour");
    invMenu1->message->selEtat = 0;
    return invMenu1;
}

EntreeTexte * sauvegardeMenu(int x, int y, int hauteur, int largeur) {
    /* Menu de sauvegarde*/
    //Initialisation
    Texte * titre;
    EntreeTexte *sauv;
    char **titreTexte = NULL;
    //Allocation mémoire texte + contenu des textes
    titreTexte = (char **) malloc(sizeof(char) * 31);
    titreTexte[0] = "Entrez le nom de la sauvegarde";

    titre = creerTexte(largeur/2 + x - 20, y + hauteur/2 - 4, titreTexte, 1, 6);
    //Création de l'interface texte pour entrer la graine
    sauv = creerEntreeTexte(x - 10 + largeur/2, y + hauteur/2 + 2, 18, 4, titre);
    return sauv;

}

EntreeTexte * graineMenu(int x, int y, int hauteur, int largeur) {
    /* Fonction servant à créer le menu de la graine en fonction des dimensions du terminal*/
    //Initialisation
    Texte * titre;
    EntreeTexte *graine;
    char **titreTexte = NULL;
    //Allocation mémoire texte + contenu des textes
    titreTexte = (char **) malloc(sizeof(char) * (43 + 34));
    titreTexte[0] = "Entrez une graine (nombre entier)";
    titreTexte[1] = "Laisser vide pour la générer aléatoirement";

    titre = creerTexte(largeur/2 + x - 20, y + hauteur/2 - 4, titreTexte, 2, 6);
    //Création de l'interface texte pour entrer la graine
    graine = creerEntreeTexte(x - 10 + largeur/2, y + hauteur/2 + 2, 18, 4, titre);
    return graine;
}

EntreeTexte * nomMenu(int x, int y, int hauteur, int largeur) {
    /* Fonction servant à créer l'entrée du nom en fonction des dimensions du terminal*/
    //Initialisation
    Texte * titre;
    EntreeTexte *nom;
    char **titreTexte = NULL;
    //Allocation mémoire texte + contenu des textes
    titreTexte = (char **) malloc(sizeof(char) * 34);
    titreTexte[0] = "Spationaute #213";
    titreTexte[1] = "Entrez votre nom";

    titre = creerTexte(largeur/2 + x - 20, y + hauteur/2 - 4, titreTexte, 2, 6);
    //Création de l'interface texte pour entrer la graine
    nom = creerEntreeTexte(x - 10 + largeur/2, y + hauteur/2 + 2, 18, 4, titre);
    return nom;
}






void renduFenetreMenu(WINDOW *win, Menu menu, int thauteur, int tlargeur) {
    /* Rendu de la fenetre du menu en fonction de la taille du terminal*/
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
    /* Fonction gérant le rendu et l'affichage de la fenetre d'option en fonction de la taille du menu option*/
    //Création de la zone de menu
    for(int i = options.y; i < options.y + options.hauteur - 1; i++) {
        for(int j = options.x; j < options.x + options.largeur - 1; j++) {
            mvwaddch(win, i, j, ' ');
        }
    }

    wattron(win, COLOR_PAIR(7));
    //Remplissage de la zone du menu avec les textes et les boutons
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
    /* Sert au rendu de la fenetre d'entrée texte (comme pour créer la graine)*/
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
    /* Sert à gérer le sélecteur du menu en fonction des touches choisies
    (bouton vers le bas pour aller au bouton du bas et idem pour le haut)*/
    switch (touche) {
        case ERR:
            break;
        case KEY_UP:
            logMessage(INFO, "up");
            if (menu->selecteur != 0) {
                menu->selecteur--;
            }
            break;
        case KEY_DOWN:
            logMessage(INFO, "down");
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
    /* Fonction servant à savoir si une entrée est valide quand on l'execute*/
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
        case 27: // échap
            entree->quitter = 1;
            break;
        case 10: // entrée
            //L'entrée est valide
            entree->valide = 1;
            break;

        default:
            if((touche >= 'a' && touche <= 'z') || (touche >= 'A' && touche <= 'Z')) {
                if (entree->taille > entree->curseur+1) {
                    entree->buffer[entree->curseur] = (char) touche;
                    entree->affichage[entree->curseur] = (char) touche;
                    entree->buffer[entree->curseur+1] = '\0';
                    entree->curseur++;
                }
            }
            //Sinon il ne se passe rien
            break;
    }
}

void entreeNum(EntreeTexte *entree, int touche) {
    /* Fonction servant à savoir si une entrée est valide quand on l'execute*/
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
            //L'entrée est valide
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
            //Sinon il ne se passe rien
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
    /* Gère le sélecteur dans les mini-menus en fonction des touches et des boutons du menu*/
    switch (touche) {
        case ERR:
            break;
        case KEY_UP:
            //Si le menu a un bouton en haut par rapport au curseur on monte
            if (message->curseur != 0) { 
                message->curseur--;
            }
            break;
        case KEY_DOWN:
            //Si le menu a un bouton en bas par rapport au curseur on descend
            if (message->curseur != message->nbBoutons - 1) {
                message->curseur++;
            }
            break;
        case 10:
            //Sinon on ne bouge pas du bouton valide surlequel on est
            message->selEtat = 1;
            logMessage(INFO, "selEtat");
            break;
    }
}

void pauseBoucle(WINDOW *mainwin, int *touche, MiniMenu *pause, int *jeuEtat, int*partieEtat, int *sauveEtat) {
    /* Fonction qui fait une boucle infini tant qu'on a pas choisi une option
    pour arrêter le jeu quand on fait pause*/
    while (!pause->selEtat) { //Tant qu'on ne sélectionne rien le jeu est arrêté
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
        case 1: // sauvegarde
            *sauveEtat = 1;
            pause->selEtat = 0;
            pause->curseur = 0;
            break;

        case 2: // retour au menu
            pause->selEtat = 0;
            pause->curseur = 0;
            *partieEtat = 0;

            break;
        case 3: //quitter
            *jeuEtat = 0;
            *partieEtat = 0;
            break;
    }
}



void entreeInv(InvMenu *invMenu, int* touche) {
    /* Fonction gérant le sélecteur de l'inventaire en fonction des touches choisies
    (bouton vers le bas pour aller au bouton du bas et idem pour le haut)*/
    switch (*touche) {
        case ERR:
            break;
        case KEY_UP:
            if (invMenu->curseurLig != 0) {
                invMenu->curseurLig--;
            }
            break;
        case KEY_DOWN:
            if (invMenu->curseurLig != invMenu->nbBoutLig - 1) {
                invMenu->curseurLig++;
            }
            break;
        case KEY_LEFT:
            if (invMenu->curseurCol != 0) {
                invMenu->curseurCol--;
            }
            break;
        case KEY_RIGHT:
            if (invMenu->curseurCol != invMenu->nbBoutCol - 1) {
                invMenu->curseurCol++;
            }
            break;
        case 27:
            invMenu->selEtat = 1;
            invMenu->montrerMsg = 0;
            invMenu->curseurLig = 0;
            invMenu->curseurCol = 0;
            break;
        case 10:
            invMenu->montrerMsg = 1;
            invMenu->selEtat = 1;
            break;
        
    }
}

