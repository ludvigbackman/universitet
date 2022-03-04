#include <stdio.h>

int main(void)
{
               // deklaration och initiering av iterationsvariabeln
  for (int i = 1; i <= 10; i = i + 1)         // iterationsvillkor (utför blocket så länge i är mindre än 11)
  {                       // loop-kropp (utförs så länge iterationsvillkoret är uppfyllt)
    printf("%d\n", i);    // skriv ut 1, och en radbrytning
                // öka i:s värde med 1 (förändring av iterationsvariabeln)
  }
  return 0;
}