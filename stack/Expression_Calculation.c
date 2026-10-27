#include "sq_stack/include/operations.h"

typedef enum {
    OP_ADD,      // 0: '+'
    OP_SUB,      // 1: '-'
    OP_MUL,      // 2: '*'
    OP_DIV,      // 3: '/'
    OP_LPAREN,   // 4: '('
    OP_RPAREN,   // 5: ')'
    OP_END,      // 6: '#'
    OP_COUNT     // 7: 用于定义数组大小（自动统计有多少种运算符）
} OpType;
OpType getOpType(char c) {
    switch (c) {
        case '+': return OP_ADD;
        case '-': return OP_SUB;
        case '*': return OP_MUL;
        case '/': return OP_DIV;
        case '(': return OP_LPAREN;
        case ')': return OP_RPAREN;
        case '#': return OP_END;
        default:  return OP_COUNT; // 若传入非法字符，返回越界值
    }
}

//    值含义：'<' 表示 θ2 优先级高，入栈；'>' 表示 θ1 优先级高，先计算；'=' 表示括号配对或结束
char PrecedeTable[OP_COUNT][OP_COUNT] = {
    //               θ2: '+'  '-'  '*'  '/'  '('  ')'  '#' 
    /* θ1: '+' */ {  '>', '>', '<', '<', '<', '>', '>' },
    /* θ1: '-' */ {  '>', '>', '<', '<', '<', '>', '>' },
    /* θ1: '*' */ {  '>', '>', '>', '>', '<', '>', '>' },
    /* θ1: '/' */ {  '>', '>', '>', '>', '<', '>', '>' },
    /* θ1: '(' */ {  '<', '<', '<', '<', '<', '=', '>' }, // 括号匹配
    /* θ1: ')' */ {  '>', '>', '>', '>', '>', '>', '>' }, // 栈内不会出现 ')'，占位
    /* θ1: '#' */ {  '<', '<', '<', '<', '<', '<', '=' }  // 结束匹配
};

char Precede(char theta1, char theta2) {
    OpType idx1 = getOpType(theta1);
    OpType idx2 = getOpType(theta2);
    if (idx1 >= OP_COUNT || idx2 >= OP_COUNT) {
        printf("Error: 非法运算符 '%c' 或 '%c'\n", theta1, theta2);
        exit(-1);
    }
    return PrecedeTable[idx1][idx2];
}

int expression_calculation(char *expr){
    SElemType *e;
    SqStack OPTR,OPND;
    InitStack(&OPTR);
    InitStack(&OPND);
    Push(&OPTR,'#');
    char *p=expr;
    while(*p!='#'||GetTop(OPTR,*e)!=(SElemType)'#'){
        if(isdigit(*p)){
            int num=0;
            while(isdigit(*p)){
                num=num*10+(*p-'0');
                p++;
            }
            push(&OPND,num);
            continue;
        }
        char c2=*p;
        char c1=(char)GetTop(OPTR,*e);
        char cmp=Precede(c1,c2);
        if(cmp=='<'){
            Push(&OPTR,(SElemType)c2);
            p++;
        }else if(cmp=='='){
            SElemType *topc;
            Pop(&OPTR,topc);
            p++;
        }else if(cmp=='>'){
            int m;
            Pop(&OPTR,&m);
            char mc=(char)m;
            int a,b;
            Pop(&OPND,&a);
            Pop(&OPND,&b);
            int result=Operate(a,m,b);
            Push(&OPND,result);
        }
    }
    int final;
    GetTop(OPND,&final);
    return final;
}