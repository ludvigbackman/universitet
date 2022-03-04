#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iterator.h"
#include "linked_list.h"
#include "common.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>



static bool elem_int_equiv(elem_t elem1, elem_t elem2)
{
  
  return elem1.int_value == elem2.int_value;  
}

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void test_has_next1(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    ioopm_linked_list_append(list, int_elem(11));
    ioopm_linked_list_append(list, int_elem(22));
    CU_ASSERT(ioopm_iterator_has_next(iter));
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_has_next2(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    CU_ASSERT(ioopm_iterator_has_next(iter) == false);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_next1(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    ioopm_linked_list_append(list, int_elem(11));
    ioopm_linked_list_append(list, int_elem(22));
    ioopm_iterator_next(iter);
    CU_ASSERT(ioopm_iterator_has_next(iter) == false);
    CU_ASSERT(elem_int_equiv(iter->prev->element, int_elem(11)));
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_next2(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    option_t result = ioopm_iterator_next(iter);
    CU_ASSERT(result.success == false);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_remove1(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    ioopm_linked_list_append(list, int_elem(11));
    ioopm_linked_list_append(list, int_elem(22));
    ioopm_iterator_remove(iter);
    CU_ASSERT(ioopm_iterator_has_next(iter) == false);
    CU_ASSERT(elem_int_equiv(iter->prev->next->element, int_elem(22)));
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_remove2(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    option_t result = ioopm_iterator_remove(iter);
    CU_ASSERT(result.success == false);
    CU_ASSERT(iter->prev->next == NULL);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_insert1(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    ioopm_linked_list_append(list, int_elem(11));
    ioopm_iterator_insert(iter, int_elem(22));
    CU_ASSERT(elem_int_equiv(iter->prev->next->element, int_elem(22)));
    CU_ASSERT(elem_int_equiv(iter->prev->next->next->element, int_elem(11)));
    CU_ASSERT(elem_int_equiv(list->last->element, int_elem(11)));
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_insert2(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    ioopm_iterator_insert(iter, int_elem(5));
    CU_ASSERT(elem_int_equiv(ioopm_iterator_current(iter).value, int_elem(5)));
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_reset1(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    ioopm_linked_list_append(list, int_elem(11));
    ioopm_linked_list_append(list, int_elem(22));
    ioopm_linked_list_append(list, int_elem(33));
    ioopm_iterator_next(iter);
    ioopm_iterator_next(iter);
    ioopm_iterator_reset(iter);
    CU_ASSERT(iter->prev == list->first);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_current1(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    ioopm_linked_list_append(list, int_elem(11));
    option_t result = ioopm_iterator_current(iter);
    CU_ASSERT(elem_int_equiv(result.value, int_elem(11)));
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void test_current2(void)
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_int_equiv);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    option_t result = ioopm_iterator_current(iter);
    CU_ASSERT(result.success == false);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

int main()
{
    CU_pSuite test_suite_has_next = NULL;
    CU_pSuite test_suite_next = NULL;
    CU_pSuite test_suite_remove = NULL;
    CU_pSuite test_suite_insert = NULL;
    CU_pSuite test_suite_reset = NULL;
    CU_pSuite test_suite_current = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    test_suite_has_next = CU_add_suite("Has next", init_suite, clean_suite);
    test_suite_next = CU_add_suite("Next", init_suite, clean_suite);
    test_suite_remove = CU_add_suite("Remove", init_suite, clean_suite);
    test_suite_insert = CU_add_suite("Insert", init_suite, clean_suite);
    test_suite_reset = CU_add_suite("Reset", init_suite, clean_suite);
    test_suite_current = CU_add_suite("Current", init_suite, clean_suite);

    if (NULL == test_suite_has_next || NULL == test_suite_next || NULL == test_suite_remove ||
        NULL == test_suite_insert || NULL == test_suite_reset || NULL == test_suite_current)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(test_suite_has_next, "Has next", test_has_next1)) ||
        (NULL == CU_add_test(test_suite_has_next, "Empty list", test_has_next2)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(test_suite_next, "Has next", test_next1)) ||
        (NULL == CU_add_test(test_suite_next, "Empty list", test_next2)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(test_suite_remove, "Non-empty list", test_remove1)) ||
        (NULL == CU_add_test(test_suite_remove, "Empty list", test_remove2)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (
        (NULL == CU_add_test(test_suite_insert, "Non-empty list", test_insert1)) ||
        (NULL == CU_add_test(test_suite_insert, "Empty List", test_insert2)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (
        (NULL == CU_add_test(test_suite_reset, "Base case", test_reset1)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(test_suite_current, "Non-empty list", test_current1)) ||
        (NULL == CU_add_test(test_suite_current, "Empty list", test_current2)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
