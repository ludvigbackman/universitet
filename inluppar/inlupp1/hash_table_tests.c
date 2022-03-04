#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"
#include "iterator.h"
#include "hash_table.h"
#include "common.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#define No_Buckets 17



static char *ioopm_strdup(char *str)
{
  size_t len = strlen(str);
  char *result = calloc(len + 1, sizeof(char));
  strncpy(result, str, len);
  return result;
}


bool int_equiv(elem_t elem1, elem_t elem2)
{
  return elem1.int_value == elem2.int_value;
}

bool string_equiv(elem_t elem1, elem_t elem2)
{
  char *string1 = elem1.ptr_value;
  char *string2 = elem2.ptr_value;
  return strcmp(string1, string2) == 0;
}

static bool string_value_equiv(elem_t key_ignored, elem_t value, void *x)
{
  elem_t *other_value_ptr = x;
  elem_t other_value = *other_value_ptr;
  return strcmp(value.ptr_value, other_value.ptr_value) == 0;
}

static void change_value(elem_t key_ignored, elem_t *value, void *x)
{
  elem_t *other_value_ptr = x;
  elem_t other_value = *other_value_ptr;
  *value = other_value;
}

int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

unsigned long int_hash_function(elem_t key)
{
  return key.int_value;
}

/*
static char * string_from_void(void *void_value)
{
  char **string_value_ptr = void_value;
  char  *test_value = *test_value_ptr;  
}
*/
#define ioopm_int_str_ht_insert(ht, i, s) \
   ioopm_hash_table_insert(ht, int_elem(i), ptr_elem(s))

void test_insert1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv); //Funkar inte, gillar inte typen. Be Ludvig kolla
  ioopm_int_str_ht_insert(ht, 4, "Hej");
  CU_ASSERT(string_equiv(ht->buckets[4]->next->value, ptr_elem("Hej")));
  ioopm_hash_table_destroy(ht);
}

void test_insert2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 4, "Hej");
  ioopm_int_str_ht_insert(ht, 21, "Hejdå");
  CU_ASSERT(string_equiv(ht->buckets[4]->next->value, ptr_elem("Hej")));
  CU_ASSERT(string_equiv(ht->buckets[4]->next->next->value, ptr_elem("Hejdå")));
  ioopm_hash_table_destroy(ht);
}

//------------Slutade här /Simon (12/10)-----------------

void test_insert3(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 4, "Hej");
  ioopm_int_str_ht_insert(ht, 38, "Hejdå");
  CU_ASSERT(string_equiv(ht->buckets[4]->next->value, ptr_elem("Hej")));
  CU_ASSERT(string_equiv(ht->buckets[4]->next->next->value, ptr_elem("Hejdå")));
  ioopm_int_str_ht_insert(ht, 21, "Hejsan");
  CU_ASSERT(string_equiv(ht->buckets[4]->next->next->value, ptr_elem("Hejsan")));
  ioopm_hash_table_destroy(ht);
}

void test_remove1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 4, "Hej");
  CU_ASSERT(string_equiv(ht->buckets[4]->next->value, ptr_elem("Hej")));
  ioopm_hash_table_remove(ht, int_elem(4));
  CU_ASSERT(ht->buckets[4]->next == NULL);
  ioopm_hash_table_destroy(ht);
}

void test_remove2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 4, "Hej");
  ioopm_int_str_ht_insert(ht, 21, "Hejdå");
  CU_ASSERT(string_equiv(ht->buckets[4]->next->value, ptr_elem("Hej")));
  CU_ASSERT(string_equiv(ht->buckets[4]->next->next->value, ptr_elem("Hejdå")));
  ioopm_hash_table_remove(ht, int_elem(4));
  CU_ASSERT(string_equiv(ht->buckets[4]->next->value, ptr_elem("Hejdå")));
  ioopm_hash_table_destroy(ht);
}

void test_remove3(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 4, "Hej");
  ioopm_int_str_ht_insert(ht, 38, "Hejdå");
  CU_ASSERT(string_equiv(ht->buckets[4]->next->value, ptr_elem("Hej")));
  CU_ASSERT(string_equiv(ht->buckets[4]->next->next->value, ptr_elem("Hejdå")));
  ioopm_int_str_ht_insert(ht, 21, "Hejsan");
  CU_ASSERT(string_equiv(ht->buckets[4]->next->next->value, ptr_elem("Hejsan")));
  ioopm_hash_table_remove(ht, int_elem(21));
  CU_ASSERT(string_equiv(ht->buckets[4]->next->next->value, ptr_elem("Hejdå")));
  ioopm_hash_table_destroy(ht);
}

void test_lookup1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 4, "Hej");
  CU_ASSERT(string_equiv(ioopm_hash_table_lookup(ht, int_elem(4)).value, ptr_elem("Hej")));
  ioopm_hash_table_destroy(ht);
}

void test_lookup2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  CU_ASSERT(ioopm_hash_table_lookup(ht, int_elem(21)).success == false);
  ioopm_hash_table_destroy(ht);
}

void test_lookup3(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 4, "Hej");
  ioopm_int_str_ht_insert(ht, 21, "Hejsan");
  ioopm_int_str_ht_insert(ht, 38, "Hejdå");
  CU_ASSERT(string_equiv(ioopm_hash_table_lookup(ht, int_elem(4)).value, ptr_elem("Hej")));
  CU_ASSERT(string_equiv(ioopm_hash_table_lookup(ht, int_elem(21)).value, ptr_elem("Hejsan")));
  CU_ASSERT(string_equiv(ioopm_hash_table_lookup(ht, int_elem(38)).value, ptr_elem("Hejdå")));
  ioopm_hash_table_destroy(ht);
}

void test_size1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  CU_ASSERT(ioopm_hash_table_size(ht) == 1);
  ioopm_hash_table_destroy(ht);
}

void test_size2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  CU_ASSERT(ioopm_hash_table_size(ht) == 0);
  ioopm_hash_table_destroy(ht);
}

void test_size3(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "Hejsan");
  ioopm_int_str_ht_insert(ht, 3, "Hejdå");
  ioopm_int_str_ht_insert(ht, 20, "Hejdå  Hej");
  ioopm_int_str_ht_insert(ht, 4, "Hejsan");
  ioopm_int_str_ht_insert(ht, 5, "Hejdå");
  ioopm_int_str_ht_insert(ht, 6, "Hejsan");
  ioopm_int_str_ht_insert(ht, 7, "Hejdå");
  ioopm_int_str_ht_insert(ht, 8, "Hejsan");
  ioopm_int_str_ht_insert(ht, 9, "Hejdå");
  ioopm_int_str_ht_insert(ht, 10, "Hejsan");
  ioopm_int_str_ht_insert(ht, 11, "Hejdå");
  ioopm_int_str_ht_insert(ht, 12, "Hejsan");
  ioopm_int_str_ht_insert(ht, 13, "Hejdå");
  ioopm_int_str_ht_insert(ht, 14, "Hejsan");
  ioopm_int_str_ht_insert(ht, 15, "Hejdå");
  ioopm_int_str_ht_insert(ht, 16, "Hejsan");
  ioopm_int_str_ht_insert(ht, 17, "Hejdå");

  CU_ASSERT(ioopm_hash_table_size(ht) == 18);
  ioopm_hash_table_destroy(ht);
}

void test_is_empty1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  CU_ASSERT(ioopm_hash_table_is_empty(ht) == false);
  ioopm_hash_table_destroy(ht);
}

void test_is_empty2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  CU_ASSERT(ioopm_hash_table_is_empty(ht) == true);
  ioopm_hash_table_destroy(ht);
}

void test_clear1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht))
  ioopm_hash_table_destroy(ht);
}

void test_clear2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "Hej");
  ioopm_int_str_ht_insert(ht, 19, "Heja");
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht))
  ioopm_hash_table_destroy(ht);
}

void test_get_keys1(void)
{
  CU_ASSERT(true);
  
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
  option_t result = ioopm_linked_list_get(keys, 0);
  CU_ASSERT(result.success == false);
  ioopm_linked_list_destroy(keys);
  ioopm_hash_table_destroy(ht);
  
}

void test_get_keys2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "Hejsan");
  ioopm_int_str_ht_insert(ht, 19, "Heja");
  ioopm_int_str_ht_insert(ht, 3, "Heja");
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
  int arg1 = 0;
  int arg2 = 1;
  int arg3 = 2;
  option_t result1 = ioopm_linked_list_get(keys, arg1);
  option_t result2 = ioopm_linked_list_get(keys, arg2);
  option_t result3 = ioopm_linked_list_get(keys, arg3);
  CU_ASSERT(int_equiv(result1.value, int_elem(1)));
  CU_ASSERT(int_equiv(result2.value, int_elem(2)));
  CU_ASSERT(int_equiv(result3.value, int_elem(19)));
  ioopm_linked_list_destroy(keys);
  ioopm_hash_table_destroy(ht);
}

void test_get_values1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_list_t *values = ioopm_hash_table_values(ht);
  CU_ASSERT(ioopm_linked_list_size(values) == 0);
  ioopm_linked_list_destroy(values);
  ioopm_hash_table_destroy(ht);
}

void test_get_values2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "Hejsan");
  ioopm_int_str_ht_insert(ht, 19, "Heja");
  ioopm_list_t *values = ioopm_hash_table_values(ht);
  CU_ASSERT(string_equiv(ioopm_linked_list_get(values, 0).value, ptr_elem("Hej")));
  CU_ASSERT(string_equiv(ioopm_linked_list_get(values, 1).value, ptr_elem("Hejsan")));
  CU_ASSERT(string_equiv(ioopm_linked_list_get(values, 2).value, ptr_elem("Heja")));
  CU_ASSERT(ioopm_linked_list_get(values, 3).success == false);
  ioopm_linked_list_destroy(values);
  ioopm_hash_table_destroy(ht);
}

void test_has_key1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  CU_ASSERT(ioopm_hash_table_has_key(ht, int_elem(1)) == false);
  ioopm_hash_table_destroy(ht);
}

void test_has_key2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "Hejsan");
  ioopm_int_str_ht_insert(ht, 19, "Heja");
  CU_ASSERT(ioopm_hash_table_has_key(ht, int_elem(1)) == true);
  CU_ASSERT(ioopm_hash_table_has_key(ht, int_elem(19)) == true);
  CU_ASSERT(ioopm_hash_table_has_key(ht, int_elem(3)) == false);
  ioopm_hash_table_destroy(ht);
}

void test_has_value1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem("OMG")) == false);
  ioopm_hash_table_destroy(ht);
}

void test_has_value2(void) //
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "hahha");
  ioopm_int_str_ht_insert(ht, 19, "Heja");
  char *test1 = ioopm_strdup("Hej");
  char *test2 = ioopm_strdup("OMG");
  char *test3 = ioopm_strdup("Heja");
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem("Hej")) == true);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem("OMG")) == false);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem("Heja")) == true);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem(test1)) == true);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem(test2)) == false);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem(test3)) == true);
  free(test1);
  free(test2);
  free(test3);
  ioopm_hash_table_destroy(ht);
}

void test_has_value3(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "Hej");
  ioopm_int_str_ht_insert(ht, 19, "Heja");
  char *test1 = ioopm_strdup("Hej");
  char *test2 = ioopm_strdup("OMG");
  char *test3 = ioopm_strdup("Heja");
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem("Hej")) == true);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem("OMG")) == false);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem("Heja")) == true);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem(test1)) == true);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem(test2)) == false);
  CU_ASSERT(ioopm_hash_table_has_value(ht, ptr_elem(test3)) == true);
  free(test1);
  free(test2);
  free(test3);
  ioopm_hash_table_destroy(ht);
}

void test_all1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "Hej");
  ioopm_int_str_ht_insert(ht, 19, "Hej");
  elem_t value;
  value.ptr_value = "Hej";
  CU_ASSERT(ioopm_hash_table_all(ht, string_value_equiv, &value));
  ioopm_hash_table_destroy(ht);
}

void test_all2(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "Hej");
  ioopm_int_str_ht_insert(ht, 19, "eja");
  elem_t value;
  value.ptr_value = "Hej";
  CU_ASSERT(ioopm_hash_table_all(ht, string_value_equiv, &value) == false);
  ioopm_hash_table_destroy(ht);
}

void test_apply_to_all1(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash_function, int_equiv, string_equiv);
  ioopm_int_str_ht_insert(ht, 1, "Hej");
  ioopm_int_str_ht_insert(ht, 2, "nope");
  ioopm_int_str_ht_insert(ht, 19, "Heja");
  elem_t value;
  value.ptr_value = "HI";
  ioopm_hash_table_apply_to_all(ht, change_value, &value);
  CU_ASSERT(ioopm_hash_table_all(ht, string_value_equiv, &value));
  ioopm_hash_table_destroy(ht);
}

int main()
{
  CU_pSuite test_suite_insert = NULL;
  CU_pSuite test_suite_remove = NULL;
  CU_pSuite test_suite_lookup = NULL;
  CU_pSuite test_suite_size = NULL;
  CU_pSuite test_suite_is_empty = NULL;
  CU_pSuite test_suite_clear = NULL;
  CU_pSuite test_suite_get_keys = NULL;
  CU_pSuite test_suite_get_values = NULL;
  CU_pSuite test_suite_has_key = NULL;
  CU_pSuite test_suite_has_value = NULL;
  CU_pSuite test_suite_all = NULL;
  CU_pSuite test_suite_apply_to_all = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  test_suite_insert = CU_add_suite("Insert", init_suite, clean_suite);
  test_suite_remove = CU_add_suite("Remove", init_suite, clean_suite);
  test_suite_lookup = CU_add_suite("Lookup", init_suite, clean_suite);
  test_suite_size = CU_add_suite("Size", init_suite, clean_suite);
  test_suite_is_empty = CU_add_suite("Is Empty", init_suite, clean_suite);
  test_suite_clear = CU_add_suite("Clear", init_suite, clean_suite);
  test_suite_get_keys = CU_add_suite("Get keys", init_suite, clean_suite);
  test_suite_get_values = CU_add_suite("Values", init_suite, clean_suite);
  test_suite_has_key = CU_add_suite("Has Key", init_suite, clean_suite);
  test_suite_has_value = CU_add_suite("Has Value", init_suite, clean_suite);
  test_suite_all = CU_add_suite("All", init_suite, clean_suite);
  test_suite_apply_to_all = CU_add_suite("Apply to all", init_suite, clean_suite);

  if (NULL == test_suite_insert || NULL == test_suite_remove || NULL == test_suite_lookup ||
      NULL == test_suite_size || NULL == test_suite_is_empty || NULL == test_suite_clear ||
      NULL == test_suite_get_keys || NULL == test_suite_get_values || NULL == test_suite_has_key ||
      NULL == test_suite_has_value || NULL == test_suite_all || NULL == test_suite_apply_to_all)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_insert, "Empty bucket", test_insert1)) ||
      (NULL == CU_add_test(test_suite_insert, "At end", test_insert2)) ||
      (NULL == CU_add_test(test_suite_insert, "In middle", test_insert3)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_remove, "At end", test_remove1)) ||
      (NULL == CU_add_test(test_suite_remove, "First", test_remove2)) ||
      (NULL == CU_add_test(test_suite_remove, "In middle", test_remove3)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_lookup, "One element", test_lookup1)) ||
      (NULL == CU_add_test(test_suite_lookup, "No element", test_lookup2)) ||
      (NULL == CU_add_test(test_suite_lookup, "Several elements", test_lookup3)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_size, "One element", test_size1)) ||
      (NULL == CU_add_test(test_suite_size, "No element", test_size2)) ||
      (NULL == CU_add_test(test_suite_size, "Several elements", test_size3)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_is_empty, "One element", test_is_empty1)) ||
      (NULL == CU_add_test(test_suite_is_empty, "No element", test_is_empty2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_clear, "No element", test_clear1)) ||
      (NULL == CU_add_test(test_suite_clear, "Several elements", test_clear2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_get_keys, "No element", test_get_keys1)) ||
      (NULL == CU_add_test(test_suite_get_keys, "Several elements", test_get_keys2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_get_values, "No element", test_get_values1)) ||
      (NULL == CU_add_test(test_suite_get_values, "Several elements", test_get_values2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_has_key, "Not in HT", test_has_key1)) ||
      (NULL == CU_add_test(test_suite_has_key, "In HT", test_has_key2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_has_value, "Not in HT", test_has_value1)) ||
      (NULL == CU_add_test(test_suite_has_value, "In HT", test_has_value2)) ||
      (NULL == CU_add_test(test_suite_has_value, "Several in HT", test_has_value3)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_all, "All match", test_all1)) ||
      (NULL == CU_add_test(test_suite_all, "One wrong", test_all2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_apply_to_all, "Change all values", test_apply_to_all1)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
