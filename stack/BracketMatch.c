#include "sq_stack/include/operations.h"
#include<string.h>
#include<ctype.h>

bool bracketmatch(char *str){
    SqStack s;
    InitStack(&s);
    int i=0;
    for(i=0;i<strlen(str);i++){
        char c=str[i];
        if(c=='('||c=='['||c=='{'){
            Push(&s,(SElemType)c);
        }else if(c==')'||c==']'||c=='}'){
            if(StackEmpty(s)){
                return false;
            }
            int topelem;
            Pop(&s,&topelem);
            if((c==')'&&topelem!='(')||(c==']'&&topelem!='[')||(c=='}'&&topelem!='{')){
                return false;
            }
        }
    }
    bool result=StackEmpty(s);
    return result;
}