#include "CosmicYonder.h"

int creation_graine(){
	/* L'utilisateur rentre un entier qui crée la graine qui sert à générer le donjon de manière procédurale. 
	Si le nombre est invalide plus de 3 fois de suite c'est à dire qu'il n'est pas un entier ou est trop 
 	grand, la graine est choisie aléatoirement.*/
  
	int graine = -1;
	int verif_int = 0; //Sert à vérifier que la graine est bien un entier.
	int compteur_tentatives = 0; //Compte le nombre de fois que le nombre de la graine est invalide.
	srand(time(NULL));
	
	do{
		printf("Entrez une graine pour générer le jeu.\n");
		verif_int = scanf("%d",&graine);
		while(getchar()!='\n'){}
		compteur_tentatives++;
	}while(graine<0 || (verif_int != 1 && compteur_tentatives>=3));
	if(compteur_tentatives == 3){
		graine = rand();
	}
	return graine;
}
