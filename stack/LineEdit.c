#include "sq_stack/include/operations.h"

void printchar(SElemType c) {
    printf("%c ",(char)c);
}

void LineEdit() {
    SqStack S;
    InitStack(&S);        
    char ch;
    while((ch=getchar())!='\n'&&ch!=EOF){
        if(ch=='#'){
            SElemType e;
            if(!StackEmpty(S)){ 
                Pop(&S,&e);      
            }
        } 
        else if(ch=='@'){
            ClearStack(&S);       
        } 
        else{
            Push(&S,(SElemType)ch); 
        }
    }
    StackTraverse(S,printchar); 
    printf("\n");
    DestroyStack(&S);           
}

int main(){
    LineEdit();
    return 0;
}