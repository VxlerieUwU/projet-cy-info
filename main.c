#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int creation_graine(){
	/* L'utilisateur rentre un entier qui crée la graine qui sert à générer le donjon de manière procédurale. 
	Si le nombre est invalide plus de 3 fois de suite c'est à dire qu'il n'est pas un entier ou est trop 
 	grand, la graine est choisie aléatoirement.*/
	int graine;
	int verif_int; //Sert à vérifier que la graine est bien un entier.
	int compteur_tentatives = 0; //Compte le nombre de fois que le nombre de la graine est invalide.

	srand(time(NULL));
	do{
		printf("Entrez une graine pour générer le jeu.\n");
		verif_int = scanf("%d",&graine);
		compteur_tentatives++;
		//printf("n %d\n", compteur_tentatives);
	}while(graine<0 && verif_int != 1 && compteur_tentatives != 3);
	if(compteur_tentatives == 3){
		graine = rand();
	}
	return graine;
}


int main(){
	int graine;
	graine = creation_graine();
	srand(graine);
	
	return 0;
}
