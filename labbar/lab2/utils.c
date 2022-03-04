#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"


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

void clear_input_buffer()
{
    int c;
    do
        {
          c = getchar();
        }
      while (c != '\n' && c != EOF);
}

int ask_question_int(char *question)
{

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      clear_input_buffer();
      
      putchar('\n');
    }
  while (conversions < 1);
  return result;
}

int read_string(char *buf, int buf_siz)
{
    
    int c;
    int i = 0;

    do
        {
          c = getchar();
          buf[i] =c;
          i++;
        }
      while (c != '\n' && c != EOF && i < buf_siz);
     buf[i-1] = '\0';
    if (i >= buf_siz && c != '\n')
    {
      clear_input_buffer();
    }
    
    return i-1;
}

char *ask_question_string(char *question, char *buf, int buf_siz)
{
  do
  {
    printf("%s\n", question);
  }
  while(read_string(buf, buf_siz) == 0);
  return strdup(buf);
  
}


