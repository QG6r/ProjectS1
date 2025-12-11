#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hashmap.h"

#define MAX_WORD 256

void clean_word(char *word) {
    int j = 0;
    for (int i = 0; word[i]; i++) {
        if (isalnum(word[i])) {
            word[j++] = tolower(word[i]);
        }
    }
    word[j] = '\0';
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error: input.txt not found.\n");
        return 1;
    }

    HashMap *map = hashmap_create(5000);

    char raw[MAX_WORD];

    while (fscanf(file, "%255s", raw) == 1) {
        clean_word(raw);

        if (strlen(raw) == 0) continue;

        int *count = hashmap_get(map, raw);

        if (count == NULL) {
            int *new_count = malloc(sizeof(int));
            *new_count = 1;
            hashmap_insert(map, raw, new_count);
        } else {
            (*count)++;
        }
    }

    fclose(file);

    printf("Word frequencies:\n");
    for (size_t i = 0; i < map->capacity; i++) {
        HashNode *node = map->buckets[i];
        while (node) {
            printf("%s: %d\n", node->key, *(int *)node->value);
            node = node->next;
        }
    }

    hashmap_destroy(map);
    return 0;
}
