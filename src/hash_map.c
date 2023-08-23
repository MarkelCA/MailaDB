#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./hash_map.h"


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

const char *get_hash_map_value(HashMap *map, const char *key) {
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

void print_hash_map(HashMap *map) {
    _print_hash_map(map, true);
}

void print_hash_map_keys(HashMap *map) {
    _print_hash_map(map, false);
}

void _print_hash_map(HashMap *map, bool print_values) {
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
//     insert_map(&my_map, "foo", "bar");
//     insert_map(&my_map, "fizz", "buzz");
//     insert_map(&my_map, "x", "y");
//
//     insert_map(&my_map, "apple", "value1");
//     insert_map(&my_map, "banana", "value3");
//
//     print_hash_map_keys(&my_map);
//
//     free_hash_map(&my_map);
// }
