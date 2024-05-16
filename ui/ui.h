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
}Message;

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
}Menu;

// PARTIE ABSTRAITE
void initCouleur(); //initialisation des couleurs ncurses
void renduTexte(WINDOW * win, Texte texte); //affichage du texte
void renduBouton(WINDOW * win, Bouton bouton, int sel); //affichage d'un bouton
void renduBoutons(WINDOW * win, Bouton ** boutons, int sel, int nbBoutons); //affichage de plusieurs boutons
void renduMessage(WINDOW * win, Message message, int selection); //affichage du message
void renduMenu(WINDOW * win, Menu menu); //affichage du menu
Menu * creerMenu(int hauteur, int largeur, Texte * titre, int nbBoutons, int espace, int couleurFond); //constructeur struct menu
Bouton * creerBouton(int x, int y, int couleur, int couleurSel, char * texte); // constructeur struct bouton
Message * creerMessage(int x, int y, int hauteur, int largeur, int couleur, Texte * titre, int nbBoutons, Texte * texte); // constructeur struct message
Texte * creerTexte(int x, int y, char ** texte, int nbLignes, int couleur); // constructeur struct texte

// PARTIE IMPLEMENTATION
Menu * cosmicMenu(int thauteur, int tlargeur); //ajout des attributs du menu
void renduFenetreMenu(WINDOW * win, Menu menu, int thauteur, int tlargeur); // rendu menu avec bordures
void entrees(Menu * menu, int touche); // gestion des touches

#endif