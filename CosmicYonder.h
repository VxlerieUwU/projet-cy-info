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
#define BOUTEILLE_O2_CHR "O"
#define BANDAGE_CHR "B"
#define CLE_CHR "C"
#define GENERATEUR_CHR "G"
#define REACTEUR_CHR "R"
#define PC_CHR "P"

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
#define IMAGES_PAR_SECONDE 60
#define MINUTEUR 300

//Enumération des différents objets

/* Les valeurs des Id des objets sont initialisés avec un décalage de 8 pour ne pas faire doublon
avec les valeurs des éléments possibles de la salle ce qui causerait des 
problèmes lors de l'affichage de la salle*/
typedef enum{
    BOUTEILLE_O2 = 8, //Objet commun
    BANDAGE = 9, //Objet commun
    CLE = 10, //Objet commun
    GENERATEUR = 11, //Objet à récupérer pour gagner
    REACTEUR_1 = 12, // Objet à récupérer pour gagner
    REACTEUR_2 = 13, // Objet à récupérer pour gagner
    PC = 14, // Objet à récupérer pour gagner
    VIDE_OBJ = 100,
}Id;

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

//Structures

typedef struct {
    int x;
    int y;
    Id id;
}Objet;

typedef struct{
	Objet obTab[INV_TAILLE]; //l'inventaire est un tableau d'objets
}Inventaire;

typedef struct{
    char * nom;
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

typedef struct {
    int longueur;
    int hauteur;
    int x; //abscisse de l'origine de la salle
    int y; //ordonnée de l'origine de la salle
    int ** disp; //disposition de la salle en unicode (murs, objets, portes...)
    int decouvert; //1 si oui 0 si non
    Porte * portes; //Portes de la salle
    int nportes; //Nombres de portes de la salle
    Objet objets[3];
    Ennemi* ennemi;
    int ennemi_existant;
}Salle;


typedef struct {
    Joueur * joueur;
    int graine;
    int portesNonOuvertes;
    int mvEnnemic;
    int objets_speciaux_apparus;
    int salles_existantes;
    int nb_obj_inv;
    int nb_obj_spe_inv;
    Salle ** carte;
}Partie;

//Fonctions

    //GRAINE
int creation_graine(EntreeTexte * graineEntree); //Crée la graine de génération du jeu.

    //SALLES
//Cette fonction permet de creer une salle a partir de dimensions fixees a l'aide de creerSalleProced
Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes, 
int entree, int posEntree, WINDOW* win, int* sallesrest, int* objets_speciaux_apparus,int portesNonOuvertes);
//permet de creer des dimensions aleatoires pour generer une salle
Salle * creerSalleProced(int x, int y, int nportes, int dir, WINDOW* win, 
int* sallesrest, int* objets_speciaux_apparus, int portesNonOuvertes);
//permet d'afficher toutes les salles
void dessineSalles(WINDOW * win, Salle ** salle, int salles_existantes);
//affiche une salle passee en parametre
void dessineSalle(WINDOW * win, Salle * salle);
//libere l'emplacement memoire de la salle
void libereSalle(Salle * salle);
//enleve le marquage afin de ne pas gener la creation de salle
void enleve_marquage(int entree, int x, int y, int taille_horizontale, int taille_verticale, int posEntree, WINDOW* win);
//empeche les superpositions lors de la creation de salle
void verif_superposition(int entree, int* posEntree, int* x, int* y, int* taille_horizontale, int* taille_verticale, WINDOW* win);

    //PORTES
//fonction constructeur de la porte
Porte initPorte(int dir,int v,int h);
// Ouverture de porte
void ouvrirPorte(Salle ** carte, int indexSalleAct,int indexNouvSalle, int indexPorte, int dir);
//Compte les portes non ouvertes
int compteurPortesNonOuvertes(Salle ** carte, int salles_existantes); 
//cree les portes d'une salle
void creationPortes(Salle* salle, int entree, int* sallesrest);
//verifie qu'une salle puisse se cree derriere une porte
void verifPorte(Salle* salle,int i, WINDOW* win);

    //JOUEUR
//initialise la structure joueur
void initJoueur(Joueur* joueur);
//cette fonction gere les interactions du joueur avec le jeu, comme les mouvements ou les combats
void interactions(int touche, Joueur* joueur, Salle ** carte, int salles_existantes, WINDOW* mainwin, int* nb_obj_inv, int* nb_obj_spe_inv); 
//Gère mise à jour du niveau du joueur en fonction de son expérience
void maj_niveau(Joueur* joueur); 
//Gère la perte de vie du joueur
void perte_vie_joueur(Joueur* joueur, Ennemi* ennemi); 
//fait reapparaitre le joueur en cas de mort
void reapparition_joueur(Joueur* joueur, Salle** carte, int salles_existantes); 

    //ENNEMIS
//initialise un ennemi à l'aide d'attributs passés en paramètre
Ennemi initEnnemi(int x, int y, int pv, int att, int def);
//calcule la position globale de l'ennemi
void ennemietat(Ennemi* ennemi,Salle* salle,Joueur* joueur, WINDOW* mainwin);
//gere les mouvements de l'ennemi
void ennemimv(Ennemi* ennemi,Salle* salle,Joueur* joueur, WINDOW* mainwin);
//affiche un ennemi
void afficheEnnemi(Ennemi* ennemi, WINDOW* mainwin);
//spawn ennemi
Ennemi* apparition_ennemi(Salle* salle);
//fait despawn l'ennemi quand il meurt
void disparition_ennemi(Ennemi* ennemi, Salle* salle,Joueur* joueur, WINDOW* win); 
//gere la perte de vie de l'ennemi
void perte_vie_ennemi(Ennemi* ennemi, Joueur* joueur); 

    //OBJETS
//Crée et fait apparaitre un objet dans une salle en fonction des objets spéciaux apparus,des salles restantes et des portes non ouvertes
Objet apparition_objet(Salle* salle, int* objets_speciaux_apparus, int sallesrest, int portesNonOuvertes);
//permet de recuperer un objet
void recup_objet(Joueur* joueur, Salle* salle, Objet objet, int* nb_obj_inv, int* nb_obj_spe_inv);
//fait disparaitre un objet quand le joueur le ramasse
void utiliser_objet(Joueur* joueur, Objet objet, int* minuteur);

    //HUD
//Fait apparaitre l'interface graphique pour les informations du joueur et de la partie
HUD * hudJeu(int x, int y, int hauteur, int largeur, Joueur * joueur,int minuteur);
void renduHUD(WINDOW * win, HUD * hud, int minuteur, Joueur * jou, int nb_obj_inv, int nb_obj_spe_inv); //affichage de la hud
void renduInvMenu(WINDOW * win, InvMenu * invMenu, Inventaire inventaire);
void renderInventaire(WINDOW * win, int y, int x, Inventaire inventaire, int nb_obj_inv, int nb_obj_spe_inv);
void invBoucle(WINDOW *mainwin, int *touche, InvMenu *invMenu, Inventaire inventaire, int* minuteur, Joueur* joueur) 

    // SAUVEGARDE
void saveGame(Partie * partie);

Partie * loadGame();
    
    //JEU
Partie * creerPartie();
int condition_victoire(Partie* partie);
void chronos(int* minuteur,int*decr_minuteur);
#endif