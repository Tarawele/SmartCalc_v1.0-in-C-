#include "s21_polish.h"

bool isDigit(char *token) {
  double out_digit;
  bool re;
  int r = sscanf(token, "%lf", &out_digit);

  if (r == 1) {
    re = true;
  } else {
    re = false;
  }
  return re;
}

int GetPriority(char *token) {
  char *mathFunc[9] = {"sqrt", "acos", "asin", "atan", "cos",
                       "sin",  "tan",  "log",  "ln"};
  int priority = 0;

  if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
    priority = 1;
  } else if (strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
             strcmp(token, "%") == 0) {
    priority = 2;
  } else if (strcmp(token, "^") == 0) {
    priority = 3;
  }

  for (int i = 0; i < 9; i++) {
    if (strcmp(token, mathFunc[i]) == 0) {
      priority = 3;
    }
  }

  return priority;
}

double PerformAnAction(double firstDigit, char *action, double secondDigit) {
  double result;

  if (strcmp(action, "+") == 0) {
    result = firstDigit + secondDigit;
  }
  if (strcmp(action, "-") == 0) {
    result = firstDigit - secondDigit;
  }
  if (strcmp(action, "*") == 0) {
    result = firstDigit * secondDigit;
  }
  if (strcmp(action, "/") == 0) {
    result = firstDigit / secondDigit;
  }
  if (strcmp(action, "%") == 0) {
    result = fmod(firstDigit, secondDigit);
  }
  if (strcmp(action, "^") == 0) {
    result = pow(firstDigit, secondDigit);
  }

  return result;
}

void Calculate(Stack *operands, Stack *operators) {
  double lastDigit;
  double secondLastDigit;
  char result[256] = {0};

  char *lastDigitPointer = operands->pop(operands);
  sscanf(lastDigitPointer, "%lf", &lastDigit);

  char *secondLastDigitPointer = operands->pop(operands);
  sscanf(secondLastDigitPointer, "%lf", &secondLastDigit);

  char *action = operators->pop(operators);
  double res = PerformAnAction(secondLastDigit, action, lastDigit);

  sprintf(result, "%lf", res);

  char *resPointer = result;
  operands->push(operands, resPointer);

  free(lastDigitPointer);
  free(secondLastDigitPointer);
  free(action);
}

void PerformMathFunc(Stack *operands, Stack *operators) {
  double resDouble = 0;
  double digit;
  char *funcName = operators->pop(operators);
  char *resCharPointer = {0};
  char resChar[256] = {0};

  char *lastDigit = operands->pop(operands);
  sscanf(lastDigit, "%lf", &digit);

  if (strcmp(funcName, "sqrt") == 0) {
    resDouble = sqrt(digit);
  }
  if (strcmp(funcName, "acos") == 0) {
    resDouble = acos(digit);
  }
  if (strcmp(funcName, "atan") == 0) {
    resDouble = atan(digit);
  }
  if (strcmp(funcName, "asin") == 0) {
    resDouble = asin(digit);
  }
  if (strcmp(funcName, "cos") == 0) {
    resDouble = cos(digit);
  }
  if (strcmp(funcName, "tan") == 0) {
    resDouble = tan(digit);
  }
  if (strcmp(funcName, "sin") == 0) {
    resDouble = sin(digit);
  }
  if (strcmp(funcName, "ln") == 0) {
    resDouble = log(digit);
  }
  if (strcmp(funcName, "log") == 0) {
    resDouble = log10(digit);
  }
  sprintf(resChar, "%lf", resDouble);
  resCharPointer = resChar;
  operands->push(operands, resCharPointer);

  free(funcName);
  free(lastDigit);
}