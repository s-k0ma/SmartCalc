#ifndef BACKEND_CALC_H
#define BACKEND_CALC_H

#include <math.h>

#include "parser.h"

double reverse(char* str);
double operation(double a, double b, char ch);
double unary(double x, char ch);
double calculation(char* input);
Axises* drawingGraph(char* input, double xMax, double xMin);

#endif  // BACKEND_PARSER_H