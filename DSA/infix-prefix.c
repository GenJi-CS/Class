#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int top;
    char items[MAX][MAX];
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char *item) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    strcpy(s->items[++s->top], item);
}

char* pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return NULL;
    }
    return s->items[s->top--];
}

char* peek(Stack *s) {
    if (isEmpty(s))
        return NULL;
    return s->items[s->top];
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

int precedence(char ch) {
    switch (ch) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void infixToPrefix(char *infix, char *prefix) {
    Stack operators;
    initStack(&operators);
    char temp[MAX][MAX];
    int k = 0;

    reverseString(infix);

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isdigit(token) || isalpha(token)) {
            char operand[2] = {token, '\0'};
            strcpy(temp[k++], operand);
        } else if (token == ')') {
            char op[2] = {token, '\0'};
            push(&operators, op);
        } else if (token == '(') {
            while (!isEmpty(&operators) && peek(&operators)[0] != ')') {
                strcpy(temp[k++], pop(&operators));
            }
            pop(&operators);
        } else if (isOperator(token)) {
            while (!isEmpty(&operators) && precedence(peek(&operators)[0]) >= precedence(token)) {
                strcpy(temp[k++], pop(&operators));
            }
            char op[2] = {token, '\0'};
            push(&operators, op);
        }
    }

    while (!isEmpty(&operators)) {
        strcpy(temp[k++], pop(&operators));
    }

    for (int i = 0; i < k; i++) {
        strcat(prefix, temp[k - i - 1]);
    }
}

int main() {
    char infix[MAX], prefix[MAX] = "";
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);

    printf("Prefix expression: %s\n", prefix);

    return 0;
}