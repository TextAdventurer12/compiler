#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscOps.h"
#include "compiler.h"
#include "preProcessor.h"
#include "function.h"

void parse(FILE* rsi, FILE* rdi)
{
    FILE* err = fopen("err", "w");
    fseek(rsi, 0, SEEK_SET);
    int lines = getLineCount(rsi);
    for (int i = 0; i < lines; i++)
    {
        fseek(rsi, 0, SEEK_SET);
        char* line = getLine(rsi, i);
        if (strcmp(line, "") == 0)
            goto endParse;
        fprintf(err, "%d: %s\n", i+1, line);
        if (contains(line, '#'))
            preProcessor(rdi, line);
        else if (contains(line, '('))
            writeFunction(rdi, line);
        else
            compiler(rdi, line);
endParse:
        free(line);
    }
}

void causeError(FILE* rsi, FILE* rdi)
{
    FILE* err = fopen("err", "w");
    fseek(rsi, 0, SEEK_SET);
    int lines = getLineCount(rsi);
    for (int i = 0; i < lines; i++)
    {
        fseek(rsi, 0, SEEK_SET);
        char* line = getLine(rsi, i);
        if (strcmp(line, "") == 0)
            goto endFor;
        fprintf(err, "%d: %s", i+1, line);
endFor:
        free(line);
    }
}

int main(int argc, char** argv)
{
    if (argc != 3)
        return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f)
        return 1;
    FILE* out = fopen(argv[2], "w");
    if (!out)
        return 1;
    parse(f, out);

    return 0;
}
