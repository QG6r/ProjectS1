#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASH_SEED 5381

static char *my_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy)
        memcpy(copy, s, len);
    return copy;
}

static unsigned long hash_string(const char *str) {
    unsigned long hash = HASH_SEED;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

HashMap *hashmap_create(size_t capacity) {
    HashMap *map = malloc(sizeof(HashMap));
    map->capacity = capacity;
    map->size = 0;
    map->buckets = calloc(capacity, sizeof(HashNode *));
    return map;
}

void hashmap_insert(HashMap *map, const char *key, void *value) {
    unsigned long hash = hash_string(key) % map->capacity;
    HashNode *node = map->buckets[hash];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }

    HashNode *new_node = malloc(sizeof(HashNode));
    new_node->key = my_strdup(key);
    new_node->value = value;
    new_node->next = map->buckets[hash];
    map->buckets[hash] = new_node;
    map->size++;
}

void *hashmap_get(HashMap *map, const char *key) {
    unsigned long hash = hash_string(key) % map->capacity;
    HashNode *node = map->buckets[hash];
    while (node) {
        if (strcmp(node->key, key) == 0)
            return node->value;
        node = node->next;
    }
    return NULL;
}

int hashmap_exists(HashMap *map, const char *key) {
    return hashmap_get(map, key) != NULL;
}

void hashmap_delete(HashMap *map, const char *key) {
    unsigned long hash = hash_string(key) % map->capacity;
    HashNode *node = map->buckets[hash];
    HashNode *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev)
                prev->next = node->next;
            else
                map->buckets[hash] = node->next;

            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

void hashmap_destroy(HashMap *map) {
    for (size_t i = 0; i < map->capacity; i++) {
        HashNode *node = map->buckets[i];
        while (node) {
            HashNode *next = node->next;
            free(node->key);      // key freed
            free(node);           // node freed
            node = next;
        }
    }
    free(map->buckets);
    free(map);
}
