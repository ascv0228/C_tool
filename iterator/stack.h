#ifndef STACK_H
#define STACK_H 1
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct stack_node{
    int data;
    struct stack_node *prev;
} stack_node;
typedef struct stack{
    int size;
    struct stack_node *top;
} stack;

int stack_pop(stack* stack);
bool stack_push(stack* stack, int data);
#endif

