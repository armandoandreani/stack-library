# Stack Library

A dynamic integer stack implementation in C with automatic memory management.

## Features

- **Dynamic resizing**: Automatically grows when full and shrinks when underutilized
- **Memory efficient**: Reduces capacity when stack uses less than 25% of allocated space
- **Simple API**: Easy-to-use functions for common stack operations
- **Safe memory management**: Proper allocation and deallocation handling

## Structure

```c
typedef struct {
  int top;        // Index of the top element (-1 if empty)
  int capacity;   // Current maximum capacity
  int *items;     // Array of integers
} Stack;
```

## API Reference

### `Stack *create_stack()`
Creates and initializes a new stack with initial capacity of 1.

**Returns**: Pointer to the new stack, or `NULL` if allocation fails.

```c
Stack *stack = create_stack();
```

### `void destroy_stack(Stack *stack)`
Frees all memory allocated for the stack.

```c
destroy_stack(stack);
```

### `Stack *push(Stack *stack, int item)`
Pushes an item onto the stack. Automatically increases capacity if needed.

**Parameters**:
- `stack`: Pointer to the stack
- `item`: Integer value to push

**Returns**: Pointer to the stack, or `NULL` if reallocation fails.

```c
push(stack, 42);
```

### `int pop(Stack *stack)`
Removes and returns the top element. Automatically shrinks capacity when stack uses ≤25% of space.

**Returns**: The value of the removed element.

**Note**: Terminates program if stack is empty.

```c
int value = pop(stack);
```

### `int peek(Stack *stack)`
Returns the top element without removing it.

**Returns**: The value at the top of the stack.

**Warning**: Does not check if stack is empty.

```c
int value = peek(stack);
```

### `bool isEmpty(Stack *stack)`
Checks if the stack is empty.

**Returns**: `true` if empty, `false` otherwise.

```c
if (isEmpty(stack)) {
    printf("Stack is empty\n");
}
```

### `bool isFull(Stack *stack)`
Checks if the stack is at maximum capacity.

**Returns**: `true` if full, `false` otherwise.

```c
if (isFull(stack)) {
    printf("Stack is full\n");
}
```

### `void print_stack(Stack *stack)`
Prints the current capacity and all elements in the stack.

```c
print_stack(stack);
```

## Usage Example

```c
#include "stack.h"
#include <stdio.h>

int main(void) {
    // Create a new stack
    Stack *stack = create_stack();
    
    // Push some values
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    
    // Print stack contents
    print_stack(stack);
    
    // Pop and print value
    int value = pop(stack);
    printf("Popped: %d\n", value);
    
    // Peek at top value
    if (!isEmpty(stack)) {
        printf("Top: %d\n", peek(stack));
    }
    
    // Clean up
    destroy_stack(stack);
    return 0;
}
```

## Compilation

### As separate files:

Create `stack.h` (header file) and `stack.c` (implementation file), then compile:

```bash
gcc -c stack.c -o stack.o
gcc main.c stack.o -o program
./program
```

### Single command:

```bash
gcc main.c stack.c -o program
./program
```

## Memory Management

- **Growth**: Capacity increases by 1 when full
- **Shrinkage**: Capacity halves when stack uses ≤25% of allocated space
- **Minimum capacity**: Always maintains at least 1 element capacity

## Limitations

- Only stores integer values
- `pop()` terminates the program if called on empty stack
- `peek()` does not check if stack is empty before accessing

## License

Free to use for educational purposes.
