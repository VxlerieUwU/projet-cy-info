#ifndef UI_H_
#define UI_H_

#include <ncurses.h>

#define ASCII_TAILLEMIN 142 // taille minimale pour afficher le titre en ascii art

enum { // TODO: à utiliser
    ACTION_NOUVELLE_PARTIE,
    ACTION_CHARGER_SAUVEGARDE,
    ACTION_SAUVEGARDER,
    ACTION_PARAMETRES,
    ACTION_QUITTER,
};

typedef struct {
    int x;
    int y;
    char ** texte;
    int nbLignes;
    int couleur;
}Texte;

typedef struct {
    int x;
    int y;
    char * texte;
    int couleur;
}MiniTexte;

typedef struct {
    int x;
    int y;
    int hauteur;
    int largeur;
    int couleur;
    int couleurSel;
    char * texte;
}Bouton;

typedef struct {
    int x;
    int y;
    int hauteur;
    int largeur;
    int couleur;
    Texte * titre;
    int nbBoutons;
    Texte * message;
    Bouton ** boutons;
    int curseur;
    int selEtat;
}MiniMenu;

typedef struct {
    int x;
    int y;
    int hauteur;
    int largeur;
    int couleur;
    Texte * titre;
    int nbBoutCol;
    int nbBoutLig;
    Bouton *** boutons;
    int curseurCol;
    int curseurLig;
    short curseurObj;
    int montrerMsg;
    int selEtat;
    int selRetour;
    MiniMenu * message;
}InvMenu;

typedef struct {
    int hauteur;
    int largeur;
    Texte *titre;
    Bouton ** boutons;
    int nbBoutons; 
    int selecteur; // bouton seléctionné
    int selEtat; // 0 = pas choisi, 1 = choisi
    int espace; // TODO: pas utilisé, espace entre les boutons
    int couleurFond;
    int focus; // stoppe le rendu du menu si fenetre ouverte
}Menu;

typedef struct {
    int x;
    int y;
    char * buffer;
    char * affichage;
    int taille;
    int valide;
    int couleur;
    int curseur;
    Texte * titre;
    int quitter;
}EntreeTexte;

typedef struct {
    int x;
    int y;
    int size;
    int color;
    int cursor;
}StatusBar;

typedef struct {
    int x;
    int y;
    int hauteur;
    int largeur;
    int outlineColor;
    Texte ** textWidgets;
    int nbText;
    StatusBar ** statBarWidgets;
    int nbStatBar;
}HUD;



// PARTIE ABSTRAITE
void initCouleur(); //initialisation des couleurs ncurses
void renduTexte(WINDOW * win, Texte texte); //affichage du texte
void renduBouton(WINDOW * win, Bouton bouton, int sel); //affichage d'un bouton
void renduBoutons(WINDOW * win, Bouton ** boutons, int sel, int nbBoutons); //affichage de plusieurs boutons
void renduMessage(WINDOW * win, MiniMenu message); //affichage du message
void renduEntreeTexte(WINDOW * win, EntreeTexte * entree); //affichage de l'entree texte
void renduMenu(WINDOW * win, Menu menu); //affichage du menu
void renduStatusBar(WINDOW * win, StatusBar * sb); //affichage de la barre de statut
Menu * creerMenu(int hauteur, int largeur, Texte * titre, int nbBoutons, int espace, int couleurFond); //constructeur struct menu
Bouton * creerBouton(int x, int y, int couleur, int couleurSel, char * texte); // constructeur struct bouton
MiniMenu * creerMessage(int x, int y, int hauteur, int largeur, int couleur, Texte * titre, int nbBoutons, Texte * texte); // constructeur struct message
Texte * creerTexte(int x, int y, char ** texte, int nbLignes, int couleur); // constructeur struct texte
EntreeTexte * creerEntreeTexte(int x, int y, int taille, int couleur, Texte * titre); //Crée les entrées textes dans le menu (lorsqu'on a besoin de choisir une graine par exemple)
StatusBar * creerStatusBar(int x, int y, int size, int color, int cursor); //Crée les barres (de vie, d'xp) de la hud
HUD * creerHUD(int x, int y, int hauteur, int largeur, int outlineColor, int nbText, int nbStatBar); //crée la HUD
InvMenu * creerInvMenu(int x, int y, int hauteur, int largeur, int couleur, Texte * titre, int nbBoutCol, int nbBoutLig); //Crée le menu de l'inventaire

void freeMenu(Menu * menu); //liberation de la memoire allouée pour le menu

void renderRespawn(WINDOW * win, Texte * respawn);

// PARTIE IMPLEMENTATION
Menu * cosmicMenu(int thauteur, int tlargeur); //ajout des attributs du menu
void renduFenetreMenu(WINDOW * win, Menu menu, int thauteur, int tlargeur); // rendu menu avec bordures
void renduFenetreEntree(WINDOW *win, EntreeTexte * entree, int x, int y, int hauteur, int largeur);
void renduFenetreOptions(WINDOW *win, MiniMenu options); // rendu message avec bordures
void renderRespawn(WINDOW * win, Texte * respawn);
void entreeMenu(Menu *menu, int touche); // gestion des touches du menu
void entreeMessage(MiniMenu *message, int touche);
void entreeTexte(EntreeTexte *entree, int touche); 
void entreeNum(EntreeTexte *entree, int touche); 
void entreeInv(InvMenu *invMenu, int* touche);  //Fonction servant à naviguer dans l'inventaire
EntreeTexte * graineMenu(int x, int y, int hauteur, int largeur); //Menu d'entrée de la graine
EntreeTexte * nomMenu(int x, int y, int hauteur, int largeur); //Menu pour tapper le nom du joueur
EntreeTexte * sauvegardeMenu(int x, int y, int hauteur, int largeur); //Menu des sauvegarde
MiniMenu * options(int x, int y, int hauteur, int largeur); //Sous-menu des options
MiniMenu *pauseMenu(int x, int y, int hauteur, int largeur); //Menu de pause
Texte * respawnTexte(int x, int y, int largeur); //Texte lors de la réapparition
InvMenu *initInvMenu(int x, int y, int hauteur, int largeur); //Initialisation du menu de l'inventaire
void pauseBoucle(WINDOW *mainwin, int *touche, MiniMenu *pause, int *jeuEtat, int *partieEtat, int *sauveEtat); //Boucle d'arrêt du jeu pendant le menu pause
// free
void freeEntreeTexte(EntreeTexte * entree); //Libère les espaces d'entrée de texte du terminal
void freeTexte(Texte * texte); //Libère le texte du terminal
void freeHUD(HUD * hud); //Libère la HUD

#endif