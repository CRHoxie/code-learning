#include<stdio.h>
int main(){
    int rabbit = 2;
    int mon,N = 0;
    scanf("%d",&N);
    for(mon = 0;rabbit<N;mon++){
        rabbit*=2;
    }
    printf("%d",(mon-1)*3);
    return 0;
}