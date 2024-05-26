//
// Created by valerie on 23/05/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "json/json.h"
#include "logger.h"
#include "CosmicYonder.h"

JSONObjet * objetVersJSON(Objet objet) {
    JSONObjet * objetJSON = NULL;
    objetJSON = malloc(sizeof(JSONObjet));
    if(objetJSON == NULL){
        logMessage(ERROR, "erreur malloc objetVersJSON objetJSON");
        exit(1);
    }
    objetJSON->length = 3; // trois attributs
    objetJSON->pairs = malloc(sizeof(JSONCleValeurCouple) * objetJSON->length);
    if(objetJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc objetVersJSON objetJSON->pairs");
        exit(1);
    }

    objetJSON->pairs[0].key = "x";
    objetJSON->pairs[0].value.type = JSON_NOMBRE;
    objetJSON->pairs[0].value.numberValue = objet.x;

    objetJSON->pairs[1].key = "y";
    objetJSON->pairs[1].value.type = JSON_NOMBRE;
    objetJSON->pairs[1].value.numberValue = objet.y;

    objetJSON->pairs[2].key = "id";
    objetJSON->pairs[2].value.type = JSON_NOMBRE;
    objetJSON->pairs[2].value.numberValue = objet.id;

    return objetJSON;
}

Objet objetDepuisJSON(JSONObjet objetJSON) {
    Objet objet;
    objet.x = objetJSON.pairs[0].value.numberValue;
    objet.y = objetJSON.pairs[1].value.numberValue;
    objet.id = objetJSON.pairs[2].value.numberValue;
    return objet;
}

Inventaire inventDepuisJSON(JSONArray invJSON) {
    Inventaire inv;
    for(int i = 0; i < invJSON.length; i++) {
        inv.obTab[i] = objetDepuisJSON(*invJSON.values[i].value.objectValue);
    }
    return inv;
}

Joueur * joueurVersJSON(JSONObjet joueurJSON) {
    Joueur * joueur;
    joueur = malloc(sizeof(Joueur));
    if(joueur == NULL) {
        logMessage(ERROR, "erreur malloc joueurVersJSON joueur");
        exit(1);
    }
    joueur->nom = NULL;
    joueur->nom = malloc(sizeof(char) * strlen(joueurJSON.pairs[0].value.stringValue) + 1);
    joueur->nom = strcpy(joueur->nom, joueurJSON.pairs[0].value.stringValue);
    joueur->x = joueurJSON.pairs[1].value.numberValue;
    joueur->y = joueurJSON.pairs[2].value.numberValue;
    joueur->pv = joueurJSON.pairs[3].value.numberValue;
    joueur->att = joueurJSON.pairs[4].value.numberValue;
    joueur->def = joueurJSON.pairs[5].value.numberValue;
    joueur->niv = joueurJSON.pairs[6].value.numberValue;
    joueur->xp = joueurJSON.pairs[7].value.numberValue;
    joueur->inventaire = inventDepuisJSON(*joueurJSON.pairs[8].value.arrayValue);
    return joueur;
}

Porte porteDepuisJSON(JSONObjet porteJSON) {
    Porte porte;
    porte.x = porteJSON.pairs[0].value.numberValue;
    porte.y = porteJSON.pairs[1].value.numberValue;
    porte.ouvert = porteJSON.pairs[2].value.boolValue;
    return porte;
}

Ennemi * ennemiDepuisJSON(JSONObjet ennemiJSON) {
    Ennemi * ennemi = NULL;
    ennemi = malloc(sizeof(Ennemi));
    if(ennemi == NULL){
        logMessage(ERROR, "erreur malloc ennemiDepuisJSON ennemi");
        exit(1);
    }
    ennemi->xGlobal = ennemiJSON.pairs[0].value.numberValue;
    ennemi->yGlobal = ennemiJSON.pairs[1].value.numberValue;
    ennemi->xRelatif = ennemiJSON.pairs[2].value.numberValue;
    ennemi->yRelatif = ennemiJSON.pairs[3].value.numberValue;
    ennemi->pv = ennemiJSON.pairs[4].value.numberValue;
    ennemi->att = ennemiJSON.pairs[5].value.numberValue;
    ennemi->def = ennemiJSON.pairs[6].value.numberValue;
    return ennemi;

}

JSONObjet * ennemiVersJSONObj(Ennemi * ennemi) {
    JSONObjet * ennemiJSON = NULL;
    ennemiJSON = malloc(sizeof(JSONObjet));
    // allocation de l'objet JSON
    if(ennemiJSON == NULL){
        logMessage(ERROR, "erreur malloc ennemiVersJSONObj ennemiJSON");
        exit(1);
    }
    // Allocation des attributs de l'objet json
    ennemiJSON->length = 7;
    ennemiJSON->pairs = malloc(sizeof(JSONCleValeurCouple) * ennemiJSON->length);
    if(ennemiJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc ennemiVersJSONObj ennemiJSON->pairs");
        exit(1);
    }
    ennemiJSON->pairs[0].key = "xGlobal";
    ennemiJSON->pairs[0].value.type = JSON_NOMBRE;
    ennemiJSON->pairs[0].value.numberValue = ennemi->xGlobal;

    ennemiJSON->pairs[1].key = "yGlobal";
    ennemiJSON->pairs[1].value.type = JSON_NOMBRE;
    ennemiJSON->pairs[1].value.numberValue = ennemi->yGlobal;

    ennemiJSON->pairs[2].key = "xRelatif";
    ennemiJSON->pairs[2].value.type = JSON_NOMBRE;
    ennemiJSON->pairs[2].value.numberValue = ennemi->xRelatif;

    ennemiJSON->pairs[3].key = "yRelatif";
    ennemiJSON->pairs[3].value.type = JSON_NOMBRE;
    ennemiJSON->pairs[3].value.numberValue = ennemi->yRelatif;

    ennemiJSON->pairs[4].key = "pv";
    ennemiJSON->pairs[4].value.type = JSON_NOMBRE;
    ennemiJSON->pairs[4].value.numberValue = ennemi->pv;

    ennemiJSON->pairs[5].key = "att";
    ennemiJSON->pairs[5].value.type = JSON_NOMBRE;
    ennemiJSON->pairs[5].value.numberValue = ennemi->att;

    ennemiJSON->pairs[6].key = "def";
    ennemiJSON->pairs[6].value.type = JSON_NOMBRE;
    ennemiJSON->pairs[6].value.numberValue = ennemi->def;

    return ennemiJSON;
}


Salle * salleDepuisJSON(JSONObjet salleJSON) {
    Salle * salle = NULL;
    salle = malloc(sizeof(Salle));
    if(salle == NULL){
        logMessage(ERROR, "erreur malloc salleDepuisJSON salle");
        exit(1);
    }
    salle->x = salleJSON.pairs[0].value.numberValue;
    salle->y = salleJSON.pairs[1].value.numberValue;
    salle->longueur = salleJSON.pairs[2].value.numberValue;
    salle->hauteur = salleJSON.pairs[3].value.numberValue;
    salle->nportes = salleJSON.pairs[7].value.numberValue;
    salle->decouvert = salleJSON.pairs[8].value.boolValue;
    salle->portes = malloc(sizeof(Porte) * salle->nportes);
    if(salle->portes == NULL){
        logMessage(ERROR, "erreur malloc salleDepuisJSON salle.portes");
        exit(1);
    }
    for(int i = 0; i < salle->nportes; i++) {
        salle->portes[i] = porteDepuisJSON(*salleJSON.pairs[4].value.arrayValue->values[i].value.objectValue);
    }
    for(int i = 0; i < 3; i++) {
        salle->objets[i] = objetDepuisJSON(*salleJSON.pairs[5].value.arrayValue->values[i].value.objectValue);
    }
    salle->disp = malloc(sizeof(int *) * salle->hauteur);
    if(salle->disp == NULL){
        logMessage(ERROR, "erreur malloc salleDepuisJSON salle.disp");
        exit(1);
    }
    for(int i = 0; i < salle->hauteur; i++) {
        salle->disp[i] = malloc(sizeof(int) * salle->longueur);
        if(salle->disp[i] == NULL){
            logMessage(ERROR, "erreur malloc salleDepuisJSON salle.disp[i]");
            exit(1);
        }
        for(int j = 0; j < salle->longueur; j++) {
            salle->disp[i][j] = salleJSON.pairs[6].value.arrayValue->values[i].value.arrayValue->values[j].value.numberValue;
        }
    }
    if(salleJSON.pairs[9].value.objectValue->length == 0) {
        salle->ennemi = NULL;
    } else {
        salle->ennemi = ennemiDepuisJSON(*salleJSON.pairs[9].value.objectValue);
    }
    return salle;
}

Salle ** carteDepuisJSON(JSONArray carteJSON) {
    int i = 0;
    Salle ** carte = NULL;
    carte = malloc(sizeof(Salle *) * MAX_SALLES);
    if(carte == NULL){
        logMessage(ERROR, "erreur malloc carteDepuisJSON carte");
        exit(1);
    }
    for(i = 0; i < MAX_SALLES; i++) {
        carte[i] = NULL;
    }
    for(i = 0; i < carteJSON.length; i++) {
        carte[i] = salleDepuisJSON(*carteJSON.values[i].value.objectValue);
    }


    return carte;
}

Partie * partieDepuisJSON(JSONObjet partieJSON) {
    Partie * partie = NULL;
    partie = malloc(sizeof(Partie));
    if(partie == NULL){
        logMessage(ERROR, "erreur malloc partieDepuisJSON partie");
        exit(1);
    }
    partie->joueur = NULL;
    partie->carte = NULL;
    partie->joueur = joueurVersJSON(*partieJSON.pairs[0].value.objectValue);
    partie->carte = carteDepuisJSON(*partieJSON.pairs[1].value.arrayValue);
    partie->graine = partieJSON.pairs[2].value.numberValue;
    partie->portesNonOuvertes = partieJSON.pairs[3].value.numberValue;
    partie->objets_speciaux_apparus = partieJSON.pairs[4].value.numberValue;
    partie->salles_existantes = partieJSON.pairs[5].value.numberValue;
    partie->mvEnnemic = partieJSON.pairs[6].value.numberValue;
    partie->nb_obj_inv = partieJSON.pairs[7].value.numberValue;
    partie->nb_obj_spe_inv = partieJSON.pairs[8].value.numberValue;
    partie->nsalles = partieJSON.pairs[9].value.numberValue;
    partie->minuteur = partieJSON.pairs[10].value.numberValue;
    partie->decr_minuteur = partieJSON.pairs[11].value.numberValue;

    return partie;
}

JSONArray * inventVersTabJSON(Inventaire inv) {
    JSONArray * invJSON = NULL;
    invJSON = malloc(sizeof(JSONArray));
    if(invJSON == NULL){
        logMessage(ERROR, "erreur malloc inventVersTabJSON invJSON");
        exit(1);
    }
    invJSON->length = INV_TAILLE;
    invJSON->values = malloc(sizeof(JSONCleValeurCouple) * invJSON->length);
    if(invJSON->values == NULL){
        logMessage(ERROR, "erreur malloc inventVersTabJSON invJSON->values");
        exit(1);
    }
    for(int i = 0; i < INV_TAILLE; i++) {
        invJSON->values[i].value.type = JSON_OBJET;
        invJSON->values[i].value.objectValue = objetVersJSON(inv.obTab[i]);
    }
    return invJSON;
}

JSONObjet * joueurVersObjJSON(Joueur * joueur) {
    JSONObjet * joueurJSON = NULL;
    joueurJSON = malloc(sizeof(JSONObjet));
    if(joueurJSON == NULL){
        logMessage(ERROR, "erreur malloc joueurVersObjJSON joueurJSON");
        exit(1);
    }
    joueurJSON->length = 9;
    joueurJSON->pairs = malloc(sizeof(JSONCleValeurCouple) * joueurJSON->length);
    if(joueurJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc joueurVersObjJSON joueurJSON->pairs");
        exit(1);
    }
    joueurJSON->pairs[0].key = "nom";
    joueurJSON->pairs[0].value.type = JSON_CHAINE;
    joueurJSON->pairs[0].value.stringValue = malloc(sizeof(char) * strlen(joueur->nom) + 1);
    if(joueurJSON->pairs[0].value.stringValue == NULL){
        logMessage(ERROR, "erreur malloc joueurVersObjJSON joueurJSON->pairs[0].value.stringValue");
        exit(1);
    }
    joueurJSON->pairs[0].value.stringValue = strcpy(joueurJSON->pairs[0].value.stringValue, joueur->nom);

    joueurJSON->pairs[1].key = "x";
    joueurJSON->pairs[1].value.type = JSON_NOMBRE;
    joueurJSON->pairs[1].value.numberValue = joueur->x;

    joueurJSON->pairs[2].key = "y";
    joueurJSON->pairs[2].value.type = JSON_NOMBRE;
    joueurJSON->pairs[2].value.numberValue = joueur->y;

    joueurJSON->pairs[3].key = "pv";
    joueurJSON->pairs[3].value.type = JSON_NOMBRE;
    joueurJSON->pairs[3].value.numberValue = joueur->pv;

    joueurJSON->pairs[4].key = "att";
    joueurJSON->pairs[4].value.type = JSON_NOMBRE;
    joueurJSON->pairs[4].value.numberValue = joueur->att;

    joueurJSON->pairs[5].key = "def";
    joueurJSON->pairs[5].value.type = JSON_NOMBRE;
    joueurJSON->pairs[5].value.numberValue = joueur->def;

    joueurJSON->pairs[6].key = "niv";
    joueurJSON->pairs[6].value.type = JSON_NOMBRE;
    joueurJSON->pairs[6].value.numberValue = joueur->niv;

    joueurJSON->pairs[7].key = "xp";
    joueurJSON->pairs[7].value.type = JSON_NOMBRE;
    joueurJSON->pairs[7].value.numberValue = joueur->xp;

    joueurJSON->pairs[8].key = "inventaire";
    joueurJSON->pairs[8].value.type = JSON_TABLEAU;
    joueurJSON->pairs[8].value.arrayValue = inventVersTabJSON(joueur->inventaire);

    return joueurJSON;
}

JSONObjet * porteVersObjJSON(Porte porte) {
    JSONObjet * porteJSON = NULL;
    porteJSON = malloc(sizeof(JSONObjet));
    if(porteJSON == NULL){
        logMessage(ERROR, "erreur malloc porteVersObjJSON porteJSON");
        exit(1);
    }
    porteJSON->length = 3;
    porteJSON->pairs = malloc(sizeof(JSONCleValeurCouple) * porteJSON->length);
    if(porteJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc porteVersObjJSON porteJSON->pairs");
        exit(1);
    }
    porteJSON->pairs[0].key = "x";
    porteJSON->pairs[0].value.type = JSON_NOMBRE;
    porteJSON->pairs[0].value.numberValue = porte.x;

    porteJSON->pairs[1].key = "y";
    porteJSON->pairs[1].value.type = JSON_NOMBRE;
    porteJSON->pairs[1].value.numberValue = porte.y;

    porteJSON->pairs[2].key = "ouvert";
    porteJSON->pairs[2].value.type = JSON_BOOL;
    porteJSON->pairs[2].value.boolValue = porte.ouvert;

    return porteJSON;
}

JSONObjet * salleVersObjJSON(Salle salle) {
    JSONObjet * salleJSON = NULL;
    salleJSON = malloc(sizeof(JSONObjet));
    if(salleJSON == NULL){
        logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON");
        exit(1);
    }
    salleJSON->length = 10;
    salleJSON->pairs = malloc(sizeof(JSONCleValeurCouple) * salleJSON->length);
    if(salleJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs");
        exit(1);
    }
    salleJSON->pairs[0].key = "x";
    salleJSON->pairs[0].value.type = JSON_NOMBRE;
    salleJSON->pairs[0].value.numberValue = salle.x;

    salleJSON->pairs[1].key = "y";
    salleJSON->pairs[1].value.type = JSON_NOMBRE;
    salleJSON->pairs[1].value.numberValue = salle.y;

    salleJSON->pairs[2].key = "longueur";
    salleJSON->pairs[2].value.type = JSON_NOMBRE;
    salleJSON->pairs[2].value.numberValue = salle.longueur;

    salleJSON->pairs[3].key = "hauteur";
    salleJSON->pairs[3].value.type = JSON_NOMBRE;
    salleJSON->pairs[3].value.numberValue = salle.hauteur;

    salleJSON->pairs[4].key = "portes";
    salleJSON->pairs[4].value.type = JSON_TABLEAU;
    salleJSON->pairs[4].value.arrayValue = malloc(sizeof(JSONArray));
    if(salleJSON->pairs[4].value.arrayValue == NULL){
        logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs[4].value.arrayValue");
        exit(1);
    }
    salleJSON->pairs[4].value.arrayValue->length = salle.nportes;
    salleJSON->pairs[4].value.arrayValue->values = malloc(sizeof(JSONCleValeurCouple) * salleJSON->pairs[4].value.arrayValue->length);
    if(salleJSON->pairs[4].value.arrayValue->values == NULL){
        logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs[4].value.arrayValue->values");
        exit(1);
    }
    for(int i = 0; i < salle.nportes; i++) {
        salleJSON->pairs[4].value.arrayValue->values[i].value.type = JSON_OBJET;
        salleJSON->pairs[4].value.arrayValue->values[i].value.objectValue = porteVersObjJSON(salle.portes[i]);
    }

    salleJSON->pairs[5].key = "objets";
    salleJSON->pairs[5].value.type = JSON_TABLEAU;
    salleJSON->pairs[5].value.arrayValue = malloc(sizeof(JSONArray));
    if(salleJSON->pairs[5].value.arrayValue == NULL){
        logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs[5].value.arrayValue");
        exit(1);
    }
    salleJSON->pairs[5].value.arrayValue->length = 3; // 3 objets max par salle
    salleJSON->pairs[5].value.arrayValue->values = malloc(sizeof(JSONCleValeurCouple) * salleJSON->pairs[5].value.arrayValue->length);
    if(salleJSON->pairs[5].value.arrayValue->values == NULL){
        logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs[5].value.arrayValue->values");
        exit(1);
    }

    for(int i = 0; i < 3; i++) {
        salleJSON->pairs[5].value.arrayValue->values[i].value.type = JSON_OBJET;
        salleJSON->pairs[5].value.arrayValue->values[i].value.objectValue = objetVersJSON(salle.objets[i]);
    }

    salleJSON->pairs[6].key = "disp";
    salleJSON->pairs[6].value.type = JSON_TABLEAU;
    salleJSON->pairs[6].value.arrayValue = malloc(sizeof(JSONArray));
    if(salleJSON->pairs[6].value.arrayValue == NULL){
        logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs[6].value.arrayValue");
        exit(1);
    }
    salleJSON->pairs[6].value.arrayValue->length = salle.hauteur;
    salleJSON->pairs[6].value.arrayValue->values = malloc(sizeof(JSONCleValeurCouple) * salleJSON->pairs[6].value.arrayValue->length);
    if(salleJSON->pairs[6].value.arrayValue->values == NULL){
        logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs[6].value.arrayValue->values");
        exit(1);
    }
    // vive les salle->disp aaaaaaaa
    for(int i = 0; i < salle.hauteur; i++) {
        salleJSON->pairs[6].value.arrayValue->values[i].value.type = JSON_TABLEAU;
        salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue = malloc(sizeof(JSONArray));
        if(salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue == NULL){
            logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue");
            exit(1);
        }
        salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->length = salle.longueur;
        salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values = malloc(sizeof(JSONCleValeurCouple) * salle.longueur);
        if(salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values == NULL){
            logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values");
            exit(1);
        }
        for(int j = 0; j < salle.longueur; j++) {
            salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values[j].value.type = JSON_NOMBRE;
            salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values[j].value.numberValue = salle.disp[i][j];
        }
    }

    salleJSON->pairs[7].key = "nportes";
    salleJSON->pairs[7].value.type = JSON_NOMBRE;
    salleJSON->pairs[7].value.numberValue = salle.nportes;

    salleJSON->pairs[8].key = "decouvert";
    salleJSON->pairs[8].value.type = JSON_BOOL;
    salleJSON->pairs[8].value.boolValue = salle.decouvert;

    salleJSON->pairs[9].key = "ennemi";
    salleJSON->pairs[9].value.type = JSON_OBJET;

    if(salle.ennemi == NULL) {
        salleJSON->pairs[9].value.objectValue = malloc(sizeof(JSONObjet));
        if(salleJSON->pairs[9].value.objectValue == NULL){
            logMessage(ERROR, "erreur malloc salleVersObjJSON salleJSON->pairs[9].value.objectValue");
            exit(1);
        }
        salleJSON->pairs[9].value.objectValue->length = 0;
        salleJSON->pairs[9].value.objectValue->pairs = NULL;
    } else {
        salleJSON->pairs[9].value.objectValue = ennemiVersJSONObj(salle.ennemi);
    }

    return salleJSON;

}

JSONArray * carteVersTabJSON(Salle ** carte, int nsalles) {
    JSONArray * carteJSON = NULL;
    carteJSON = malloc(sizeof(JSONArray));
    if(carteJSON == NULL){
        logMessage(ERROR, "erreur malloc carteVersTabJSON carteJSON");
        exit(1);
    }
    carteJSON->length = nsalles;
    carteJSON->values = malloc(sizeof(JSONCleValeurCouple) * carteJSON->length);
    if(carteJSON->values == NULL){
        logMessage(ERROR, "erreur malloc carteVersTabJSON carteJSON->values");
        exit(1);
    }
    for(int i = 0; i < nsalles; i++) {
        carteJSON->values[i].value.type = JSON_OBJET;
        carteJSON->values[i].value.objectValue = salleVersObjJSON(*carte[i]);
    }
    return carteJSON;
}

JSONObjet * partieVersObjJSON(Partie * partie) {
    JSONObjet * partieJSON = NULL;
    partieJSON = malloc(sizeof(JSONObjet));
    if(partieJSON == NULL){
        logMessage(ERROR, "erreur malloc partieVersObjJSON partieJSON");
        exit(1);
    }
    partieJSON->length = 12;
    partieJSON->pairs = malloc(sizeof(JSONCleValeurCouple) * partieJSON->length);
    if(partieJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc partieVersObjJSON partieJSON->pairs");
        exit(1);
    }
    partieJSON->pairs[0].key = "joueur";
    partieJSON->pairs[0].value.type = JSON_OBJET;
    partieJSON->pairs[0].value.objectValue = joueurVersObjJSON(partie->joueur);

    partieJSON->pairs[1].key = "carte";
    partieJSON->pairs[1].value.type = JSON_TABLEAU;
    partieJSON->pairs[1].value.arrayValue = carteVersTabJSON(partie->carte, partie->salles_existantes);

    partieJSON->pairs[2].key = "graine";
    partieJSON->pairs[2].value.type = JSON_NOMBRE;
    partieJSON->pairs[2].value.numberValue = partie->graine;

    partieJSON->pairs[3].key = "portesNonOuvertes";
    partieJSON->pairs[3].value.type = JSON_NOMBRE;
    partieJSON->pairs[3].value.numberValue = partie->portesNonOuvertes;

    partieJSON->pairs[4].key = "objets_speciaux_apparus";
    partieJSON->pairs[4].value.type = JSON_NOMBRE;
    partieJSON->pairs[4].value.numberValue = partie->objets_speciaux_apparus;

    partieJSON->pairs[5].key = "salles_existantes";
    partieJSON->pairs[5].value.type = JSON_NOMBRE;
    partieJSON->pairs[5].value.numberValue = partie->salles_existantes;

    partieJSON->pairs[6].key = "mvEnnemic";
    partieJSON->pairs[6].value.type = JSON_NOMBRE;
    partieJSON->pairs[6].value.numberValue = partie->mvEnnemic;

    partieJSON->pairs[7].key = "nb_obj_inv";
    partieJSON->pairs[7].value.type = JSON_NOMBRE;
    partieJSON->pairs[7].value.numberValue = partie->nb_obj_inv;

    partieJSON->pairs[8].key = "nb_obj_spe_inv";
    partieJSON->pairs[8].value.type = JSON_NOMBRE;
    partieJSON->pairs[8].value.numberValue = partie->nb_obj_spe_inv;

    partieJSON->pairs[9].key = "nsalles";
    partieJSON->pairs[9].value.type = JSON_NOMBRE;
    partieJSON->pairs[9].value.numberValue = partie->nsalles;

    partieJSON->pairs[10].key = "minuteur";
    partieJSON->pairs[10].value.type = JSON_NOMBRE;
    partieJSON->pairs[10].value.numberValue = partie->minuteur;

    partieJSON->pairs[11].key = "decr_minuteur";
    partieJSON->pairs[11].value.type = JSON_NOMBRE;
    partieJSON->pairs[11].value.numberValue = partie->decr_minuteur;

    return partieJSON;
}

void freeObjetJSON(JSONObjet * obj) { // fonction récursive pour se débarasser de tous les mallocs
    for(int i = 0; i < obj->length; i++) {
        if(obj->pairs[i].value.type == JSON_TABLEAU) {
            for(int j = 0; j < obj->pairs[i].value.arrayValue->length; j++) {
                if(obj->pairs[i].value.arrayValue->values[j].value.type == JSON_OBJET) {
                    freeObjetJSON(obj->pairs[i].value.arrayValue->values[j].value.objectValue);
                }
            }
            free(obj->pairs[i].value.arrayValue->values);
            free(obj->pairs[i].value.arrayValue);
        }
        if(obj->pairs[i].value.type == JSON_OBJET) {
            freeObjetJSON(obj->pairs[i].value.objectValue);
        }
    }
    free(obj->pairs);
    free(obj);
}

void sauveJeu(Partie * partie, char * nomFichier) {
    char * chemin = malloc(sizeof(char) * strlen(nomFichier) + 6); // 5 pour le .json et le \0
    if(chemin == NULL) {
        logMessage(ERROR, "erreur malloc path sauveJeu");
        exit(1);
    }
    chemin = strcpy(chemin, nomFichier);
    chemin = strcat(chemin, ".json");
    JSONObjet * partieJSON = partieVersObjJSON(partie);
    char * serialized = serializeObjetJSON(*partieJSON);
    FILE * save = fopen(chemin, "w");
    if(save == NULL) {
        logMessage(ERROR, "erreur ouverture fichier save.json");
        exit(1);
    }
    fprintf(save, "%s", serialized);
    fclose(save);
    free(serialized);
    freeObjetJSON(partieJSON);
}

Partie * chargerJeu(char * nomFichier) {
    char * chemin = malloc(sizeof(char) * strlen(nomFichier) + 6); // 5 pour le .json et le \0
    if(chemin == NULL) {
        logMessage(ERROR, "erreur malloc path chargerJeu");
        exit(1);
    }
    chemin = strcpy(chemin, nomFichier);
    chemin = strcat(chemin, ".json");
    FILE * save = fopen(chemin, "r");
    if(save == NULL) {
        logMessage(ERROR, "erreur ouverture fichier save.json");
        exit(1);
    }
    // obtention de la longueur du fichier
    fseek(save, 0, SEEK_END);
    unsigned int fsize = ftell(save);
    fseek(save, 0, SEEK_SET);
    // définiton buffer
    char * buffer = malloc(fsize + 1);
    // sauvegarde du pointeur
    char * bufferPtr = buffer;

    if(buffer == NULL) {
        logMessage(ERROR, "erreur malloc buffer chargerJeu");
        exit(1);
    }
    // lecture du fichier
    fread(buffer, 1, fsize, save);
    fclose(save);
    buffer[fsize] = '\0'; // ajout du caractère de fin de chaine
    // creation JSONObjet
    JSONObjet * partieJSON = parserObjetJSON(&buffer);
    Partie * partie = NULL;
    partie = partieDepuisJSON(*partieJSON);
    // libération de la mémoire
    free(bufferPtr);
    freeObjetJSON(partieJSON);
    return partie;
}

int verifFichier(char * nomSauvegarde) {
    // vérification si le fichier existe
    char * chemin = malloc(sizeof(char) * strlen(nomSauvegarde) + 6); // 6 pour le .json et le \0
    if(chemin == NULL) {
        logMessage(ERROR, "erreur malloc path chargerJeu");
        exit(1);
    }
    chemin = strcpy(chemin, nomSauvegarde);
    chemin = strcat(chemin, ".json"); // ajout extension
    if(access(chemin, F_OK) == 0) { // vérification de l'existence du fichier
        free(chemin);
        return 1;
    } else {
        free(chemin);
        return 0;
    }
}

void sauvegardeBoucle(WINDOW * mainwin, EntreeTexte * sauve, int x, int y, int hauteur, int longueur, int* touche) {
    int fichier_exists = 1;
    sauve->valide = 0;

    do {
        while (!sauve->valide) { //Tant qu'on ne sélectionne rien le jeu est arrêté
            wrefresh(mainwin);
            *touche = wgetch(mainwin);
            werase(mainwin);
            renduFenetreEntree(mainwin, sauve, x, y, hauteur/3, longueur/3);
            entreeTexte(sauve, *touche);
            napms(1000 / IMAGES_PAR_SECONDE);
        }
        fichier_exists = verifFichier(sauve->buffer);
        if(fichier_exists) { // affiche erreur
            for(int i = 0; i < longueur/2-1; i++) {
                mvwaddch(mainwin, hauteur / 2, longueur / 2 - 8 + i, ' ');
            }
            wattron(mainwin, COLOR_PAIR(1));
            mvwprintw(mainwin, hauteur / 2, longueur / 2 - 8, "%s.json inexistant", sauve->buffer);
            wattroff(mainwin, COLOR_PAIR(1));
            sauve->valide = 0;
        }

    } while (fichier_exists);
}