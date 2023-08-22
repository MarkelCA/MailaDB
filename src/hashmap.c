#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./hashmap.h"


unsigned int hash_function(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % HASH_TABLE_SIZE;
}

Map *create_map(const char *key, const char *value) {
    Map *kv = (Map *)malloc(sizeof(Map));
    kv->key = strdup(key);
    kv->value = strdup(value);
    kv->next = NULL;
    return kv;
}

void insert_map(HashMap *map, const char *key, const char *value) {
    unsigned int index = hash_function(key);
    Map *kv = create_map(key, value);

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

const char *get_value(HashMap *map, const char *key) {
    unsigned int index = hash_function(key);
    Map *current = map->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

void free_hash_map(HashMap *map) {
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

// int main() {
//     // printf("%i", hash_function("a"));
//     HashMap my_map;
//     memset(&my_map, 0, sizeof(HashMap));
//
//     insert_map(&my_map, "foo", "bar");
//     insert_map(&my_map, "fizz", "buzz");
//     insert_map(&my_map, "x", "y");
//
//     printf("foo: %s\n", get_value(&my_map, "foo"));
//     printf("fizz: %s\n", get_value(&my_map, "fizz"));
//     printf("x: %s\n", get_value(&my_map, "x"));
//
//     free_hash_map(&my_map);
//
//     // return 0;
// }
