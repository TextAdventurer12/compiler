#ifndef MISCOPS_H
#define MISCOPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getFileLen(FILE* rsi);
int getLineLength(FILE* f, int lineNum);
int getLineCount(FILE* rsi);
char* getLine(FILE* rsi, int lineNum);
int contains(char* arr, char chk);
char* strcpybtwn(char* rsi, int start, int end);
int rightBit(int n);
int getBitCount(int n);
int containsString(char* rsi, char* chk);
char getSigChar(char* line);

#endif
