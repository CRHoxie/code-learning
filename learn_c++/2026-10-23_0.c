/*本题要求编写程序，打印一个高度为n的、由“*”组成的正菱形图案。

输入格式:
输入在一行中给出一个正的奇数n。 

输出格式:
输出由n行星号“*”组成的菱形，如样例所示。每个星号后跟一个空格。*/
#include<stdio.h> 
void star(int a){
    for(int x=0;x<a;x++){
        printf("* ");
    }
    printf("\n");
}
void blank(int b){
    for(int c=0;c<b;c++){
    printf(" ");
}
}

int main(){
    int n;
    scanf("%d",&n);//n-1 
    for(int i=1;i<n;i+=2){
        blank(n-i);
        star(i);
        //printf("\n");
    }
    star(n);
    for(int j=n-2;j>0;j-=2){
        blank(n-j);
        star(j);
    }
    return 0;
}