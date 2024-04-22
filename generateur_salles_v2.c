#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#define TAILLE_MAX_V 10
#define TAILLE_MAX_H 20

int main(){
    wchar_t** salle = NULL; //Création du pointeur salle
    int taille_verticale, taille_horizontale;
    srand(time(NULL));
    setlocale(LC_CTYPE, ""); //Sélectionne la table unicode de la machine en locale.


    taille_verticale = TAILLE_MAX_V-(rand()%(TAILLE_MAX_V-2));
    taille_horizontale = TAILLE_MAX_H-(rand()%(TAILLE_MAX_H-2));
    printf("h %d v %d\n", taille_horizontale, taille_verticale);

    salle = malloc(sizeof(wchar_t*)*taille_verticale*taille_horizontale);
    if(salle == NULL){
        printf("Espace mémoire de la salle non alloué");
        exit(1);
        
    }
    for(int i=0;i<taille_verticale;i++){
      //Allocation des lignes de la salle
      
      salle[i] = malloc(sizeof(wchar_t)*taille_horizontale);
      //Vérification allocation
      if(salle[i] == NULL){
        printf("Espace mémoire de la ligne de la salle non alloué");
        exit(2);
        
      }


        
      for(int j=0;j<taille_horizontale;j++){
        salle[i][j] = ' ';
            
        if(i==0 || i==taille_verticale-1){
            salle[i][j] = 0x02550; //Affichage bordure droite et gauche

          }
        else if(j==0 || j==taille_horizontale-1){
          salle[i][j] = 0x02551; //Affichage bordure haut et bas

        }   

      }
    }
    //Bord supérieur gauche
    salle[0][taille_horizontale-1] = 0x2557;

    //Bord supérieur droit
    salle[0][0]=0x2554;

    //Bord inférieur gauche
    salle[taille_verticale-1][taille_horizontale-1] = 0x255D;
    //Bord inférieur droit
    salle[taille_verticale-1][0] = 0x255A;


  //Affichage salle
  for(int i=0;i<taille_verticale;i++){
    for(int j=0;j<taille_horizontale;j++){
      printf("%lc",salle[i][j]);
    }
    printf("\n");
  }

    return 0;
}
