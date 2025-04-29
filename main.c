#include "stack.h"
#include <stdio.h>

void display_menu() {
    printf("\nStack Management System\n");
    printf("1. Create stack and find sum until min element\n");
    printf("2. Create first stack\n");
    printf("3. Create second stack\n");
    printf("4. Merge two stacks in ascending order\n");
    printf("5. View stack contents\n");
    printf("6. Push element to stack\n");
    printf("7. Pop element from stack\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int getPositiveInteger(const char *prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value > 0) {
            return value;
        }
        printf("Input error. Please enter a positive integer.\n");
        while (getchar() != '\n');
    }
}

int main() {
    Stack *mainStack = NULL;
    Stack *stack1 = NULL;
    Stack *stack2 = NULL;
    Stack *mergedStack = NULL;
    int choice;
    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Input error. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        if (choice == 0) {
            break;
        }
        switch (choice) {
            case 1: {
                if (mainStack) {
                    printf("Clearing existing stack...\n");
                    destroyStack(mainStack);
                }
                int capacity = getPositiveInteger("Enter maximum stack size: ");
                mainStack = createStack(capacity);
                if (!mainStack) {
                    printf("Stack creation error.\n");
                    break;
                }
                printf("Enter %d stack elements:\n", capacity);
                for (int i = 0; i < capacity; i++) {
                    printf("Element %d: ", i + 1);
                    int value;
                    while (scanf("%d", &value) != 1) {
                        printf("Input error. Please enter an integer: ");
                        while (getchar() != '\n');
                    }
                    push(mainStack, value);
                }
                printf("\nStack contents:\n");
                printStack(mainStack);
                int sum = sumUntilMin(mainStack);
                printf("Sum of elements above minimum: %d\n", sum);
                break;
            }
            case 2: {
                if (stack1) {
                    printf("Clearing existing first stack...\n");
                    destroyStack(stack1);
                }
                int capacity = getPositiveInteger("Enter size for first stack: ");
                stack1 = createFirstStack(capacity);
                if (stack1) {
                    printf("\nFirst stack created:\n");
                    printStack(stack1);
                }
                break;
            }
            case 3: {
                if (stack2) {
                    printf("Clearing existing second stack...\n");
                    destroyStack(stack2);
                }
                int capacity = getPositiveInteger("Enter size for second stack: ");
                stack2 = createSecondStack(capacity);
                if (stack2) {
                    printf("\nSecond stack created:\n");
                    printStack(stack2);
                }
                break;
            }
            case 4: {
                if (!stack1 || !stack2) {
                    printf("Please create both stacks first.\n");
                    break;
                }
                if (mergedStack) destroyStack(mergedStack);
                mergedStack = createMergedStack(stack1, stack2);
                if (mergedStack) {
                    printf("\nMerged stack:\n");
                    printStack(mergedStack);
                }
                break;
            }
            case 5: {
                printf("\nSelect stack to view:\n");
                printf("1. Main stack\n");
                printf("2. First stack\n");
                printf("3. Second stack\n");
                printf("4. Merged stack\n");
                printf("Choice: ");
                int stackChoice;
                if (scanf("%d", &stackChoice) != 1) {
                    printf("Input error.\n");
                    while (getchar() != '\n');
                    break;
                }
                Stack *stackToPrint = NULL;
                switch (stackChoice) {
                    case 1: stackToPrint = mainStack; break;
                    case 2: stackToPrint = stack1; break;
                    case 3: stackToPrint = stack2; break;
                    case 4: stackToPrint = mergedStack; break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                if (stackToPrint) {
                    printf("\nStack contents:\n");
                    printStack(stackToPrint);
                } else {
                    printf("Stack not created.\n");
                }
                break;
            }
            case 6: {
                printf("\nSelect stack to push to:\n");
                printf("1. Main stack\n");
                printf("2. First stack\n");
                printf("3. Second stack\n");
                printf("Choice: ");
                int stackChoice;
                if (scanf("%d", &stackChoice) != 1) {
                    printf("Input error.\n");
                    while (getchar() != '\n');
                    break;
                }
                Stack *targetStack = NULL;
                switch (stackChoice) {
                    case 1: targetStack = mainStack; break;
                    case 2: targetStack = stack1; break;
                    case 3: targetStack = stack2; break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                if (!targetStack) {
                    printf("Please create the stack first.\n");
                    break;
                }
                if (isFull(targetStack)) {
                    printf("Stack is full.\n");
                    break;
                }
                printf("Enter element value: ");
                int value;
                if (scanf("%d", &value) != 1) {
                    printf("Input error.\n");
                    while (getchar() != '\n');
                    break;
                }
                push(targetStack, value);
                printf("Element pushed. Current stack:\n");
                printStack(targetStack);
                break;
            }
            case 7: {
                printf("\nSelect stack to pop from:\n");
                printf("1. Main stack\n");
                printf("2. First stack\n");
                printf("3. Second stack\n");
                printf("Choice: ");
                int stackChoice;
                if (scanf("%d", &stackChoice) != 1) {
                    printf("Input error.\n");
                    while (getchar() != '\n');
                    break;
                }
                Stack *targetStack = NULL;
                switch (stackChoice) {
                    case 1: targetStack = mainStack; break;
                    case 2: targetStack = stack1; break;
                    case 3: targetStack = stack2; break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                if (!targetStack) {
                    printf("Stack not created.\n");
                    break;
                }
                if (isEmpty(targetStack)) {
                    printf("Stack is empty.\n");
                    break;
                }
                int value = pop(targetStack);
                printf("Popped element: %d\n", value);
                printf("Current stack:\n");
                printStack(targetStack);
                break;
            }
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    destroyStack(mainStack);
    destroyStack(stack1);
    destroyStack(stack2);
    destroyStack(mergedStack);
    return 0;
}