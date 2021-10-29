#include "mm.h"
#include "queue.h"

int deQueue(queue* queue)
{
    int ret = -1;
    if(!queue->size)
        return ret; 
    queue_node *tmp_node = queue->start;
    queue->start = queue->start->next;
    ret = tmp_node->data;
    myfree(tmp_node);
    --queue->size;
    tmp_node = NULL;
    return ret;
}

bool enQueue(queue* queue, int data){
    queue_node *tmp_node = queue->start;
    bool flag = false;
    if(!tmp_node){
        ++queue->size;
        queue->start = (queue_node*) mycalloc(1,sizeof(queue_node));
        queue->start->data = data;
        queue->end = queue->start;
        flag = true;
        return flag;
    }
    
    ++queue->size;
    queue->end->next = (queue_node*) mycalloc(1,sizeof(queue_node));
    queue->end = queue->end->next;
    queue->end->data = data;
    flag = true;
    return flag;
}

bool isEnpty(queue *queue){
    return !queue->size;
}

queue* createQueue(){
    return (queue*) mycalloc(1,sizeof(queue));
}
