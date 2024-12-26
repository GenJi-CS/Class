#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX 100
typedef struct
{
    int data[MAX];
    int top;
} Stack;
void initStack(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
int isFull(Stack *s) { return s->top == MAX - 1; }
void push(Stack *s, int value)
{
    if (isFull(s))
    {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->data[++(s->top)] = value;
}
int pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}
int evaluatePostfix(char *expression)
{
    Stack stack;
    initStack(&stack);
    for (int i = 0; expression[i] != '\0'; i++)
    {
        char ch = expression[i];
        if (isdigit(ch))
        {
            push(&stack, ch - '0');
        }
        else
        {
            int val2 = pop(&stack);
            int val1 = pop(&stack);
            switch (ch)
            {
            case '+':
                push(&stack, val1 + val2);
                break;
            case '-':
                push(&stack, val1 - val2);
                break;
            case '*':
                push(&stack, val1 * val2);
                break;
            case '/':
                if (val2 == 0)
                {
                    printf("Division by zero error\n");
                    exit(1);
                }
                push(&stack, val1 / val2);
                break;
            case '^':
                push(&stack, pow(val1, val2));
                break;
            default:
                printf("Invalid operator: %c\n", ch);
                exit(1);
            }
        }
    }
    return pop(&stack);
}
int main()
{
    char postfix[MAX];
    printf("Enter a postfix expression: ");
    scanf("%s", postfix);
    int result = evaluatePostfix(postfix);
    printf("The result of the postfix expression is: %d\n", result);
    return 0;
}