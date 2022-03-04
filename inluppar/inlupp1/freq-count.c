#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"
#include "common.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

static char *ioopm_strdup(char *str)
{
  size_t len = strlen(str);
  char *result = calloc(len + 1, sizeof(char));
  strncpy(result, str, len);
  return result;
}

static void free_strdup(elem_t key, elem_t *value, void *extra)
{
    free(key.string_value);
}

static int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
  qsort(keys, no_keys, sizeof(char *), cmpstringp);
}


void process_word(char *word, ioopm_hash_table_t *ht)
{

  int freq = 0;
  elem_t elem_word = { .string_value = word};
  if(ioopm_hash_table_has_key(ht, elem_word))
  {
    freq = ioopm_hash_table_lookup(ht, elem_word).value.int_value;
  }

  if(freq == 0)
  {
    elem_t temp;
    temp.string_value = strdup(word);
    ioopm_hash_table_insert(ht, temp, int_elem(1));
  }
  else
  {
    ioopm_hash_table_insert(ht, string_elem(word), int_elem(freq +1));
  }

/*
  // FIXME: Rewrite to match your own interface, error-handling, etc.
  int freq =
    ioopm_hash_table_has_key(ht, (elem_t) {.string_value = word})?
    (ioopm_hash_table_lookup(ht, (elem_t) {.string_value = word})).value.int_value:
    0;
  if (freq == 0)
  {
    elem_t temp;
    temp.string_value = ioopm_strdup(word);
    ioopm_hash_table_insert(ht, temp, (elem_t) {.int_value = freq + 1});
  }
  else
  {
    ioopm_hash_table_insert(ht, (elem_t) {.string_value = word}, (elem_t) {.int_value = freq + 1});
  }
*/
}
  


  

void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");

  while (true)
  {
    char *buf = NULL;
    size_t len = 0;
    getline(&buf, &len, f);

    if (feof(f))
    {
      free(buf);
      break;
    }

    for (char *word = strtok(buf, Delimiters);
         word && *word;
         word = strtok(NULL, Delimiters))
    {
      process_word(word, ht);
    }

    free(buf);
  }

  fclose(f);
}

unsigned long string_sum_hash(elem_t e)
{
  char *str = e.string_value;
  unsigned long result = 0;
  do
    {
      result += *str;
    }
  while (*++str != '\0');
  return result;
}

unsigned long string_knr_hash(elem_t e)
{
  char *str = e.string_value;
  unsigned long result = 0;
  do
    {
      result = result * 31 + *str;
    }
  while (*++str != '\0');
  return result;
}

bool string_eq(elem_t e1, elem_t e2)
{
  /*
  char *tmp1 = e1.string_value;
  char *tmp2 = e2.string_value;
  return (strcmp(tmp1, tmp2) == 0);
  */
  return strcmp(e1.string_value, e2.string_value) == 0;
}

int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create((ioopm_hash_function) string_knr_hash, string_eq, NULL);

  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      process_file(argv[i], ht);
    }
    ioopm_list_t *key_list = ioopm_hash_table_keys(ht);
    int size = ioopm_linked_list_size(key_list);
    char *keys[size];
    for(int i = 0; i < size; i++)
    {
      keys[i] = ioopm_linked_list_get(key_list, i).value.string_value;
    }
    sort_keys(keys, size);

    for (int i = 0; i < size; ++i)
    {
      // FIXME: Update to match your own interface, error handling, etc.
      int freq = (ioopm_hash_table_lookup(ht, (elem_t) {.string_value = keys[i]})).value.int_value;
      printf("%s: %d\n", keys[i], freq);
    }
    ioopm_linked_list_destroy(key_list);
  }
  else
  {
    puts("Usage: freq-count file1 ... filen");
  }

  // FIXME: Leaks memory! Use valgrind to find out where that memory is 
  // being allocated, and then insert code here to free it.
  
  ioopm_hash_table_apply_to_all(ht, free_strdup, NULL);
  ioopm_hash_table_destroy(ht);
}

