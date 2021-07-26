
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

    insert_opcode(str2op, ARRAY_SIZE(str2op), "nop", NOP);
    insert_opcode(str2op, ARRAY_SIZE(str2op), "mov", MOV);

    printf("nop: %s\n", op2str[get_opcode(str2op, ARRAY_SIZE(str2op), "nop")]);
    printf("mov: %s\n", op2str[get_opcode(str2op, ARRAY_SIZE(str2op), "mov")]);

    return EXIT_SUCCESS;
}