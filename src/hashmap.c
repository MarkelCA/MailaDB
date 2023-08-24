#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./hashmap.h"


void _hashmap_print(HashMap *map, bool print_values);

unsigned int hashmap_hash_function(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % HASH_TABLE_SIZE;
}

Map *hashmap_create(const char *key, const char *value) {
    Map *kv = (Map *)malloc(sizeof(Map));
    kv->key = strdup(key);
    kv->value = strdup(value);
    kv->next = NULL;
    return kv;
}

void hashmap_insert(HashMap *map, const char *key, const char *value) {
    unsigned int index = hashmap_hash_function(key);
    Map *kv = hashmap_create(key, value);

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
    unsigned int index = hashmap_hash_function(key);
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
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
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
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
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
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
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

// int main() {
//     HashMap my_map;
//     memset(&my_map, 0, sizeof(HashMap));
//
//     hashmap_insert(&my_map, "foo", "bar");
//     hashmap_insert(&my_map, "fizz", "buzz");
//     hashmap_insert(&my_map, "x", "y");
//
//     hashmap_insert(&my_map, "apple", "value1");
//     hashmap_insert(&my_map, "banana", "value2");
//
//     // hashmap_print_keys(&my_map);
//     // hashmap_print(&my_map);
//
//     printf("%s", hashmap_get_keys(&my_map));
//
//     hashmap_free(&my_map);
// }
