#include<stdio.h>
int main(){
    int T;
    scanf("%d",&T);
    for(int i=0;i<T;i++)
    {
        int times,sum;
        sum=0;
        scanf("%d",&times);
        printf("-%d1-",sum);
        for(int j=0;j<times;j++)
        {
            int n;
            scanf("%d",&n);
            sum =sum+n;
            printf("-%d2-",sum);
        }
        printf("-%d3-",sum);
        if (sum%5==0 && sum%7==0 && sum%3==0) printf("YES\n");
        else printf("NO\n");
    }
    
    return 0;
}