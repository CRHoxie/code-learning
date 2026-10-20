/*本题要求编写程序，计算序列 2/1+3/2+5/3+8/5+... 的前N项之和。注意该序列从第2项起，每一项的分子是前一项分子与分母的和，分母是前一项的分子。

输入格式:
输入在一行中给出一个正整数N。

输出格式:
在一行中输出部分和的值，精确到小数点后两位。题目保证计算结果不超过双精度范围。*/
#include<stdio.h>
int main(){
    int N;
    double last=2.00,llast=1.00,now;
    double sum = 0.00;
    scanf("%d",&N);
    for (int i = 0;i<N;i++){
        sum+=last*1.00/llast*1.00;
        now=last;
        last+=llast;
        llast=now;
    }
    printf("%.2lf",sum);
}
//又是斐波那契数列问题
//更好的写法
/*
#include<stdio.h>

int main(void){
    int N;
    scanf("%d", &N);

    double sum = 0.0;
    double term = 2.0 / 1.0;  // 第一项 2/1

    for(int i = 0; i < N; i++){
        sum += term;              // 累加当前项
        term = 1.0 + 1.0 / term;  // 由当前项得到下一项
    }

    printf("%.2f\n", sum);
    return 0;
}
*/