#ifndef STACK_H_
#define STACK_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct last_char {
  char *last_char;
  struct last_char *prev_last_char;
} last_elem;

typedef struct stack_char {
  size_t size;
  last_elem *last;

  void (*push)(struct stack_char *self, char *c);
  char *(*pop)(struct stack_char *self);
  char *(*peek)(struct stack_char *self);

  void (*remove_from_stack)(struct stack_char **self);
  bool (*is_empty_stack)(struct stack_char *self);
} Stack;

Stack *stack_init(void);
void remove_from_stack(Stack **self);
bool is_empty_stack(Stack *self);
void stack_push(Stack *self, char *elem);
char *stack_pop(Stack *self);
char *stack_peek(Stack *self);

#endif