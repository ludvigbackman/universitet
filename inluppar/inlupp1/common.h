#pragma once
#include <stdlib.h>
/**
 * @file common.h
 * @author Simon Kedvall & Ludvig Bäckman
 * @date 1 Oct 2021
 * @brief --
 */

typedef union elem elem_t;
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

typedef struct link link_t;
typedef struct list ioopm_list_t;
typedef struct ioopm_list_iterator ioopm_list_iterator_t;

typedef struct option option_t;


typedef unsigned long (*ioopm_hash_function)(elem_t key);
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);
typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);

union elem
{
  int int_value;
  unsigned int uint_value;
  bool bool_value;
  float float_value;
  char *string_value;
  void *ptr_value;
  /// other choices certainly possible
};

struct entry
{
  elem_t key;    // holds the key
  elem_t value;  // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t **buckets;
  ioopm_hash_function hash;
  ioopm_eq_function key_eq_func;
  ioopm_eq_function value_eq_func;
  float load_factor;
  size_t no_buckets;
  size_t size;
  int prime_index;
};

struct option
{
  bool success;
  elem_t value;
};

struct link
{
    elem_t element;
    struct link *next;
};

struct list
{
    link_t *first;
    link_t *last;
    size_t size;
    ioopm_eq_function eq_func;
};

struct ioopm_list_iterator
{
    ioopm_list_t *list;
    link_t *prev;
};

#define int_elem(x) (elem_t) { .int_value=(x) }
#define ptr_elem(x) (elem_t) { .ptr_value=(x) }
#define string_elem(x) (elem_t) { .string_value=(x) }



