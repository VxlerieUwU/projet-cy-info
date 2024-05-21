//
// Created by valerie on 19/05/24.
//

// json.h
#ifndef JSON_H
#define JSON_H

typedef enum {
    JSON_STRING,
    JSON_NUMBER,
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_BOOL,
    JSON_NULL,
}JSONType;


typedef struct {
    JSONType type;
    union {
        char *stringValue;
        int numberValue;
        int boolValue;
        struct JSONObject *objectValue;
        struct JSONArray *arrayValue;
    };
} JSONValue;

// Structure pour une paire clé-valeur d'un objet JSON
typedef struct JSONKeyValuePair {
    char *key;
    JSONValue value;
} JSONKeyValuePair;

// Structure pour un objet JSON
typedef struct JSONObject {
    JSONKeyValuePair *pairs;
    int length;
} JSONObject;

// Structure pour un tableau JSON
typedef struct JSONArray {
    JSONKeyValuePair *values;
    int length;
} JSONArray;

JSONObject * parseJSONObject(char **str);
JSONValue parseJSONValue(char **str);
JSONArray * parseJSONArray(char **str);
int parseJSONBool(char **str);
int parseJSONInt(char **str);
char * parseJSONString(char **str);
int chrLookup(char **str, char chr);
char * skipSpaces(char *str);

char * serializeJSONObject(JSONObject o);
char * serializeJSONArray(JSONArray a);
char * serializeJSONBool(JSONValue b);
char * serializeJSONInt(JSONValue i);
#endif // JSON_H
