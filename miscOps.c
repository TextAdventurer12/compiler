#include "miscOps.h"

char getSigChar(char* line)
{
    int i = 0;
    for (i = 0; i < strlen(line) && line[i] == ' '; i++);
    return line[i-1];
}

int getFileLen(FILE* rsi)
{
    char curChar = 2;
    int fLen;
    while (fread(&curChar, 1, 1, rsi) == 1)
        fLen++;
    fseek(rsi, 0, SEEK_SET);
    return fLen;
}

int getLineLength(FILE* rsi, int lineNum)
{
    int lines = 0;
    char buf = 0;
    int i = 0;
    for (; fread(&buf, 1, 1, rsi) == 1 && lines < lineNum; lines += buf == '\n' ? 1 : 0)
        i++;
    fseek(rsi, i, SEEK_SET);
    int j = 0;
    for (; buf != '\n'; j++)
    {
        if (fread(&buf, 1, 1, rsi) != 1)
            return j;
    }
    return j;
}

int getLineCount(FILE* rsi)
{
    int i = 0;
    char buf;
    while (fread(&buf, 1, 1, rsi) == 1)
        if (buf == '\n')
            i++;
    return i+1;
}

char* getLine(FILE* rsi, int lineNum)
{
    int lineStart = 0;
    char buf = 0;
    for (int i = 0; i != lineNum; lineStart++)
        if (fread(&buf, 1, 1, rsi) == 1)
        {
            if (buf == '\n')
                i++;
        }
        else
            break;
    fseek(rsi, 0, SEEK_SET);
    int lineLen = getLineLength(rsi, lineNum);
    fseek(rsi, lineStart, SEEK_SET);
    char* line = malloc(lineLen);
    for (int i = 0; i < lineLen; i++)
        if (fread(&buf, 1, 1, rsi) == 1)
            line[i] = buf;
        else
            return line;
    return line;
}

int contains(char* arr, char chk)
{
    int i = 0;
    for (; i < strlen(arr) && arr[i] != chk; i++);
    return i != strlen(arr);
}

char* strcpybtwn(char* rsi, int start, int end)
{
    if (end < start)
        return NULL;
    char* rdi = malloc(end - start);
    for (int i  = start; i < end; i++)
        rdi[i - start] = rsi[i];
    return rdi;
}

int rightBit(int n)
{
    int s1 = n >> 1;
    return n != s1 << 1;
}

int getBitCount(int n)
{
    int i = 0;
    for (; n != 0; )
    {
        if (rightBit(n))
            i++;
        n = n >> 1;
    }
    return i;
}
int containsString(char* rsi, char* chk)
{
    for (int i = 0; i < (int)strlen(rsi) - (int)strlen(chk); i++)
    {
        char* tmpStr = strcpybtwn(rsi, i, i+strlen(chk));
        if (!strcmp(tmpStr, chk))
            return 1;
    }
    return 0;
}
