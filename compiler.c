#include "compiler.h"
#include <string.h>
#include <stdlib.h>


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
    
}

void compiler(FILE* rdi, char* line)
{
    //fprintf(rdi, "%s%c", line, getLastChar(line) != '\n' ? '\n' : ' ');
    Operation op;
    struct IndexedString str = getInstruction(line);
    op.instruction = str.symbol;
    if (!op.instruction)
    {
        fprintf(rdi, "%s%c", line, getLastChar(line) != '\n' ? '\n' : ' ');
        return;
    }
    int regCount = getRegCount(op.instruction);
    op.reg1 = getFirstRegister(line);
}
