#ifndef GRAPHICS_H_   /* Include guard */
#define GRAPHICS_H_

#include <ncurses.h>
#include <wchar.h>

typedef struct {
    int x;
    int y;
}Porte;


typedef struct {
    int width;
    int height;
    int x;
    int y;
    int ** disp;
    Porte * portes;
    int nportes;
}Salle;


enum {
    MUR_SUPG,
    MUR_INFD,
    MUR_SUPD,
    MUR_INFG,
    MUR_HORIZ,
    MUR_VERTI,
    VOID,
    PORTE,
};

Salle * creerSalle(int taille_horizontale, int taille_verticale, int x, int y, int nportes);

Salle * creerSalleProced(int x, int y);

void drawSalle(WINDOW * win, Salle * salle);

void freeSalle(Salle * salle);

#endif 