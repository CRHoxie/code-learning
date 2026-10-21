/*本题要求编写程序,计算序列 1 - 1/4 + 1/7 - 1/10 + ... 的前N项之和。

输入格式:
输入在一行中给出一个正整数N。

输出格式:
在一行中按照“sum = S”的格式输出部分和的值S，精确到小数点后三位。题目保证计算结果不超过双精度范围。*/
#include<stdio.h>
int main(){
    int N,one;
    double sum;
    scanf("%d",&N);
    for(int i=1;i<=N;i++){
        if(i%2==0) one=-1;
        else one=1;
        sum+=1/(3.0*i-2)*one;
    }
    printf("sum = %.3f",sum);
    return 0;
}