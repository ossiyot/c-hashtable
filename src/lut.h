#ifndef LUT_H
#define LUT_H

#include <stdint.h>

#define CREATE_LUT(name, lut_size) struct {                \
                                    Pair table[lut_size];   \
                                    const size_t size;            \
                                    } name = {.size = lut_size}


#define LUT_MAX_KEY_SIZE 16
typedef struct Pair {
    char key[LUT_MAX_KEY_SIZE];
    int value; 
} Pair;

void lut_insert(Pair* table, const size_t size, 
                   const char* key, const int value);
int lut_get(Pair* table, const size_t size, const char* key);
void lut_fill(Pair* table, const size_t size,
              const char* const r_table[], const size_t r_size);

#endif