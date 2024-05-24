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


char * skipSpaces(char *str) { // ignore les espaces
    while(isspace(*str)) {
        str++;
    }
    return str;
}

int chrLookup(char **str, char chr) { // place le caractère recherché en index 0 de la chaine de caractères
    *str = skipSpaces(*str);
    if (**str == chr) {
        (*str)++;
        return 1;
    }
    return 0;
}

int intLength(int i) { // retourne la longueur d'un entier, plus rapide que log10()
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

char * parseJSONString(char **str) {
    *str = skipSpaces(*str);
    if (**str != '"') { // pas une chaine de caractères
        return NULL;
    }
    (*str)++;
    char *start = *str;
    while (**str != '\0' && **str != '"') {
        (*str)++;
    }
    if (**str != '"') {
        return NULL;
    }
    int length = *str - start;

    char * result = NULL;
    result = malloc(length + 1);
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result parseJSONString");
        exit(1);
    }

    strncpy(result, start, length); // copie la chaine de caractères
    result[length] = '\0';
    (*str)++; // avance le pointeur
    return result;
}

int parseJSONInt(char **str) {
    *str = skipSpaces(*str);
    int result;
    int verif = -1;
    verif = sscanf(*str, "%d", &result);
    if(verif != 1) {
        logMessage(CRITICAL, "erreur sscanf parseJSONInt");
    }
    while(isdigit(**str)) { // déplace le curseur
        (*str)++;
    }

    return result;
}

int parseJSONBool(char **str) {
    *str = skipSpaces(*str);
    if (strncmp(*str, "true", 4) == 0) {
        *str += 4;
        return 1;
    } else if (strncmp(*str, "false", 5) == 0) {
        *str += 5;
        return 0;
    }
    logMessage(CRITICAL, "erreur parse parseJSONBool");
    return -1; // Erreur
}

JSONArray * parseJSONArray(char **str) {
    if (!chrLookup(str, '[')) {
        logMessage(CRITICAL, "erreur parseJSONArray, [ manquant");
        exit(1); // Erreur
    }
    JSONArray * array = NULL;
    array = malloc(sizeof(JSONArray));
    if(array == NULL) {
        logMessage(CRITICAL, "erreur malloc array parseJSONArray");
        exit(1);
    }
    array->values = NULL;
    array->length = 0;

    while (!chrLookup(str, ']')) {
        JSONKeyValuePair pair; //creation du couple clé-valeur
        pair.value = parseJSONValue(str);
        array->values = realloc(array->values, sizeof(JSONKeyValuePair) * (array->length + 1)); // agrandit l'allocation mémoire des valeurs
        array->values[array->length++] = pair;
        chrLookup(str, ','); // avance à la virgule suivante
    }

    return array;

}

JSONValue parseJSONValue(char **str) {
    *str = skipSpaces(*str);
    JSONValue v;
    if (**str == '"') {
        v.type = JSON_STRING;
        v.stringValue = parseJSONString(str);
    } else if (**str == '{') {
        v.type = JSON_OBJECT;
        v.objectValue = parseJSONObject(str);
    } else if (**str == '[') {
        v.type = JSON_ARRAY;
        v.arrayValue = parseJSONArray(str);
    } else if (isdigit(**str)) {
        v.type = JSON_NUMBER;
        v.numberValue = parseJSONInt(str);
    } else if (strncmp(*str, "true", 4) == 0 || strncmp(*str, "false", 5) == 0) {
        v.type = JSON_BOOL;
        v.boolValue = parseJSONBool(str);
    } else {
        logMessage(CRITICAL, "erreur parseJSONValue");
        v.type = JSON_NULL; // Erreur
    }
    return v;
}



JSONObject * parseJSONObject(char ** str) {
    if (!chrLookup(str, '{')) {
        logMessage(CRITICAL, "erreur parseJSONObject, { manquant");
        exit(1); // Erreur
    }
    JSONObject * object = NULL;
    object = malloc(sizeof(JSONObject));
    if(object == NULL) {
        logMessage(CRITICAL, "erreur malloc object parseJSONObject");
        exit(1);
    }
    object->pairs = NULL;
    object->length = 0;

    while (!chrLookup(str, '}')) {
        JSONKeyValuePair pair;
        pair.key = parseJSONString(str);
        if (!pair.key || !chrLookup(str, ':')) {
            free(object);
            logMessage(CRITICAL, "erreur parseJSONObject, : manquant");
            exit(1); // Erreur
        }
        pair.value = parseJSONValue(str);
        object->pairs = realloc(object->pairs, sizeof(JSONKeyValuePair) * (object->length + 1)); // agrandit l'allocation mémoire  des couples clé-valeur
        object->pairs[object->length++] = pair;
        chrLookup(str, ','); // avance à la virgule suivante
    }
    return object;
}

char * serializeJSONString(JSONValue str) {
    char * result = NULL;
    result = malloc(strlen(str.stringValue) + 3);
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeJSONString");
        exit(1);
    }
    sprintf(result, "\"%s\"", str.stringValue);
    return result;
}

char * serializeJSONInt(JSONValue i) {
    char * result = NULL;
    result = malloc(sizeof(char) * intLength(i.numberValue) + 1);
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeJSONInt");
        exit(1);
    }
    sprintf(result, "%d", i.numberValue);
    return result;
}

char * serializeJSONBool(JSONValue b) {
    char * result = NULL;
    result = malloc(sizeof(char) * 6);
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeJSONBool");
        exit(1);
    }
    if (b.boolValue) {
        sprintf(result, "true");
    } else {
        sprintf(result, "false");
    }
    return result;
}

char * serializeJSONArray(JSONArray a) {
    char * result = NULL;
    char * finalString = NULL;
    char * value = NULL;

    result = malloc(sizeof(char));
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeJSONArray");
        exit(1);
    }
    result[0] = '\0';
    for (int i = 0; i < a.length; i++) {
        switch (a.values[i].value.type) {
            case JSON_STRING:
                value = serializeJSONString(a.values[i].value);
                break;
            case JSON_NUMBER:
                value = serializeJSONInt(a.values[i].value);
                break;
            case JSON_BOOL:
                value = serializeJSONBool(a.values[i].value);
                break;
            case JSON_OBJECT:
                value = serializeJSONObject(*a.values[i].value.objectValue);
                break;
            case JSON_ARRAY:
                value = serializeJSONArray(*a.values[i].value.arrayValue);
                break;
            default:
                logMessage(CRITICAL, "erreur serializeJSONArray");
                exit(1);
        }
        result = realloc(result, strlen(result) + strlen(value) + 2);
        strcat(result, value);
        if (i < a.length - 1) {
            result = realloc(result, strlen(result) + 2); // agrandit l'allocation suivant les données restantes
            strcat(result, ",");
        }
        free(value);
    }
    finalString = malloc(strlen(result) + 3);
    if (finalString == NULL) {
        logMessage(CRITICAL, "erreur malloc finalResult serializeJSONArray");
        exit(1);
    }
    sprintf(finalString, "[%s]", result);
    free(result);
    return finalString;
}

char * serializeJSONObject(JSONObject o) {
    char * result = NULL;
    char * value = NULL;
    char * finalString = NULL;

    result = malloc(sizeof(char));
    if (result == NULL) {
        logMessage(CRITICAL, "erreur malloc result serializeJSONObject");
        exit(1);
    }
    result[0] = '\0';
    for (int i = 0; i < o.length; i++) {
        switch (o.pairs[i].value.type) {
            case JSON_STRING:
                value = serializeJSONString(o.pairs[i].value);
                break;
            case JSON_NUMBER:
                value = serializeJSONInt(o.pairs[i].value);
                break;
            case JSON_BOOL:
                value = serializeJSONBool(o.pairs[i].value);
                break;
            case JSON_OBJECT:
                value = serializeJSONObject(*o.pairs[i].value.objectValue);
                break;
            case JSON_ARRAY:
                value = serializeJSONArray(*o.pairs[i].value.arrayValue);
                break;
            default:
                logMessage(CRITICAL, "erreur serializeJSONObject");
                exit(1);
        }
        result = realloc(result, strlen(result) + strlen(o.pairs[i].key) + strlen(value) + 5);
        strcat(result, "\"");
        strcat(result, o.pairs[i].key);
        strcat(result, "\":");
        strcat(result, value);
        if (i < o.length - 1) {
            result = realloc(result, strlen(result) + 2);
            strcat(result, ",");
        }
        free(value);
    }

    finalString = malloc(strlen(result) + 3); // + accolades et \0
    if (finalString == NULL) {
        logMessage(CRITICAL, "erreur malloc finalString serializeJSONObject");
        exit(1);
    }
    sprintf(finalString, "{%s}", result); // ajoute les accolades
    free(result); // libere la mémoire
    return finalString;
}

