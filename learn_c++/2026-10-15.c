#include<stdio.h>
int main(){
    int N,num,sum;
    num=scanf("%d",&N);
    printf("%d ",num);
    for(int i = 0;i<num;i++){
        sum+=N%10;
        N=N/10;
        printf("%d-%d\n",sum,N);
    }
    printf("%d",sum);
    return 0;
}