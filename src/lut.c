#include "lut.h"
#include <string.h>
#include <stdint.h>

#define FNV_OFFSET 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL

static inline uint64_t fnv1a_hash(const char* str) {
    uint64_t hash = FNV_OFFSET;
    for(const char* p = str; *p; ++p) {
        hash ^= (uint64_t)(uint8_t)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

void lut_insert(Pair* table, const size_t size, 
                   const char* key, const int value) {                      
    uint64_t hash = fnv1a_hash(key);
    const size_t index =  (size_t)hash % size;

    for (size_t i = index; i < size; ++i) {
        if (!(*table[i].key)) {
            strcpy_s(table[i].key, LUT_MAX_KEY_SIZE, key);
            table[i].value = value;
            return;
        }
    }

    for (unsigned int i = 0; i < index; ++i) {
        if (!(*table[i].key)) {
            strcpy_s(table[i].key, LUT_MAX_KEY_SIZE, key);
            table[i].value = value;
            return;
        }
    }
}

int lut_get(Pair* table, const size_t size, const char* key) {
    uint64_t hash = fnv1a_hash(key);
    const size_t index = (size_t)hash % size;

    for (size_t i = index; i < size; ++i) {
        if (strcmp(table[i].key, key) == 0) {
            return table[i].value;
        }
    }

    for (unsigned int i = 0; i < index; ++i) {
        if (strcmp(table[i].key, key) == 0) {
            return table[i].value;
        }
    }
    return -1;
}

void lut_fill(Pair* table, const size_t size,
              const char* const r_table[], const size_t r_size) {
    for (size_t i = 0; i < r_size; i++) {
        lut_insert(table, size, r_table[i], i);
    }
}