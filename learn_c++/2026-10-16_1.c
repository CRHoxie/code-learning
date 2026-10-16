/*7-2 求N分之一交错序列前N项和
输入一个正整数N，计算序列 1 - 1/2 + 1/3 - 1/4 + ... 的前N项之和，精确到小数点后三位。

输入格式:
输入在一行中给出一个正整数N。

输出格式:
在一行中按照“sum = S”的格式输出部分和的值S，精确到小数点后3位。
题目保证计算结果不超过双精度范围。*/
#include<stdio.h>
int power (double a);
int main(){
    int N;
    double sum=0.00;
    scanf("%d", &N);
    for(double j=1.00;j<=N;j++){
        sum=sum+1/j*power(j);
        //printf("%lf \n %f \n %d--\n",sum,j,power(j));
    }
    printf("sum = %.3f",sum);
    return 0;
}
int power (double a){
    int one=-1;
    for(int i=0;i<a;i++){
        one*=-1;
    }
    return one;
}