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
        if (contains(line, '#'))
            preProcessor(rdi, line);
        else if (contains(line, '('))
            writeFunction(rdi, line);
        else
            fprintf(err, "%d\n", compiler(rdi, line));
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
