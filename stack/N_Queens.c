#include<stdio.h>

int pos[100]={-1};

void PrintQueens(int n){
    int i=0;
    int j=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(pos[i]==j){
                printf("Q ");
            }else{
                printf("* ");
            }

        }
        printf("\n");
    }
    printf("\n");
}
void Queens(int n,int m,int* col,int* main,int* sub){
    int i=m;
    int j=0;

    for(j=0;j<n;j++){
        if(col[j]==0&&main[j-i+n-1]==0&&sub[i+j]==0){
            col[j]=1;
            main[j-i+n-1]=1;
            sub[i+j]=1;
            pos[i]=j;
            if(i==n-1){
                PrintQueens(n);

                
            }else{
                Queens(n,i+1,col,main,sub);
            }
            col[j]=0;
            main[j-i+n-1]=0;
            sub[i+j]=0;
        }
    }
}

int main(){
    int n=0;
    scanf("%d",&n);
    int col[n];
    int main[2*n-1];
    int sub[2*n-1];
    int i=0;
    for(i=0;i<n;i++){
        col[i]=0;
    }
    for(i=0;i<2*n-1;i++){
        main[i]=0;
        sub[i]=0;
    }
    Queens(n,0,col,main,sub);
    return 0;
}
