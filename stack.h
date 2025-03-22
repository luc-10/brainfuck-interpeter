#ifndef STACK_H
#define STACK_H

// Stack
typedef struct Stack
{
    short int value;
    struct Stack *next;
} Stack;

// Functions
void push(short int val);
short int pop();
short int top();
short int empty();
void freeStack();

#endif