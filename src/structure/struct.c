#include <stdlib.h>
#include <string.h>
#include "struct.h"

static const uint32_t INITIAL_CAPACITY = 53;

static HashNode *CreateNode(const char *key, const char *value) {
    if (key == NULL || value == NULL) {
        return NULL;
    }

    HashNode *node = malloc(sizeof(HashNode));
    if (node == NULL) {
        return NULL;
    }

    node->key = strdup(key);
    node->value = strdup(value);

    if (node->key == NULL || node->value == NULL) {
        free(node->key);
        free(node->value);
        free(node);
        return NULL;
    }

    return node;
}

HashTable *CreateHashTable(void) {
    HashTable *table = malloc(sizeof(HashTable));
    if (table == NULL) {
        return NULL;
    }

    table->capacity = INITIAL_CAPACITY;
    table->size = 0;

    table->buckets = calloc(table->capacity, sizeof(HashNode *));
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }

    return table;
}