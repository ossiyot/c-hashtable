#ifndef LUT_H
#define LUT_H

#include <stdint.h>

/**
 * @brief Hashtable struct
 */
typedef struct Hashtable {
    size_t size;
    uint64_t* keys;
    int* values;
    int* taken;
} Hashtable;

/**
 * @brief Macro to create underlying struct for hashtable
 *
 * @param name variable name of the hashtable
 * @param table_size size of the hashtable
 */
#define CREATE_HASHTABLE(name, table_size)                                     \
    struct {                                                                   \
        uint64_t keys[table_size];                                             \
        int values[table_size];                                                \
        int taken[table_size];                                                 \
        const size_t size;                                                     \
    } name##_s = {.size = table_size};                                         \
    Hashtable name = {.size = table_size,                                      \
                      .keys = name##_s.keys,                                   \
                      .values = name##_s.values,                               \
                      .taken = name##_s.taken}

/**
 * @brief Insert key-value pair into hashtable
 *
 * @param table hashtable to be inserted into
 * @param key key to be inserted
 * @param value value to be inserted
 *
 * @return 0 if succeeded, else -1
 */
int lut_insert(Hashtable* table, const char* key, int value);

/**
 * @brief Get associated value for key from hashtable
 *
 * @param table hashtable to get value from
 * @param key key for lookup
 * @param out value from hashtable
 *
 * @return 0 if found, else -1
 */
int lut_get(Hashtable* table, const char* key, int* out);

/**
 * @brief Fill lookup table with reverse table (integers mapped to strings)
 *
 * @param table hashtable to fill
 * @param r_table array of strings
 * @param r_size size of \p r_table
 *
 * @return 0 if all elements got inserted, else -1
 */
int lut_fill(Hashtable* table, const char* const r_table[], size_t r_size);

#endif