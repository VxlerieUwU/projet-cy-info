//Bibliothèques
#include <wchar.h>
#include <linux/input-event-codes.h>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Constantes
#define GRAPHICS_H_
#define JOUEUR_H_
#define ESC 27
#define INV_SIZE 10 

//Structures
typedef struct {
    int x;
    int y;
}Porte;

typedef struct{
	int x;
	int y;
}Tuile;

typedef struct {
    int longueur;
    int hauteur;
    int x; //abscisse de l'origine de la salle
    int y; //ordonnée de l'origine de la salle
    int ** disp; //disposition de la salle en unicode (murs, objets, portes...)
    int decouvert = 0; //1 si oui 0 si non
    Porte * portes; //Portes de la salle
    int nportes; //Nombres de portes de la salle
}Salle;

typedef struct {
    char name[255];
    int x;
    int y;
    int count;
    int id;
}Item;

typedef struct{
	Item ItTab[INV_SIZE]; //l'inventaire est un tableau d'objets (a definir)
}Inventory;

typedef struct{
	int hp;
	int xp;
	int lvl;
	Inventory inventory;
	int x;
	int y;
}Joueur;

//Enumération des élements possibles de la salle
enum {
    MUR_SUPG,
    MUR_INFD,
    MUR_SUPD,
    MUR_INFG,
    MUR_HORIZ,
    MUR_VERTI,
    VOID,
    PORTE,
};

//Fonctions
Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes);
Salle * creerSalleProced(int x, int y);
void drawSalle(WINDOW * win, Salle * salle);
void freeSalle(Salle * salle);
void initJoueur(Joueur* joueur);
