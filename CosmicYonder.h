//Bibliothèques
#include <linux/input-event-codes.h>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "ui/ui.h"
//Constantes
#ifndef COSMICYONDER_H_
#define COSMICYONDER_H_
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
#define MARQUAGE_CHR "\u2800"
#define UNICODE_STRING_LONG 10
#define TAILLE_MAX_V 10
#define TAILLE_MAX_H 20
#define MAX_SALLES 10
#define FRAMES_PER_SECOND 60

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
	int att;
	int def;
	Inventaire inventaire;
	int x;
	int y;
}Joueur;


typedef struct {
    int x;
    int y;
    int ouvert;
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

typedef struct{
    int pv;
    //position globale de l'ennemi
    int xGlobal;
    int yGlobal;
    //position relative de l'ennemi par rapport a l'origine de la salle ou il se trouve
    int xRelatif;
    int yRelatif;
    int att;
    int def;
}Ennemi;

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

//Enumération des directions
enum{
    DROITE,
    BAS,
    GAUCHE,
    HAUT
};

//Fonctions

//Cette fonction permet de creer une salle a partir de dimensions fixees a l'aide de creerSalleProced
Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes, int entree, int posEntree, WINDOW* win, int* sallerest);
//permet de creer des dimensions aleatoires pour generer une salle
Salle * creerSalleProced(int x, int y, int nportes, int dir, WINDOW* win, int* sallerest);
//permet d'afficher toutes les salles
void dessineSalles(WINDOW * win, Salle ** salle, int salles_existantes);
//affiche une salle passee en parametre
void dessineSalle(WINDOW * win, Salle * salle);
//libere l'emplacement memoire de la salle
void libereSalle(Salle * salle);
//fonction constructeur de la porte
Porte initPorte(int dir,int v,int h);
// Ouverture de porte
void ouvrirPorte(Salle ** carte, int indexSalleAct,int indexNouvSalle, int indexPorte, int dir);
//initialise la structure joueur
void initJoueur(Joueur* joueur);
//cette fonction gere les interactions du joueur avec le jeu, comme les mouvements ou les combats
void interactions(int touche, Joueur* joueur, Salle ** carte, int salles_existantes, WINDOW* mainwin); 
//initialise un ennemi à l'aide d'attributs passés en paramètre
Ennemi initEnnemi(int x, int y, int pv, int att, int def);
//gere les mouvements de l'ennemi
void ennemimv(Ennemi* ennemi,Salle* salle,Joueur* joueur, WINDOW* mainwin);
//affiche un ennemi
void afficheEnnemi(Ennemi* ennemi, WINDOW* mainwin);

int creation_graine(EntreeTexte * graineEntree); //Crée la graine de génération du jeu.

int maj_niveau(Joueur* joueur); //Gère mise à jour du niveau du joueur en fonction de son expérience
int perte_vie(Joueur* joueur, Ennemi* ennemi); //Gère la perte de vie du joueur

#endif