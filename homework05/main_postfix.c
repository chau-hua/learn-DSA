#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "stack_postfix.h"

int* stack = NULL;
int top = -1;
int stack_size = 100;

int postfix_evaluate(char* expression);
int is_number(char* token);
int is_operator(char* token);
char* get_token(char** expression);
int evaluate(int a, int b, char op);
void stop_program(void);
void convert_infix_to_postfix(char infix[], char postfix[]);
int is_parentheses(char *x);
int is_operator2(char* token);
void postfix_push(char postfix_stack[], int *postfix_top, char x);
char postfix_pop(char postfix_stack[], int *postfix_top);
int priority(char x);

int main(int argc, const char * argv[])
{
    printf("Enter a postfix expression (ex: (2 + 3) / 12: ");
    char expr[100] = {0};
    char postfix[100] = {0};
    scanf("%[^\n]s", expr);
    printf("Expression: %s\n", expr);
    convert_infix_to_postfix(expr, postfix);
    printf("Postfix: %s\n", postfix);
    
    printf("Value = %d\n", postfix_evaluate(postfix));
    return 0;
}

void convert_infix_to_postfix(char infix[], char postfix[])
{
    char *e, x;
    char postfix_stack[100];
    int postfix_top = -1;
    int i = 0;

    e = infix;
    while(*e != '\0')
    {
        if(*e == ' ')
        {
            e++;
            continue;
        }
        else if(*e == '(')
            postfix_push(postfix_stack, &postfix_top, *e);
        else if(*e == ')')
        {
            while((x = postfix_pop(postfix_stack, &postfix_top)) != '(')
            {
                postfix[i++] = x;
                postfix[i++] = ' ';
            }
        }
        else if(isalnum(*e))
        {
            while (*e != ' ' && *e != '\0'
                && !is_parentheses(e) && !is_operator2(e))
            {
                postfix[i++] = *e;
                e++;
            }
            postfix[i++] = ' ';
            continue;
        }
        else
        {
            while(priority(postfix_stack[postfix_top]) >= priority(*e))
            {
                postfix[i++] = postfix_pop(postfix_stack, &postfix_top);
                postfix[i++] = ' ';
            }
            postfix_push(postfix_stack, &postfix_top, *e);
        }
        e++;
    }

    while(postfix_top != -1)
    {
        if(postfix_stack[postfix_top] != '(')
        {
            postfix[i++] = postfix_pop(postfix_stack, &postfix_top);
            if(postfix_top != -1) postfix[i++] = ' ';
        }
        else postfix_top--;
    }
}

int is_parentheses(char *x)
{
    return (*x == '(' || *x == ')');
}

int is_operator2(char* token)
{
    switch (token[0])
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^': return 1;
        default : return 0;
    }
}

void postfix_push(char postfix_stack[], int *postfix_top, char x)
{
    postfix_stack[++(*postfix_top)] = x;
}

char postfix_pop(char postfix_stack[], int *postfix_top)
{
    if(*postfix_top == -1)
    {
        printf("Invalid postfix!\n");
        exit(1);
    }
    else
        return postfix_stack[(*postfix_top)--];
}

int priority(char x)
{
    if(x == '(')
        return 0;
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
    return 0;
}

int postfix_evaluate(char* expression)
{
    init_stack();

    char *token;
    while((token = get_token(&expression)) != NULL)
    {
        if(is_number(token))
            push(atoi(token));
        else if(is_operator(token))
        {
            int val1 = pop();
            int val2 = pop();
            int result = evaluate(val1, val2, *token);
            push(result);
        }
        else
            stop_program();
    }

    if(get_size() == 1)
        return stack[0];
    else
        stop_program();
}

char* get_token(char** expression)
{
    if (*expression == NULL) return NULL;
    char* token = *expression;
    char* end = *expression;
    while (*end != ' ' && *end != '\0') end++;
    if (*end == '\0') *expression = NULL;
    else
    {
        *end = '\0';
        *expression = end+1;
    }
    return token;
}

int is_number(char* token)
{
    for (int i = 0; i < strlen(token); i++)
        if (!isdigit(token[i])) return 0;
    return 1;
}

int is_operator(char* token)
{
    if (strlen(token) != 1) return 0;
    switch (token[0])
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^': return 1;
        default : return 0;
    }
}

int evaluate(int a, int b, char op)
{
    switch (op)
    {
        case '+': return b + a;
        case '-': return b - a;
        case '*': return b * a;
        case '/': return b / a;
        case '^': return pow(b, a);
        default : return 0; // never get this
    }
}

void stop_program()
{
    clear_stack();
    printf("Error: Invalid postfix!\n");
    exit(1);
}