#include "compiler.h"
#include <string.h>
#include <stdlib.h>
#include "miscOps.h"

char* readFrom(Hashtable table, char* key)
{
    int i = 0;
    for (; i < table.len && strcmp(table.key[i], key) != 0; i++);
        //printf("[%s, %s]  ", table.key[i], key);
    //printf("\n");
    if (i == table.len)
        return NULL;
    return table.content[i];
}

Hashtable* initSymbols()
{
    Hashtable* symbols = malloc(sizeof(symbols));
    symbols->content = malloc(17 * sizeof(char*));
    symbols->key = malloc(17 * sizeof(char*));
    for(int i = 0; i < 17; i++)
    {
        symbols->content[i] = malloc(3);
        symbols->key[i] = malloc(2);
    }
    symbols->content[0 ] = (char*)"add";
    symbols->content[1 ] = (char*)"and";
    symbols->content[2 ] = (char*)"cmp";
    symbols->content[3 ] = (char*)"dec";
    symbols->content[4 ] = "div";
    symbols->content[5 ] = "inc";
    symbols->content[6 ] = "lea";
    symbols->content[7 ] = "mov";
    symbols->content[8 ] = "mul";
    symbols->content[9 ] = "neg";
    symbols->content[10] = "not";
    symbols->content[11] = "or ";
    symbols->content[12] = "shl";
    symbols->content[13] = "shr";
    symbols->content[14] = "sub";
    symbols->content[15] = "xor";
    symbols->content[16] = "bswap";
    symbols->key[0 ] = "+=";
    symbols->key[1 ] = "&&";
    symbols->key[2 ] = "??";
    symbols->key[3 ] = "--";
    symbols->key[4 ] = "/=";
    symbols->key[5 ] = "++";
    symbols->key[6 ] = "<&";
    symbols->key[7 ] = "<-";
    symbols->key[8 ] = "*=";
    symbols->key[9 ] = "=-";
    symbols->key[10] = "=!";
    symbols->key[11] = "||";
    symbols->key[12] = "<<";
    symbols->key[13] = ">>";
    symbols->key[14] = "-=";
    symbols->key[15] = "^^";
    symbols->key[16] = "><";
    symbols->len = 17;
    return symbols;
}

struct IndexedString getInstruction(char* line)
{
    Hashtable* symbols = initSymbols();
    for (int i = 0; i < (int)strlen(line) - 2; i++)
    {
        char* tmp = strcpybtwn(line, i, i+2);
        char* symbol = readFrom(*symbols, tmp);
        //printf("%p\n", symbol);
        if (symbol)
            return (struct IndexedString){symbol, i};
        free(tmp);
    }
    return (struct IndexedString){NULL, -1};
}

int getRegCount(char* instruction)
{
    char singleInstructions[5][5] = {"dec", "inc", "neg", "not", "bswap"};
    int i = 0;
    for (; i < 5; i++)
        if (!strcmp(instruction, singleInstructions[i]))
            goto end;
end:
    if (i == 5)
        return 2;
    return 1;
}

char getLastChar(char* line)
{
    int i = 0;
    for (; i < strlen(line); i++);
    return line[i-1];
}

char* getFirstRegister(char* line)
{
    int j = 0;
    for (; j < strlen(line) && line[j] == ' '; j++);
    if (j == strlen(line))
            return NULL;
    return strcpybtwn(line, j, j+3);
}

char* getSecondRegister(char* line, int symIndex)
{
    symIndex += 2;
    int i = (int)strlen(line);
    for (; symIndex < strlen(line) && line[symIndex] == ' '; symIndex++);
    if (symIndex >= i)
        return NULL;
    return strcpybtwn(line, symIndex, i);
}

void removeOperation(Operation op)
{
    if (op.reg1)
        free(op.reg1);
    if (op.reg2)
        free(op.reg2);
    return;
}

int compiler(FILE* rdi, char* line)
{
    Operation op;
    struct IndexedString str = getInstruction(line);
    if (!str.symbol)
      return fprintf(rdi, "%s%c", line, getLastChar(line) != '\n' ? '\n' : ' ') ? 1 : 1;
    op.instruction = str.symbol;
    if (!op.instruction)
        return fprintf(rdi, "%s%c", line, getLastChar(line) != '\n' ? '\n' : ' ') ? 2 : 2;
    int regCount = getRegCount(op.instruction);
    op.reg1 = getFirstRegister(line);
    if (!op.reg1)
        return fprintf(rdi, "%s%c", line, getLastChar(line) != '\n' ? '\n' : ' ') ? 3 : 3;
    if (regCount == 2)
    {
        op.reg2 = getSecondRegister(line, str.index);
        if (!op.reg2)
            return fprintf(rdi, "%s%c", line, getLastChar(line) != '\n' ? '\n' : ' ') ? 4 : 4;
        fprintf(rdi, "%s %s, %s", op.instruction, op.reg1, op.reg2);
        removeOperation(op);
        return 5;
    }
    if (regCount == 1)
    {
        fprintf(rdi, "%s %s", op.instruction, op.reg1);
        removeOperation(op);
        return 6;
    }
    fprintf(rdi, "%s%c", line, getLastChar(line) != '\n' ? '\n' : ' ');
    return 0;
}
