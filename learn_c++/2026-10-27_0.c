/*7-16 个位数出现的次数
分数 10
作者 xuwanzhen
单位 广东东软学院
输入一个整数a和一个个位数的整数b，请输出整数b在整数a中出现的次数。题目保证整数b为0-9之间的个位整数。

输入格式:
在一行中输入两个整数a和b。

输出格式:
输出整数b在整数a中出现的次数.*/
#include<stdio.h>
int main(){
    int a,b,sum=0;
    scanf("%d %d",&a,&b);
    while(a>0){
        if(a%10==b) sum++;
        a/=10;
    }
    printf("%d",sum);
    return 0;
}