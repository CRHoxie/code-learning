/*某工地需要搬运砖块，已知男人一人搬 3 块，女人一人搬 2 块，小孩两人搬1块。

如果想用 n 人正好搬 n 块砖（注意小孩的人数只能是偶数），问有多少种搬法？

(注意当某类人数为 0 时，也是合理的方案)

输入格式:
在一行中输入一个正整数n。

输出格式:
直接输出方案的数目。*/

#include<stdio.h>

int main(){
    int N,men,women,child,types=0;
    scanf("%d",&N);
    for(men=0;men<=N;men++){
        for(women=0;women<=N;women++){
            for(child=0;child<=N;child+=2){
                if(6*men+4*women+child==N && men+women+child==N)
                    types+=1;
                    }
            }
    }
    printf("%d",types);
    return 0;
}
//看到题并想到这个方法的时候突然好想笑,非常暴力的解法.无限循环,循环套循环  :)
//查完发现有更简洁的方法
/*#include<stdio.h>
int main(){
    int N, types = 0;
    scanf("%d", &N);
    for(int m = 0; m * 5 <= N; m++)
        if((N - 5 * m) % 3 == 0) types++;
    printf("%d", types);
    return 0;
}*/
//结果还有更简洁的方法
/*#include<stdio.h>
int main(){
    int N, r;
    scanf("%d", &N);
    r = (2 * N) % 3;
    if(r > N / 5) printf("0");
    else printf("%d", (N / 5 - r) / 3 + 1);
    return 0;
}*/