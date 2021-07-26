#ifndef LUT_H
#define LUT_H

#include <stdint.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define CREATE_LUT(name, size) Pair name[size]

typedef struct Pair {
    char key[16];
    int value; 
} Pair;

void insert_opcode(Pair* table, const size_t size, 
                   const char* key, const int value);

int get_opcode(Pair* table, const size_t size, const char* key);

#endif