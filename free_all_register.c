#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
typedef struct header {
    unsigned int size; // 分配的記憶體大小
    unsigned int isfree; // 是否被釋放
    struct header *next; // 下一段記憶體區塊在哪
}Header;

void *mycalloc(size_t nitems, size_t size);
void myfree(void *ptr);
void *mymalloc(size_t size);
void *myrealloc(void *ptr, size_t size);

void* _malloc(unsigned int size);
void* _calloc(size_t nitems, size_t type_size);
void* _realloc(void *ptr, size_t size);
void _free(Header *target);

/////////////////////////////////////////////////

void free_all_register_address(void);               // 釋放

void register_address(void *address);               // 標記
void deregist_address(void *address);

void* mymalloc2(unsigned int size); // 分配
void* myrealloc2(void *ptr, size_t size);
void connect_address_pool(void ****get_address_pool, void **get_index);
void get_address_pool(void ***get_address_pool, int *get_index);

///////////////////////////////////////////////////////////////
void *global_base = NULL;
#define BLOCK_SIZE 24
void *mycalloc(size_t nitems, size_t size){
    return _calloc(nitems, size);
}

void myfree(void *address){
    if(address == NULL)
    {
        printf("Cannot free NULL ptr\n");
        return;
    }
    deregist_address(address);
    _free(address);
}

void *mymalloc(size_t size){
    
    /*分配記憶體*/
    void* ptr = _malloc(size);
    
    if (ptr == NULL) {  //內存不足，記憶體分配失敗
        printf("Failed malloc\n");
        return NULL;
    }    
    /*紀錄地址*/
    register_address(ptr);
    
    /*註冊 atexit() */
    /*僅在程序第一次執行時呼叫 atexit() */
    static int first_process = 1;
    if (first_process) {
        atexit(&free_all_register_address);  //此函數只會被呼叫一次
        first_process = 0;  //第一次執行的標記
    }
    return ptr;
}
void *myrealloc(void *ptr, size_t size){
    
    /*重新分配記憶體*/
    void *temp_ptr = _realloc(ptr, size);  
    
    /*對realloc分配記憶體的錯誤檢測*/
    if (temp_ptr == NULL) {  //內存不足，記憶體分配失敗
        printf("Failed realloc\n");
        return NULL;
    }

    /*分配後地址不相同*/
    if (temp_ptr != ptr) {
        deregist_address(ptr);  //註銷註冊
        register_address(temp_ptr);  //重新登記
    }

    /*成功建立的空間分配給ptr*/
    return temp_ptr;
}

Header *request_memory(Header *last, unsigned int size){
    void *heapBegin = sbrk(0);
    Header *block = sbrk(sizeof(Header) + size);
    if(!block){
        printf("sbrk error");
        return NULL;
    }
    if(last == NULL){
        last = block;
    }
    block->size = size;
    block->isfree = 0;
    block->next = NULL;
    return block;
}

void *find_free_space(unsigned int size){
    Header *current = global_base;
    while(current->next){
        if(current->size>=size && current->isfree == 1){
            return current;
        }
        current = current->next;
    }
    return current;
}

void* _malloc(unsigned int size){
    Header *available_block;
    if(!global_base){
        available_block = request_memory(NULL, size);
        global_base = available_block;
    }
    else{
        Header *block = find_free_space(size); //檢查是否有適合的空間
        if(block->next == NULL){ // 若走到最後一個block，則直接宣告新空間
            available_block = request_memory(block, size);
            block->next = available_block; // 把最後一個block連結到新的block上
        }
        else{ //找到適合的空間直接使用
            block->size = size;
            block->isfree = 0;
            available_block = block;
        }
    }
    return (available_block+1);

}

void _free(Header *target){
    if(target == NULL) return;
    Header *h = target-1;
    h->isfree = 1;
}

void* _calloc(size_t nitems, size_t type_size)
{
    size_t size = nitems * type_size;
    void *ptr = _malloc(size);
    memset(ptr, 0, size);
    return ptr;
}
size_t getsize(void * p) {
    size_t * in = p;
    if (in) { --in; return *in; }
    return -1;
}

void* _realloc(void *ptr, size_t size)
{
    void *newptr;
    int msize;
    msize = getsize(ptr);
    if ((long)size <= (long)msize)
        return ptr;
    newptr = _malloc(size);
    if(msize > 0)
        memcpy(newptr, ptr, msize);
    _free(ptr);
    
    return newptr;
}


//////////////////////////////////////////////////////////////////////////

void register_address(void *address){
    
    /*用於取得記憶體地址池的資料*/
    void ***address_pool = NULL;
    int *index;

    /*取得記憶體地址池的資料*/
    connect_address_pool(&address_pool, (void*)&index);
    
    /*擴大、重新分配用於儲存記憶體地址的空間*/
    void **temp_ptr = NULL;  //中轉指標
    temp_ptr = (void**)myrealloc(*address_pool, (*index + 1) * sizeof(void*));
    
    /*對realloc分配記憶體的錯誤檢測*/ // ...省略......
    
    /*成功建立的空間分配給address_pool*/
    *address_pool = temp_ptr;  //取得中轉指標的地址
    
    /*註冊記憶體地址*/
    (*address_pool)[*index] = address;
    (*index)++;  //空間擴大、索引移位
    
}

void free_all_register_address(void) {

    /*用於取得記憶體地址池的資料*/
    void **address_pool = NULL;
    int index;

    /*取得記憶體地址池的資料*/
    get_address_pool(&address_pool, &index);
    /*遍歷 address_pool 的空間*/
    for (int i = 0; i < index; i++) {
        _free(address_pool[i]);  //釋放曾經記錄過的記憶體地址的空間
        address_pool[i] = NULL;
    }

    /*釋放用於紀錄的空間*/
    myfree(address_pool);
    address_pool = NULL;
}


void connect_address_pool(void ****get_address_pool, void **get_index){

    /*用於儲存記憶體地址池的空間*/
    static void **address_pool = NULL;
    static int index = 0;  //address_pool 的索引

    *get_address_pool = &address_pool;
    *get_index = &index;
}

void get_address_pool(void ***get_address_pool, int *get_index){
    
    /*用於取得記憶體地址池的資料*/
    void ***address_pool = NULL;
    int *index;

    /*取得記憶體地址池的資料*/
    connect_address_pool(&address_pool, (void*)&index);
    
    *get_address_pool = *address_pool;
    *get_index = *index;
}

void deregist_address(void *address) {
    if(address == NULL) return;
    /*用於取得記憶體地址池的資料*/
    void ***address_pool = NULL;
    int *index;
    
    /*取得記憶體地址池的資料*/
    connect_address_pool(&address_pool, (void*)&index);
    /*遍歷 address_pool 的空間*/
    for (int i = 0; i < *index; i++) {
        /*具體註銷工作*/
        if ((*address_pool)[i] == address) {  //尋找對應的記憶體地址
            (*address_pool)[i] = NULL;  //註銷註冊
            return;  //減少迴圈開支
        }
    }
}

int main(){
    int* ptr;
    ptr = (int*)mymalloc(10* sizeof(int));
    for(int i = 0; i<10 ; i++)
    {
        ptr[i] = i;
    }
    
    for(int i = 0; i<10 ; i++)
    {
        printf("%d\n", ptr[i]);
    }
    
    myfree(ptr);
}
