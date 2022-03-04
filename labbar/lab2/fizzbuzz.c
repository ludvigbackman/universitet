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

void print_number(int num)
{
    if (num % 3 == 0 && num % 5 == 0)
    {
        printf(", FizzBuzz");
    }
    else if (num % 3 == 0)
    {
        printf(", Fizz");
    }
    else if (num % 5 == 0)
    {
        printf(", Buzz");
    }
    else
    {
        printf(", %d", num);
    }
}


int main(int argc, char *argv[])
{
    if ((argc < 2 || argc > 2) || !is_number(argv[1]))
    {
    printf("Usage: ./a int");
    }
    else
    {
        printf("1");
        for (int i = 2; i <= atoi(argv[1]); i++)
        {
        print_number(i);  
        }
        return 0;
    }
}