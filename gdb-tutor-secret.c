#include <stdio.h>
#include <stdlib.h>
int level2()
{
    int a = rand();
    int b = 0;
    __asm__("int3");
    printf("请告诉我位于 %p 处的int变量，其值是多少：", &a);
    scanf("%d", &b);
    return a == b;
}
