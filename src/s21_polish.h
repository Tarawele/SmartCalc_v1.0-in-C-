#ifndef SRC_S21_POLISH_H_
#define SRC_S21_POLISH_H_

#include "s21_stack.h"

bool isDigit(char *token);
int GetPriority(char *token);
double PerformAnAction(double firstDigit, char *action, double secondDigit);
void Calculate(Stack *operands, Stack *operators);
void PerformMathFunc(Stack *operands, Stack *operators);
char *Parser(char *expression);

#endif // SRC_S21_POLISH_H_
