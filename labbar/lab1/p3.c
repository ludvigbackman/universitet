#include <stdio.h>

int main(void)
{
  int x = 0;            
  for (int i = 1; i <= 10; i = i + 1)         
  {                       
    for (int n = 1; n <= i; n++)         
    {                       
      printf("*");    
                  
    }    
    printf("\n");
    x = x+i;            
  }
  printf("Totalt: %d", x);
  return 0;
}