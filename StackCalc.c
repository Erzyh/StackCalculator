#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct stack {
    int top;
    char items[MAX_SIZE];
} Stack;

void push(Stack* stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Error: Stack is full\n");
        exit(1);
    }
    stack->items[++stack->top] = item;
}

char pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Error: Stack is empty\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

char top(Stack* stack) {
    if (stack->top == -1) {
        printf("Error: Stack is empty\n");
        exit(1);
    }
    return stack->items[stack->top];
}

int is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char operator) {
    switch (operator) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

void infix_to_postfix(char* infix_expression, char* postfix_expression) {
    Stack operator_stack;
    operator_stack.top = -1;
    int i = 0, j = 0;

    while (infix_expression[i] != '\0') {
        char ch = infix_expression[i];
        if (isdigit(ch)) {
            postfix_expression[j++] = ch;
        }
        else if (is_operator(ch)) {
            while (operator_stack.top != -1 && precedence(ch) <= precedence(top(&operator_stack))) {
                postfix_expression[j++] = pop(&operator_stack);
            }
            push(&operator_stack, ch);
        }
        else if (ch == '(') {
            push(&operator_stack, ch);
        }
        else if (ch == ')') {
            while (top(&operator_stack) != '(') {
                postfix_expression[j++] = pop(&operator_stack);
            }
            pop(&operator_stack);
        }
        i++;
    }
    while (operator_stack.top != -1) {
        postfix_expression[j++] = pop(&operator_stack);
    }
    postfix_expression[j] = '\0';
}

int evaluate_postfix(char* postfix_expression) {
    Stack operand_stack;
    operand_stack.top = -1;
    int i = 0;

    while (postfix_expression[i] != '\0') {
        char ch = postfix_expression[i];
        if (isdigit(ch)) {
            push(&operand_stack, ch - '0');
        }
        else if (is_operator(ch)) {
            int operand2 = pop(&operand_stack);
            int operand1 = pop(&operand_stack);
            int result = evaluate(operand1, operand2, ch);
            push(&operand_stack, result);
        }
        i++;
    }
    return pop(&operand_stack);
}

int evaluate(int operand1, int operand2, char operator) {
    switch (operator) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    default:
        return 0;
    }
}

void main() {
    char infix_expression[MAX_SIZE];
    char postfix_expression[MAX_SIZE];
    printf("중위 수식을 입력하세요: ");
    fgets(infix_expression, MAX_SIZE, stdin);
    infix_expression[strcspn(infix_expression, "\n")] = '\0';
    infix_to_postfix(infix_expression, postfix_expression);
    int result = evaluate_postfix(postfix_expression);

    printf("후위 수식: %s\n", postfix_expression);
    printf("결과: %d\n", result);
}
