/*本题要求编写程序读入N个学生的百分制成绩，统计五分制成绩的分布。百分制成绩到五分制成绩的转换规则：

大于等于90分为A；
小于90且大于等于80为B；
小于80且大于等于70为C；
小于70且大于等于60为D；
小于60为E。
输入格式:
输入在第一行中给出一个正整数N（≤1000），即学生人数；第二行中给出N个学生的百分制成绩，其间以空格分隔。 

输出格式:
在一行中输出A、B、C、D、E对应的五分制成绩的人数分布，数字间以空格分隔，行末不得有多余空格。*/
#include<stdio.h>
int main(){
    int N,A=0,B=0,C=0,D=0,E=0;
    scanf("%d", &N);
    for(int i=0;i<N;i++){
        int temp;
        scanf("%d",&temp);
        if(temp>=90) A+=1;
        if(temp<90 && temp>=80) B+=1;
        if(temp<80 && temp>=70) C+=1;
        if(temp<70 && temp>=60) D+=1;
        if(temp<60) E+=1;
        
    }
    printf("%d ",A);
    printf("%d ",B);
    printf("%d ",C);
    printf("%d ",D);
    printf("%d",E);
}