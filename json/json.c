//
// Created by valerie on 19/05/24.
// parseur/serializer JSON basique, ne respecte pas completement la norme JSON.
//

// json.c
#include "json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../logger.h"


char * sauteEspaces(char *str) { // ignore les espaces
    while(isspace(*str)) {
        str++;
    }
    return str;
}

int chercheChar(char **str, char chr) { // place le caractère recherché en index 0 de la chaine de caractères
    *str = sauteEspaces(*str);
    if (**str == chr) {
        (*str)++;
        return 1;
    }
    return 0;
}

int longueurInt(int i) { // retourne la longueur d'un entier, plus rapide que log10()
    if(i < 0) {
        i = -i;
    }
    if (i >= 1000000000) {
        return 10;
    }
    if (i >= 100000000) {
        return 9;
    }
    if (i >= 10000000) {
        return 8;
    }
    if (i >= 1000000) {
        return 7;
    }
    if (i >= 100000) {
        return 6;
    }
    if (i >= 10000) {
        return 5;
    }
    if (i >= 1000) {
        return 4;
    }
    if (i >= 100) {
        return 3;
    }
    if (i >= 10) {
        return 2;
    }
    return 1;
}

char * parserChaineJSON(char **str) {
    *str = sauteEspaces(*str);
    if (**str != '"') { // pas une chaine de caractères
        return NULL;
    }
    (*str)++;
    char *start = *str;
    while (**str != '\0' && **str != '"') { // parcoure toute la chaine
        (*str)++;
    }
    if (**str != '"') {
        return NULL;
    }
    int length = *str - start; // longueur de la chaine

    char * result = NULL;
    result = malloc(length + 1);
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result parserChaineJSON");
        exit(1);
    }

    strncpy(result, start, length); // copie la chaine de caractères
    result[length] = '\0';
    (*str)++; // avance le pointeur
    return result;
}

int parserEntierJSON(char **str, int sign) {
    *str = sauteEspaces(*str);
    int result;
    int verif = -1;
    verif = sscanf(*str, "%d", &result);
    if(verif != 1) {
        logMessage(CRITICAL, "erreur sscanf parserEntierJSON");
    }
    while(isdigit(**str)) { // parcoure tout le nombre
        (*str)++;
    }
    if (!sign) { // passage au négatif si présence d'un - avant le nombre
        result = -result;
    }
    return result;
}

int parserBooleenJSON(char **str) {
    *str = sauteEspaces(*str);
    if (strncmp(*str, "true", 4) == 0) {
        *str += 4;
        return 1;
    } else if (strncmp(*str, "false", 5) == 0) {
        *str += 5;
        return 0;
    }
    logMessage(CRITICAL, "erreur parse parserBooleenJSON");
    return -1; // Erreur
}

JSONArray * parserTabJSON(char **str) {
    if (!chercheChar(str, '[')) {
        logMessage(CRITICAL, "erreur parserTabJSON, [ manquant");
        exit(1); // Erreur
    }
    JSONArray * array = NULL;
    array = malloc(sizeof(JSONArray));
    if(array == NULL) {
        logMessage(CRITICAL, "erreur malloc array parserTabJSON");
        exit(1);
    }
    array->values = NULL;
    array->length = 0;

    while (!chercheChar(str, ']')) {
        JSONCleValeurCouple pair; //creation du couple clé-valeur
        pair.value = parserValeurJSON(str);
        array->values = realloc(array->values, sizeof(JSONCleValeurCouple) * (array->length + 1)); // agrandit l'allocation mémoire des valeurs
        if(array->values == NULL) {
            logMessage(CRITICAL, "erreur realloc array parserTabJSON");
            exit(1);
        }
        array->values[array->length++] = pair;
        chercheChar(str, ','); // avance à la virgule suivante
    }

    return array;

}

JSONValeur parserValeurJSON(char **str) { // parse une valeur JSON
    *str = sauteEspaces(*str);
    JSONValeur v;
    if (**str == '"') {
        v.type = JSON_CHAINE;
        v.stringValue = parserChaineJSON(str);
    } else if (**str == '{') {
        v.type = JSON_OBJET;
        v.objectValue = parserObjetJSON(str);
    } else if (**str == '[') {
        v.type = JSON_TABLEAU;
        v.arrayValue = parserTabJSON(str);
    } else if (**str == '-') {
        (*str)++;
        v.type = JSON_NOMBRE;
        v.numberValue = parserEntierJSON(str, 0);
    } else if (isdigit(**str)) {
        v.type = JSON_NOMBRE;
        v.numberValue = parserEntierJSON(str, 1);
    } else if (strncmp(*str, "true", 4) == 0 || strncmp(*str, "false", 5) == 0) {
        v.type = JSON_BOOL;
        v.boolValue = parserBooleenJSON(str);
    } else {
        logMessage(CRITICAL, "erreur parserValeurJSON");
        v.type = JSON_NULL; // Erreur
    }
    return v;
}



JSONObjet * parserObjetJSON(char ** str) {
    if (!chercheChar(str, '{')) { // vérifie la présence de l'accolade
        logMessage(CRITICAL, "erreur parserObjetJSON, { manquant");
        exit(1); // Erreur
    }
    JSONObjet * object = NULL; // creation de l'objet
    object = malloc(sizeof(JSONObjet));
    if(object == NULL) {
        logMessage(CRITICAL, "erreur malloc object parserObjetJSON");
        exit(1);
    }
    object->pairs = NULL;
    object->length = 0;

    while (!chercheChar(str, '}')) {
        JSONCleValeurCouple pair;
        pair.key = parserChaineJSON(str);
        if (!pair.key || !chercheChar(str, ':')) {
            free(object);
            logMessage(CRITICAL, "erreur parserObjetJSON, : manquant");
            exit(1); // Erreur
        }
        pair.value = parserValeurJSON(str);
        object->pairs = realloc(object->pairs, sizeof(JSONCleValeurCouple) * (object->length + 1)); // agrandit l'allocation mémoire  des couples clé-valeur
        if(object->pairs == NULL) {
            logMessage(CRITICAL, "erreur realloc object parserObjetJSON");
            exit(1);
        }
        object->pairs[object->length++] = pair;
        chercheChar(str, ','); // avance à la virgule suivante
    }
    return object;
}

char * serializeChaineJSON(JSONValeur str) {
    char * result = NULL; // chaine de caractères finale
    result = malloc(strlen(str.stringValue) + 3); // + guillemets et \0
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeChaineJSON");
        exit(1);
    }
    sprintf(result, "\"%s\"", str.stringValue);
    return result;
}

char * serializeEntierJSON(JSONValeur i) {
    char * result = NULL; // chaine de caractères finale
    result = malloc(sizeof(char) * longueurInt(i.numberValue) + 1);
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeEntierJSON");
        exit(1);
    }
    sprintf(result, "%d", i.numberValue);
    return result;
}

char * serializeBooleenJSON(JSONValeur b) {
    char * result = NULL; // chaine de caractères finale
    result = malloc(sizeof(char) * 6); // true ou false
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeBooleenJSON");
        exit(1);
    }
    if (b.boolValue) {
        sprintf(result, "true");
    } else {
        sprintf(result, "false");
    }
    return result;
}

char * serializeTabJSON(JSONArray a) {
    char * result = NULL; // chaine de caractères finale
    char * finalString = NULL; // chaine de caractères finale avec les crochets
    char * value = NULL; // chaine de caractères temporaire

    result = malloc(sizeof(char));
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeTabJSON");
        exit(1);
    }
    result[0] = '\0';
    for (int i = 0; i < a.length; i++) {
        switch (a.values[i].value.type) { // assigne la valeur en fonction du type
            case JSON_CHAINE:
                value = serializeChaineJSON(a.values[i].value);
                break;
            case JSON_NOMBRE:
                value = serializeEntierJSON(a.values[i].value);
                break;
            case JSON_BOOL:
                value = serializeBooleenJSON(a.values[i].value);
                break;
            case JSON_OBJET:
                value = serializeObjetJSON(*a.values[i].value.objectValue);
                break;
            case JSON_TABLEAU:
                value = serializeTabJSON(*a.values[i].value.arrayValue);
                break;
            default:
                logMessage(CRITICAL, "erreur serializeTabJSON");
                exit(1);
        }
        result = realloc(result, strlen(result) + strlen(value) + 2);
        if(result == NULL) {
            logMessage(CRITICAL, "erreur realloc result serializeTabJSON");
            exit(1);
        }
        strcat(result, value);
        if (i < a.length - 1) {
            result = realloc(result, strlen(result) + 2); // agrandit l'allocation suivant les données restantes
            if(result == NULL) {
                logMessage(CRITICAL, "erreur realloc result serializeTabJSON");
                exit(1);
            }
            strcat(result, ",");
        }
        free(value);
    }
    finalString = malloc(strlen(result) + 3); // + crochets et \0
    if (finalString == NULL) {
        logMessage(CRITICAL, "erreur malloc finalResult serializeTabJSON");
        exit(1);
    }
    sprintf(finalString, "[%s]", result); // ajoute les crochets
    free(result);
    return finalString;
}

char * serializeObjetJSON(JSONObjet o) {
    char * result = NULL;
    char * value = NULL;
    char * finalString = NULL;

    result = malloc(sizeof(char));
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeObjetJSON");
        exit(1);
    }
    result[0] = '\0';
    for (int i = 0; i < o.length; i++) {
        switch (o.pairs[i].value.type) { // assigne la valeur en fonction du type
            case JSON_CHAINE:
                value = serializeChaineJSON(o.pairs[i].value);
                break;
            case JSON_NOMBRE:
                value = serializeEntierJSON(o.pairs[i].value);
                break;
            case JSON_BOOL:
                value = serializeBooleenJSON(o.pairs[i].value);
                break;
            case JSON_OBJET:
                value = serializeObjetJSON(*o.pairs[i].value.objectValue);
                break;
            case JSON_TABLEAU:
                value = serializeTabJSON(*o.pairs[i].value.arrayValue);
                break;
            default: // type non reconnu
                logMessage(CRITICAL, "erreur serializeObjetJSON");
                exit(1);
        }
        result = realloc(result, strlen(result) + strlen(o.pairs[i].key) + strlen(value) + 5);
        if(result == NULL) {
            logMessage(CRITICAL, "erreur realloc result serializeObjetJSON");
            exit(1);
        }
        // ajout de la clé / formattage
        strcat(result, "\"");
        strcat(result, o.pairs[i].key);
        strcat(result, "\":");
        strcat(result, value); // ajout de la valeur
        if (i < o.length - 1) {
            result = realloc(result, strlen(result) + 2);
            if(result == NULL) {
                logMessage(CRITICAL, "erreur realloc result serializeObjetJSON");
                exit(1);
            }
            strcat(result, ",");
        }
        free(value);
    }

    finalString = malloc(strlen(result) + 3); // + accolades et \0
    if (finalString == NULL) {
        logMessage(CRITICAL, "erreur malloc finalString serializeObjetJSON");
        exit(1);
    }
    sprintf(finalString, "{%s}", result); // ajoute les accolades
    free(result); // libere la mémoire
    return finalString;
}

