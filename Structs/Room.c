typedef struct{
	int xO; //abscisse de l'origine
	int yO; // ordonnée de l'origine
	int length;
	int height;
	int discovered;
	Door doors[4];
}Room;