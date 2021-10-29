#include <stdlib.h>
#include <stdio.h>


char* int2string(int x, char *s){
    sprintf(s,"%d",x);
    return s;
}

int string2int(char *s, int* x){
    *x = atoi(s);
    return *x;
}

void stdin_clear(){
    while(getchar != '\n');
}
