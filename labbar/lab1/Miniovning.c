#include <stdio.h>

int main(void)
{
  int x = 1;
  int y = 2;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  puts("=====");
  int z = x;
  x = y;
  y= z;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  return 0;
}