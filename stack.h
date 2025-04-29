#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Stack {
    int *data;
    int top;
    int capacity;
} Stack;
Stack* createStack(int capacity);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void push(Stack *stack, int item);
int pop(Stack *stack);
int peek(Stack *stack);
void printStack(Stack *stack);
void destroyStack(Stack *stack);
int sumUntilMin(Stack *stack);
Stack* createFirstStack(int capacity);
Stack* createSecondStack(int capacity);
Stack* createMergedStack(Stack *stack1, Stack *stack2);

#endif