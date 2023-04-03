#include "s21_polish.h"

static char *GetToken(char *expression, int *position, Stack *operands) {
  char const mathFunc[5] = {'s', 'a', 'c', 't', 'l'};
  char *token = (char *)malloc(sizeof(char) * 256);
  // token = "0";

  while (true) {
    if ((expression[*position] <= '9' && expression[*position] >= '0') ||
        expression[*position] == '.') { // digit
      strncat(token, expression + (*position), 1);

      if ((expression[*position + 1] <= '9' &&
           expression[*position + 1] >= '0') ||
          expression[*position + 1] == '.') {
        (*position)++;
      } else {
        (*position)++;

        break;
      }
    } else if (expression[*position] >= 'a' && expression[*position] <= 't') {
      if (expression[*position] == 'a' ||
          (expression[*position] == 's' &&
           expression[*position + 1] == 'q')) { // acos, atan, asin, sqrt
        strncat(token, expression + (*position), 4);
        (*position) += 4;

        break;
      } else if (expression[*position] == 'l' &&
                 expression[*position + 1] == 'n') { // ln
        strncat(token, expression + (*position), 3);
        (*position) += 3;

        break;
      } else { // cos, tan, sin, log
        strncat(token, expression + (*position), 3);
        (*position) += 3;

        break;
      }
    } else if (expression[*position] == '-' ||
               expression[*position] == '+') { // unary operation (+, -)
      bool isMathFunc = false;

      for (int i = 0; i < 5;
           i++) { // apply decision (operator is it mathFunc or not)
        if (expression[*position + 1] == mathFunc[i]) {
          isMathFunc = true;
          break;
        }
      }

      if ((expression[*position + 1] <= '9' &&
           expression[*position + 1] >= '0') ||
          isMathFunc) {
        if (!(expression[*position - 1] <= '9' &&
              expression[*position - 1] >= '0')) {
          if (expression[*position - 1] != ')') {
            operands->push(operands, "0");

            strncat(token, expression + (*position), 1);
            (*position)++;

            break;
          } else {
            strncat(token, expression + (*position), 1);
            (*position)++;

            break;
          }
        } else {
          strncat(token, expression + (*position), 1);
          (*position)++;

          break;
        }
      }

      // -()
      if (expression[*position + 1] == '(' &&
          expression[*position - 1] != ')') {
        if (!(expression[*position - 1] <= '9' &&
              expression[*position - 1] >= '0')) {
          operands->push(operands, "0");

          strncat(token, expression + (*position), 1);
          (*position)++;

          break;
        }
      }

      strncat(token, expression + (*position), 1);
      (*position)++;

      break;
    } else { // action
      strncat(token, expression + (*position), 1);
      (*position)++;

      break;
    }
  }

  return token;
}

char *Parser(char *expression) {
  Stack *operators = stack_init();
  Stack *operands = stack_init();

  char *mathFunc[9] = {"sqrt", "acos", "asin", "atan", "cos",
                       "sin",  "tan",  "log",  "ln"};
  int position = 0;

  while (expression[position] != '\0') {
    char *token = GetToken(expression, &position, operands);

    if (isDigit(token)) {
      operands->push(operands, token);
      free(token);
      continue;
    } else {
      // if get first token || stack is empty
      if (operators->is_empty_stack(operators)) {
        operators->push(operators, token);
        free(token);
        continue;
      }

      // if token == ( || )
      if (strcmp(token, ")") == 0) {
        while (strcmp(operators->peek(operators), "(") != 0) {
          bool isMathFunc = false;

          for (int i = 0; i < 9;
               i++) { // apply decision (operator is it mathFunc or not)
            if (strcmp(operators->peek(operators), mathFunc[i]) == 0) {
              isMathFunc = true;
              break;
            }
          }

          if (isMathFunc) { // if operator is it mathFunc
            if (operators->is_empty_stack(operators) || operands->size < 1) {
              break;
            }
            PerformMathFunc(operands, operators);
          } else {
            if (operators->is_empty_stack(operators) || operands->size < 2) {
              break;
            }

            Calculate(operands, operators);
          }
        }

        if (!operators->is_empty_stack(operators)) {
          if (strcmp(operators->peek(operators), "(") == 0) {
            char *bracket = operators->pop(operators);
            free(bracket);
          }
        }

        free(token);

        continue;
      } else if (strcmp(token, "(") == 0) {
        operators->push(operators, token);
        free(token);
        continue;
      }

      // Get Priority
      if (GetPriority(token) > GetPriority(operators->peek(operators))) {
        operators->push(operators, token);
        free(token);
        continue;
      } else if (GetPriority(token) <=
                 GetPriority(operators->peek(operators))) {
        while (GetPriority(token) <= GetPriority(operators->peek(operators)) ||
               strcmp(operators->peek(operators), "(") == 0) {
          bool isMathFunc = false;

          for (int i = 0; i < 9; i++) {
            if (strcmp(operators->peek(operators), mathFunc[i]) == 0) {
              isMathFunc = true;
              break; // apply decision (operator is it mathFunc or not)
            }
          }

          if (isMathFunc) { // if operator is it mathFunc
            if (operators->is_empty_stack(operators) || operands->size < 1) {
              break;
            }

            PerformMathFunc(operands, operators);
          } else {
            if (operators->is_empty_stack(operators) || operands->size < 2) {
              break;
            }

            Calculate(operands, operators);
          }

          if (operators->is_empty_stack(operators)) {
            break;
          }
        }

        operators->push(operators, token);
        free(token);
        continue;
      }

      free(token);
    }

    free(token);
  }

  while (!operators->is_empty_stack(operators) && operands->size >= 2) {
    Calculate(operands, operators);
  }

  if (!operands->is_empty_stack(operands)) {
    char *res = operands->pop(operands);

    operands->remove_from_stack(&operands);
    operators->remove_from_stack(&operators);

    return res;
  } else {
    operands->remove_from_stack(&operands);
    operators->remove_from_stack(&operators);

    return "error";
  }
}
