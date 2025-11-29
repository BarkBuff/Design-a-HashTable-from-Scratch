#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} HashNode;

typedef struct {
    uint32_t capacity;
    uint32_t size;
    HashNode **buckets;
} HashTable;