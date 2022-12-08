#include "function.h"
#include <string.h>
#include <stdlib.h>
#include "miscOps.h"


int getFuncIndex(char* line)
{
    int i = 0;
    for (; i < strlen(line) && line[i] != '('; i++);
    if (i == strlen(line))
        return -1;
    return i;
}

int getArgCount(char* line)
{
    int i = 0;
    for (int j = 0; j < strlen(line); j++)
        if (line[j] == ',') i++;
    return i + (getSecondToLastChar(line) != '(');
}

int getNext(char* line)
{
    int i = 0;
    for (; i < strlen(line); i++)
        if (line[i] == ',' || line[i] == ')') return i;
    return -1;
}

struct Args getArgs(char* line, int index)
{
    int argc = getArgCount(line+index);
    if (argc == 0)
        return (struct Args){NULL, 0};
    char** out = nestMalloc(argc, 64);
    int prev = index+1;
    int next;
    for (int i = 0; i < argc; i++)
    {
        int j = prev;
        for (; j < (next = getNext(line+prev)+prev); j++)
            out[i][j-prev] = line[j];
        out[i][j-prev] = '\0';
        prev = next+1;
    }

    return (struct Args){out, argc};
}

char* getLabel(char* line)
{
    int i = 0;
    for (; i < strlen(line) && line[i] == ' '; i++);
    if (i == strlen(line))
        return NULL;
    int j = i;
    for (; j < strlen(line) && line[j] != '('; j++);
    if (j == strlen(line))
        return NULL;
    return strcpybtwn(line, i, j);
}

int writeFunction(FILE* rdi, char* line)
{
    printf("%s", line);
    char* labl = getLabel(line);
    if (!labl)
        exit(1);
    struct Args arg = getArgs(line, getFuncIndex(line));
    for (int i = 0; i < arg.argc; i++)
        if (!arg.argv[i])
            exit(1);
    if (arg.argc == 0)
    {
        fprintf(rdi, "call %s\n", labl);
        free(labl);
        return 0;
    }
    for (int i = 0; i < arg.argc; i++)
        fprintf(rdi, "push %s\n", arg.argv[i]);
    //printf("call %s\n", labl);
    fprintf(rdi, "call %s\n", labl);
    fprintf(rdi, "add rsp, %d\n", arg.argc * 8);
    for (int i = 0; i < arg.argc; i++)
        free(arg.argv[i]);
    free(arg.argv);
    free(labl);
    return 0;
}
