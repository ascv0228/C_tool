#include "list.h"
#include "mm.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>

bool list_append(list *list, int data)  //return successful, or not.
{
    bool flag = false;
    if(list->head == NULL){
        list_node *add_node = (list_node*)mycalloc(1,sizeof(list_node));
        add_node->data = data;
        list->head = add_node;
        list->tail = add_node;
        ++list->size;
        flag = true;
        return flag;
    }
    list_node *add_node = (list_node*)mycalloc(1,sizeof(list_node));
    add_node->data = data;
    list->tail->next = add_node;
    list->tail = add_node;
    ++list->size;
    flag = true;
    return flag;
}
bool list_append_from_head(list *list, int data)  //return successful, or not.
{
    bool flag = false;
    if(list->head == NULL){
        list_node *add_node = (list_node*)mycalloc(1,sizeof(list_node));
        add_node->data = data;
        list->head = add_node;
        list->tail = add_node;
        ++list->size;
        flag = true;
        return flag;
    }
    list_node *add_node = (list_node*)mycalloc(1,sizeof(list_node));
    add_node->data = data;
    add_node->next = list->head;
    list->head = add_node;
    ++list->size;
    flag = true;
    return flag;
}
int list_pop(list *list)  //return the delete value, if succeed, or return -1
{
    int ret = -1;
    if(list->head == NULL){
        list->size = 0;
        return ret;
    }
    if(list->head->next == NULL){
        ret = list->head->data;
        myfree(list->head);
        list->head = NULL; 
        list->tail = NULL; 
        list->size = 0;
        return ret;
    }
    list_node *tmp_node = list->head;
    while(tmp_node->next->next){
        tmp_node = tmp_node->next;
    }
    ret = tmp_node->next->data;
    myfree(tmp_node->next);
    tmp_node->next = NULL;
    list->tail = tmp_node;
    --list->size;
    return ret;
}
int list_pop_from_head(list *list)  //return the delete value, if succeed, or return -1
{
    int ret = -1;
    if(list->head == NULL){
        list->size = 0;
        return ret;
    }
    if(list->head->next == NULL){
        ret = list->head->data;
        myfree(list->head);
        list->head = NULL; 
        list->tail = NULL; 
        list->size = 0;
        return ret;
    }
    list_node *tmp_node = list->head;
    ret = list->head->data;
    list->head = list->head->next;
    myfree(tmp_node);
    --list->size;
    return ret;
}

int list_get(list *list, int position) //the first element is located on [0], remainder of position is real position
{
    int len = list->size;
    if(len == 0)
        return -1;
    if(len == 1)
        return list->head->data;
    list_node *tmp_node = list->head;
    int p = position % len;
    for (int i = 0; i < p; ++i){
        tmp_node = tmp_node->next;
    }
    return tmp_node->data;
}
int list_len(list *list)
{
    return list->size;
}
list queue2List(queue *queue){
    if(!queue){
        list res_list = {0};
        return res_list;
    }
    list res_list = {0};
    queue_node *tmp_node = queue->start;
    while(tmp_node){
        list_append(&res_list, tmp_node->data);
        tmp_node = tmp_node->next;
    }
    return res_list;
}
list stack2List(stack *stack){
    if(!stack){
        list res_list = {0};
        return res_list;
    }
    list res_list = {0};
    stack_node *tmp_node = stack->top;
    while(tmp_node){
        list_append(&res_list, tmp_node->data);
        tmp_node = tmp_node->prev;
    }
    return res_list;
}
void show_all(list *list)
{
    list_node *tmp_node = list->head;
    printf("[%d",tmp_node->data);
    for(int i = 1; i < list->size; ++i){
        tmp_node = tmp_node->next;
        printf(", %d",tmp_node->data);
    }
    printf("]\n");
}
