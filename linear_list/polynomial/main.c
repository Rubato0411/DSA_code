#include "include/operations.h"

void menu(){
    printf("1. Create polynomial\n");
    printf("2. Print polynomial\n");
    printf("3. Add polynomials\n");
    printf("4. Subtract polynomials\n");
    printf("5. Multiply polynomials\n");
    printf("6. Calculate polynomial at x\n");
    printf("7. Derivative of polynomial\n");
    printf("8. Exit\n");
}

int main(){
    polynomial a=NULL;
    polynomial b=NULL;
    int m=0;
    int n=0;
    float x=0.0;
    while(1){
        menu();
        scanf("%d",&m);
        switch(m){
            case 1:
                printf("Enter A: ");
                scanf("%d",&n);
                CreatPolyn(&a,n);
                printf("Enter B: ");
                scanf("%d",&n);
                CreatPolyn(&b,n);
                break;
            case 2:
                SortPolynomial(&a);
                printf("A: ");
                PrintPolyn(a);
                SortPolynomial(&b);
                printf("B: ");
                PrintPolyn(b);
                break;
            case 3:
                AddPolyn(&a,&b);
                SortPolynomial(&a);
                printf("A + B: ");
                PrintPolyn(a);
                break;
            case 4:
                SubtractPolyn(&a,&b);
                SortPolynomial(&a);
                printf("A - B: ");
                PrintPolyn(a);
                break;
            case 5:
                MultiplyPolyn(&a,&b);
                SortPolynomial(&a);
                printf("A * B: ");
                SortPolynomial(&a);
                PrintPolyn(a);
                break;
            case 6:
                printf("Enter x: ");
                scanf("%f",&x);
                float result=calculate(a,x);
                printf("A(%f) = %f\n",x,result);
                break;
            case 7:
                Derivative(&a);
                SortPolynomial(&a);
                printf("A': ");
                PrintPolyn(a);
                break;
            case 8:
                DestroyPolyn(&a);
                DestroyPolyn(&b);
                return 0;
            default:
                printf("try again\n");
        }
    }

}