#include "../include/operations.h"

void CreatPolyn(polynomial *p,int m){
    if(m<1){
        *p=NULL;
        return;
    }
    *p=(polynomial)malloc(sizeof(PolyNode));
    if(!*p){
        exit(-1);
    }
    (*p)->next=NULL;
    for(int i=0;i<m;i++){
        term t;
        scanf("%f %d",&t.coef,&t.expn);
        if(t.coef==0){
            continue;
        }
        PolyNode *pre=*p;
        PolyNode *cur=(*p)->next;
        while(cur!=NULL&&cur->data.expn<t.expn){
            pre=cur;
            cur=cur->next;
        }
        if(cur!=NULL&&cur->data.expn==t.expn){
            cur->data.coef+=t.coef;
            if(cur->data.coef==0){
                pre->next=cur->next;
                free(cur);
            }
        }else{
            PolyNode *newnode=(PolyNode*)malloc(sizeof(PolyNode));
            if(!newnode){
                exit(-1);
            }
            newnode->data.coef=t.coef;
            newnode->data.expn=t.expn;
            newnode->next=cur;
            pre->next=newnode;
        }
    }
}
void DestroyPolyn(polynomial *p){
    PolyNode *cur=*p;
    while(cur!=NULL){
        PolyNode *temp=cur;
        cur=cur->next;
        free(temp);
    }
    *p=NULL;
}
void PrintPolyn(polynomial p){
    if(p==NULL||p->next==NULL){
        printf("0 0\n");
        return;
    }
    PolyNode *cur=p->next;
    while(cur!=NULL){
        printf("%.1f %d\n",cur->data.coef,cur->data.expn);
        cur=cur->next;
    }
}
int PolynLength(polynomial p){
    int len=0;
    PolyNode *cur=p->next;
    while(cur!=NULL){
        len++;
        cur=cur->next;
    }
    return len;
}
void AddPolyn(polynomial *p1,polynomial *p2){
    PolyNode *pa=(*p1)->next;
    PolyNode *pb=(*p2)->next;
    PolyNode *pc=*p1;//记录结果链表的尾节点，维护删除情况
    while(pa&&pb){
        int flag=cmp(pa->data,pb->data);
        if(flag==0){
            pa->data.coef+=pb->data.coef;
            if(pa->data.coef==0){
                pc->next=pa->next;
                free(pa);
            }else{
                pc=pa;
                pa=pa->next;
            }
            PolyNode *temp=pb;
            pb=pb->next;
            free(temp);
        }else if(flag<0){
            pc=pa;
            pa=pa->next;
        }else{
            PolyNode *temp=pb;
            pb=pb->next;
            temp->next=pa;
            pc->next=temp;
            pc=temp;
        }
    }
    if(pb){
        pc->next=pb;
    }else{
        pc->next=pa;
    }
    (*p2)->next=NULL; //清空p2的头节点
}
void SubtractPolyn(polynomial *p1,polynomial *p2){
    if(*p2==NULL||(*p2)->next==NULL){
        return;
    }
    PolyNode *pb=(*p2)->next;
    while(pb!=NULL){
        pb->data.coef=-pb->data.coef;
        pb=pb->next;
    }
    AddPolyn(p1,p2);//取反调用加法
}
void InsertTerm(polynomial head, float coef, int expn) {
    if(coef==0){
        return;
    }
    PolyNode *pre=head;
    PolyNode *cur=head->next;
    while(cur&&cur->data.expn<expn){
        pre=cur;
        cur=cur->next;
    }
    if(cur&&cur->data.expn==expn){
        cur->data.coef+=coef;
        if(cur->data.coef==0){
            pre->next=cur->next;
            free(cur);
        }
        return;
    }
    PolyNode *newNode=(PolyNode*)malloc(sizeof(PolyNode));
    if(!newNode){
        exit(-1);
    }
    newNode->data.coef=coef;
    newNode->data.expn=expn;
    newNode->next=cur;
    pre->next=newNode;
}
void MultiplyPolyn(polynomial *p1, polynomial *p2) {
    if(*p1==NULL||(*p1)->next==NULL||*p2==NULL||(*p2)->next==NULL) {
        DestroyPolyn(p1);
        return;
    }
    polynomial result=(polynomial)malloc(sizeof(PolyNode));
    if(!result){
        exit(-1);
    }
    result->next=NULL;
    PolyNode *pa=(*p1)->next;
    while(pa){
        PolyNode *pb=(*p2)->next;
        while (pb) {
            float newCoef=pa->data.coef*pb->data.coef;
            int newExpn=pa->data.expn+pb->data.expn;
            InsertTerm(result, newCoef, newExpn);
            pb=pb->next;
        }
        pa=pa->next;
    }
    DestroyPolyn(p1);
    *p1 = result;
}
int cmp(term a,term b){
    if(a.expn==b.expn){
        return 0;
    }
    return a.expn>b.expn?1:-1;
}