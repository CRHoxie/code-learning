/*本题要求实现一个打印非负整数阶乘的函数。

函数接口定义：
void Print_Factorial ( const int N );
其中N是用户传入的参数，其值不超过1000。如果N是非负整数，则该函数必须在一行中打印出N!的值，否则打印“Invalid input”。
[1]第一次提交
void Print_Factorial (const int N){
    long long int sum=1;
    if(N>=0){
        for(int i=1;i<=N;i++){
            sum*=i;
            //printf("%lld-%d\n",sum,i);
        }
        printf("%lld",sum);
    }
    else{
        printf("Invalid input");
    }
}
*/
//第二次提交

#include <stdio.h>

void Print_Factorial ( const int N );

int main()
{
    int N;
    
    scanf("%d", &N);
    Print_Factorial(N);
    return 0;
}

void Print_Factorial (const int N){
    int a[3000];
    int len=1;
    a[0]=1;
    if (N<0){
        printf("Invalid input");
        return;
    }
    for(int i=2;i<=N;i++){
        int carry=0;
        for(int j=0;j<len;j++){
            int t =a[j]*i+carry;
            a[j]=t%10;
            carry=t/10;
        }
        while(carry>0){
            a[len++]=carry%10;
            carry/=10;
        }
    }
    for(int i=len-1;i>=0;i--){
        printf("%d",a[i]);
        }
}