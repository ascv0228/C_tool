#include <stdio.h>
#include "list.h"
#include "queue.h"

int main(int argc, char* argv[]) {
    queue queue = {0};

    printf("size: %d\n", queue.size);
    printf("top address: %p\n", queue.start);
    printf("tail address: %p\n", queue.end);

    printf("add value: %d\n", 99);
    enQueue(&queue, 99);
    printf("add value: %d\n", 87);
    enQueue(&queue, 87);
    printf("add value: %d\n", 66);
    enQueue(&queue, 66);
    printf("add value: %d\n", 12);
    enQueue(&queue, 12);
    printf("add value: %d\n", 7777);
    enQueue(&queue, 7777);
    printf("Queue to List\n");
    list lst = queue2List(&queue);
    show_all(&lst);
    printf("size: %d\n", queue.size);
    printf("top address: %p\n", queue.start);
    printf("tail address: %p\n", queue.end);

    printf("pop value: %d\n", deQueue(&queue));
    printf("size: %d\n", queue.size);
    printf("top address: %p\n", queue.start);
    printf("tail address: %p\n", queue.end);

    printf("pop value: %d\n", deQueue(&queue));
    printf("size: %d\n", queue.size);
    printf("top address: %p\n", queue.start);
    printf("tail address: %p\n", queue.end);

    printf("pop five value...\n");
    printf("pop value: %d\n", deQueue(&queue));
    printf("pop value: %d\n", deQueue(&queue));
    printf("pop value: %d\n", deQueue(&queue));
    printf("pop value: %d\n", deQueue(&queue));
    printf("pop value: %d\n", deQueue(&queue));

    printf("size: %d\n", queue.size);
    printf("top address: %p\n", queue.start);
}
