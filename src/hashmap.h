#ifndef HASHMAP_H
#define HASHMAP_H

#define HASH_TABLE_SIZE 100

typedef struct Map {
    char *key;
    char *value;
    struct Map *next;
} Map;

typedef struct {
    Map *buckets[HASH_TABLE_SIZE];
} HashMap;

unsigned int hash_function(const char *key);
Map *create_map(const char *key, const char *value);
void insert_map(HashMap *map, const char *key, const char *value);
const char *get_value(HashMap *map, const char *key);
void free_hash_map(HashMap *map);

#endif // HASHMAP_H

