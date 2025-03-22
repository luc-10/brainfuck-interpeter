#include "stack.h"
#include <stdlib.h>

// Stack variable
Stack *stack = NULL;

// Push
void push(short int val)
{
    Stack *top = (Stack *)malloc(sizeof(Stack));
    top->value = val;
    top->next = stack;
    stack = top;
}

// Pop
short int pop()
{
    Stack *top = stack;
    stack = stack->next;
    short int val = top->value;
    free(top);
    return val;
}

// Top
short int top()
{
    if (empty())
        return -1;
    else
        return stack->value;
}

// Empty
short int empty()
{
    return (stack == NULL);
}

// Deallocate
void freeStack()
{
    if (stack == NULL)
        return;
    Stack *toFree = stack;
    stack = stack->next;
    free(toFree);
    freeStack();
}