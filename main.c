#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscOps.h"
#include "compiler.h"
#include "preProcessor.h"

void parse(FILE* rsi, FILE* rdi)
{
    fseek(rsi, 0, SEEK_SET);
    int lines = getLineCount(rsi);
    for (int i = 0; i < lines; i++)
    {
        fseek(rsi, 0, SEEK_SET);
        char* line = getLine(rsi, i);
        if (!contains(line, '#'))
            printf("%d\n", compiler(rdi, line));
        else
            preProcessor(rdi, line);
    }
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return 1;
    char psm[64];
    char outName[64];
    strcpy(psm, argv[1]);
    strcpy(outName, argv[1]);
    strcat(psm, ".psm");
    strcat(outName, ".asm");
    FILE* f = fopen(psm, "r");
    if (!f)
        return 1;
    FILE* out = fopen(outName, "w");
    if (!out)
        return 1;
    parse(f, out);

    return 0;
}
