#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * Stack structure
 *
 * @field top: Index of the top element in the stack (-1 if empty)
 * @field capacity: Current maximum number of elements the stack can hold
 * @field items: Dynamically allocated array containing stack elements
 */
typedef struct {
  int top;
  int capacity;
  int *items;
} Stack;

/**
 * Creates and initializes a new stack
 *
 * Allocates memory for the stack structure and its internal array.
 * The stack starts with a capacity of 1 and no elements (top = -1).
 *
 * @return Pointer to the newly created stack, or NULL if allocation fails
 */
Stack *create_stack() {
  Stack *stack = malloc(sizeof(Stack));
  // Returns NULL if memory allocation fails
  if (!stack) {
    return NULL;
  }
  stack->top = -1;
  stack->capacity = 1;
  stack->items = (int*)malloc(stack->capacity * sizeof(int));
  // Returns NULL if memory allocation fails
  if (!stack->items) {
    free(stack);
    return NULL;
  }
  return stack;
}

/**
 * Destroys the stack and frees all allocated memory
 *
 * Frees both the internal items array and the stack structure itself.
 *
 * @param stack: Pointer to the stack to be destroyed
 */
void destroy_stack(Stack *stack) {
  free(stack->items);
  free(stack);
}

/**
 * Checks if the stack is full
 *
 * @param stack: Pointer to the stack
 * @return true if the stack is at maximum capacity, false otherwise
 */
bool isFull(Stack *stack) {
  return stack->top == stack->capacity - 1;
}

/**
 * Checks if the stack is empty
 *
 * @param stack: Pointer to the stack
 * @return true if the stack contains no elements, false otherwise
 */
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

/**
 * Pushes an item onto the stack
 *
 * If the stack is full, it automatically increases its capacity by 1.
 * The new item is placed at the top of the stack.
 *
 * @param stack: Pointer to the stack
 * @param item: Integer value to be pushed onto the stack
 * @return Pointer to the stack, or NULL if reallocation fails
 */
Stack *push(Stack *stack, int item) {
  if (isFull(stack)) {
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
  stack->items[stack->top] = item;
  return stack;
}

/**
 * Prints the contents of the stack
 *
 * Displays the current capacity and all elements in the stack
 * from bottom (index 0) to top (index stack->top).
 *
 * @param stack: Pointer to the stack to be printed
 */
void print_stack(Stack* stack) {
    printf("The stack size is : %d\n", stack->capacity);
    for(int i = 0; i <= stack->top; i++){
        printf("Stack item number (%d) : %d\n", i, stack->items[i]);
    }
}

/**
 * Removes and returns the top element from the stack
 *
 * If the stack becomes too sparse (uses only 1/4 of its capacity),
 * the capacity is reduced by half to save memory.
 * Terminates the program if the stack is empty.
 *
 * @param stack: Pointer to the stack
 * @return The value of the removed top element
 */
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
    }
    int item = stack->items[stack->top];
    stack->top--;
    // Shrink capacity if stack is using less than 1/4 of allocated space
    if (stack->top + 1 <= stack->capacity / 4 && stack->capacity > 1) {
        int new_capacity = stack->capacity / 2;
        int *temp = realloc(stack->items, new_capacity * sizeof(int));
        if (temp) {
            stack->items = temp;
            stack->capacity = new_capacity;
        }
    }
    return item;
}

/**
 * Returns the top element without removing it
 *
 * @param stack: Pointer to the stack
 * @return The value at the top of the stack (does not check if stack is empty)
 */
int peek(Stack* stack) {
    if(isEmpty(stack)) {
        printf("The stack is empty!");
    }
    return stack->items[stack->top];
}

int main(void) {
    Stack* stack = create_stack();
    pop(stack);
    return 0;
}
