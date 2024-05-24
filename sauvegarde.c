//
// Created by valerie on 23/05/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "json/json.h"
#include "logger.h"
#include "CosmicYonder.h"

JSONObject * objetToJSONObj(Objet objet) {
    JSONObject * objetJSON = NULL;
    objetJSON = malloc(sizeof(JSONObject));
    if(objetJSON == NULL){
        logMessage(ERROR, "erreur malloc objetToJSONObj objetJSON");
        exit(1);
    }
    objetJSON->length = 3;
    objetJSON->pairs = malloc(sizeof(JSONKeyValuePair) * objetJSON->length);
    if(objetJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc objetToJSONObj objetJSON->pairs");
        exit(1);
    }
    objetJSON->pairs[0].key = "x";
    objetJSON->pairs[0].value.type = JSON_NUMBER;
    objetJSON->pairs[0].value.numberValue = objet.x;

    objetJSON->pairs[1].key = "y";
    objetJSON->pairs[1].value.type = JSON_NUMBER;
    objetJSON->pairs[1].value.numberValue = objet.y;

    objetJSON->pairs[2].key = "id";
    objetJSON->pairs[2].value.type = JSON_NUMBER;
    objetJSON->pairs[2].value.numberValue = objet.id;

    return objetJSON;
}

Objet objetFromJSONObj(JSONObject objetJSON) {
    Objet objet;
    objet.x = objetJSON.pairs[0].value.numberValue;
    objet.y = objetJSON.pairs[1].value.numberValue;
    objet.id = objetJSON.pairs[2].value.numberValue;
    return objet;
}

Inventaire inventFromJSONArr(JSONArray invJSON) {
    Inventaire inv;
    for(int i = 0; i < invJSON.length; i++) {
        inv.obTab[i] = objetFromJSONObj(*invJSON.values[i].value.objectValue);
    }
    return inv;
}

Joueur * joueurFromJSONObj(JSONObject joueurJSON) {
    Joueur * joueur;
    joueur = malloc(sizeof(Joueur));
    if(joueur == NULL) {
        logMessage(ERROR, "erreur malloc joueurFromJSONObj joueur");
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
    joueur->inventaire = inventFromJSONArr(*joueurJSON.pairs[8].value.arrayValue);
    return joueur;
}

Porte porteFromJSONObj(JSONObject porteJSON) {
    Porte porte;
    porte.x = porteJSON.pairs[0].value.numberValue;
    porte.y = porteJSON.pairs[1].value.numberValue;
    porte.ouvert = porteJSON.pairs[2].value.boolValue;
    return porte;
}

Salle * salleFromJSONObj(JSONObject salleJSON) {
    Salle * salle = NULL;
    salle = malloc(sizeof(Salle));
    if(salle == NULL){
        logMessage(ERROR, "erreur malloc salleFromJSONObj salle");
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
        logMessage(ERROR, "erreur malloc salleFromJSONObj salle.portes");
        exit(1);
    }
    for(int i = 0; i < salle->nportes; i++) {
        salle->portes[i] = porteFromJSONObj(*salleJSON.pairs[4].value.arrayValue->values[i].value.objectValue);
    }
    for(int i = 0; i < 3; i++) {
        salle->objets[i] = objetFromJSONObj(*salleJSON.pairs[5].value.arrayValue->values[i].value.objectValue);
    }
    salle->disp = malloc(sizeof(int *) * salle->hauteur);
    if(salle->disp == NULL){
        logMessage(ERROR, "erreur malloc salleFromJSONObj salle.disp");
        exit(1);
    }
    for(int i = 0; i < salle->hauteur; i++) {
        salle->disp[i] = malloc(sizeof(int) * salle->longueur);
        if(salle->disp[i] == NULL){
            logMessage(ERROR, "erreur malloc salleFromJSONObj salle.disp[i]");
            exit(1);
        }
        for(int j = 0; j < salle->longueur; j++) {
            salle->disp[i][j] = salleJSON.pairs[6].value.arrayValue->values[i].value.arrayValue->values[j].value.numberValue;
        }
    }
    return salle;
}

Salle ** carteFromJSONArr(JSONArray carteJSON) {
    Salle ** carte = NULL;
    carte = malloc(sizeof(Salle *) * MAX_SALLES);
    if(carte == NULL){
        logMessage(ERROR, "erreur malloc carteFromJSONArr carte");
        exit(1);
    }
    for(int i = 0; i < carteJSON.length; i++) {
        carte[i] = salleFromJSONObj(*carteJSON.values[i].value.objectValue);
    }

    for(int j = carteJSON.length; j < MAX_SALLES; j++) {
        carte[j] = NULL;
    }
    return carte;
}

Partie * partieFromJSONObj(JSONObject partieJSON) {
    Partie * partie = NULL;
    partie = malloc(sizeof(Partie));
    if(partie == NULL){
        logMessage(ERROR, "erreur malloc partieFromJSONObj partie");
        exit(1);
    }
    partie->joueur = malloc(sizeof(Joueur));
    if(partie->joueur == NULL){
        logMessage(ERROR, "erreur malloc partieFromJSONObj partie.joueur");
        exit(1);
    }
    partie->joueur = joueurFromJSONObj(*partieJSON.pairs[0].value.objectValue);
    partie->carte = carteFromJSONArr(*partieJSON.pairs[1].value.arrayValue);
    partie->graine = partieJSON.pairs[2].value.numberValue;
    partie->portesNonOuvertes = partieJSON.pairs[3].value.numberValue;
    partie->objets_speciaux_apparus = partieJSON.pairs[4].value.numberValue;
    partie->salles_existantes = partieJSON.pairs[5].value.numberValue;
    partie->mvEnnemic = partieJSON.pairs[6].value.numberValue;
    return partie;
}

JSONArray * inventToJSONArr(Inventaire inv) {
    int nobj = 0;
    JSONArray * invJSON = NULL;
    invJSON = malloc(sizeof(JSONArray));
    if(invJSON == NULL){
        logMessage(ERROR, "erreur malloc inventToJSONArr invJSON");
        exit(1);
    }
    while(inv.obTab[nobj].id != 0) {
        nobj++;
    }
    invJSON->length = nobj;

    invJSON->values = malloc(sizeof(JSONKeyValuePair) * invJSON->length);
    if(invJSON->values == NULL){
        logMessage(ERROR, "erreur malloc inventToJSONArr invJSON->values");
        exit(1);
    }
    for(int i = 0; i < nobj; i++) {
        invJSON->values[nobj].value.type = JSON_OBJECT;
        invJSON->values[nobj].value.objectValue = objetToJSONObj(inv.obTab[nobj]);
    }
    return invJSON;
}

JSONObject * joueurToJSONObj(Joueur joueur) {
    JSONObject * joueurJSON = NULL;
    joueurJSON = malloc(sizeof(JSONObject));
    if(joueurJSON == NULL){
        logMessage(ERROR, "erreur malloc joueurToJSONObj joueurJSON");
        exit(1);
    }
    joueurJSON->length = 9;
    joueurJSON->pairs = malloc(sizeof(JSONKeyValuePair) * joueurJSON->length);
    if(joueurJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc joueurToJSONObj joueurJSON->pairs");
        exit(1);
    }
    joueurJSON->pairs[0].key = "nom";
    joueurJSON->pairs[0].value.type = JSON_STRING;
    joueurJSON->pairs[0].value.stringValue = joueur.nom;

    joueurJSON->pairs[1].key = "x";
    joueurJSON->pairs[1].value.type = JSON_NUMBER;
    joueurJSON->pairs[1].value.numberValue = joueur.x;

    joueurJSON->pairs[2].key = "y";
    joueurJSON->pairs[2].value.type = JSON_NUMBER;
    joueurJSON->pairs[2].value.numberValue = joueur.y;

    joueurJSON->pairs[3].key = "pv";
    joueurJSON->pairs[3].value.type = JSON_NUMBER;
    joueurJSON->pairs[3].value.numberValue = joueur.pv;

    joueurJSON->pairs[4].key = "att";
    joueurJSON->pairs[4].value.type = JSON_NUMBER;
    joueurJSON->pairs[4].value.numberValue = joueur.att;

    joueurJSON->pairs[5].key = "def";
    joueurJSON->pairs[5].value.type = JSON_NUMBER;
    joueurJSON->pairs[5].value.numberValue = joueur.def;

    joueurJSON->pairs[6].key = "niv";
    joueurJSON->pairs[6].value.type = JSON_NUMBER;
    joueurJSON->pairs[6].value.numberValue = joueur.niv;

    joueurJSON->pairs[7].key = "xp";
    joueurJSON->pairs[7].value.type = JSON_NUMBER;
    joueurJSON->pairs[7].value.numberValue = joueur.xp;

    joueurJSON->pairs[8].key = "inventaire";
    joueurJSON->pairs[8].value.type = JSON_ARRAY;
    joueurJSON->pairs[8].value.arrayValue = inventToJSONArr(joueur.inventaire);

    return joueurJSON;
}

JSONObject * porteToJSONObj(Porte porte) {
    JSONObject * porteJSON = NULL;
    porteJSON = malloc(sizeof(JSONObject));
    if(porteJSON == NULL){
        logMessage(ERROR, "erreur malloc porteToJSONObj porteJSON");
        exit(1);
    }
    porteJSON->length = 3;
    porteJSON->pairs = malloc(sizeof(JSONKeyValuePair) * porteJSON->length);
    if(porteJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc porteToJSONObj porteJSON->pairs");
        exit(1);
    }
    porteJSON->pairs[0].key = "x";
    porteJSON->pairs[0].value.type = JSON_NUMBER;
    porteJSON->pairs[0].value.numberValue = porte.x;

    porteJSON->pairs[1].key = "y";
    porteJSON->pairs[1].value.type = JSON_NUMBER;
    porteJSON->pairs[1].value.numberValue = porte.y;

    porteJSON->pairs[2].key = "ouvert";
    porteJSON->pairs[2].value.type = JSON_BOOL;
    porteJSON->pairs[2].value.boolValue = porte.ouvert;

    return porteJSON;
}

JSONObject * salleToJSONObj(Salle salle) {
    JSONObject * salleJSON = NULL;
    salleJSON = malloc(sizeof(JSONObject));
    if(salleJSON == NULL){
        logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON");
        exit(1);
    }
    salleJSON->length = 9;
    salleJSON->pairs = malloc(sizeof(JSONKeyValuePair) * salleJSON->length);
    if(salleJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON->pairs");
        exit(1);
    }
    salleJSON->pairs[0].key = "x";
    salleJSON->pairs[0].value.type = JSON_NUMBER;
    salleJSON->pairs[0].value.numberValue = salle.x;

    salleJSON->pairs[1].key = "y";
    salleJSON->pairs[1].value.type = JSON_NUMBER;
    salleJSON->pairs[1].value.numberValue = salle.y;

    salleJSON->pairs[2].key = "longueur";
    salleJSON->pairs[2].value.type = JSON_NUMBER;
    salleJSON->pairs[2].value.numberValue = salle.longueur;

    salleJSON->pairs[3].key = "hauteur";
    salleJSON->pairs[3].value.type = JSON_NUMBER;
    salleJSON->pairs[3].value.numberValue = salle.hauteur;

    salleJSON->pairs[4].key = "portes";
    salleJSON->pairs[4].value.type = JSON_ARRAY;
    salleJSON->pairs[4].value.arrayValue = malloc(sizeof(JSONArray));
    if(salleJSON->pairs[4].value.arrayValue == NULL){
        logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON->pairs[4].value.arrayValue");
        exit(1);
    }
    salleJSON->pairs[4].value.arrayValue->length = salle.nportes;
    salleJSON->pairs[4].value.arrayValue->values = malloc(sizeof(JSONKeyValuePair) * salleJSON->pairs[4].value.arrayValue->length);
    if(salleJSON->pairs[4].value.arrayValue->values == NULL){
        logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON->pairs[4].value.arrayValue->values");
        exit(1);
    }
    for(int i = 0; i < salle.nportes; i++) {
        salleJSON->pairs[4].value.arrayValue->values[i].value.type = JSON_OBJECT;
        salleJSON->pairs[4].value.arrayValue->values[i].value.objectValue = porteToJSONObj(salle.portes[i]);
    }

    salleJSON->pairs[5].key = "objets";
    salleJSON->pairs[5].value.type = JSON_ARRAY;
    salleJSON->pairs[5].value.arrayValue = malloc(sizeof(JSONArray));
    if(salleJSON->pairs[5].value.arrayValue == NULL){
        logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON->pairs[5].value.arrayValue");
        exit(1);
    }
    salleJSON->pairs[5].value.arrayValue->length = 3; // 3 objets max par salle
    salleJSON->pairs[5].value.arrayValue->values = malloc(sizeof(JSONKeyValuePair) * salleJSON->pairs[5].value.arrayValue->length);
    if(salleJSON->pairs[5].value.arrayValue->values == NULL){
        logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON->pairs[5].value.arrayValue->values");
        exit(1);
    }

    for(int i = 0; i < 4; i++) {
        salleJSON->pairs[5].value.arrayValue->values[i].value.type = JSON_OBJECT;
        salleJSON->pairs[5].value.arrayValue->values[i].value.objectValue = objetToJSONObj(salle.objets[i]);
    }

    salleJSON->pairs[6].key = "disp";
    salleJSON->pairs[6].value.type = JSON_ARRAY;
    salleJSON->pairs[6].value.arrayValue = malloc(sizeof(JSONArray));
    if(salleJSON->pairs[6].value.arrayValue == NULL){
        logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON->pairs[6].value.arrayValue");
        exit(1);
    }
    salleJSON->pairs[6].value.arrayValue->length = salle.hauteur;
    salleJSON->pairs[6].value.arrayValue->values = malloc(sizeof(JSONKeyValuePair) * salleJSON->pairs[6].value.arrayValue->length);
    if(salleJSON->pairs[6].value.arrayValue->values == NULL){
        logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON->pairs[6].value.arrayValue->values");
        exit(1);
    }
    // vive les salle->disp aaaaaaaa
    for(int i = 0; i < salle.hauteur; i++) {
        salleJSON->pairs[6].value.arrayValue->values[i].value.type = JSON_ARRAY;
        salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue = malloc(sizeof(JSONArray));
        if(salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue == NULL){
            logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue");
            exit(1);
        }
        salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->length = salle.longueur;
        salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values = malloc(sizeof(JSONKeyValuePair) * salle.longueur);
        if(salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values == NULL){
            logMessage(ERROR, "erreur malloc salleToJSONObj salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values");
            exit(1);
        }
        for(int j = 0; j < salle.longueur; j++) {
            salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values[j].value.type = JSON_NUMBER;
            salleJSON->pairs[6].value.arrayValue->values[i].value.arrayValue->values[j].value.numberValue = salle.disp[i][j];
        }
    }

    salleJSON->pairs[7].key = "nportes";
    salleJSON->pairs[7].value.type = JSON_NUMBER;
    salleJSON->pairs[7].value.numberValue = salle.nportes;

    salleJSON->pairs[8].key = "decouvert";
    salleJSON->pairs[8].value.type = JSON_BOOL;
    salleJSON->pairs[8].value.boolValue = salle.decouvert;

    return salleJSON;

}

JSONArray * carteToJSONArr(Salle ** carte, int nsalles) {
    JSONArray * carteJSON = NULL;
    carteJSON = malloc(sizeof(JSONArray));
    if(carteJSON == NULL){
        logMessage(ERROR, "erreur malloc carteToJSONArr carteJSON");
        exit(1);
    }
    carteJSON->length = nsalles;
    carteJSON->values = malloc(sizeof(JSONKeyValuePair) * carteJSON->length);
    if(carteJSON->values == NULL){
        logMessage(ERROR, "erreur malloc carteToJSONArr carteJSON->values");
        exit(1);
    }
    for(int i = 0; i < nsalles; i++) {
        carteJSON->values[i].value.type = JSON_OBJECT;
        carteJSON->values[i].value.objectValue = salleToJSONObj(*carte[i]);
    }
    return carteJSON;
}

JSONObject * partieToJSONObj(Partie partie) {
    JSONObject * partieJSON = NULL;
    partieJSON = malloc(sizeof(JSONObject));
    if(partieJSON == NULL){
        logMessage(ERROR, "erreur malloc partieToJSONObj partieJSON");
        exit(1);
    }
    partieJSON->length = 7;
    partieJSON->pairs = malloc(sizeof(JSONKeyValuePair) * partieJSON->length);
    if(partieJSON->pairs == NULL){
        logMessage(ERROR, "erreur malloc partieToJSONObj partieJSON->pairs");
        exit(1);
    }
    partieJSON->pairs[0].key = "joueur";
    partieJSON->pairs[0].value.type = JSON_OBJECT;
    partieJSON->pairs[0].value.objectValue = joueurToJSONObj(*partie.joueur);

    partieJSON->pairs[1].key = "carte";
    partieJSON->pairs[1].value.type = JSON_ARRAY;
    partieJSON->pairs[1].value.arrayValue = carteToJSONArr(partie.carte, partie.salles_existantes);

    partieJSON->pairs[2].key = "graine";
    partieJSON->pairs[2].value.type = JSON_NUMBER;
    partieJSON->pairs[2].value.numberValue = partie.graine;

    partieJSON->pairs[3].key = "portesNonOuvertes";
    partieJSON->pairs[3].value.type = JSON_NUMBER;
    partieJSON->pairs[3].value.numberValue = partie.portesNonOuvertes;

    partieJSON->pairs[4].key = "objets_speciaux_apparus";
    partieJSON->pairs[4].value.type = JSON_NUMBER;
    partieJSON->pairs[4].value.numberValue = partie.objets_speciaux_apparus;

    partieJSON->pairs[5].key = "salles_existantes";
    partieJSON->pairs[5].value.type = JSON_NUMBER;
    partieJSON->pairs[5].value.numberValue = partie.salles_existantes;

    partieJSON->pairs[6].key = "mvEnnemic";
    partieJSON->pairs[6].value.type = JSON_NUMBER;
    partieJSON->pairs[6].value.numberValue = partie.mvEnnemic;

    return partieJSON;
}

void freeJSONObject(JSONObject * obj) { // fonction récursive pour se débarasser de tous les mallocs
    for(int i = 0; i < obj->length; i++) {
        if(obj->pairs[i].value.type == JSON_ARRAY) {
            for(int j = 0; j < obj->pairs[i].value.arrayValue->length; j++) {
                if(obj->pairs[i].value.arrayValue->values[j].value.type == JSON_OBJECT) {
                    freeJSONObject(obj->pairs[i].value.arrayValue->values[j].value.objectValue);
                }
            }
            free(obj->pairs[i].value.arrayValue->values);
            free(obj->pairs[i].value.arrayValue);
        }
        if(obj->pairs[i].value.type == JSON_OBJECT) {
            freeJSONObject(obj->pairs[i].value.objectValue);
        }
    }
    free(obj->pairs);
    free(obj);
}

void saveGame(Partie partie) {
    JSONObject * partieJSON = partieToJSONObj(partie);
    char * serialized = serializeJSONObject(*partieJSON);
    FILE * save = fopen("save.json", "w");
    if(save == NULL) {
        logMessage(ERROR, "erreur ouverture fichier save.json");
        exit(1);
    }
    fprintf(save, "%s", serialized);
    fclose(save);
    free(serialized);
    freeJSONObject(partieJSON);
}

Partie * loadGame() {
    FILE * save = fopen("save.json", "r");
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
    if(buffer == NULL) {
        logMessage(ERROR, "erreur malloc buffer loadGame");
        exit(1);
    }
    // lecture du fichier
    fread(buffer, 1, fsize, save);
    fclose(save);
    buffer[fsize] = '\0'; // ajout du caractère de fin de chaine
    // creation JSONObject
    JSONObject * partieJSON = parseJSONObject(&buffer);
    Partie * partie = malloc(sizeof(Partie));
    if(partie == NULL) {
        logMessage(ERROR, "erreur malloc partie loadGame");
        exit(1);
    }

    partie = partieFromJSONObj(*partieJSON);
    // libération de la mémoire
    //free(buffer);
    freeJSONObject(partieJSON);
    return partie;
}

