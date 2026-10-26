/*本题要求编写程序，输入一行字符，统计其中数字字符、空格和其他字符的个数。建议使用switch语句编写。

输入格式:
输入在一行中给出若干字符，最后一个回车表示输入结束，不算在内。

输出格式:
在一行内按照

blank = 空格个数, digit = 数字字符个数, other = 其他字符个数
的格式输出。请注意，等号的左右各有一个空格，逗号后有一个空格。*/
#include<stdio.h>
int main(){
    int sum=0,b=0,d=0,ch;
    while((ch=getchar())!='\n'){
        if (ch==' ') b++;
        if (48<=ch&&ch<=57) d++;
        sum++;
    }
printf("blank = %d, digit = %d, other = %d",b,d,sum-b-d);
}