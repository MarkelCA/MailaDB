#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "./hashmap.h"


void _hashmap_print(HashMap *map, bool print_values);

unsigned int hashmap_hash_function(const char *key, uint size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % size;
}

Map *hashmap_create_map(const char *key, const char *value) {
    Map *kv = (Map *)malloc(sizeof(Map));
    kv->key = strdup(key);
    kv->value = strdup(value);
    kv->next = NULL;
    return kv;
}

void hashmap_insert(HashMap *map, const char *key, const char *value) {
    unsigned int index = hashmap_hash_function(key, map->size);
    Map *kv = hashmap_create_map(key, value);

    if (map->buckets[index] == NULL) {
        map->buckets[index] = kv;
    } else {
        Map *current = map->buckets[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = kv;
    }
}

const char *hashmap_get(HashMap *map, const char *key) {
    unsigned int index = hashmap_hash_function(key, map->size);
    Map *current = map->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

void hashmap_free(HashMap *map) {
    for (int i = 0; i < map->size; i++) {
        Map *current = map->buckets[i];
        while (current != NULL) {
            Map *temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
}

void hashmap_print(HashMap *map) {
    _hashmap_print(map, true);
}

char* hashmap_get_keys(HashMap *map) {
    Map *current_map;
    uint lenght = 0;
    char* result;
    char* current_result;
    result = (char*) calloc(sizeof(char), 1);
    for (int i = 0; i < map->size; i++) {
        current_map = map->buckets[i];

        while (current_map != NULL) {
            char* current_value = current_map->key;
            lenght = strlen(result) + strlen(current_value);
            current_result = realloc(result,  sizeof(char) * lenght + 1); // +1 for the \n

            strcat(current_result, current_map->key);
            strcat(current_result, "\n");

            current_map = current_map->next;
            result = current_result;
        }
    }

    return result;
}

void hashmap_print_keys(HashMap *map) {
    _hashmap_print(map, false);
}

void _hashmap_print(HashMap *map, bool print_values) {
    Map *current;
    for (int i = 0; i < map->size; i++) {
        current = map->buckets[i];

        while (current != NULL) {
            if(print_values == true) {
                printf("%s -> %s\n", current->key, current->value);
            } else {
                printf("%s\n", current->key);
            }
            current = current->next;
        }
    }
}

HashMap* hashmap_create(uint size) {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (Map **)calloc(size, sizeof(Map *));
    map->size = size;
    return map;
}

