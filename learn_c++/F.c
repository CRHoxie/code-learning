#include<stdio.h>
int main(){
    int T,n,m,k,t,S,i;
    scanf("%d",&T);
    for (i = 0; i < T; i++)
    {
        scanf("%d %d %d %d",&n,&m,&k,&t);
        S=n+m*k;
        for (int j = 1; j <= t; j++)
        {  
            int A;
            scanf("%d",&A);
            if (S>=A)
            {
                S=S-A;
                printf("%d",j);
                printf(" ");
            }
        }
        printf("\n");
    }
}