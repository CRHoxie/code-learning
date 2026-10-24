/*本题要求计算并输出不超过n的最大的k个素数以及它们的和。

输入格式:
输入在一行中给出n(10≤n≤10000)和k(1≤k≤10)的值。*/
#include<stdio.h>
int main(){
    int n,k,sum=0,judge=1,first=1,times=0;
    scanf("%d %d",&n,&k);
    for(int i=n;i>=2;i--){
        judge=1;
        for(int j=2;j<i;j++){
            if(i%j==0) {
                judge=0;
                break;}
        }
            if(judge){
                if(first){
                    printf("%d",i);
                    sum+=i;
                    times++;
                    first=0;
                }
                else {printf("+%d",i);sum+=i;times++;}
            }
        if(times==k) break;
    }
    printf("=%d",sum);
}