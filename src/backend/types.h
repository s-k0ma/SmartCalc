#ifndef BACKEND_TYPES_H
#define BACKEND_TYPES_H

#include <stdlib.h>

typedef enum { OPERATOR, OPERAND_DOUBLE } ElementType;

typedef struct {
  ElementType type;
  union {
    char operatorValue;
    double doubleOperand;
  } value;
} Element;

typedef struct StackNode {
  Element data;
  struct StackNode* next;
} StackNode;

typedef struct {
  StackNode* top;
} s21_stack;

struct OperatorPriority {
  char operatorSymbol;
  int priority;
};

struct Abbreviation {
  char* function;
  char abbr;
};

typedef struct Axises {
  double* axisX;
  double* axisY;
} Axises;

typedef struct DiffNode {
  double mainPay;
  double persentPay;
  double monthPay;
  double dept;
} DiffNode;

typedef struct DebetNode {
  double percentCharged;
  double balanceChange;
  double payment;
  double balance;
} DebetNode;

s21_stack* initStack();
void push(s21_stack* stack, Element element);
Element pop(s21_stack* stack);
void destroy(s21_stack* stack);
int isEmpty(s21_stack* stack);
Element writeElement(ElementType type, void* data);
Axises* initAxises(int size);
void destroyAxises(Axises* axises);

#endif  // C7_SMARTCALC_V1_0_1_TYPES_H