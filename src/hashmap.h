#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

typedef struct HashNode {
    char *key;
    void *value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **buckets;
    size_t capacity;
    size_t size;
} HashMap;

HashMap *hashmap_create(size_t capacity);
void hashmap_insert(HashMap *map, const char *key, void *value);
void *hashmap_get(HashMap *map, const char *key);
int hashmap_exists(HashMap *map, const char *key);
void hashmap_delete(HashMap *map, const char *key);
void hashmap_destroy(HashMap *map);

#endif

