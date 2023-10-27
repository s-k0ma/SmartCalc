#include "calc.h"

/**
 * @file calc.c
 * @brief Функции с для вычислений
 */

/**
 * @brief Функция для отрисовки графика
 * возвращает структуру из двух массивов с координатами
 *
 * @param input строка с выражением может содержать X
 * @param xMax максимальное значение в диапазоне
 * @param xMin минимальное значение в диапазоне
 *
 * @return структура с массивами
 * @return NULL
 */
Axises* drawingGraph(char* input, double xMax, double xMin) {
  Axises* praxis = NULL;
  double xRange = xMax - xMin;
  double step = (xMax - xMin) / 1000;
  if (validator(input)) {
    int size = (int)floor(xRange / step);
    praxis = initAxises(size);

    int k = 0;
    for (double i = xMin; i <= xMax; i += step) {
      char* line = replaceXtoDigit(input, i);
      double calculated = calculation(line);

      if (calculated != NAN) {
        praxis->axisX[k] = i;
        praxis->axisY[k] = calculated;
      } else {
        free(line);
        continue;
      }
      if (i + step <= xMax) k++;
      free(line);
    }
  }
  return praxis;
}

/**
 * @brief Функция для вычислений
 *
 * @param input строка с выражением может содержать X
 *
 * @return результат вычислений
 * @return NAN
 */
double calculation(char* input) {
  double result = 0;
  if (validator(input)) {
    result = reverse(input);
  } else
    result = NAN;
  return result;
}

/**
 * @brief Функция для перевода в ОПН и вычисления
 *
 * @param str строка с выражением может содержать X
 *
 * @return результат вычислений
 * @return NAN
 */
double reverse(char* str) {
  char* postfix = NULL;
  double result = (double)toPostfix(str, &postfix);
  if (result != -1) {
    s21_stack* stack = initStack();
    for (int i = 0; i < (int)strlen(postfix); i++) {
      if (!isDigit(postfix[i])) {
        char* digit = NULL;
        while (!isDigit(postfix[i])) {
          appendSymbol(&digit, postfix[i]);
          i++;
        }
        double val = atof(digit);
        push(stack, writeElement(OPERAND_DOUBLE, &val));
        free(digit);
      }
      if (getOperatorPriority(postfix[i]) != -1) {
        if (getOperatorPriority(postfix[i]) == 4) {
          Element val = pop(stack);
          double x = unary(val.value.doubleOperand, postfix[i]);
          push(stack, writeElement(OPERAND_DOUBLE, &x));
          continue;
        }
        Element first = pop(stack);
        Element second = pop(stack);
        double a = first.value.doubleOperand;
        double b = second.value.doubleOperand;
        double result = operation(b, a, postfix[i]);
        push(stack, writeElement(OPERAND_DOUBLE, &result));
      }
    }
    Element el = pop(stack);
    result = el.value.doubleOperand;
    free(postfix);
    destroy(stack);
  } else
    result = NAN;
  return result;
}

/**
 * @brief Функция для вычисления унарных операций
 *
 * @param x операнд
 * @param ch символ обозначающий операцию
 *
 * @return результат вычислений
 */
double unary(double x, char ch) {
  double result = 0;
  switch (ch) {
    case '~':
      result = x * -1;
      break;
    case 'c':
      result = cos(x);
      break;
    case 's':
      result = sin(x);
      break;
    case 't':
      result = tan(x);
      break;
    case 'C':
      result = acos(x);
      break;
    case 'S':
      result = asin(x);
      break;
    case 'T':
      result = atan(x);
      break;
    case 'q':
      result = sqrt(x);
      break;
    case 'l':
      result = log(x);
      break;
    case 'L':
      result = log10(x);
      break;
  }
  return result;
}

/**
 * @brief Функция для вычисления математических выражений
 *
 * @param a операнд
 * @param b операнд
 * @param ch символ обозначающий операцию
 *
 * @return результат вычислений
 */
double operation(double a, double b, char ch) {
  double result = 0;
  switch (ch) {
    case '+':
      result = a + b;
      break;
    case '-':
      result = a - b;
      break;
    case '*':
      result = a * b;
      break;
    case '/':
      result = a / b;
      break;
    case '^':
      result = pow(a, b);
      break;
    case '%':
      result = (int)a % (int)b;
      break;
  }
  return result;
}