#ifndef QUEUE_H
#define QUEUE_H 1
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct queue_node{
    int data;
    struct queue_node *next;
} queue_node;
typedef struct queue{
    int size;
    struct queue_node *start,*end;
} queue;

int deQueue(queue* queue);
bool enQueue(queue* queue, int data);
bool isEnpty(queue *queue);
queue* createQueue();
#endif
