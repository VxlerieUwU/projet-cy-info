//
// Created by valerie on 19/05/24.
//

// json.h
#ifndef JSON_H
#define JSON_H

typedef enum {
    JSON_CHAINE,
    JSON_NOMBRE,
    JSON_OBJET,
    JSON_TABLEAU,
    JSON_BOOL,
    JSON_NULL,
}JSONType;


typedef struct {
    JSONType type;
    union {
        char *stringValue;
        int numberValue;
        int boolValue;
        struct JSONObjet *objectValue;
        struct JSONArray *arrayValue;
    };
} JSONValeur;

// Structure pour une paire clé-valeur d'un objet JSON
typedef struct JSONCleValeurCouple {
    char *key;
    JSONValeur value;
} JSONCleValeurCouple;

// Structure pour un objet JSON
typedef struct JSONObjet {
    JSONCleValeurCouple *pairs;
    int length;
} JSONObjet;

// Structure pour un tableau JSON
typedef struct JSONArray {
    JSONCleValeurCouple *values;
    int length;
} JSONArray;

JSONObjet * parserObjetJSON(char **str);
JSONValeur parserValeurJSON(char **str);
JSONArray * parserTabJSON(char **str);
int parserBooleenJSON(char **str);
int parserEntierJSON(char **str, int sign);
char * parserChaineJSON(char **str);
int chercheChar(char **str, char chr);
char * sauteEspaces(char *str);
int longueurInt(int i);

char * serializeObjetJSON(JSONObjet o);
char * serializeTabJSON(JSONArray a);
char * serializeBooleenJSON(JSONValeur b);
char * serializeEntierJSON(JSONValeur i);
#endif // JSON_H
