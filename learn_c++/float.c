#include<stdio.h>

int main(void)
{
    float num;
    printf("This code is used for floating-point conversion...\n");
    printf("Enter a float");
    scanf("%f",&num);
    printf("The %.2f can also be represented as %.2e or %a",num,num,num);
    return 0;
    
}