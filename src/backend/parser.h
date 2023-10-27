#ifndef BACKEND_PARSER_H
#define BACKEND_PARSER_H

#include <stdio.h>
#include <string.h>

#include "types.h"

int toPostfix(char* input, char** postfix);
int simplification(char* str, char** output);
char* replaceXtoDigit(char* expression, double value);
int getShortFuncName(char* name);
int isDigit(char ch);
int isLetter(char ch);
void appendSymbol(char** str, char ch);
int validator(char* input);
int getOperatorPriority(char opSymbol);

#endif  // BACKEND_PARSER_H
