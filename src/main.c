
#include "lut.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))

typedef enum OPCODE {
    NOP,
    MOV
} OPCODE;

const char* const op2str[] = {
    [NOP] = "nop",
    [MOV] = "mov"
};

int main() {
    CREATE_LUT(str2op, 32);

    lut_fill(str2op.table, str2op.size, op2str, ARRAY_SIZE(op2str));

    printf("nop: %s\n", op2str[lut_get(str2op.table, str2op.size, "nop")]);
    printf("mov: %s\n", op2str[lut_get(str2op.table, str2op.size, "mov")]);

    return EXIT_SUCCESS;
}