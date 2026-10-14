#include<stdio.h>
#include<math.h>

int main(){
    float x,y,a;
    scanf("%f",&x);
    if(x<0){
        a=sqrt(x+1);
        y=a+2*x+1/x;
    }
    else{
        y=pow(x,0.5);
    }
    printf("f(%.2f) = %.2f",x,y);
    return 0;
}





/*
9.29 work test
#include<stdio.h>
int main(){
    float x,y;
    scanf("%f",&x);
    if (x==0){
        y=0;
    }
    else{
        y=1/x;
    }
    printf("f(%.1f) = %.1f",x,y);
    return 0;
}
*/