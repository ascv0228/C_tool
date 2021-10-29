#include <stdio.h>

#include "list.h"
#include "stack.h"

int main(int argc, char* argv[]) {
    stack stack = {0};

    printf("size: %d\n", stack.size);
    printf("top address: %p\n", stack.top);

    printf("add value: %d\n", 99);
    stack_push(&stack, 99);
    printf("add value: %d\n", 87);
    stack_push(&stack, 87);
    printf("add value: %d\n", 66);
    stack_push(&stack, 66);
    printf("add value: %d\n", 12);
    stack_push(&stack, 12);
    printf("add value: %d\n", 7777);
    stack_push(&stack, 7777);
    list lst = stack2List(&stack);
    show_all(&lst);
    printf("size: %d\n", stack.size);
    printf("top address: %p\n", stack.top);

    printf("pop value: %d\n", stack_pop(&stack));
    printf("size: %d\n", stack.size);
    printf("top address: %p\n", stack.top);

    printf("pop value: %d\n", stack_pop(&stack));
    printf("size: %d\n", stack.size);
    printf("top address: %p\n", stack.top);

    printf("pop five value...\n");
    printf("pop value: %d\n", stack_pop(&stack));
    printf("pop value: %d\n", stack_pop(&stack));
    printf("pop value: %d\n", stack_pop(&stack));
    printf("pop value: %d\n", stack_pop(&stack));
    printf("pop value: %d\n", stack_pop(&stack));

    printf("size: %d\n", stack.size);
    printf("top address: %p\n", stack.top);
}
