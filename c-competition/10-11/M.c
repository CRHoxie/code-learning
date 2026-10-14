#include<stdio.h>
int main(){
    int T,win;
    scanf("%d",&T);
    for (int i = 0; i < T; i++)
    {
        long long int n,a;
        win=0;
        scanf("%lld",&n);
        for (int j = 0; j < n; j++)
        {
        scanf("%lld",&a);
        if (a % 2 == 1) {
                win = 1;
            }
        }
      
        if (win==1) printf("Alice\n");
        else printf("Bob\n");  
    
    }  
    return 0; 
}