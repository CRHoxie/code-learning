#include<stdio.h>
#include<math.h>
/*long long gcb(long int a,long int b){
    long long int i,c,d;
    c =pow(a,b)%998244353;
    d =pow(b,a)%998244353;
    int min = c<d ?c:d;
    for ( i=  min; i>=1; i--)
    {
        if (c%i==0 && d%i==0){    
        }
    }
    return i;
}*/
long long gcb(){
    long long c,d;
    
}
int main(){
    long int times;
    scanf("%ld",&times);
    while (times>0)
    {
        long long int A,B,C;
        scanf("%lld %lld",&A,&B);
        C= gcb (A,B);
        printf("%lld\n",C);
        times--;
    }
}