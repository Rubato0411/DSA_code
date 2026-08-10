#include "../include/operations.h"

static void select(HuffmanTree HT,int range,int *s1,int*s2){
    unsigned int min1=UINT_MAX;
    unsigned int min2=UINT_MAX;
    *s1=*s2=0;
    int i=0;
    for(i=0;i<range;i++){
        if(HT[i].parent==0){
            if(HT[i].weight<min1){
                min2=min1;
                *s2=*s1;
                min1=HT[i].weight;
                *s1=i;
            }else if(HT[i].weight<min2){
                min2=HT[i].weight;
                *s2=i;
            }
        }
    }
}
void CreateHuffmanTree(HuffmanTree *HT,unsigned int *w,unsigned int n){
    if(n<=1){
        return;
    }
    int total=2*n-1;
    *HT=(HuffmanTree)malloc((total+1)*sizeof(HNode));
    for(int i=1;i<=total;i++){
        (*HT)[i].weight=0;
        (*HT)[i].parent=0;
        (*HT)[i].lchild=0;
        (*HT)[i].rchild=0;
    }
    int i=0;
    for(i=1;i<=n;i++){
        (*HT)[i].weight=w[i-1];
    }
    for(i=n+1;i<=total;i++){
        int s1,s2;
        select(*HT,i-1,&s1,&s2);
        (*HT)[s1].parent=i;
        (*HT)[s2].parent=i;
        (*HT)[i].lchild=s1;
        (*HT)[i].rchild=s2;
        (*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
    }
}
void CreateHuffmanCode(HuffmanTree HT,HuffmanCode *HC,unsigned int n){
    if(n<=0){
        return;
    }
    *HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
    if(!(*HC)){
        return;
    }
    char *cd=(char*)malloc(n*sizeof(char));
    if(!cd){
        return;
    }
    cd[n-1]='\0';
    for(int i=1;i<=n;i++){
        int start=n-1;
        int c=i;
        int p=HT[i].parent;
        while(p!=0){
            --start;
            if(HT[p].lchild==c){
                cd[start]='0';
            }else{
                cd[start]='1';
            }
            c=p;
            p=HT[p].parent;
        }
        (*HC)[i]=(char*)malloc((n-start)*sizeof(char));
        if(!(*HC)[i]){
            return;
        }
        strcpy((*HC)[i],cd+start);
    }
    free(cd);
}
char* Encode(HuffmanCode HC,char *str,int n,char* charset){
    if(!str||!HC||n<=0){
        return NULL;
    }
    int len=0;
    char *p=str;
    while(*p){
        for(int i=0;i<n;i++){
            if(*p==charset[i]){
                len+=strlen(HC[i+1]);
                break;
            }
        }
        p++;
    }
    char *result=(char*)malloc((len+1)*sizeof(char));
    if(!result){
        return NULL;
    }
    result[0]='\0';
    p=str;
    while(*p){
        for(int i=0;i<n;i++){
            if(*p==charset[i]){
                strcat(result, HC[i+1]);
                break;
            }
        }
        p++;
    }
    return result;
}
char* Decode(HuffmanTree HT,char *str,int n,char* charset){
    if(!str||!HT||n<=0){
        return NULL;
    }
    int len=strlen(str);
    char *result=(char*)malloc((len+1)*sizeof(char));
    if(!result){
        return NULL;
    }
    int index=0;
    int cur=2*n-1;
    int p=cur;
    char *q=str;
    while(*q){
        if(*q=='0'){
            p=HT[p].lchild;
        }else if(*q=='1'){
            p=HT[p].rchild;
        }else{
            return NULL;
        }
        if(HT[p].lchild==0&&HT[p].rchild==0){
            for(int i=0;i<=n;i++){
                if(p==i){
                    result[index++]=charset[i-1];
                    break;
                }
            }
            p=cur;
        }
        q++;
    }
    result[index]='\0';
    char* final=(char*)realloc(result,(index+1)*sizeof(char));
    return final?final:result;//防止realloc失败
}
void destroyHuffmanTree(HuffmanTree *HT){
    if(*HT){
        free(*HT);
        *HT=NULL;
    }
}
void destroyHuffmanCode(HuffmanCode *HC,unsigned int n){
    if(*HC){
        for(int i=1;i<=n;i++){
            if((*HC)[i]){
                free((*HC)[i]);
                (*HC)[i]=NULL;
            }
        }
        free(*HC);
        *HC=NULL;
    }
}