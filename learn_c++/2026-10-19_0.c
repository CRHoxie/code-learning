/*一对兔子，从出生后第3个月起每个月都生一对兔子。小兔子长到第3个月后每个月又生一对兔子。假如兔子都不死，请问第1个月出生的一对兔子，至少需要繁衍到第几个月时兔子总数才可以达到N对？

输入格式:
输入在一行中给出一个不超过10000的正整数N。

输出格式:
在一行中输出兔子总数达到N最少需要的月数。*/
#include<stdio.h>
int main(){
    int first = 1;
    int second = 1;
    int N,mon;
    scanf("%d",&N);
    if (N>1) {
        for(mon = 2;second<N;mon++){
            int now = first + second;
            first =second;
            second =now;
        }
        printf("%d",mon);
    }
    else printf("1");
    return 0;
}
/*斐波那契数列问题。

第 1 个月：1 对
第 2 个月：1 对
第 3 个月：2 对
第 4 个月：3 对
第 5 个月：5 对
……

即每月兔子总数为斐波那契数列：
F(1)=1, F(2)=1, F(n)=F(n-1)+F(n-2)*/