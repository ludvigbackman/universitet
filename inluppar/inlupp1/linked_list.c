#include "linked_list.h"
#include "iterator.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @file linked_list.c
 * @author Simon Kedvall && Ludvig Bäckman
 * @date 28 Sep 2021
 * @brief A simple linked list that implements parts of the interface 
 * of `linked_list.h`. The functions that are not implemented will fail
 * at runtime with an assertion error, printing a message to stderr.
 */


// The links of the linked list



static link_t *link_create(elem_t element, link_t *next)
{
    link_t *link = calloc(1, sizeof(link_t));
    link->element = element;
    link->next = next;
    return link;
}

static void link_destroy(link_t *link)
{
    free(link);
}





static link_t *find_previous_link(ioopm_list_t *list, int index)
{
    link_t *cursor = list->first;
    for (int i = 0; i < index; i++)
    {
        cursor = cursor->next;
        assert(cursor);
    }
    return cursor;
}

ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function eq_f)
{
    ioopm_list_t *ll = calloc(1, sizeof(struct list));
    elem_t tmp;
    ll->first = link_create(tmp, NULL);
    ll->last = ll->first;
    ll->size = 0;
    ll->eq_func = eq_f;
    return ll;
}

void ioopm_linked_list_append(ioopm_list_t *list, elem_t element)
{
    assert(list);
    link_t *new = link_create(element, NULL);
    list->last->next = new;
    list->last = new;
    list->size++;
}

void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t element)
{
    assert(list);
    link_t *new = link_create(element, list->first->next);
    list->first->next = new;
    if (list->size == 0)
    {
        list->last = new;
    }
    list->size++;
}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t element)
{
    assert(list);
    if (index > list->size)
    {
        index = list->size;
    }
    else if (index < 0)
    {
        index = 0;
    }
    link_t *prev = find_previous_link(list, index);
    prev->next = link_create(element, prev->next);
    if (prev == list->last)
    {
        list->last = prev->next;
    }
    list->size++;
}

option_t ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    assert(list);
    option_t result;
    if (index < 0 || index > list->size)
    {
        result.success = false;
        return result;
    }
    link_t *prev = find_previous_link(list, index);
    link_t *current = prev->next;
    assert(current);
    if (list->last == current)
    {
        list->last = prev;
    }
    prev->next = current->next;
    result.value = current->element;
    result.success = true;
    link_destroy(current);
    list->size--;
    return result;
}


option_t ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    assert(list);
    option_t result;
    if (index < 0 || index >= list->size)
    {
        result.success = false;
        return result;
    }
    link_t *prev = find_previous_link(list, index);
    result.value = prev->next->element;
    result.success = true;
    return result;
}


bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{
    assert(list);
    link_t *cursor = list->first->next;
    bool result = false;
    while (cursor)
    {
        result = result || list->eq_func(element, cursor->element);
        cursor = cursor->next;
    }
    return result;
}

int ioopm_linked_list_size(ioopm_list_t *list)
{
    assert(list);
    return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
    assert(list);
    return list->size == 0;
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
    assert(list);
    link_t *current = list->first->next;
    while (current)
    {
        link_t *tmp = current;
        current = current->next;
        link_destroy(tmp);
    }
    list->first->next = NULL;
    list->last = list->first;
    list->size = 0;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    assert(list);
    ioopm_linked_list_clear(list);
    free(list->first);
    free(list);
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_predicate prop, void *extra)
{
    assert(list);
    link_t *cursor = list->first->next;
    bool result = true;
    elem_t tmp;
    while (cursor)
    {
        result = result && prop(tmp, cursor->element, extra);
        cursor = cursor->next;
    }
    return result;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_predicate prop, void *extra)
{
    assert(list);
    link_t *cursor = list->first->next;
    bool result = false;
    elem_t tmp;
    while (cursor)
    {
        result = result || prop(tmp, cursor->element, extra);
        cursor = cursor->next;
    }
    return result;
}

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_function fun, void *extra)
{
    assert(list);
    link_t *cursor = list->first->next;
    elem_t tmp;
    while (cursor)
    {
        fun(tmp, &cursor->element, extra);
        cursor = cursor->next;
    }
}

//------------------- iterator ----------------------



ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list)
{
    ioopm_list_iterator_t *new_iter = calloc(1, sizeof(struct ioopm_list_iterator));
    new_iter->list = list;
    new_iter->prev = list->first;
    return new_iter;
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{
    link_t *current = iter->prev->next;
    if (current && current->next)
    {
        return true;
    }
    return false;
}

option_t ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
    link_t *current = iter->prev->next;
    option_t result;
    if (current && current->next)
    {
        iter->prev = current;
        result.value = current->element;
        result.success = true;
        return result;
    }
    result.success = false;
    return result;
}

option_t ioopm_iterator_remove(ioopm_list_iterator_t *iter)
{
    link_t *prev = iter->prev;
    link_t *current = prev->next;
    option_t result;
    if (current)
    {
        prev->next = current->next;
        result.value = current->element;
        link_destroy(current);
        iter->list->size--;
        result.success = true;
        return result;
    }
    else
    {
        result.success = false;
        return result;
    }
}

void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element)
{
    link_t *prev = iter->prev;
    prev->next = link_create(element, prev->next);
    if (prev == iter->list->last)
    {
        iter->list->last = prev->next;
    }
    iter->list->size++;
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
    iter->prev = iter->list->first;
}

option_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
    option_t result;
    if (iter->prev->next)
    {
        result.value = iter->prev->next->element;
        result.success = true;
        return result;
    }
    result.success = false;
    return result;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}