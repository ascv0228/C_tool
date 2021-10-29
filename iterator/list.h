#ifndef LIST_H
#define LIST_H 1
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "queue.h"
#include "stack.h"

typedef struct list_node{
    int data;
    struct list_node *next;
} list_node;
typedef struct list{
    size_t size;
    struct list_node *head, *tail;
}list;

bool list_append(list *list, int data);
bool list_append_from_head(list *list, int data);
int list_pop(list *list);
int list_pop_from_head(list *list);
int list_get(list *list, int position);
int list_len(list *list);
list stack2List(stack *stack);
list queue2List(queue *queue);
void show_all(list *list);
#endif
