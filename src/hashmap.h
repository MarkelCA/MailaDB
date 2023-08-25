#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>
#include <sys/types.h>

// #define HASH_TABLE_SIZE 100

typedef struct Map {
    char *key;
    char *value;
    struct Map *next; // Uses a linked list in case of hash collisions
} Map;

typedef struct {
    Map **buckets;
    uint size;
} HashMap;

HashMap* hashmap_create(uint size);
unsigned int hashmap_hash_function(const char *key, uint size);
Map *hashmap_create_map(const char *key, const char *value);
void hashmap_insert(HashMap *map, const char *key, const char *value);
const char *hashmap_get(HashMap *map, const char *key);
void hashmap_free(HashMap *map);
void hashmap_print(HashMap *map);
void hashmap_print_keys(HashMap *map);
char* hashmap_get_keys(HashMap *map);

#endif // HASHMAP_H

