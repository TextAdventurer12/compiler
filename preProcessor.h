#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscOps.h"
#include "definitions.h"


// returns the string that will push all of the selected registers
string push_active(reg_key regs);
// returns the string that will pop all of the selected registers
string pop_active(reg_key regs);
// looks through the given string to detect the mentioned registers
reg_key get_active_registers(string line);
// writes the function prologue
// dst -> the file that is written to
// alloc_size -> the number of bytes that is allocated for use in the function
// regs -> the reg_key representing the registers that should be prepared for the function
int write_prologue(FILE* dst, size_t alloc_size, reg_key regs);
// writes the function epilogue
// dst -> the file that is written
// regs -> the reg_key representing the registers that should be fixed after the function
int write_epilogue(FILE* dst, reg_key regs);
// invokes all necessary preprocessor commands for the single line, and writes to dst
int preprocessor(FILE* dst, string line);

#endif