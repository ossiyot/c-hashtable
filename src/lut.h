#ifndef LUT_H
#define LUT_H

#include <stdint.h>

typedef struct Hashtable {
    size_t size;
    uint64_t* keys;
    int* values;
    int* taken;
} Hashtable;

/**
 * Macro to create variable size lookup table at compile time
 */
#define CREATE_LUT(name, lut_size)                                             \
    struct {                                                                   \
        uint64_t keys[lut_size];                                               \
        int values[lut_size];                                                  \
        int taken[lut_size];                                                   \
        const size_t size;                                                     \
    } name##_s = {.size = lut_size};                                           \
    Hashtable name = {.size = lut_size,                                        \
                      .keys = name##_s.keys,                                   \
                      .values = name##_s.values,                               \
                      .taken = name##_s.taken}

//
#define LUT_MAX_KEY_SIZE 16

/**
 * @brief Insert key-value pair into lookup table
 *
 * @param table table of the lookup table
 * @param size size of the lookup table
 * @param key key to be inserted
 * @param value value to be inserted
 *
 * @return 0 if succeeded, else -1
 */
int lut_insert(Hashtable* table, const char* key, int value);

/**
 * @brief Get value of key from lookup table
 *
 * @param table table of the lookup table
 * @param size size of the lookup table
 * @param key key for lookup
 * @param out value from table
 *
 * @return 0 if found, else -1
 */
int lut_get(Hashtable* table, const char* key, int* out);

/**
 * @brief Fill lookup table with reverse table (integers mapped to strings)
 *
 * @param table table of the lookup table
 * @param size size of the lookup table
 * @param r_table array of strings
 * @param r_size size of \p r_table
 *
 * @return 0 if all elements got inserted, else -1
 */
int lut_fill(Hashtable* table, const char* const r_table[], size_t r_size);

#endif