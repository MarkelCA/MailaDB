#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

#define HASH_TABLE_SIZE 100

typedef struct Map {
    char *key;
    char *value;
    struct Map *next; // Uses a linked list in case of hash collisions
} Map;

typedef struct {
    Map *buckets[HASH_TABLE_SIZE];
} HashMap;

unsigned int hashmap_hash_function(const char *key);
Map *hashmap_create(const char *key, const char *value);
void hashmap_insert(HashMap *map, const char *key, const char *value);
const char *hashmap_get(HashMap *map, const char *key);
void hashmap_free(HashMap *map);
void hashmap_print(HashMap *map);
void hashmap_print_keys(HashMap *map);
char* hashmap_get_keys(HashMap *map);

#endif // HASHMAP_H

