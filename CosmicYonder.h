//Bibliothèques
#include <linux/input-event-codes.h>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

//Constantes
#define GRAPHIQUES_H_
#define ESC 27
#define INV_TAILLE 10 
#define JOUEUR_H_
#define MUR_VERTI_CHR "\u2550"
#define MUR_HORIZ_CHR "\u2551"
#define MUR_SUPG_CHR "\u2557"
#define MUR_SUPD_CHR "\u2554"
#define MUR_INFG_CHR "\u255D"
#define MUR_INFD_CHR "\u255A"
#define PORTE_CHR "\u25A2"
#define UNICODE_STRING_LONG 10
#define TAILLE_MAX_V 10
#define TAILLE_MAX_H 20

//Structures

typedef struct {
    char nom[255];
    int x;
    int y;
    int compteur;
    int id;
}Objet;

typedef struct{
	Objet obTab[INV_TAILLE]; //l'inventaire est un tableau d'objets (a definir)
}Inventaire;

typedef struct{
	int pv;
	int xp;
	int niv;
	Inventaire inventaire;
	int x;
	int y;
}Joueur;


typedef struct {
    int x;
    int y;
}Porte;

typedef struct {
    int longueur;
    int hauteur;
    int x; //abscisse de l'origine de la salle
    int y; //ordonnée de l'origine de la salle
    int ** disp; //disposition de la salle en unicode (murs, objets, portes...)
    int decouvert; //1 si oui 0 si non
    Porte * portes; //Portes de la salle
    int nportes; //Nombres de portes de la salle
}Salle;

typedef struct{
	int x;
	int y;
}Tuile;

//Enumération des élements possibles de la salle
enum {
    MUR_SUPG,
    MUR_INFD,
    MUR_SUPD,
    MUR_INFG,
    MUR_HORIZ,
    MUR_VERTI,
    VIDE,
    PORTE,
};

//Fonctions
Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes);
Salle * creerSalleProced(int x, int y, int dir);
void dessineSalle(WINDOW * win, Salle * salle);
void libereSalle(Salle * salle);
void initJoueur(Joueur* joueur);
void interactions(int touche, Joueur* joueur, WINDOW* mainwin, char* logBuffer, Salle* salle);
