#include <stdio.h>

void addmoney(int money) {  
    money = money + 100;  
    printf("函数内部：%d\n", money); 
}

int main() {
    int money = 100;
    printf("函数外部：%d\n", money);
    addmoney(money);           
    printf("函数外部：%d\n", money); 
    return 0;
}