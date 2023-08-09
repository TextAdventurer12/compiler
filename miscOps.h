#ifndef MISCOPS_H
#define MISCOPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gets the number of characters within a file.
// src will be set to the start of the file after execution, but will count from where src is set at the start
int file_len(FILE* f);
// gets the length of the specified line (VERY UNOPTIMISED)
int line_len(FILE* f, int num);
// gets the number of lines in the file f
int line_count(FILE* f);
// returns the line number num in the file src
string get_line(FILE* src, int num);
// checks if the string str contains the character chk
bool contains(string str, char chk);
string strcpybtwn(string src, int start, int end);
bit rightBit(int n);
int getBitCount(int n);
bool containsString(string str, string chk);
char getSigChar(string line);
string *nestMalloc(size_t n, size_t size);
int nestFree(string *ptr, size_t n);
char getSecondToLastChar(string str);

#endif
