#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

static void change_elem_int(elem_t ignore, elem_t *value, void *extra)
{
  elem_t *other_elem_ptr = extra;
  elem_t other_elem = *other_elem_ptr;
  value->int_value = other_elem.int_value;
}

static bool elem_int_equiv(elem_t elem1, elem_t elem2)
{
  
  return elem1.int_value == elem2.int_value;  
}

static bool elem_int_predicate_equiv(elem_t ignore, elem_t elem2, void *extra)
{
  elem_t *other_elem_ptr = extra;
  elem_t other_elem = *other_elem_ptr;
  return elem2.int_value == other_elem.int_value;  
}

void test_append1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  CU_ASSERT(elem_int_equiv(list->first->next->element, int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(11)));
  ioopm_linked_list_destroy(list);
}

void test_append2(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  CU_ASSERT(elem_int_equiv(list->first->next->element, int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(11)));
  ioopm_linked_list_append(list, int_elem(22));
  CU_ASSERT(elem_int_equiv(list->first->next->next->element, int_elem(22)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(22)));
  ioopm_linked_list_destroy(list);
}

void test_prepend1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_prepend(list, int_elem(11));
  CU_ASSERT(elem_int_equiv(list->first->next->element, int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(11)));
  ioopm_linked_list_destroy(list);
}

void test_prepend2(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_prepend(list, int_elem(11));
  CU_ASSERT(elem_int_equiv(list->first->next->element, int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(11)));
  ioopm_linked_list_prepend(list, int_elem(22));
  CU_ASSERT(elem_int_equiv(list->first->next->element, int_elem(22)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(11)));
  ioopm_linked_list_destroy(list);
}

void test_insert1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_insert(list, 0, int_elem(11));
  CU_ASSERT(elem_int_equiv(list->first->next->element,  int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(11)));
  ioopm_linked_list_destroy(list);
}

void test_insert2(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_insert(list, 0, int_elem(11));
  CU_ASSERT(elem_int_equiv(list->first->next->element, int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(11)));
  ioopm_linked_list_insert(list, 11, int_elem(22));
  CU_ASSERT(elem_int_equiv(list->first->next->element,  int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(22)));
  ioopm_linked_list_destroy(list);
}

void test_insert3(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  ioopm_linked_list_append(list, int_elem(33));
  CU_ASSERT(elem_int_equiv(list->first->next->element,  int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(33)));
  ioopm_linked_list_insert(list, 1, int_elem(22));
  CU_ASSERT(elem_int_equiv(list->first->next->next->element, int_elem(22)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(33)));
  ioopm_linked_list_destroy(list);
}

void test_remove1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  ioopm_linked_list_append(list, int_elem(22));
  CU_ASSERT(elem_int_equiv(list->first->next->element,  int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(22)));
  ioopm_linked_list_remove(list, 0);
  CU_ASSERT(elem_int_equiv(list->first->next->element,  int_elem(22)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(22)));
  ioopm_linked_list_destroy(list);
}

void test_remove2(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  ioopm_linked_list_append(list, int_elem(22));
  CU_ASSERT(elem_int_equiv(list->first->next->element,  int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(22)));
  ioopm_linked_list_remove(list, 1);
  CU_ASSERT(elem_int_equiv(list->first->next->element,  int_elem(11)));
  CU_ASSERT(elem_int_equiv(list->last->element, int_elem(11)));
  ioopm_linked_list_destroy(list);
}

void test_remove3(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  ioopm_linked_list_remove(list, 0);
  CU_ASSERT(list->first->next == NULL);
  CU_ASSERT(list->last == list->first);
  ioopm_linked_list_destroy(list);
}

void test_get1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  option_t test1 = ioopm_linked_list_get(list, 0);
  CU_ASSERT(elem_int_equiv(test1.value, int_elem(11)));
  ioopm_linked_list_append(list, int_elem(22));
  test1 = ioopm_linked_list_get(list, 0);
  option_t test2 = ioopm_linked_list_get(list, 1);
  CU_ASSERT(elem_int_equiv(test1.value, int_elem(11)));
  CU_ASSERT(elem_int_equiv(test2.value, int_elem(22)));
  ioopm_linked_list_append(list, int_elem(33));
  ioopm_linked_list_append(list, int_elem(44));
           test1 = ioopm_linked_list_get(list, 0);
           test2 = ioopm_linked_list_get(list, 1);
  option_t test3 = ioopm_linked_list_get(list, 2);
  option_t test4 = ioopm_linked_list_get(list, 3);
  CU_ASSERT(elem_int_equiv(test1.value, int_elem(11)));
  CU_ASSERT(elem_int_equiv(test2.value, int_elem(22)));
  CU_ASSERT(elem_int_equiv(test3.value, int_elem(33)));
  CU_ASSERT(elem_int_equiv(test4.value, int_elem(44)));
  option_t fail = ioopm_linked_list_get(list, 5);
  CU_ASSERT(fail.success == false)

  ioopm_linked_list_destroy(list);
}

void test_contains1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  ioopm_linked_list_append(list, int_elem(33));
  CU_ASSERT(ioopm_linked_list_contains(list, int_elem(11)));
  CU_ASSERT(ioopm_linked_list_contains(list, int_elem(33)));
  ioopm_linked_list_destroy(list);
}

void test_contains2(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  CU_ASSERT(ioopm_linked_list_contains(list, int_elem(11)) == false);
  ioopm_linked_list_destroy(list);
}

void test_size1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  CU_ASSERT(ioopm_linked_list_size(list) == 0);
  ioopm_linked_list_append(list, int_elem(11));
  CU_ASSERT(ioopm_linked_list_size(list) == 1);
  ioopm_linked_list_prepend(list, int_elem(22));
  CU_ASSERT(ioopm_linked_list_size(list) == 2);
  ioopm_linked_list_insert(list, 2, int_elem(33));
  CU_ASSERT(ioopm_linked_list_size(list) == 3);
  ioopm_linked_list_destroy(list);
}

void test_is_empty1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  CU_ASSERT(ioopm_linked_list_is_empty(list) == false);
  ioopm_linked_list_destroy(list);
}

void test_is_empty2(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  CU_ASSERT(ioopm_linked_list_is_empty(list));
  ioopm_linked_list_destroy(list);
}

void test_clear1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_clear(list);
  CU_ASSERT(ioopm_linked_list_size(list) == 0);
  ioopm_linked_list_append(list, int_elem(11));
  ioopm_linked_list_append(list, int_elem(33));
  CU_ASSERT(ioopm_linked_list_size(list) == 2);
  ioopm_linked_list_clear(list);
  CU_ASSERT(ioopm_linked_list_size(list) == 0);
  CU_ASSERT(list->last == list->first);
  CU_ASSERT(list->first->next == NULL);
  ioopm_linked_list_destroy(list);
}

void test_all1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  ioopm_linked_list_append(list, int_elem(22));
  CU_ASSERT(ioopm_linked_list_all(list, elem_int_predicate_equiv, &int_elem(11)) == false);
  ioopm_linked_list_destroy(list);
}

void test_all2(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(33));
  ioopm_linked_list_append(list, int_elem(33));
  CU_ASSERT(ioopm_linked_list_all(list, elem_int_predicate_equiv, &int_elem(33)));
  ioopm_linked_list_destroy(list);
}

void test_any1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  ioopm_linked_list_append(list, int_elem(22));
  CU_ASSERT(ioopm_linked_list_any(list, elem_int_predicate_equiv, &int_elem(22)));
  ioopm_linked_list_destroy(list);
}

void test_any2(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(33));
  ioopm_linked_list_append(list, int_elem(33));
  CU_ASSERT(ioopm_linked_list_any(list, elem_int_predicate_equiv, &int_elem(22)) == false);
  ioopm_linked_list_destroy(list);
}

void test_apply_to_all1(void)
{
  ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_append(list, int_elem(11));
  ioopm_linked_list_append(list, int_elem(22));
  ioopm_linked_list_apply_to_all(list, change_elem_int, &int_elem(11));
  CU_ASSERT(ioopm_linked_list_all(list, elem_int_predicate_equiv, &int_elem(11)));
  ioopm_linked_list_destroy(list);
}

int main()
{
  CU_pSuite test_suite_append = NULL;
  CU_pSuite test_suite_prepend = NULL;
  CU_pSuite test_suite_insert = NULL;
  CU_pSuite test_suite_remove = NULL;
  CU_pSuite test_suite_get = NULL;
  CU_pSuite test_suite_contains = NULL;
  CU_pSuite test_suite_size = NULL;
  CU_pSuite test_suite_is_empty = NULL;
  CU_pSuite test_suite_clear = NULL;
  CU_pSuite test_suite_all = NULL;
  CU_pSuite test_suite_any = NULL;
  CU_pSuite test_suite_apply_to_all = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  test_suite_append = CU_add_suite("Append", init_suite, clean_suite);
  test_suite_prepend = CU_add_suite("Prepend", init_suite, clean_suite);
  test_suite_insert = CU_add_suite("Insert", init_suite, clean_suite);
  test_suite_remove = CU_add_suite("Remove", init_suite, clean_suite);
  test_suite_get = CU_add_suite("Get", init_suite, clean_suite);
  test_suite_contains = CU_add_suite("Contains", init_suite, clean_suite);
  test_suite_size = CU_add_suite("Size", init_suite, clean_suite);
  test_suite_is_empty = CU_add_suite("Is empty", init_suite, clean_suite);
  test_suite_clear = CU_add_suite("Clear", init_suite, clean_suite);
  test_suite_all = CU_add_suite("All", init_suite, clean_suite);
  test_suite_any = CU_add_suite("Any", init_suite, clean_suite);
  test_suite_apply_to_all = CU_add_suite("Apply to all", init_suite, clean_suite);

  if (NULL == test_suite_append || NULL == test_suite_prepend || NULL == test_suite_insert ||
      NULL == test_suite_remove || NULL == test_suite_get || NULL == test_suite_contains ||
      NULL == test_suite_size || NULL == test_suite_is_empty || NULL == test_suite_clear ||
      NULL == test_suite_all || NULL == test_suite_any || NULL == test_suite_apply_to_all)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_append, "Empty list", test_append1)) ||
      (NULL == CU_add_test(test_suite_append, "At end", test_append2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_prepend, "Empty List", test_prepend1)) ||
      (NULL == CU_add_test(test_suite_prepend, "First", test_prepend2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_insert, "Empty list", test_insert1)) ||
      (NULL == CU_add_test(test_suite_insert, "At end", test_insert2)) ||
      (NULL == CU_add_test(test_suite_insert, "In middle", test_insert3)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_remove, "First", test_remove1)) ||
      (NULL == CU_add_test(test_suite_remove, "Last", test_remove2)) ||
      (NULL == CU_add_test(test_suite_remove, "One element", test_remove3)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_get, "Multiple", test_get1)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_contains, "First and last", test_contains1)) ||
      (NULL == CU_add_test(test_suite_contains, "Empty list", test_contains2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_size, "Multiple", test_size1)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_is_empty, "One link", test_is_empty1)) ||
      (NULL == CU_add_test(test_suite_is_empty, "Empty list", test_is_empty2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_clear, "Clear several", test_clear1)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_all, "False", test_all1)) ||
      (NULL == CU_add_test(test_suite_all, "True", test_all2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_any, "True", test_any1)) ||
      (NULL == CU_add_test(test_suite_any, "False", test_any2)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(test_suite_apply_to_all, "Apply", test_apply_to_all1)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
