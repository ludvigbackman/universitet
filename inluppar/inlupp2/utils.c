#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "../inlupp1/linked_list.h"
#include "../inlupp1/iterator.h"
#include "../inlupp1/common.h"
#define _XOPEN_SOURCE 700
extern char *strdup(const char *);

///	@union answer
///	@brief This union allows different types to be used in the same function
///	@var answer::int_value
///		Member 'int_value' contains an int value
///	@var answer::float_value
///		Member 'float_value' contains a float value
///	@var answer::string_value
///		Member 'string_value' contains a string value 
union answer { 
  int   int_value;
  float float_value;
  char *string_value;
};

//typedef bool(*check_func)(char *);
//typedef answer_t(*convert_func)(char *);


void destroy_lists_and_itrs(ioopm_list_t* list1, ioopm_list_t *list2, ioopm_list_iterator_t *itr1, ioopm_list_iterator_t *itr2)
{
	ioopm_linked_list_destroy(list1);
	ioopm_linked_list_destroy(list2);
	ioopm_iterator_destroy(itr1);
	ioopm_iterator_destroy(itr2);
	list1 = NULL;
	list2 = NULL;
	itr1 = NULL;
	itr2 = NULL;
}

void destroy_list_and_itr(ioopm_list_t* list, ioopm_list_iterator_t *itr)
{
	ioopm_linked_list_destroy(list);
	ioopm_iterator_destroy(itr);
	list = NULL;
	itr = NULL;
}

void destroy_two_lists(ioopm_list_t* list1, ioopm_list_t* list2)
{
	ioopm_linked_list_destroy(list1);
	ioopm_linked_list_destroy(list2);
	list1 = NULL;
	list2 = NULL;
}


static answer_t ioopm_strdup(char *str)
{
  size_t len = strlen(str);
  char *result = calloc(len + 1, sizeof(char));
  strncpy(result, str, len);
  return (answer_t){.string_value = result};
}


bool is_number(char *str)
{
	if (str[0] == '-' || isdigit(str[0]))
	{
		for (size_t i = 1; i < strlen(str); i++)
		{
			if (isdigit(str[i]) == false)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool is_float(char *str)
{
	if (str[0] == '-' || isdigit(str[0]))
	{
		int counter = 0;
		for (size_t i = 1; i < strlen(str); i++)
		{
			if ((str[i] == '.') && counter > 1)
			{
				return false;
			}
			else if ((str[i] == '.') && counter <= 1)
			{
				counter++;
			}
			else if (isdigit(str[i]) == false)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void clear_input_buffer()
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}

int ask_question_int(char *question)
{
	answer_t answer = ask_question(question, is_number, make_int);
	return answer.int_value;
}

int read_string(char *buf, int buf_siz)
{
	int c;
	int i = 0;
	do
	{
		c = getchar();
		buf[i] = c;
		i++;
	} while (c != '\n' && c != EOF && i < buf_siz);
	buf[i - 1] = '\0';
	if (i >= buf_siz && c != '\n')
	{
		clear_input_buffer();
	}

	return i - 1;
}

char *ask_question_string(char *question)
{
    answer_t answer = ask_question(question, not_empty, ioopm_strdup);
	return answer.string_value;
}

double ask_question_float(char *question)
{
	return ask_question(question, is_float, make_float).float_value;
}

bool not_empty(char *str)
{
	return strlen(str) > 0;
}

answer_t make_float(char *str)
{
	return (answer_t){.float_value = atof(str)};
}

answer_t make_int(char *str)
{
	return (answer_t){.int_value = atoi(str)};
}

answer_t ask_question(char *question, check_func check, convert_func convert)
{
	int buf = 255;
	char answer[buf];
	do
	{
		printf("%s", question);
		read_string(answer, buf);
	} while (!check(answer));
	return convert(answer);
}
