#include "CosmicYonder.h"
#include "ui/ui.h"

int creation_graine(EntreeTexte * graineEntree){
	/* L'utilisateur rentre un entier qui crée la graine qui sert à générer le donjon de manière procédurale. 
 	Si l'entrée est incorrecte ou nulle, la graine est choisie aléatoirement.*/
  
	int graine = -1; //Initialisation graine
	int verif_int = 0; //Sert à vérifier que la graine est bien un entier.
	srand(time(NULL));

    verif_int = sscanf(graineEntree->buffer, "%d",&graine);
	if(verif_int != 1){
		graine = rand();
	}
	return graine;
}
