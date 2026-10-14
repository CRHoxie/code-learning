#include<stdio.h>
int count (int *a)
{
    return *a * 365;
}
int main()
{
     int years = 2026-2008; 
    int days = count (&years);
    printf("I were spent a total of %d days in my life\n",days);
    printf ("%d",days);
}