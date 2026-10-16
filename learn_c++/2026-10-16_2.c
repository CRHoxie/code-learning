/*本题要求编写程序，计算序列 1 + 1/3 + 1/5 + ... 的前N项之和。

输入格式:
输入在一行中给出一个正整数N。

输出格式:
 在一行中按照“sum = S”的格式输出部分和的值S，精确到小数点后6位。题目保证计算结果不超过双精度范围。*/
#include<stdio.h>
int main(){
    int N,j=1;
    double sum=0.00;
    scanf("%d",&N);
    //printf("%d\n",N);
    for(double i=1.00;i<=N;i++){
        j++;
        sum+=1/(2*i-1);
        printf("%.2lf %d\n",sum,j);
    }
    printf("sum = %.6lf",sum);
    return 0;
}

/*int main(){
    double sum=0,i=1.00;
    int N;
    scanf("%d",&N);
    printf("%d",N);
    while(i<=N*1.0){
        sum+=1/i;
        i++;
        printf("%lf %lf\n",i,sum);
    }
    printf("sum = %.6lf",sum);
    return 0;
}*/