#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscOps.h"

typedef int reg_key;
typedef const char *string;

// returns the string that will push all of the selected registers
char* push_active(reg_key regs);
// returns the string that will pop all of the selected registers
char* pop_active(reg_key regs);
// looks through the given string to detect the mentioned registers
reg_key get_active_registers(string line);
// writes the function prologue
// dst -> the file that is written to
// alloc_size -> the number of bytes that is allocated for use in the function
// regs -> the reg_key representing the registers that should be prepared for the function
void write_prologue(FILE* dst, size_t alloc_size, reg_key regs);
// writes the function epilogue
// dst -> the file that is written
// regs -> the reg_key representing the registers that should be fixed after the function
void write_epilogue(FILE* dst, reg_key regs);
void preProcessor(FILE* rdi, string line);

#endif