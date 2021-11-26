#include <stdio.h>
#include <stdlib.h>
void free_all_register_address(void);               // 釋放
void register_address(void *address);               // 標記
void my_calloc(void **ptr, int length, int type_side); // 分配

void **address_pool = NULL;  //將會是一個動態陣列，儲存 void*
int index_ = 0;               //索引，指向目前可以儲存地址的空間
#define mc(ptr, len, type) my_calloc((void **)ptr, len, sizeof(type));

void register_address(void *address){

    /*擴大、重新分配用於儲存記憶體地址的空間*/
    void **temp_ptr = NULL;  //中轉指標
	temp_ptr = (void**)realloc(address_pool, (index_ + 1) * sizeof(void*));
    
    /*對realloc分配記憶體的錯誤檢測*/
    if (temp_ptr == NULL) {
        /*錯誤處理*/
	}
    
    /*成功建立的空間分配給address_pool*/
	address_pool = temp_ptr;  //取得中轉指標的地址
    
    /*註冊記憶體地址*/
	address_pool[index_] = address;
	index_++;  //空間擴大、索引移位
    
}


void free_all_register_address(void) {

	/*遍歷 address_pool 的空間*/
	for (int i = 0; i < index_; i++) {
		free(address_pool[i]);  //釋放曾經記錄過的記憶體地址的空間
		address_pool[i] = NULL;
	}

    /*釋放用於紀錄的空間*/
	free(address_pool);
	address_pool = NULL;
}


void my_calloc(void **ptr, int length, int type_size){

    /*分配記憶體*/
    *ptr = calloc(length, type_size);
    
    /*紀錄地址*/
    register_address(*ptr);
    
    /*註冊 atexit() */
    /*僅在程序第一次執行時呼叫 atexit() */
	static int first_process = 1;
	if (first_process) {
		atexit(&free_all_register_address);  //此函數只會被呼叫一次
		first_process = 0;  //第一次執行的標記
	}
    
}


int main()
{
    printf("Hello World");
    int *p;
    mc(&p, 3, int);

    return 0;
}
