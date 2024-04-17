#define INV_SIZE 10 //taille de l'inventaire

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
}Stats;