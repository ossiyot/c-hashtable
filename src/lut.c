#include "lut.h"
#include <limits.h>
#include <stdint.h>
#include <string.h>

#define FNV_OFFSET 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/**
 * @brief FNV-1a hash function
 *
 * @param str string to be hashed
 *
 * @return hash value
 */
static inline uint64_t fnv1a_hash(const char *str) {
    uint64_t hash = FNV_OFFSET;
    for (const char *p = str; *p; ++p) {
        hash ^= (uint64_t)(uint8_t)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

/**
 * @brief dfb2 hash function
 *
 * @param str string to be hashed
 *
 * @return hash value
 */
static inline uint64_t djb2(const unsigned char *str) {
    uint64_t hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int lut_insert(Pair *table, const size_t size, const char *key,
                const int value) {
    uint64_t hash = djb2(key);
    const size_t index = (size_t)hash % size;

    // Try positions from index -> end
    for (size_t i = index; i < size; ++i) {
        if (!table[i].taken) {
            table[i].key = hash;
            table[i].value = value;
            table[i].taken = 1;
            return 0;
        }
    }

    // Try positions 0 -> index
    for (unsigned int i = 0; i < index; ++i) {
        if (!table[i].taken) {
            table[i].key = hash;
            table[i].value = value;
            table[i].taken = 1;
            return 0;
        }
    }
    // If there isn't enough space return -1
    return -1;
}

int lut_get(Pair *table, const size_t size, const char *key, int* out) {
    uint64_t hash = djb2(key);
    const size_t index = ((size_t)hash) % size;

    // Search positions from index -> end
    for (size_t i = index; i < size; ++i) {
        if (table[i].key == hash) {
            *out = table[i].value;
            return 0;
        }
    }
    // Search positions 0 -> index
    for (unsigned int i = 0; i < index; ++i) {
        if (table[i].key == hash) {
            *out = table[i].value;
            return 0;
        }
    }
    // We didn't find key, return -1
    return -1;
}

int lut_fill(Pair *table, const size_t size, const char *const r_table[],
              const size_t r_size) {
    // Add all keys from r_table or until lookup table is full
    for (size_t i = 0; i < MIN(r_size, size); i++) {
        lut_insert(table, size, r_table[i], i);
    }
    return r_size < size ? 0 : -1;
}