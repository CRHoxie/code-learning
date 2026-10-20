/*本题要求编写程序，计算交错序列 1-2/3+3/5-4/7+5/9-6/11+... 的前N项之和。

输入格式:
输入在一行中给出一个正整数N。

输出格式:
在一行中输出部分和的值，结果保留三位小数。*/

#include<stdio.h>
int main(){
    int N,one;
    double sum=0.00;
    scanf("%d",&N);
    for(double i = 1;i<=N;i++){
        one =-1;
        for(int j=0;j<i;j++){
            one*=-1;
        }
        float c =i/(2*i-1)*one;
        sum+=i/(2*i-1)*one;
        printf("%.3lf\n",sum);
        printf("-%f\n",c);
    }
    printf("%.3lf\n",sum);
    return 0;
}