#include<stdio.h>
int main(){
    int num;
    long long int energy,sum=1;
    scanf("%d",&num);
    for (int i = 0; i < num; i++)
    {
        scanf("%lld",&energy);
        sum=(sum*(energy%998244353))%998244353;
    }
    printf("%lld",sum);
    return 0;
}