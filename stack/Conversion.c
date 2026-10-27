#include "sq_stack/include/operations.h"
#include<string.h>
#include<ctype.h>

void conversion(int N){
    SqStack S;
    InitStack(&S);
    if(N==0){
        printf("0");
        return;
    }
    while(N>0){
        Push(&S,N%8);
        N/=8;
    }
    while(!StackEmpty(S)){
        SElemType e;
        Pop(&S,&e);
        printf("%d",e);
    }
}
//十进制转八进制