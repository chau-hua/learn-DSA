#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>

extern int* stack;
extern int top;
extern int stack_size;

#define INC_SIZE 10

void init_stack(void);
void clear_stack(void);
int is_empty(void);
int is_full(void);
void push(const int n);
int pop(void);
int get_size(void);

#endif /* stack_h */