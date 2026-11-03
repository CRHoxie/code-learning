/*
请编写函数，完成移动汉诺塔的任务。

函数原型
void MoveTower(int num, char src, char dst, char trs);
说明：参数 num 为金片数，src、dst 和 trs 分别为起始柱、目的柱和过渡柱。若金片数大于 0，则函数将金片组成的汉诺塔由起始柱利用过渡柱最终搬到目的柱，否则什么也不做。

下面的程序，输入汉诺塔圆片的数量，输出移动汉诺塔的步骤。

裁判程序
▾
#include <stdio.h>

void MoveTower(int num, char src, char dst, char trs);

int main()
{
    int n;
    char s, d, t;
    scanf("%d %c %c %c", &n, &s, &d, &t);
    MoveTower(n, s, d, t);
    return 0;
}

<你提交的代码将被嵌在这里>
输入格式
圆盘数
起始柱 目的柱 过渡柱

输出格式
移动汉诺塔的步骤
每行显示一步操作，具体格式为：
盘片号: 起始柱 -> 目的柱
其中盘片号从 1 开始由小到大顺序编号。

输入样例
3
a c b
输出样例
1: a -> c
2: a -> b
1: c -> b
3: a -> c
1: b -> a
2: b -> c
1: a -> c
*/
#include <stdio.h>

void MoveTower(int num, char src, char dst, char trs);

int main()
{
    int n;
    char s, d, t;
    scanf("%d %c %c %c", &n, &s, &d, &t);
    MoveTower(n, s, d, t);
    return 0;
}
void MoveTower(int num,char src,char dst,char trs){
    if(num==0)
        return;
    MoveTower(num-1,src,trs,dst);
    printf("%d: %c -> %c\n",num,src,dst);
    MoveTower(num-1,trs,dst,src);
}