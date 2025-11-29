#include <string.h>
#include "hash.h"

// Polynomial rolling hash: O(n), stable, integer-safe
int Hash(const char *s, int a, int m) {
    long hash = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        hash = (hash * a + s[i]) % m;
    }

    return (int)hash;
}