#include<stdio.h>
int main(){
    int N,j=1;
    double sum=0.00;
    scanf("%d",&N);
    //printf("%d\n",N);
    for(double i=1.00;i<=N;i++){
        j++;
        sum+=1/(2*i-1);
        printf("%.2lf %d\n",sum,j);
    }
    printf("sum = %.6lf",sum);
    return 0;
}

/*int main(){
    double sum=0,i=1.00;
    int N;
    scanf("%d",&N);
    printf("%d",N);
    while(i<=N*1.0){
        sum+=1/i;
        i++;
        printf("%lf %lf\n",i,sum);
    }
    printf("sum = %.6lf",sum);
    return 0;
}*/