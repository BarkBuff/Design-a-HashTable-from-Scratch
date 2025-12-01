#include <stdlib.h>
#include <string.h>
#include "struct.h"

static const uint32_t INITIAL_CAPACITY = 53;
static HashNode HT_DELETED_NODE = { NULL, NULL }; /* Global tombstone sentinel */

#define HT_PRIME_1 151
#define HT_PRIME_2 163

/* Polynomial rolling hash */
static int Hash(const char *s, int a, int m) {
    long hash = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        hash = (hash * a + s[i]) % m;
    }

    return (int)hash;
}

/* Double hashing: hash_a + attempt*(hash_b+1) */
static int GetHash(const char *s, int num_buckets, int attempt) {
    int hash_a = Hash(s, HT_PRIME_1, num_buckets);
    int hash_b = Hash(s, HT_PRIME_2, num_buckets);

    return (hash_a + attempt * (hash_b + 1)) % num_buckets;
}

/* Allocate a new key-value pair */
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

/* Destroy a node (skip tombstone) */
static void DeleteNode(HashNode *node) {
    if (node == NULL || node == &HT_DELETED_NODE) {
        return;
    }

    free(node->key);
    free(node->value);
    free(node);
}

/* Create an empty hash table */
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

/* Destroy the entire hash table */
void DeleteHashTable(HashTable *table) {
    if (table == NULL) {
        return;
    }

    for (uint32_t i = 0; i < table->capacity; i++) {
        HashNode *node = table->buckets[i];
        if (node != NULL && node != &HT_DELETED_NODE) {
            DeleteNode(node);
        }
    }

    free(table->buckets);
    free(table);
}

/* Insert or update a key */
void Insert(HashTable *table, const char *key, const char *value) {
    HashNode *node = CreateNode(key, value);
    if (node == NULL) {
        return;
    }

    int attempt = 0;
    int index = GetHash(key, table->capacity, attempt);

    int first_tombstone = -1;
    HashNode *cur = table->buckets[index];

    while (cur != NULL) {

        /* Remember the first tombstone */
        if (cur == &HT_DELETED_NODE && first_tombstone == -1) {
            first_tombstone = index;
        }

        /* Update if key already exists */
        if (cur != &HT_DELETED_NODE) {
            if (strcmp(cur->key, key) == 0) {
                DeleteNode(cur);
                table->buckets[index] = node;
                return;
            }
        }

        /* Continue probing */
        attempt++;
        index = GetHash(key, table->capacity, attempt);
        cur = table->buckets[index];
    }

    /* Insert into tombstone or null slot */
    if (first_tombstone != -1) {
        table->buckets[first_tombstone] = node;
    } else {
        table->buckets[index] = node;
    }

    table->size++;
}

/* Search for a key */
char *Search(HashTable *table, const char *key) {
    int attempt = 0;
    int index = GetHash(key, table->capacity, attempt);

    HashNode *node = table->buckets[index];

    while (node != NULL) {

        if (node != &HT_DELETED_NODE) {
            if (strcmp(node->key, key) == 0) {
                return node->value;
            }
        }

        attempt++;
        index = GetHash(key, table->capacity, attempt);
        node = table->buckets[index];
    }

    return NULL;
}

/* Logically delete a key using tombstone */
void Delete(HashTable *table, const char *key) {
    int attempt = 0;
    int index = GetHash(key, table->capacity, attempt);

    HashNode *node = table->buckets[index];

    while (node != NULL) {

        if (node != &HT_DELETED_NODE) {
            if (strcmp(node->key, key) == 0) {
                DeleteNode(node);
                table->buckets[index] = &HT_DELETED_NODE;
                table->size--;
                return;
            }
        }

        attempt++;
        index = GetHash(key, table->capacity, attempt);
        node = table->buckets[index];
    }
}