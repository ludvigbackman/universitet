#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"

/**
 * @file hash_table.c
 * @author Simon Kedvall && Ludvig Bäckman
 * @date 14 Sep 2021
 * @brief Simple hash table that maps integer keys to string values.
 */

//#define No_Buckets 17
#define Success(v) (option_t){.success = true, .value = v};
#define Failure() (option_t){.success = false};
#define Successful(o) (o.success == true);
#define Unsuccessful(o) (o.success == false);
#define Initial_Value 17
#define Load_Factor 0.75

int primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381};



static entry_t *find_previous_entry_for_key(ioopm_hash_function hash, entry_t *node, unsigned long int_key) //TODO: ändra från hash till eq_func
{
  while (node->next && hash(node->next->key) < int_key)
  {
    node = node->next;
  }
  return node;
}

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  return new_entry;
}

static void entry_destroy(entry_t *node)
{
  free(node);
}

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash, ioopm_eq_function key_eq_func, ioopm_eq_function value_eq_func)
{
  return ioopm_hash_table_dynamic_create(hash, key_eq_func, value_eq_func, Load_Factor, Initial_Value, 0);
}

ioopm_hash_table_t *ioopm_hash_table_dynamic_create(ioopm_hash_function hash, ioopm_eq_function key_eq_func, ioopm_eq_function value_eq_func, float load_factor, size_t no_buckets, int prime_index)
{
  ioopm_hash_table_t *new_hash_table = calloc(1, sizeof(ioopm_hash_table_t));
  entry_t **buckets = calloc(1, sizeof(entry_t[no_buckets]));
  elem_t tmp;
  new_hash_table->buckets = buckets;
  for (int i = 0; i < no_buckets; i++)
  {
    new_hash_table->buckets[i] = entry_create(tmp, tmp, NULL);
  }

  new_hash_table->hash = hash;
  new_hash_table->key_eq_func = key_eq_func;
  new_hash_table->value_eq_func = value_eq_func;
  new_hash_table->no_buckets = no_buckets;
  new_hash_table->load_factor = load_factor;
  new_hash_table->size = 0;
  new_hash_table->prime_index = prime_index;
  return new_hash_table;
}

void realloc_buckets(ioopm_hash_table_t *ht)
{  
  int old_no_buckets = ht->no_buckets;
  ht->prime_index++;
  //printf("p_index:%d", ht->prime_index);
  ht->no_buckets = primes[ht->prime_index];
  entry_t **buckets = realloc(ht->buckets, sizeof(entry_t[ht->no_buckets]));
  elem_t tmp;
  for (int i = old_no_buckets; i < ht->no_buckets; i++)
  {
    buckets[i] = entry_create(tmp, tmp, NULL);
  }
  ht->buckets = buckets;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

static void ht_resize(ioopm_hash_table_t *ht) //Troligtviss ett dumt sätt att lösa på, fundera på om man kan använda realloc istället för att göra en helt ny hashtable
{
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
  ioopm_list_t *values = ioopm_hash_table_values(ht);
  ioopm_list_iterator_t *iter_keys = ioopm_list_iterator(keys);
  ioopm_list_iterator_t *iter_values = ioopm_list_iterator(values);
  ioopm_hash_table_clear(ht);
  realloc_buckets(ht);
  size_t size = ioopm_linked_list_size(keys);
  for (int i = 0; i < size; i++)
  {
    //printf("\nNO_ITEMS:%d\n", i);
    ioopm_hash_table_insert(ht, ioopm_iterator_current(iter_keys).value, ioopm_iterator_current(iter_values).value);
    ioopm_iterator_next(iter_keys);
    ioopm_iterator_next(iter_values);
  }
  ioopm_linked_list_destroy(keys);
  ioopm_linked_list_destroy(values);
  ioopm_iterator_destroy(iter_keys);
  ioopm_iterator_destroy(iter_values);
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < ht->no_buckets; i++)
  {
    entry_t *node = ht->buckets[i];
    entry_t *next_node;
    do
    {
      next_node = node->next;
      entry_destroy(node);
      node = next_node;
    } while (node);
  }
  free(ht->buckets);
  free(ht);
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  
  if (((ht->size + 1) / ht->no_buckets) >= ht->load_factor)
  {
    ht_resize(ht);
  }

  /// Calculate the bucket for this entry
  unsigned long int_key = ht->hash(key);
  int bucket = int_key % ht->no_buckets;
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(ht->hash, ht->buckets[bucket], int_key);
  entry_t *next = entry->next;

  if (next != NULL && ht->key_eq_func(next->key, key))
  {
    next->value = value;
  }
  else
  {
    entry->next = entry_create(key, value, next);
    ht->size++;
    //printf("\nSIZE:%d\n", ht->size);
  }
}

option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
  unsigned long int_key = ht->hash(key);
  int bucket = int_key % ht->no_buckets;
  entry_t *prev = find_previous_entry_for_key(ht->hash, ht->buckets[bucket], int_key);
  entry_t *node = prev->next;
  if (node && ht->key_eq_func(node->key, key))
  {
    return Success(node->value);
  }
  else
  {
    return Failure();
  }
}

option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
  unsigned long int_key = ht->hash(key);
  int bucket = int_key % ht->no_buckets;
  entry_t *prev = find_previous_entry_for_key(ht->hash, ht->buckets[bucket], int_key);
  entry_t *node = prev->next;
  option_t result;

  if (node && ht->key_eq_func(node->key, key))
  {
    result = Success(node->value);
    prev->next = node->next;
    entry_destroy(node);
    ht->size--;
  }
  else
  {
    result = Failure();
  }
  return result;
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  return ht->size;
  /*
  size_t counter = 0;
  for (int i = 0; i < ht->no_buckets; i++)
  {
    entry_t *node = ht->buckets[i]->next;
    while (node)
    {
      counter++;
      node = node->next;
    }
  }
  return counter;
  */
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ht->size == 0;
  /*
  for (int i = 0; i < ht->no_buckets; i++)
  {
    if (ht->buckets[i]->next)
    {
      return false;
    }
  }
  return true;
  */
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < ht->no_buckets; i++)
  {
    entry_t *node = ht->buckets[i]->next;
    entry_t *next_node;
    while (node)
    {
      next_node = node->next;
      entry_destroy(node);
      node = next_node;
    }
    ht->buckets[i]->next = NULL;
  }
  ht->size = 0;
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *list = ioopm_linked_list_create(ht->key_eq_func);
  for (int i = 0; i < ht->no_buckets; i++)
  {
    entry_t *node = ht->buckets[i]->next;
    while (node)
    {
      ioopm_linked_list_append(list, node->key);
      node = node->next;
    }
  }
  return list;
}

ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  ioopm_list_t *list = ioopm_linked_list_create(ht->value_eq_func);
  for (int i = 0; i < ht->no_buckets; i++)
  {
    entry_t *node = ht->buckets[i]->next;
    while (node)
    {
      ioopm_linked_list_append(list, node->value);
      node = node->next;
    }
  }
  return list;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
  bool result = ioopm_linked_list_contains(keys, key);
  ioopm_linked_list_destroy(keys);
  return result;
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
  ioopm_list_t *values = ioopm_hash_table_values(ht);
  //ioopm_list_iterator_t *iter = ioopm_list_iterator(values);
  bool result = ioopm_linked_list_contains(values, value);
  ioopm_linked_list_destroy(values);
  //ioopm_iterator_destroy(iter);
  return result;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
  size_t size = ioopm_hash_table_size(ht);
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
  ioopm_list_t *values = ioopm_hash_table_values(ht);
  ioopm_list_iterator_t *iter_keys = ioopm_list_iterator(keys);
  ioopm_list_iterator_t *iter_values = ioopm_list_iterator(values);
  bool result = true;
  for (int i = 0; i < size && result; ++i)
  {
    result = result && pred(ioopm_iterator_current(iter_keys).value, ioopm_iterator_current(iter_values).value, arg);
    ioopm_iterator_next(iter_keys);
    ioopm_iterator_next(iter_values);
  }
  ioopm_linked_list_destroy(keys);
  ioopm_linked_list_destroy(values);
  ioopm_iterator_destroy(iter_keys);
  ioopm_iterator_destroy(iter_values);
  return result;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
  size_t size = ioopm_hash_table_size(ht);
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
  ioopm_list_t *values = ioopm_hash_table_values(ht);
  ioopm_list_iterator_t *iter_keys = ioopm_list_iterator(keys);
  ioopm_list_iterator_t *iter_values = ioopm_list_iterator(values);
  bool result = false;
  for (int i = 0; i < size && result; ++i)
  {
    result = result || pred(ioopm_iterator_current(iter_keys).value, ioopm_iterator_current(iter_values).value, arg);
    ioopm_iterator_next(iter_keys);
    ioopm_iterator_next(iter_values);
  }
  ioopm_linked_list_destroy(keys);
  ioopm_linked_list_destroy(values);
  ioopm_iterator_destroy(iter_keys);
  ioopm_iterator_destroy(iter_values);
  return result;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg)
{
  for (int i = 0; i < ht->no_buckets; i++)
  {
    entry_t *node = ht->buckets[i]->next;
    while (node)
    {
      apply_fun(node->key, &node->value, arg);
      node = node->next;
    }
  }
}