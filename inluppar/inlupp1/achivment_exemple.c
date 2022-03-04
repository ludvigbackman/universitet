#include <stdio.h>
#include <stdlib.h>

void swap1(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void swap2(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{

    puts("H19: Skillnaden mellan identitet och ekvivalens\n");

    int *val1 = calloc(1, sizeof(int));
    int *val2 = calloc(1, sizeof(int));
    *val1 = 1;
    *val2 = 1;
    printf("val1:%d\n", *val1);
    printf("val2:%d\n", *val2);
    *val1 += 1;
    puts("\nval1 + 1\n");
    printf("val1:%d\n", *val1);
    printf("val2:%d\n", *val2);

    puts("\n-------------------\n");
    *val1 = 1;
    val2 = val1;
    printf("val1:%d\n", *val1);
    printf("val2:%d\n", *val2);
    *val1 += 1;
    puts("\nval1 + 1\n");
    printf("val1:%d\n", *val1);
    printf("val2:%d\n", *val2);

    puts("\n-------------------\n");

    puts("H20: Värdeöverföring\n");
    int x = 7;
    int y = 42;
    printf("%d, %d\n", x, y);
    swap1(x, y);
    printf("Efter swap1: %d, %d\n", x, y);
    swap2(&x, &y);
    printf("Efter swap2: %d, %d\n", x, y);
    

    return 0;
}