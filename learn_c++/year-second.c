#include<stdio.h>
int main(void)
{
    long year;
    printf("This code is transform you year to second\n");
    printf("Enter your year\n");
    scanf("%ld",&year);
    printf("You are spent %d second of your life",year*3.156e7);
    return 0;
}