#include "CosmicYonder.h"
#include "logger.h"
#include "ui/ui.h"

Partie * creerPartie() {
	/* Fonction servant à créer la sauvegarde de la partie en allouant les différents
	éléments nécessaires pour la restaurer*/
	Partie * partie = NULL;
	partie = malloc(sizeof(Partie));
	if(partie == NULL) {
		logMessage(CRITICAL, "erreur malloc partie");
		exit(1);
	}
	partie->joueur = malloc(sizeof(Joueur));
	if(partie->joueur == NULL) {
		logMessage(CRITICAL, "erreur malloc joueur");
		exit(1);
	}
	partie->carte = malloc(MAX_SALLES * sizeof(Salle));
	if(partie->carte == NULL) {
		logMessage(CRITICAL, "erreur malloc carte");
		exit(1);
	}
	partie->salles_existantes = 0; 	//compteur de salles existantes
	partie->objets_speciaux_apparus = 0;  //Compteur des objets à récupérer pour gagner apparus
	partie->portesNonOuvertes = 0;//Compte les portes non ouvertes sur la carte
	partie->nb_obj_inv = 0;
	partie->nb_obj_spe_inv = 0;
	partie->mvEnnemic = 0;
	return partie;
}

int condition_victoire(Partie* partie){
	/*verifie si le joueur remplit la condition de victoire
	(qui est d'obtenir tous les objets speciaux)*/
	if(partie==NULL){
		exit(1);
	}
    int compteur = 0;
		for(int i = 0;i<partie->nb_obj_inv + partie->nb_obj_spe_inv;i++){
			if(partie->joueur->inventaire.obTab[i].id >= 11){
				compteur += 1;
			}
		}
		if(compteur == 4){
			return 0;
		}
        else{
            return 1;
        }
        
}

void chronos(int* minuteur,int*decr_minuteur){
/*decr_ minuteur ajuste le minuteur pour
qu'il retire bien 1 seconde par seconde en jeu en comptant les images par secondes*/
	if(minuteur==NULL){
		exit(2);
	}
	if(decr_minuteur==NULL){
		exit(3);
	}
	(*decr_minuteur)++;
	if((*decr_minuteur) >= IMAGES_PAR_SECONDE){
	    (*decr_minuteur) = 0;
		(*minuteur)--;
	}
}