#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include "miscOps.h"

typedef struct
{
    char* content;
    char* key;
} Entry;

typedef struct
{
    char** content;
    char** key;
    int len;
} Hashtable;

typedef struct
{
    char* reg1;
    char* reg2;
    char* instruction;
} Operation;

char* readFrom(Hashtable table, char* key);
char* getInstruction(char* line);
void compiler(FILE* rdi, char* line);
void printInstructions(FILE* rdi, Operation op);

#endif
