#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
  if (argc < 2 || argc > 2)
{
  printf("Usage: ./a int");
}
else
{
  int num = atoi(argv[1]);
  int lim = ((floor(sqrt(num)))+1);
  int x = 0;            
  for (int i = 1; i <= lim; i = i + 1)         
  {                       
    for (int n = 2; n <= num; n++)         
    {                       
      if ((n*i) == num)
      {
        x++;
        printf("%d * ", i);
        printf("%d\n", n);
      }    
                  
    }    
    
                
  }
  if (x>1 || num == 1 || num == 0)
  {
    printf("%d is not a prime number", num);
  }
  else
  {
    printf("%d is a prime number", num);
  }
  
  return 0;
}
  
}