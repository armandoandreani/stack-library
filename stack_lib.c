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
} IntStack;

typedef struct {
  int top;
  int capacity;
  char **items;
} CharStack;

typedef enum{
    INT_STACK,
    CHAR_STACK
} Stack;


/**
 * Creates and initializes a new integer stack
 *
 * Allocates memory for the stack structure and its internal array.
 * The stack starts with a capacity of 1 and no elements (top = -1).
 *
 * @return Pointer to the newly created stack, or NULL if allocation fails
 */
IntStack *create_int_stack() {
  IntStack *int_stack = malloc(sizeof(IntStack));

  // Returns NULL if memory allocation fails
  if (!int_stack) {
    return NULL;
  }

  int_stack->top = -1;
  int_stack->capacity = 1;
  int_stack->items = (int*)malloc(int_stack->capacity * sizeof(int));

  // Returns NULL if memory allocation fails
  if (!int_stack->items) {
    free(int_stack);
    return NULL;
  }

  return int_stack;
}

/**
 * Creates and initializes a new char stack
 *
 * Allocates memory for the stack structure and its internal array.
 * The stack starts with a capacity of 1 and no elements (top = -1).
 *
 * @return Pointer to the newly created stack, or NULL if allocation fails
 */
CharStack *create_char_stack() {
    CharStack *char_stack = malloc(sizeof(CharStack));

    //Returns NULL if memalloc fails.
    if(!char_stack) {
        return NULL;
    }

    char_stack->top = -1;
    char_stack->capacity = 1;
    char_stack->items = (char**)malloc(char_stack->capacity * sizeof(char*));

    // Returns NULL if the memalloc fails.
    if(!char_stack->items) {
        free(char_stack);
        return NULL;
    }

    return char_stack;
}

/**
 * Destroys the stack and frees all allocated memory
 *
 * Frees both the internal items array and the stack structure itself.
 *
 * @param stack: Pointer to the stack to be destroyed
 */
void destroy_int_stack(IntStack *stack) {
  free(stack->items);
  free(stack);
}

/**
 * Destroys the char stack and frees all allocated memory
 *
 * Frees both the internal items array and the stack structure itself.
 *
 * @param stack: Pointer to the stack to be destroyed
 */
void destroy_char_stack(CharStack *stack) {
  free(stack->items);
  free(stack);
}

/**
 * Checks if the integer stack is full
 *
 * @param stack: Pointer to the stack
 * @return true if the stack is at maximum capacity, false otherwise
 */
bool isIntFull(IntStack *stack) {
  return stack->top == stack->capacity - 1;
}

/**
 * Checks if the char stack is full
 *
 * @param stack: Pointer to the stack
 * @return true if the stack is at maximum capacity, false otherwise
 */
bool isCharFull(CharStack *stack) {
  return stack->top == stack->capacity - 1;
}

/**
 * Checks if the integer stack is empty
 *
 * @param stack: Pointer to the stack
 * @return true if the stack contains no elements, false otherwise
 */
bool isIntEmpty(IntStack* stack) {
    return stack->top == -1;
}

/**
 * Checks if the char stack is empty
 *
 * @param stack: Pointer to the stack
 * @return true if the stack contains no elements, false otherwise
 */
bool isCharEmpty(CharStack* stack) {
    return stack->top == -1;
}

/**
 * Pushes an item onto the integer stack
 *
 * If the stack is full, it automatically increases its capacity by 1.
 * The new item is placed at the top of the stack.
 *
 * @param stack: Pointer to the stack
 * @param item: Integer value to be pushed onto the stack
 * @return Pointer to the stack, or NULL if reallocation fails
 */
IntStack *push_to_int(IntStack *stack, int item) {
  if (isIntFull(stack)) {
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
 * Pushes an item onto the char stack
 *
 * If the stack is full, it automatically increases its capacity by 1.
 * The new item is placed at the top of the stack.
 *
 * @param stack: Pointer to the stack
 * @param item: Char pointer value to be pushed onto the stack
 * @return Pointer to the stack, or NULL if reallocation fails
 */
CharStack *push_to_char(CharStack *stack, char *item) {
  if (isCharFull(stack)) {
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
  stack->items[stack->top] = item;
  return stack;
}

/**
 * Prints the contents of the int stack
 *
 * Displays the current capacity and all elements in the stack
 * from bottom (index 0) to top (index stack->top).
 *
 * @param stack: Pointer to the stack to be printed
 */
void print_int_stack(IntStack* stack) {
    printf("The stack size is : %d\n", stack->capacity);
    for(int i = 0; i <= stack->top; i++){
        printf("Stack item number (%d) : %d\n", i, stack->items[i]);
    }
}

/**
 * Prints the contents of the char stack
 *
 * Displays the current capacity and all elements in the stack
 * from bottom (index 0) to top (index stack->top).
 *
 * @param stack: Pointer to the stack to be printed
 */
void print_char_stack(CharStack* stack) {
    printf("The stack size is : %d\n", stack->capacity);
    for(int i = 0; i <= stack->top; i++){
        printf("Stack item number (%d) : %s\n", i, stack->items[i]);
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
int pop_int(IntStack *stack) {
    if (isIntEmpty(stack)) {
        printf("Stack is empty!\n");
        exit(1);
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
 * Removes and returns the top element from the stack
 *
 * If the stack becomes too sparse (uses only 1/4 of its capacity),
 * the capacity is reduced by half to save memory.
 * Terminates the program if the stack is empty.
 *
 * @param stack: Pointer to the stack
 * @return The value of the removed top element
 */
char* pop_char(CharStack *stack) {
    if (isCharEmpty(stack)) {
        printf("Stack is empty!\n");
        exit(1);
    }
    char* item = stack->items[stack->top];
    stack->top--;
    // Shrink capacity if stack is using less than 1/4 of allocated space
    if (stack->top + 1 <= stack->capacity / 4 && stack->capacity > 1) {
        int new_capacity = stack->capacity / 2;
        char **temp = realloc(stack->items, new_capacity * sizeof(char*));
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
 * @return The value at the top of the stack
 */
int peek_int(IntStack* stack) {
    if(isIntEmpty(stack)) {
        printf("The stack is empty!\n");
        exit(1);
    }
    return stack->items[stack->top];
}

/**
 * Returns the top element without removing it
 *
 * @param stack: Pointer to the stack
 * @return The value at the top of the stack
 */
char* peek_char(CharStack* stack) {
    if(isCharEmpty(stack)) {
        printf("The stack is empty!\n");
        exit(1);
    }
    return stack->items[stack->top];
}

/*
 * Creates a generic stack of the specified type
 *
 * Allocates and initializes either an IntStack or CharStack based on the
 * provided type parameter.
 *
 * @param type: The type of stack to create (INT_STACK or CHAR_STACK)
 * @return Pointer to the newly created stack as void*, or terminates if invalid type
 */
void* create_stack(Stack type) {
    if(type == INT_STACK) {
        return create_int_stack();
    }
    if(type == CHAR_STACK){
        return create_char_stack();
    }
    exit(1);
}

/*
 * Destroys a stack and frees all allocated memory
 *
 * Calls the appropriate destructor function based on the stack type.
 * The caller must ensure the type matches the actual stack being destroyed.
 *
 * @param type: The type of stack being destroyed (INT_STACK or CHAR_STACK)
 * @param stack: Void pointer to the stack structure to be destroyed
 */
void destroy_stack(Stack type, void* stack) {
    if(type == INT_STACK) {
        destroy_int_stack(stack);
        return;
    }
    if(type == CHAR_STACK) {
        destroy_char_stack(stack);
        return;
    }
    exit(1);
}

/*
 * Prints the contents of a stack
 *
 * Displays all elements in the stack along with capacity information.
 * The output format depends on the stack type.
 *
 * @param type: The type of stack to print (INT_STACK or CHAR_STACK)
 * @param stack: Void pointer to the stack structure to be printed
 */
void print_stack(Stack type, void* stack) {
    if(type == INT_STACK) {
        print_int_stack(stack);
        return;
    }
    if(type == CHAR_STACK) {
        print_char_stack(stack);
        return;
    }
    exit(1);
}

/*
 * Checks if a stack is empty
 *
 * Determines whether the stack contains any elements by checking the
 * appropriate type-specific is(type)Empty function.
 *
 * @param type: The type of stack to check (INT_STACK or CHAR_STACK)
 * @param stack: Void pointer to the stack structure to be checked
 * @return true if the stack is empty (top == -1), false otherwise
 *         Terminates program if invalid type is provided
 */
bool isStackEmpty(Stack type, void* stack){
    if(type == INT_STACK) return isIntEmpty(stack);
    if(type == CHAR_STACK) return isCharEmpty(stack);
    exit(1);
}

/*
 * Checks if a stack is full
 *
 * Determines whether the stack has reached maximum capacity by checking the
 * appropriate type-specific is(type)Full function.
 *
 * @param type: The type of stack to check (INT_STACK or CHAR_STACK)
 * @param stack: Void pointer to the stack structure to be checked
 * @return true if the stack is full (top == capacity - 1), false otherwise
 *         Terminates program if invalid type is provided
 */
bool isStackFull(Stack type, void* stack){
    if(type == INT_STACK) return isIntFull(stack);
    if(type == CHAR_STACK) return isCharFull(stack);
    exit(1);
}

/*
 * Generic push function that delegates to type-specific implementations
 *
 * Acts as a dispatcher that routes push operations to the appropriate
 * stack type (integer or character) based on the StackType parameter.
 * The type-specific functions handle proper casting and dereferencing.
 *
 * @param type: The type of stack (INT_STACK or CHAR_STACK)
 * @param stack: Void pointer to the stack structure
 * @param item: Void pointer to the item to push (must be passed by address)
 * @return Void pointer to the updated stack after push operation
 *         Returns NULL if type-specific push fails
 *
 * Example usage:
 *   int value = 42;
 *   push(INT_STACK, my_stack, value);
 */
void* push(Stack type, void* stack, void* item) {
    if(type == INT_STACK) return push_to_int(stack, (int)(intptr_t)item);
    if(type == CHAR_STACK) return push_to_char(stack, (char*)item);
    exit(1);
}

/*
 * Generic pop function that delegates to type-specific implementations
 *
 * Acts as a dispatcher that routes pop operations to the appropriate
 * stack type (integer or character) based on the StackType parameter.
 * Removes and returns the top element from the specified stack.
 *
 * @param type: The type of stack (INT_STACK or CHAR_STACK)
 * @param stack: Void pointer to the stack structure
 * @return Void pointer to the popped value (must be cast to appropriate type)
 *         For INT_STACK: cast to (intptr_t) for integer value
 *         For CHAR_STACK: cast to (char*)
 *         Terminates program if invalid type is provided
 *
 * Example usage:
 *   int value = (int)(intptr_t)pop(INT_STACK, my_stack);
 *   printf("Popped: %d\n", value);
 *
 * Note: The caller is responsible for properly casting
 *       the returned void pointer based on the stack type
 */
void* pop(Stack type, void* stack){
    if(type == INT_STACK) return (void*)(intptr_t)pop_int(stack);
    if(type == CHAR_STACK) return pop_char(stack);
    exit(1);
}

/*
 * Generic peek function that delegates to type-specific implementations
 *
 * Acts as a dispatcher that routes peek operations to the appropriate
 * stack type based on the StackType parameter. Returns the top element
 * without removing it from the stack.
 *
 * @param type: The type of stack (INT_STACK or CHAR_STACK)
 * @param stack: Void pointer to the stack structure
 * @return Void pointer to the top element value (must be cast to appropriate type)
 *         For INT_STACK: cast to (intptr_t) for integer value
 *         For CHAR_STACK: cast to (char*)
 *
 * Example usage:
 *   int value = (int)(intptr_t)peek(INT_STACK, my_stack);
 *   printf("Top: %d\n", value);
 */
void* peek(Stack type, void* stack){
    if(type == INT_STACK) return (void*)(intptr_t)peek_int(stack);
    if(type == CHAR_STACK) return peek_char(stack);
    exit(1);
}
