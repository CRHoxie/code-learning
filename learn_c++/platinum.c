#include<stdio.h>
int main (void)
{
    float weight;
    float value;\
    int test;
    int a=sizeof(test);

    printf ("Are you worth your weight in platinum\n");
    printf ("Let's check it out\n");
    printf ("Please enter your weihght in pounds\n");
    
    scanf ("%f",&weight);
    value=1700.0*weight*14.5833;
    printf("your weight in platinum is worth $%.2f.\n",value);
    printf("yes\n%d",a);
    return 0;
    getchar();
    getchar();
}