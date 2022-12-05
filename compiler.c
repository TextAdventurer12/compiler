#include "compiler.h"
#include <string.h>
#include <stdlib.h>
#include "miscOps.h"

char* readFrom(Hashtable table, char* key)
{
    int i = 0;
    for (; i < table.len && strcmp(table.key[i], key); i++);
    if (i == table.len)
        return NULL;
    return table.content[i];
}

struct IndexedString getInstruction(char* line)
{
    Hashtable symbols = (Hashtable){ (char*[]){"add", "and", "cmp", "dec", "div", "inc", "lea", "mov", "mul", "neg", "not", "or", "shl", "shr", "sub", "xor", "bswap"}, (char*[]){"+=", "&&", "??", "--", "/=", "++", "<&", "<-", "*=", "=-", "=!", "||", "<<", ">>", "-=", "^^", "><"}, 17 };
    for (int i = 0; i < (int)strlen(line) - 2; i++)
    {
        char* tmp = strcpybtwn(line, i, i+2);
        char* symbol = readFrom(symbols, tmp);
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
