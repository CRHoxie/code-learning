#include<stdio.h>
#include<string.h>
int main(){
    int lon;
    char s[10002];
    scanf("%d",&lon);
    scanf("%s",s);
    int last;
    last = lon-strlen(s);
    for (int i = 0; i < last; i++)
    {
        printf("h");
    }
    printf("%s",s);
    return 0;
}