
#include "lut.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

    lut_insert(str2op.table, str2op.size, "nop", NOP);
    lut_insert(str2op.table, str2op.size, "mov", MOV);

    printf("nop: %s\n", op2str[lut_get(str2op.table, str2op.size, "nop")]);
    printf("mov: %s\n", op2str[lut_get(str2op.table, str2op.size, "mov")]);

    return EXIT_SUCCESS;
}