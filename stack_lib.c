#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/*
 * Enumeration
 *
 * @field INT_STACK: Represents an integer stack
 * @field CHAR_STACK: Represents a stack of char pointers (strings)
 */

typedef enum{
    INT_STACK,
    CHAR_STACK,
} StackType;


/**
 * Stack structure
 *
 * @field type: The type of the stack (from enum StackType)
 * @field top: Index of the top element (-1 means empty)
 * @field capacity: Current maximum capacity of the stack
 * @field items: Dynamically allocated array storing the stack's elements
 */

 typedef struct {
    StackType type;
    int top;
    int capacity;
    void *items;
} GenericStack;

/*
 * create_stack
 *
 * Allocates and initializes a new stack with an initial capacity of 1.
 * Allocates the correct type of array depending on the stack type.
 *
 * Returns a pointer to the created stack, or NULL on allocation failure.
 */
GenericStack* create_stack(StackType type) {
     GenericStack* stack = malloc(sizeof(GenericStack));
     if(!stack) return NULL;

     stack->type = type;
     stack->capacity = 1;
     stack->top = -1;

     if(type == INT_STACK) {
         stack->items = (int*)malloc(stack->capacity * sizeof(int));
         if(!stack->items) return NULL;
     }
     if(type == CHAR_STACK) {
         stack->items = (char**)malloc(stack->capacity * sizeof(char*));
         if(!stack->items) return NULL;
     }
     return stack;
}

/*
 * isFull
 *
 * Returns true if the stack has reached its capacity.
 */
bool isFull(GenericStack* stack) {
    return stack->top == stack->capacity - 1;
}

/*
 * isEmpty
 *
 * Returns true if the stack contains no elements.
 */
bool isEmpty(GenericStack* stack) {
    return stack->top == -1;
}

/*
 * push
 *
 * Pushes a new element into the stack.
 * If the stack is full, increases the capacity by 1 (realloc).
 *
 * @param item: Passed as void*, internally cast to the correct type.
 *
 * Returns the stack pointer (or NULL on reallocation failure).
 */
GenericStack* push(GenericStack* stack, void* item) {
    if(stack->type == INT_STACK) {
        int* int_items = (int*) stack->items;
        int int_item = (int)(intptr_t) item;
        if(isFull(stack)){
            int new_capacity = stack->capacity + 1;
            int *temp = realloc(stack->items, new_capacity * sizeof(int));
            if (!temp) {
                printf("Memory reallocation failed!\n");
                return NULL;
            }
            stack->items = temp;
            stack->capacity = new_capacity;
        }
        stack->top++;
        int_items[stack->top] = int_item;
    }

    if(stack->type == CHAR_STACK) {
        char** char_items = (char**)stack->items;
        char* char_item = (char*)item;
        if(isFull(stack)){
            int new_capacity = stack->capacity + 1;
            char **temp = realloc(stack->items, new_capacity * sizeof(char*));
            if (!temp) {
                printf("Memory reallocation failed!\n");
                return NULL;
            }
            stack->items = temp;
            stack->capacity = new_capacity;
        }
        stack->top++;
        char_items[stack->top] = char_item;
    }
    return stack;
}

/*
 * pop
 *
 * Removes the top element from the stack.
 * Prints an error if the stack is empty.
 *
 * Shrinks capacity by half if usage falls below 25%.
 *
 * Returns the stack pointer.
 */
GenericStack* pop(GenericStack* stack) {
    if(isEmpty(stack)) {
        printf("Stack is empty!\n");
    }
    if(stack->type == INT_STACK) {
        int int_items = (int)(intptr_t)stack->items;
        stack->top--;
        if (stack->top + 1 <= stack->capacity / 4 && stack->capacity > 1) {
            int new_capacity = stack->capacity / 2;
            int *temp = realloc(stack->items, new_capacity * sizeof(int));
            if (temp) {
                stack->items = temp;
                stack->capacity = new_capacity;
            }
        }
    }
    if(stack->type == CHAR_STACK) {
        char* char_items = (char*)stack->items;
        stack->top--;
        if (stack->top + 1 <= stack->capacity / 4 && stack->capacity > 1) {
            int new_capacity = stack->capacity / 2;
            char *temp = realloc(stack->items, new_capacity * sizeof(char*));
            if (temp) {
                stack->items = temp;
                stack->capacity = new_capacity;
            }
        }
    }
    stack->capacity--;
    return stack;
}

/*
 * print_stack
 *
 * Prints the entire stack:
 * - Its capacity
 * - Each stored element
 */
void print_stack(GenericStack* stack) {
     StackType type = stack->type;
    if(type == INT_STACK) {
        int* int_items = (int*)stack->items;
        printf("The stack size is : %d\n", stack->capacity);
        for(int i = 0; i <= stack->top; i++){
            printf("Stack item number (%d) : %d\n", i+1, int_items[i]);
        }
    }
    if(type == CHAR_STACK) {
        char** char_items = (char**)stack->items;
        printf("The stack size is : %d\n", stack->capacity);
        for(int i = 0; i <= stack->top; i++){
            printf("Stack item number (%d) : %s\n", i+1, char_items[i]);
        }
    }
}

/*
 * destroy_stack
 *
 * Frees the allocated items array and the stack structure itself.
 */
void destroy_stack(GenericStack* stack) {
    free(stack->items);
    free(stack);
    printf("\nStack Destroyed!\n");
}

/*
 * peek
 *
 * Prints the element at the top of the stack without removing it.
 *
 * Always returns NULL.
 */
void* peek (GenericStack* stack) {
    if(stack->type == INT_STACK){
        int* int_items = (int*)stack->items;
        int top_item = int_items[stack->top];
        printf("The top item is: %d\n", top_item);
    }
    if(stack->type == CHAR_STACK){
        char** char_items = (char**)stack->items;
        printf("The top item is: %s\n", char_items[stack->top]);
    }
    return NULL;
}
