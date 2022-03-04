#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


bool is_number(char *str)
{
  for (int i = 0; i < strlen(str); i++)
  {
      if (isdigit(str[i]) == false)
      {
          return false;
      }
  }
  return true;
}

int main (int argc, char *argv[])
{
    if ((argc < 3 || argc > 3) || !is_number(argv[1]) || !is_number(argv[2]))
    {
    printf("Usage: ./a int int");
    }
    else
    {
    
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    while (a!=b && a>1 && b>1)
    {
        if (a>b)
        {
            a = a-b;
        }
        else
        {
            b = b-a;
        }
    }
    printf("gcd(%s, %s) = %d", argv[1], argv[2], a);
    return 0;
    }
}