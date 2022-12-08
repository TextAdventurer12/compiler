#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>

struct Args
{
    char** argv;
    int argc;
};

struct Args getArgs(char* line, int index);
int getArgCount(char* line);
int getFuncIndex(char* line);
int writeFunction(FILE* rdi, char* line);
char* getLabel(char* line);
int getNext(char* line);

#endif
