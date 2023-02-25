#include "stack_postfix.h"

void init_stack(void)
{
    stack_size = INC_SIZE;
    stack = (int *)malloc(stack_size * sizeof(int));
    top = -1;
    // TODO: allocate stack, set top = -1
}
void clear_stack(void)
{
    free(stack);
    top = -1;
    // TODO: deallocate stack, set top = -1
}
void push(const int n)
{
    if(is_full())
    {
        stack_size += INC_SIZE;
        stack = (int *)realloc(stack, stack_size * sizeof(int));
    }
    stack[++top] = n;
    // TODO: If full then reallocate stack, 
    // increase stack_size by INC_SIZE then update top
}

int is_empty(void)
{
    return top == -1;
}
int is_full(void)
{
    return top == stack_size - 1;
}

int pop(void)
{
    if (!is_empty()) return stack[top--];
    else
    {
        printf("Invalid postfix!\n");
        exit(1);
    }
}
int get_size(void)
{
    return top + 1;
}