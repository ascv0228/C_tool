#ifndef MM_H
#define MM_H 1
#include <stddef.h>

void *mycalloc(size_t nitems, size_t size);
void myfree(void *ptr);
void *mymalloc(size_t size);
void *myrealloc(void *ptr, size_t size);
#endif
