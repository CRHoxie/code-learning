/*6-3 求组合数(递归)
请编写函数，求组合数。

题图1.jpg

题图2.jpg

函数原型
double Cmb(int x, int y);
说明：参数 x 和 y 为自然数，且 x≥y，函数值为组合数 C 
裁判程序
#include <stdio.h>

int IntMin(int x, int y);
double Cmb(int x, int y);

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    printf("%.14g\n", Cmb(m, n));
    return 0;
}

int IntMin(int x, int y)
{
    ...(略)...
}

<你提交的代码将被嵌在这里>
说明：IntMin 为两整数最小值的函数。
要求：用递归方法完成函数的设计，不得使用循环语句，不得调用阶乘函数和排列数函数。找出递推公式，该函数直接调用自己求得计算结果。*/
#include <stdio.h>

int IntMin(int x, int y);
double Cmb(int x, int y);

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    printf("%.14g\n", Cmb(m, n));
    return 0;
}

int IntMin(int x, int y)
{
    return (x>y)?y:x;
}

double Cmb(int x,int y){
    int k=Intmin(y,x-y);
    if (k==0) return 1;
    //printf("%d-%d\n",x,y);
    return ((x-k+1)*1.0/k*1.0)*Cmb(x,k-1);
}