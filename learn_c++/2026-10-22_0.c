/*根据下面关系式，求圆周率的值，直到最后一项的值小于给定阈值。

2/π =1+ 1/3 + 2!/3×5 + 3!/3×5×7 +⋯+ n!/3×5×7×⋯×(2n+1) +⋯

输入格式：
输入在一行中给出小于1的阈值。

输出格式：
在一行中输出满足阈值条件的近似圆周率，输出到小数点后6位。*/
#include<stdio.h>
double fac(int a){
    double b=1.0;
    for(int i=1;i<=a;i++){
        b*=i*1.0;
    }
    return b;
}
double power(int a){
    double b=1.0;
    for(int j=1;j<=a;j++){
        b*=(2*j+1);
    }
    return b;
}
int main(){
    double N,last=1,sum=1.0;
    int i=1;
    scanf ("%lf",&N);
    while(last>N){
        sum+=fac(i)/power(i);
        last=fac(i)/power(i);
        i++;
    }
    printf("%.6lf",sum*2.0);
}
