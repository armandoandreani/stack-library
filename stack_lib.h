#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef struct {
  int top;
  int capacity;
  int *items;
} IntStack;

IntStack *create_int_stack();
void destroy_int_stack(IntStack *stack);
void print_int_stack(IntStack *stack);
bool isIntFull(IntStack *stack);
bool isIntEmpty(IntStack *stack);
IntStack *push_to_int(IntStack *stack, int item);
void pop_int(IntStack *stack);
void* peek_int(IntStack *stack);

typedef struct{
    int top;
    int capacity;
    char **items;
} CharStack;

CharStack *create_char_stack();
void destroy_char_stack(CharStack *stack);
void print_char_stack(CharStack *stack);
bool isCharFull(CharStack *stack);
bool isCharEmpty(CharStack *stack);
CharStack *push_to_char(CharStack *stack, char *item);
char *pop_char(CharStack *stack);
void* peek_char(CharStack *stack);

typedef enum{
    INT_STACK,
    CHAR_STACK
} Stack;

void* create_stack(Stack* type);
void* destroy_stack(Stack* type, void* stack);
void* print_stack(Stack* type, void* stack);
bool isStackEmpty(Stack* type, void* stack);
bool isStackFull(Stack* type, void* stack);
void* push(Stack* type, void* stack, int item);
void* pop(Stack* type, void* stack);
void* peek(Stack* type, void* stack);

#endif
