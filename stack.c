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
    int prev = INT_MAX;
    for (int i = 0; i < capacity; i++) {
        printf("Element %d (must be <= %d): ", i + 1, prev);
        int value;
        while (1) {
            while (scanf("%d", &value) != 1) {
                printf("Invalid input: ");
                while (getchar() != '\n');
            }
            if (value <= prev) {
                prev = value;
                break;
            } else {
                printf("Error. The number must be less (%d). Try again: ", prev);
            }
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
    int prev = INT_MIN;
    for (int i = 0; i < capacity; i++) {
        printf("Element %d (must be > %d): ", i + 1, prev);
        int value;
        while (1) {
            while (scanf("%d", &value) != 1) {
                printf("Invalid input. Please enter an integer: ");
                while (getchar() != '\n');
            }
            if (value > prev) {
                prev = value;
                break;
            } else {
                printf("Error. The number must be greater (%d). Try again: ", prev);
            }
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
    Stack *result = createStack(stack1->capacity + stack2->capacity);
    if (!result) {
        return NULL;
    }
    int i = stack1->top;
    int j = 0;
    while (i >= 0 && j <= stack2->top) {
        if (stack1->data[i] <= stack2->data[j]) {
            push(result, stack1->data[i]);
            i--;
        } else {
            push(result, stack2->data[j]);
            j++;
        }
    }
    while (i >= 0) {
        push(result, stack1->data[i]);
        i--;
    }
    while (j <= stack2->top) {
        push(result, stack2->data[j]);
        j++;
    }
    return result;
}