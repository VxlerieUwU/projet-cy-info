#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#define TAILLE_MAX 10


void generateur_salle(){
    int taille_min_verticale, taille_min_horizontale;
    srand(time(NULL)); //Initialisation du random/#include <stdio.h>
    setlocale(LC_CTYPE, ""); //Sélectionne la table unicode de la machine en locale.


    taille_min_verticale = rand()%TAILLE_MAX-3;
    taille_min_horizontale = rand()%TAILLE_MAX-3;

    //Boucle pour créer et afficher la salle vide
    for(int i=taille_min_verticale;i<TAILLE_MAX;i++){



        printf("\n"); //Saut de ligne pour les colonnes pour créer une salle en 2D
        
        for(int j=taille_min_horizontale;j<TAILLE_MAX;j++){

            if(i!=taille_min_verticale && i!=TAILLE_MAX-1 && j!=taille_min_horizontale && j!=TAILLE_MAX-1){
              //Espace "vide"/cases de la salle
                printf(" ");
            }

            //Affichage des bordures
          
            if(i==taille_min_verticale && j==TAILLE_MAX-1){
                //Affichage bord supérieur gauche
                printf("%lc",0x2557);
            }
            else if(i==taille_min_verticale && j==taille_min_horizontale){
                //Affichage bord supérieur droit
                printf("%lc",0x2554);
            }
            else if(i==TAILLE_MAX-1 && j==TAILLE_MAX-1){
                //Affichage bord inférieur gauche
                printf("%lc",0x255D);
            }
            else if(i==TAILLE_MAX-1 && j==taille_min_horizontale){
                //Affichage bord inférieur droit
                printf("%lc",0x255A);
            }
            else if(i==taille_min_verticale || i==TAILLE_MAX-1){
            printf("%lc",0x02550); //Affichage bordure droite et gauche

            }
            else if(j==taille_min_horizontale || j==TAILLE_MAX-1){
                printf("%lc",0x02551); //Affichage bordure haut et bas

            }
        }
    }
}
