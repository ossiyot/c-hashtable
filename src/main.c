
#include "lut.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))

#define OPCODE_LIST \
    X(NOP)          \
    X(MOV)          \
    X(PUSH)         \
    X(POP)          \
    X(LEA)          \
    X(INC)          \
    X(DEC)          \
    X(ADD)          \
    X(SUB)          \
    X(MUL)          \
    X(DIV)          \
    X(AND)          \
    X(OR)           \
    X(XOR)          \
    X(NOT)          \
    X(NEG)          \
    X(SHL)          \
    X(SHR)          \
    X(JMP)          \
    X(CMP)          \
    X(JE)           \
    X(JNE)          \
    X(JG)           \
    X(JL)           \
    X(HALT)

typedef enum OPCODE {
    #define X(name) name,
        OPCODE_LIST
    #undef X
} OPCODE;

const char* const op2str[] = {
    #define X(name) [name] = #name,
        OPCODE_LIST
    #undef X
};

#define PROGRAM_SIZE 134217728
OPCODE program_table[PROGRAM_SIZE];
OPCODE program_array[PROGRAM_SIZE];
char program_str[PROGRAM_SIZE][5];

CREATE_LUT(str2op, 64);

int main() {
    srand(time(NULL));

    lut_fill(str2op.table, str2op.size, op2str, ARRAY_SIZE(op2str));

    clock_t average_table;
    clock_t average_array;

    for (int k = 0; k < 1; k++) {
        // Generate benchmark program
        for (int i = 0; i < PROGRAM_SIZE; ++i) {
            const char* opcode = op2str[rand() % ARRAY_SIZE(op2str)];
            strcpy(program_str[i], opcode);
        } 

        clock_t start = clock();
        for (int i = 0; i < PROGRAM_SIZE; i++) {
            const char* opcode = program_str[i];
            program_table[i] = lut_get(str2op.table, str2op.size, opcode);
        }
        average_table += clock() - start;

        start = clock();
        for (int i = 0; i < PROGRAM_SIZE; i++) {
            const char* opcode = program_str[i];
            for (int j = 0; j < ARRAY_SIZE(op2str); j++) {
                if (strcmp(opcode, op2str[j]) == 0) {
                    program_array[i] = j;
                    break;
                }
            }
        }
        average_array += clock() - start;

    }
    printf("%s\n", op2str[program_table[PROGRAM_SIZE-1203]]);
    printf("%s\n", op2str[program_array[PROGRAM_SIZE-1203]]);
    printf("Table average: %f\n", (double)average_table / (10 * CLOCKS_PER_SEC));
    printf("Array average: %f\n", (double)average_array / (10 * CLOCKS_PER_SEC));
    return EXIT_SUCCESS;
}