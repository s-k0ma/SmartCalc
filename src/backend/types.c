#include "types.h"

/**
 * @file types.c
 * @brief Типы данных используемые в приложении
 */

/**
 * @brief Объявляет стек и выделяет память
 *
 * @return указатель на стек
 */
s21_stack* initStack() {
  s21_stack* stack = (s21_stack*)malloc(sizeof(s21_stack*));
  stack->top = NULL;
  return stack == NULL ? NULL : stack;
}

/**
 * @brief Добавляет запись в стек
 *
 * @param stack указатель на стек
 * @param element элемент который нужно добавить
 *
 */
void push(s21_stack* stack, Element element) {
  StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
  if (newNode != NULL) {
    newNode->data = element;
    newNode->next = stack->top;
    stack->top = newNode;
  }
}

/**
 * @brief Записывает параметр в ноду стека
 * Тип данных Element нужен для перегрузки
 *
 * @param type указатель на стек
 * @param data пустой указатель для записи
 *
 */
Element writeElement(ElementType type, void* data) {
  Element element;
  element.type = type;
  switch (type) {
    case OPERATOR:
      element.value.operatorValue = *(char*)data;
      break;
    case OPERAND_DOUBLE:
      element.value.doubleOperand = *(double*)data;
      break;
  }
  return element;
}

/**
 * @brief Получает верхний элемент стека
 * После получения указатель на запись удаляется из стека
 *
 * @param stack указатель на стек
 *
 * @return element
 *
 */
Element pop(s21_stack* stack) {
  if (stack->top == NULL) {
    Element emptyElement = {OPERATOR, {'\0'}};  // Return an empty operator
    return emptyElement;
  }
  StackNode* temp = stack->top;
  Element element = temp->data;
  stack->top = temp->next;
  free(temp);
  return element;
}

/**
 * @brief Освобождает память занимаемую стеком и его элементами
 *
 * @param stack указатель на стек
 *
 */
void destroy(s21_stack* stack) {
  while (!isEmpty(stack)) {
    StackNode* temp = stack->top;
    stack->top = temp->next;
    free(temp);
  }
  free(stack);
}

/**
 * @brief Проверяет наличие элементов в стеке
 *
 */
int isEmpty(s21_stack* stack) { return stack->top == NULL; }

/**
 * @brief Выделяет память для структуры
 * Хранящей два массивами с точками координат
 *
 * @param size размер массива для инициализации
 *
 * @return axises
 *
 */
Axises* initAxises(int size) {
  Axises* axises = (Axises*)malloc(sizeof(Axises));
  if (axises) {
    axises->axisX = (double*)malloc(sizeof(double) * size);
    axises->axisY = (double*)malloc(sizeof(double) * size);

    if (!axises->axisX || !axises->axisY) {
      free(axises->axisX);
      free(axises->axisY);
      free(axises);
      return NULL;
    }
  }

  return axises;
}

/**
 * @brief Освобождает память занимаему структурой
 *
 * @param axises указатель на структуру
 *
 */
void destroyAxises(Axises* axises) {
  if (axises) {
    free(axises->axisX);
    free(axises->axisY);
    free(axises);
  }
}