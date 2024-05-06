#ifndef JOUEUR_H_   /* Include guard */
#define JOUEUR_H_

#define INV_SIZE 10 

typedef struct {
    char name[255];
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

void initJoueur(Joueur* joueur);

#endif