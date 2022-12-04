#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscOps.h"

char* pushActive(int regs);
char* popActive(int regs);
int getActiveRegs(char* line);
void writePrologue(FILE* rdi, int allocSize, int regs);
void writeEpilogue(FILE* rdi, int regs);
void preProcessor(FILE* rdi, char* line);

#endif