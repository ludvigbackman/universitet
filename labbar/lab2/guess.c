#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

int main() 
{
    int buf_size = 255;
    char name[buf_size];
    int tries = 15;

    srand(time(NULL));
    int r = rand() % 50;


    char *name1 = ask_question_string("Skriv in ditt namn:", name, buf_size);
    
    printf("Du %s, jag tänker på ett tal ... kan du gissa vilket?", name1);
    int guess = ask_question_int("");

    for (int x = 0; x < tries; ++x)
    {
        if (guess == r)
        {
            printf("Bingo!\n Det tog %s %d gissningar att komma fram till %d", name1, x, r);
            return 0;
        }
        else if (guess > r)
        {
            guess = ask_question_int("För stort!");
        }
        else
        {
            guess = ask_question_int("För litet!");
        }

    }

    printf("Nu har du slut på gissningar! Jag tänkte på %d!\n", r);
    
    return 0;
}
