#include "mm.h"
#include "stack.h"
#include <stdlib.h>

bool stack_push(stack *stack, int data){
    stack_node *new_top = (stack_node*) malloc(sizeof(stack_node));
    if(!new_top)
    	return false;
    new_top -> data = data;
    if(stack->top)
    {
        new_top->prev = stack->top;
    }
    stack->top = new_top;
    ++stack->size;
    return true;
}

int stack_pop(stack* stack){
    int ret = -1;
    if(stack->size){
        ret = stack->top->data;
        stack_node *tmp_node = stack->top;
        stack->top = stack->top->prev;
        ret = tmp_node->data;
        --stack->size;
        myfree(tmp_node);
        tmp_node =NULL;
    }
    return ret;
    
}
