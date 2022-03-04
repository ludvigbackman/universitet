#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc < 3 || argc > 3)
{
  printf("Usage: ./a rows growth");
}
else
{
  int row = atoi(argv[1]);
  int grow = atoi(argv[2]);
  int x = 0;            
  for (int i = 1; i <= row; i = i + 1)         
  {                       
    for (int n = 1; n <= (i*grow); n++)         
    {                       
      printf("*");    
                  
    }    
    printf("\n");
    x = x+(i*grow);            
  }
  printf("Totalt: %d", x);
  return 0;
}
  
}