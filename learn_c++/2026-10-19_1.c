/*从键盘输入一个正整数a，要求：a在1到9之间，求x=a+a*a+a*a*a+a*a*a*a+a*a*a*a*a的值。若a不在1到9之间，则输出：输入数据不在范围内。
输入格式:
5。

输出格式:
x =  3905。*/
#include<stdio.h>
int main(){
    int a,i,j,sum=0,b;
    scanf("%d",&a);
    sum =0;
    if (a<9&&a>1){
        for(i= 1;i<=5;i++)
        {
            b=1;
            for(j=0;j<i;j++){
                
                b*=a;
            }
            sum +=b;
            }
        printf("x = %d",sum);
        }
    else{
        printf("输入数据不在范围内");
    }
}