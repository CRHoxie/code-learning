#include<stdio.h>
void bubble_sort(int arr[],int len){
    int i,j,temp;
    for(i=0;i<len-1;i++){
        for(j=0;j<len-1;j++)
        if ( arr[j]>arr[j+1])
        {
            temp =arr[j];
            arr[j]=arr[j+1];
            arr[j+1] = temp;
        }
    } 
}
int main(){
    //printf("please enter an array with on more than 30 element.");
    int arr[]={22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70};
    //for (int i = 0;scanf("%d",&arr[i])!=EOF; i++){}
    int len =sizeof(arr)/sizeof(arr[0]);
    bubble_sort(arr,len);
    for (int i = 0; i < len; i++) {
           printf("%d",arr[i]);  
           printf(" ");
        }
    return 0;
}