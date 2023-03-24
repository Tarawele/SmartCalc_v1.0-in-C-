#include "s21_stack.h"

Stack *stack_init(void) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));

  stack->last = NULL;
  stack->size = 0;

  stack->push = stack_push;
  stack->pop = stack_pop;
  stack->peek = stack_peek;

  stack->remove_from_stack = remove_from_stack;
  stack->is_empty_stack = is_empty_stack;

  return stack;
}

bool is_empty_stack(Stack *self) {
  int state;
  if (self->size > 0) {
    state = 0;
  } else {
    state = 1;
  }
  return state;
}

void remove_from_stack(Stack **self) {
  last_elem *last;
  last_elem *prev_last;

  last = (*self)->last;
  prev_last = NULL;

  while (last) {
    prev_last = last->prev_last_char;
    if (last->last_char) {
      free(last->last_char);
    }
    free(last);
    last = prev_last;
  }

  free(*self);
}

void stack_push(Stack *self, char *elem) {
  last_elem *last = (last_elem *)malloc(sizeof(last_elem));
  asprintf(&last->last_char, "%s", elem);

  last->prev_last_char = self->last;
  self->last = last;
  self->size = self->size + 1;
}

char *stack_pop(Stack *self) {
  char *c = NULL, *cur_last;
  last_elem *last;

  if (self->size > 0) {
    last = self->last->prev_last_char;
    cur_last = self->last->last_char;
    if (cur_last) {
      c = cur_last;
    }
    free(self->last);
    self->last = last;
    self->size = self->size - 1;
  }

  return c;
}

char *stack_peek(Stack *self) {
  char *last_char_from_stack;

  last_char_from_stack = self->last->last_char;
  return last_char_from_stack;
}
