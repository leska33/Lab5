#include "stack.h"

Stack* createStack(int capacity) {
    if (capacity <= 0) {
        printf("Error: Stack capacity must be positive.\n");
        return NULL;
    }
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        printf("Error allocating memory for stack.\n");
        return NULL;
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (int*)malloc(stack->capacity * sizeof(int));
    if (!stack->data) {
        printf("Error allocating memory for stack data.\n");
        free(stack);
        return NULL;
    }
    return stack;
}

bool isEmpty(Stack *stack) {
    if (!stack) {
        printf("Error: Stack does not exist.\n");
        return true;
    }
    return stack->top == -1;
}

bool isFull(Stack *stack) {
    if (!stack) {
        printf("Error: Stack does not exist.\n");
        return false;
    }
    return stack->top == stack->capacity - 1;
}

void push(Stack *stack, int item) {
    if (!stack) {
        printf("Error: Stack does not exist.\n");
        return;
    }
    if (isFull(stack)) {
        printf("Error: Stack is full.\n");
        return;
    }
    stack->data[++stack->top] = item;
}

int pop(Stack *stack) {
    if (!stack) {
        printf("Error: Stack does not exist.\n");
        return INT_MIN;
    }
    if (isEmpty(stack)) {
        printf("Error: Stack is empty.\n");
        return INT_MIN;
    }
    return stack->data[stack->top--];
}

int peek(Stack *stack) {
    if (!stack) {
        printf("Error: Stack does not exist.\n");
        return INT_MIN;
    }
    if (isEmpty(stack)) {
        printf("Error: Stack is empty.\n");
        return INT_MIN;
    }
    return stack->data[stack->top];
}

void printStack(Stack *stack) {
    if (!stack) {
        printf("Error: Stack does not exist.\n");
        return;
    }
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack contents:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->data[i]);
    }
}

void destroyStack(Stack *stack) {
    if (stack) {
        if (stack->data) {
            free(stack->data);
        }
        free(stack);
    }
}

int sumUntilMin(Stack *stack) {
    if (!stack) {
        printf("Error: Stack does not exist.\n");
        return 0;
    }
    if (isEmpty(stack)) {
        printf("Error: Stack is empty.\n");
        return 0;
    }
    int min = stack->data[stack->top];
    int minIndex = stack->top;
    for (int i = stack->top; i >= 0; i--) {
        if (stack->data[i] < min) {
            min = stack->data[i];
            minIndex = i;
        }
    }
    int sum = 0;
    for (int i = stack->top; i > minIndex; i--) {
        sum += stack->data[i];
    }
    return sum;
}

Stack* createFirstStack(int capacity) {
    Stack *stack = createStack(capacity);
    if (!stack) {
        return NULL;
    }
    printf("Enter %d elements for first stack:\n", capacity);
    for (int i = 0; i < capacity; i++) {
        printf("Element %d: ", i + 1);
        int value;
        while (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter an integer: ");
            while (getchar() != '\n');
        }
        push(stack, value);
    }
    return stack;
}

Stack* createSecondStack(int capacity) {
    Stack *stack = createStack(capacity);
    if (!stack) {
        return NULL;
    }
    printf("Enter %d elements for second stack:\n", capacity);
    for (int i = 0; i < capacity; i++) {
        printf("Element %d: ", i + 1);
        int value;
        while (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter an integer: ");
            while (getchar() != '\n');
        }
        push(stack, value);
    }
    return stack;
}

Stack* createMergedStack(Stack *stack1, Stack *stack2) {
    if (!stack1 || !stack2) {
        printf("Error: One of the stacks does not exist.\n");
        return NULL;
    }
    Stack *temp1 = createStack(stack1->capacity);
    Stack *temp2 = createStack(stack2->capacity);
    Stack *result = createStack(stack1->capacity + stack2->capacity);
    if (!temp1 || !temp2 || !result) {
        destroyStack(temp1);
        destroyStack(temp2);
        destroyStack(result);
        return NULL;
    }
    for (int i = 0; i <= stack1->top; i++) {
        push(temp1, stack1->data[i]);
    }
    for (int i = 0; i <= stack2->top; i++) {
        push(temp2, stack2->data[i]);
    }
    while (!isEmpty(temp1) || !isEmpty(temp2)) {
        if (isEmpty(temp1)) {
            push(result, pop(temp2));
        }
        else if (isEmpty(temp2)) {
            push(result, pop(temp1));
        }
        else if (peek(temp1) <= peek(temp2)) {
            push(result, pop(temp1));
        }
        else {
            push(result, pop(temp2));
        }
    }
    destroyStack(temp1);
    destroyStack(temp2);
    Stack *finalResult = createStack(result->capacity);
    while (!isEmpty(result)) {
        push(finalResult, pop(result));
    }
    destroyStack(result);
    return finalResult;
}