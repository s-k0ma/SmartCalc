#include "parser.h"
/**
 * @file parser.c
 * @brief Функции с для обработки выражений
 */

/**
 * @brief Функция для перевод заданного выражение
 * В выражение в польской записи
 * возвращает 1 при успешной записи
 * -1 при ошибке
 *
 * @param input входное выражение
 * @param postfix указатель на записываемое выражение
 *
 * @return 1
 * @return -1
 */
int toPostfix(char* input, char** postfix) {
  char* simple = NULL;
  int result = simplification(input, &simple);
  s21_stack* stack = initStack();

  if (result != -1) {
    for (int i = 0; i < (int)strlen(simple); i++) {
      while (!isDigit(simple[i])) {
        appendSymbol(postfix, simple[i]);
        i++;
      }
      if (simple[i] == '(') {
        char ch = simple[i];
        push(stack, writeElement(OPERATOR, &ch));
      }
      if (simple[i] == ')') {
        while (stack->top->data.value.operatorValue != '(') {
          appendSymbol(postfix, stack->top->data.value.operatorValue);
          pop(stack);
        }
        pop(stack);
      }
      if (getOperatorPriority(simple[i]) != -1) {
        char op = simple[i];
        if (op == '-' &&
            (i == 0 || (i > 1 && getOperatorPriority(simple[i - 1]) != -1)))
          op = '~';
        if (op == '+' &&
            (i == 0 || (i > 1 && getOperatorPriority(simple[i - 1]) != -1)))
          op = 'p';
        while (!isEmpty(stack) &&
               (getOperatorPriority(stack->top->data.value.operatorValue) >=
                getOperatorPriority(op))) {
          appendSymbol(postfix, stack->top->data.value.operatorValue);
          pop(stack);
        }
        push(stack, writeElement(OPERATOR, &op));
        appendSymbol(postfix, ' ');
      }
    }
    while (!isEmpty(stack)) {
      appendSymbol(postfix, stack->top->data.value.operatorValue);
      pop(stack);
    }
    free(simple);
    destroy(stack);
  }
  return result;
}

/**
 * @brief Проверяет является ли символ
 * Числом X-ом или точкой
 *
 * @param ch входное выражение
 *
 * @return 1
 * @return -1
 */
int isDigit(char ch) {
  return ((ch >= 48 && ch <= 57) || ch == '.' || ch == 'X') ? 0 : 1;
}

/**
 * @brief Проверяет является ли символ буквой
 *
 * @param ch входное выражение
 *
 * @return 1
 * @return -1
 */
int isLetter(char ch) { return (ch >= 97 && ch <= 122) ? 0 : 1; }

/**
 * @brief Добавляет символ к концу строки
 *
 * @param str указатель на расширяемую строку
 * @param ch символ который требуется добавить
 *
 */
void appendSymbol(char** str, char ch) {
  if (*str == NULL) {
    // If the string is NULL, allocate memory for the initial character and
    // null-terminator
    *str = (char*)malloc(2 * sizeof(char));
    if (*str == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      exit(1);
    }
    (*str)[0] = ch;
    (*str)[1] = '\0';
  } else {
    // If the string is not NULL, reallocate memory to accommodate the new
    // character
    size_t len = strlen(*str);
    *str = (char*)realloc(*str, (len + 2) * sizeof(char));
    if (*str == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      exit(1);
    }
    (*str)[len] = ch;
    (*str)[len + 1] = '\0';
  }
}

/**
 * @brief Находит подстроки с названиями тригонометрических функций
 * Перезаписывает длинные названия в условные обозначения
 * Требуется для дальнейших вычислений
 *
 * @param str указатель на исходное выражение
 * @param output указатель на преобраованное выражение
 *
 * @return 1
 * @return -1
 */
int simplification(char* str, char** output) {
  int result = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == ' ') continue;
    if (!isLetter(str[i])) {
      char* func = NULL;
      while (!isLetter(str[i])) {
        appendSymbol(&func, str[i]);
        i++;
      }
      int ch = getShortFuncName(func);
      if (ch != -1) {
        appendSymbol(output, getShortFuncName(func));
      } else {
        result = -1;
        free(func);
        break;
      }
      free(func);
    }
    appendSymbol(output, str[i]);
  }
  return result;
}

/**
 * @brief Возвращает условное обозначение функции
 *
 * @param name указатель на название функции
 *
 * @return -1
 */
int getShortFuncName(char* name) {
  struct Abbreviation names[] = {
      {"cos", 'c'},  {"sin", 's'},  {"tan", 't'}, {"acos", 'C'}, {"asin", 'S'},
      {"atan", 'T'}, {"sqrt", 'q'}, {"ln", 'l'},  {"log", 'L'},  {"mod", '%'},
  };
  for (int i = 0; i < 10; i++) {
    if (!strcmp(names[i].function, name)) {
      return names[i].abbr;
    }
  }
  return -1;
}

/**
 * @brief Возвращает приоритет операции
 *
 * @param opSymbol условный символ операции
 *
 * @return -1
 */
int getOperatorPriority(char opSymbol) {
  struct OperatorPriority operators[] = {
      {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}, {'^', 3},
      {'~', 4}, {'p', 4}, {'c', 4}, {'s', 4}, {'t', 4}, {'C', 4},
      {'S', 4}, {'T', 4}, {'q', 4}, {'l', 4}, {'L', 4},
  };

  for (int i = 0; i < (int)(sizeof(operators) / sizeof(operators[0])); i++) {
    if (operators[i].operatorSymbol == opSymbol) {
      return operators[i].priority;
    }
  }
  return -1;  // Operator not found
}

/**
 * @brief Проверяет валидность открытых и закрытых скобок в выражении
 *
 * @param input выражение
 *
 * @return 0
 * @return 1
 */
int validator(char* input) {
  int result = 0;
  int len = (int)strlen(input);
  if (len > 0) {
    int bracketCounter = 0;
    for (int i = 0; i < len; i++) {
      if (bracketCounter == -1) break;
      if (input[i] == '(')
        bracketCounter++;
      else if (input[i] == ')')
        bracketCounter--;
    }
    if (bracketCounter == 0) result = 1;
  }
  return result;
}

/**
 * @brief Заменяет X на число в выражении
 *
 * @param input выражение
 * @param value значение Х
 *
 * @return измененное выражение
 */
char* replaceXtoDigit(char* input, double value) {
  // Calculate the maximum length needed for the result string.
  int inputLen = (int)strlen(input);
  int maxResultLen =
      inputLen + 20;  // Assuming a double will not exceed 20 characters.

  // Allocate memory for the result string.
  char* result = (char*)malloc(maxResultLen);
  if (result == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  int i = 0;  // Index for the input string.
  int j = 0;  // Index for the result string.

  while (i < inputLen) {
    if (input[i] == 'X') {
      // Replace 'X' with the double value as a string.
      int charsWritten = snprintf(result + j, maxResultLen - j, "%.6f", value);
      if (charsWritten < 0) {
        fprintf(stderr, "Error writing double value\n");
        free(result);
        return NULL;
      }
      j += charsWritten;
      i++;  // Skip the 'X'.
    } else {
      // Copy other characters as they are.
      result[j] = input[i];
      i++;
      j++;
    }
  }
  result[j] = '\0';  // Null-terminate the result string.

  return result;
}