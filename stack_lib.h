#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef enum{
    INT_STACK,
    CHAR_STACK
} StackType;

typedef struct {
    StackType type;
    int top;
    int capacity;
    void *items;
} GenericStack;


GenericStack* create_stack(StackType type);
GenericStack* pop(GenericStack* stack);
GenericStack* push(GenericStack* stack, void* item);
void destroy_stack(GenericStack* stack);
void* print_stack(GenericStack* stack);
void* peek(GenericStack* stack);
bool isFull(GenericStack* stack);
bool isEmpty(GenericStack* stack);

#endif
