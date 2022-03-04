#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "utils.h"
#include "shop_backend.h"
#include "../inlupp1/linked_list.h"
#include "../inlupp1/hash_table.h"
#include "../inlupp1/iterator.h"
#include "../inlupp1/common.h"
#include "internal_data_structures.h"


static unsigned long string_knr_hash(const elem_t e);

static void destroy_locations(ioopm_list_t *locs)
{
	size_t no_of_locs = ioopm_linked_list_size(locs);
	for (size_t i = 0; i < no_of_locs; i++)
	{
		location_t *loc = ioopm_linked_list_get(locs, i).ptr;
		free(loc);
		loc = NULL;
	}
}

void ioopm_merch_destroy(merch_t *merch)
{
	destroy_locations(merch->locs);
	ioopm_linked_list_destroy(merch->locs);
	free(merch->desc);
	free(merch->name);
	merch->locs = NULL;
	free(merch);
	merch = NULL;
}

shop_t *ioopm_shop_create()
{
	ioopm_hash_table_t *ht_merch = ioopm_hash_table_create(string_knr_hash, string_key_equiv, string_eq);
	ioopm_hash_table_t *ht_shelf = ioopm_hash_table_create(string_knr_hash, string_key_equiv, string_eq);
	shop_t *shop = calloc(1, sizeof(shop_t));
	shop->ht_merch = ht_merch;
	shop->ht_shelf = ht_shelf;
	return shop;
}

void ioopm_shop_destroy(shop_t *shop)
{
	//ioopm_list_t *merch_names = ioopm_hash_table_keys(shop->ht_merch);
	//ioopm_list_iterator_t *merch_iterator = ioopm_list_iterator(merch_names);
	if(!ioopm_hash_table_is_empty(shop->ht_merch))
	{
		for(size_t i = 0; i<shop->ht_merch->size; i++)
		{
			//merch_t *current_merch = ioopm_hash_table_lookup(shop->ht_merch, ioopm_iterator_current(merch_iterator)).value.ptr;
			ioopm_shop_remove(shop, i);
			//free(current_merch->desc);
			//free(current_merch->name); 
		}
	}
	ioopm_hash_table_destroy(shop->ht_merch);
	ioopm_hash_table_destroy(shop->ht_shelf);
	free(shop);
	shop = NULL;
}

void ioopm_shop_add(shop_t *shop, char *name_chosen, char *desc_chosen, int price_chosen)
{
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	assert(ht_merch);
	if (!ioopm_hash_table_has_key(ht_merch, string_elem(name_chosen)))
	{
		merch_t *merch = calloc(1, sizeof(struct merch));
		merch->name = name_chosen;
		merch->desc = desc_chosen;
		merch->price = price_chosen;
		merch->locs = ioopm_linked_list_create(NULL);
		ioopm_hash_table_insert(ht_merch, string_elem(name_chosen), ptr_elem(merch));
	}
	else
	{
		printf("This name already exist! Operation failed.");
	}
}

static void shop_remove_shelf(ioopm_hash_table_t *ht_shelf, char *item_name)
{
	ioopm_list_t *list_of_items = ioopm_hash_table_values(ht_shelf);
	ioopm_list_t *list_of_shelves = ioopm_hash_table_keys(ht_shelf);
	if (ioopm_linked_list_is_empty(list_of_items) || ioopm_linked_list_is_empty(list_of_shelves))
	{
		return;
	}
	ioopm_list_iterator_t *itr_items = ioopm_list_iterator(list_of_items);
	ioopm_list_iterator_t *itr_locs = ioopm_list_iterator(list_of_shelves);
	size_t size = ioopm_linked_list_size(list_of_items);
	size_t i = 0;
	while (i < size)
	{
		char *current_item = ioopm_iterator_current(itr_items).string_value;
		char *current_loc = ioopm_iterator_current(itr_locs).string_value;
		if (item_name == current_item)
		{
			ioopm_hash_table_remove(ht_shelf, string_elem(current_loc));
			free(current_loc);
		}
		ioopm_iterator_next(itr_items);
		ioopm_iterator_next(itr_locs);
		i++;
	}
	destroy_lists_and_itrs(list_of_items, list_of_shelves, itr_items, itr_locs);
}

option_t ioopm_shop_remove(shop_t *shop, size_t answer)
{
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_hash_table_t *s_ht = shop->ht_shelf;
	ioopm_list_t *merch_names = ioopm_hash_table_keys(m_ht);
	ioopm_list_iterator_t *itr_merch = ioopm_list_iterator(merch_names);
	size_t size = ioopm_linked_list_size(merch_names);
	if (answer <= size)
	{
		for (size_t i = 0; i < answer; i++)
		{
			ioopm_iterator_next(itr_merch);
		}
		elem_t value = ioopm_iterator_current(itr_merch);
		option_t removed_item = ioopm_hash_table_remove(m_ht, value);
		merch_t *merch = removed_item.value.ptr;
		ioopm_list_t *locations = merch->locs;
		if (ioopm_linked_list_size(locations) == 0)
		{
			ioopm_merch_destroy(merch);
			destroy_list_and_itr(merch_names, itr_merch);
			return removed_item;
		}
		char *name_of_item_to_remove = merch->name;
		if (s_ht->size > 0)
		{
			shop_remove_shelf(s_ht, name_of_item_to_remove);
		}
		ioopm_merch_destroy(removed_item.value.ptr);
		destroy_list_and_itr(merch_names, itr_merch);
		return removed_item;
	}
	else
	{
		destroy_list_and_itr(merch_names, itr_merch);
		return Failure();
	}
}

static unsigned long string_knr_hash(const elem_t e)
{
	unsigned long result = 0;
	char *str = e.string_value;
	do
	{
		result = result * 31 + *str;
	} while (*++str != '\0');
	return result;
}

static void shop_rename_item_shelf(ioopm_hash_table_t *ht_shelf, char *old_item_name, char *new_item_name)
{
	ioopm_list_t *list_of_items = ioopm_hash_table_values(ht_shelf);
	ioopm_list_t *list_of_shelves = ioopm_hash_table_keys(ht_shelf);
	if (ioopm_linked_list_is_empty(list_of_items) || ioopm_linked_list_is_empty(list_of_shelves))
	{
		destroy_two_lists(list_of_items, list_of_shelves);
		return;
	}
	ioopm_list_iterator_t *itr_items = ioopm_list_iterator(list_of_items);
	ioopm_list_iterator_t *itr_locs = ioopm_list_iterator(list_of_shelves);
	size_t size = ioopm_linked_list_size(list_of_items);
	size_t i = 0;
	while (i < size)
	{
		char *current_item = ioopm_iterator_current(itr_items).string_value;
		char *current_loc = ioopm_iterator_current(itr_locs).string_value;
		if (old_item_name == current_item)
		{
			ioopm_hash_table_remove(ht_shelf, string_elem(current_loc));
			ioopm_hash_table_insert(ht_shelf, string_elem(current_loc), string_elem(new_item_name));
		}
		ioopm_iterator_next(itr_items);
		ioopm_iterator_next(itr_locs);
		i++;
	}
	destroy_lists_and_itrs(list_of_items, list_of_shelves, itr_items, itr_locs);
}

option_t ioopm_shop_edit(shop_t *shop, char *old_name, char *name, char *desc, int price)
{
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_hash_table_t *s_ht = shop->ht_shelf;
	option_t result = ioopm_hash_table_lookup(m_ht, string_elem(old_name));
	if (Successful(result))
	{
		elem_t foo = result.value;
		merch_t *old_merch = foo.ptr;
		ioopm_list_t *locs_to_save = old_merch->locs;
		ioopm_list_t *locs = calloc(1, sizeof(ioopm_list_t));
		*locs = *locs_to_save;
		free(old_merch->locs);
		free(old_merch);
		merch_t item = {.name = name, .desc = desc, .price = price, .locs = locs};
		merch_t *merch = calloc(1, sizeof(merch_t));
		*merch = item;
		ioopm_hash_table_remove(m_ht, string_elem(old_name));
		ioopm_hash_table_insert(m_ht, string_elem(name), ptr_elem(merch));
		shop_rename_item_shelf(s_ht, old_name, name);
		option_t return_value = {.success = true, .value.ptr = merch};
		return return_value;
	}
	else
	{
		return Failure();
	}
}

static option_t find_location(ioopm_list_t *locs, char *shelf)
{
	ioopm_list_iterator_t *iter = ioopm_list_iterator(locs);
	size_t size = ioopm_linked_list_size(locs);
	for (size_t i = 0; i < size; i++)
	{
		location_t *loc = ioopm_iterator_current(iter).ptr;
		if (strcmp(loc->shelf, shelf) == 0)
		{
			option_t return_value = {.success = true, .value.ptr = loc};
			ioopm_iterator_destroy(iter);
			return return_value;
		}
		ioopm_iterator_next(iter);
	}
	ioopm_iterator_destroy(iter);
	iter = NULL;
	return Failure();
}

option_t ioopm_shop_replenish(shop_t *shop, int item_to_replenish, char *shelf, int quantity)
{
	int size = strlen(shelf);
	if (size != 3 || !(isalpha(shelf[0]) && isdigit(shelf[1]) && isdigit(shelf[2])))
	{
		return Failure();
	}
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_hash_table_t *ht_shelf = shop->ht_shelf;
	assert(ht_merch);
	assert(ht_shelf);
	ioopm_list_t *merch_names = ioopm_hash_table_keys(ht_merch);
	ioopm_list_iterator_t *itr_merch = ioopm_list_iterator(merch_names);
	for (int i = 0; i < item_to_replenish; i++)
	{
		ioopm_iterator_next(itr_merch);
	}
	elem_t value = ioopm_iterator_current(itr_merch);
	merch_t *merch = ioopm_hash_table_lookup(ht_merch, value).value.ptr;
	char *name_of_item = merch->name;
	destroy_list_and_itr(merch_names, itr_merch);
	if (ioopm_hash_table_has_key(ht_shelf, string_elem(shelf)) && strcmp((ioopm_hash_table_lookup(ht_shelf, string_elem(shelf))).value.string_value, name_of_item) != 0)
	{
		return Failure();
	}
	option_t result = find_location(merch->locs, shelf);
	if (!Successful(result) && !ioopm_hash_table_has_key(ht_shelf, string_elem(shelf)))
	{
		location_t *shelf_unit = calloc(1, sizeof(location_t));
		shelf_unit->shelf = shelf;
		shelf_unit->quant = quantity;
		ioopm_hash_table_insert(ht_shelf, string_elem(shelf), string_elem(name_of_item));
		ioopm_linked_list_append(merch->locs, ptr_elem(shelf_unit));
		return Success(quantity);
	}
	else if (Successful(result) && ioopm_hash_table_has_key(ht_shelf, string_elem(shelf)))
	{
		location_t *loc = result.value.ptr;
		loc->quant += quantity;
		return Success(loc->quant);
	}
}

// CART FUNCTIONS // 

ioopm_hash_table_t *ioopm_create_cart(ioopm_list_t *list_of_carts) 
{
	ioopm_hash_table_t *cart = ioopm_hash_table_create(string_knr_hash, string_key_equiv, string_eq);
	ioopm_linked_list_append(list_of_carts, ptr_elem(cart));
	return cart;
}

static int calculate_index_of_cart(ioopm_list_t *list_of_carts, ioopm_hash_table_t *cart)
{
	ioopm_list_iterator_t *itr_carts = ioopm_list_iterator(list_of_carts);
	size_t size = ioopm_linked_list_size(list_of_carts);
	int counter = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (ioopm_iterator_current(itr_carts).ptr == cart)
		{
			ioopm_iterator_destroy(itr_carts);
			itr_carts = NULL;
			return counter;
		}
		counter++;
		ioopm_iterator_next(itr_carts);
	}
	ioopm_iterator_destroy(itr_carts);
	itr_carts = NULL;
	return -1;
}

void ioopm_remove_cart(ioopm_list_t *list, int index) 
{
	elem_t removed_item = ioopm_linked_list_remove(list, index);
	ioopm_hash_table_destroy(removed_item.ptr);
}

/*void ioopm_destroy_all_carts(ioopm_list_t *list_of_carts)
{
	size_t size =
}*/

static option_t check_stock(shop_t *shop, elem_t value, int quantity)
{
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_hash_table_t *s_ht = shop->ht_shelf;
	option_t lookup = ioopm_hash_table_lookup(m_ht, value);
	if (Successful(lookup))
	{
		merch_t *temp = lookup.value.ptr;
		ioopm_list_t *locs = temp->locs;
		int sum = 0;
		size_t size_locs = ioopm_linked_list_size(locs);
		size_t i = 0;
		while (i < size_locs)
		{
			location_t *locc = ioopm_linked_list_get(locs, i).ptr;
			int sum_quant = locc->quant;
			int tempint = sum + sum_quant;
			sum = tempint;
			i++;
		}
		if (quantity > sum)
		{
			return Failure();
		}
		else
			return Success(int_elem(sum - quantity));
	}
	return Failure();
}

option_t ioopm_add_to_cart(shop_t *shop, ioopm_hash_table_t *cart, size_t choice_of_merch, int quantity)
{
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_list_t *merch_names = ioopm_hash_table_keys(m_ht);
	ioopm_list_iterator_t *itr_merch = ioopm_list_iterator(merch_names);
	size_t merch_in_store = ioopm_linked_list_size(merch_names);
	if (choice_of_merch < merch_in_store)
	{
		for (size_t i = 0; i < choice_of_merch; i++)
		{
			ioopm_iterator_next(itr_merch);
		}
		elem_t value = ioopm_iterator_current(itr_merch);
		option_t stock = check_stock(shop, value, quantity);
		if (!Successful(stock))
		{
			destroy_list_and_itr(merch_names, itr_merch);
			return Failure();
		}
		option_t value_exists = ioopm_hash_table_lookup(cart, value);
		if (Successful(value_exists))
		{
			quantity = quantity + value_exists.value.int_value;
			ioopm_hash_table_remove(cart, value);
			ioopm_hash_table_insert(cart, value, int_elem(quantity));
			destroy_list_and_itr(merch_names, itr_merch);
			return Success(value);
		}
		else
		{
			ioopm_hash_table_insert(cart, value, int_elem(quantity));
			destroy_list_and_itr(merch_names, itr_merch);
			return Success(value);
		}
	}
	else
	{
		destroy_list_and_itr(merch_names, itr_merch);
		return Failure();
	}
}

option_t ioopm_remove_from_cart(ioopm_hash_table_t *cart, size_t item_to_remove, int quantity_to_remove)
{
	ioopm_list_t *merch_names = ioopm_hash_table_keys(cart);
	ioopm_list_iterator_t *itr_merch = ioopm_list_iterator(merch_names);
	size_t size = ioopm_linked_list_size(merch_names);
	if (item_to_remove <= size)
	{
		for (size_t i = 0; i < item_to_remove; i++)
		{
			ioopm_iterator_next(itr_merch);
		}
		elem_t value = ioopm_iterator_current(itr_merch);
		int quantity_in_cart = ioopm_hash_table_lookup(cart, value).value.int_value;
		if (quantity_to_remove >= quantity_in_cart)
		{
			ioopm_hash_table_remove(cart, value);
			destroy_list_and_itr(merch_names, itr_merch);
			return Success(ptr_elem(cart));
		}
		else
		{
			quantity_in_cart -= quantity_to_remove;
			ioopm_hash_table_remove(cart, value);
			ioopm_hash_table_insert(cart, value, int_elem(quantity_in_cart));
			destroy_list_and_itr(merch_names, itr_merch);
			return Success(ptr_elem(cart));
		}
	}
	else
	{
		destroy_list_and_itr(merch_names, itr_merch);
		return Failure();
	}
}

static int calculate_cost(ioopm_list_t *prices)
{
	ioopm_list_iterator_t *itr_prices = ioopm_list_iterator(prices);
	int total_cost = 0;
	for (size_t i = 0; i < ioopm_linked_list_size(prices); i++)
	{
		int curr_price = ioopm_iterator_current(itr_prices).int_value;
		total_cost = total_cost + curr_price;
		ioopm_iterator_next(itr_prices);
	}
	destroy_list_and_itr(prices, itr_prices);
	return total_cost;
}

int ioopm_cost_of_cart(shop_t *shop, ioopm_hash_table_t *cart)
{
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_hash_table_t *s_ht = shop->ht_shelf;
	ioopm_list_t *items_in_cart = ioopm_hash_table_keys(cart);
	ioopm_list_t *quantites_in_cart = ioopm_hash_table_values(cart);
	ioopm_list_iterator_t *itr_items = ioopm_list_iterator(items_in_cart);
	ioopm_list_iterator_t *itr_quantites = ioopm_list_iterator(quantites_in_cart);
	ioopm_list_t *prices = ioopm_linked_list_create(NULL);
	for (size_t i = 0; i < ioopm_linked_list_size(items_in_cart); i++)
	{
		elem_t name_of_item = ioopm_iterator_current(itr_items);
		int quant_of_item = ioopm_iterator_current(itr_quantites).int_value;
		merch_t *temp = ioopm_hash_table_lookup(m_ht, name_of_item).value.ptr;
		int price = temp->price;
		ioopm_linked_list_append(prices, int_elem(price * quant_of_item));
		ioopm_iterator_next(itr_items);
		ioopm_iterator_next(itr_quantites);
	}
	destroy_lists_and_itrs(items_in_cart, quantites_in_cart, itr_items, itr_quantites);
	return calculate_cost(prices);
}

static size_t get_num_of_item(shop_t *shop, elem_t name)
{
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	size_t ht_size = ht_merch->size;
	ioopm_list_t *merch_names = ioopm_hash_table_keys(ht_merch);
	ioopm_list_iterator_t *itr_merch = ioopm_list_iterator(merch_names);
	size_t counter = 0;
	for (size_t i = 0; i < ht_size; i++)
	{
		if (ioopm_iterator_current(itr_merch).string_value == name.string_value)
		{
			destroy_list_and_itr(merch_names, itr_merch);
			return counter;
		}
		counter++;
		ioopm_iterator_next(itr_merch);
	}
	destroy_list_and_itr(merch_names, itr_merch);
	return -1;
}

static int get_quantity(shop_t *shop, elem_t name)
{
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	option_t lookup = ioopm_hash_table_lookup(m_ht, name);
	if (Successful(lookup))
	{
		merch_t *temp = lookup.value.ptr;
		ioopm_list_t *locs = temp->locs;
		int sum = 0;
		size_t size_locs = ioopm_linked_list_size(locs);
		size_t i = 0;
		while (i < size_locs)
		{
			location_t *locc = ioopm_linked_list_get(locs, i).ptr;
			int sum_quant = locc->quant;
			int tempint = sum + sum_quant;
			sum = tempint;
			i++;
		}
		return sum;
	}
	else
	{
		return -1;
	}
}

void ioopm_checkout_cart(shop_t *shop, ioopm_list_t *list_of_carts, ioopm_hash_table_t *cart)
{
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_hash_table_t *ht_shelf = shop->ht_shelf;
	ioopm_list_t *names = ioopm_hash_table_keys(cart);
	ioopm_list_t *values = ioopm_hash_table_values(cart);
	if (cart->size == 1)
	{
		elem_t name_of_item1 = ioopm_linked_list_get(names, 0);
		elem_t quant_of_item = ioopm_linked_list_get(values, 0);
		option_t stock_option1 = check_stock(shop, name_of_item1, quant_of_item.int_value);
		if (stock_option1.success && stock_option1.value.int_value == 0)
		{
			size_t answer = get_num_of_item(shop, name_of_item1);
			ioopm_shop_remove(shop, answer);
			ioopm_remove_cart(list_of_carts, 0);
			destroy_two_lists(names, values);
			return;
		}
	}
	ioopm_list_iterator_t *itr_names = ioopm_list_iterator(names);
	ioopm_list_iterator_t *itr_values = ioopm_list_iterator(values);
	for (size_t i = 0; i < ioopm_linked_list_size(names); i++)
	{
		elem_t current_name_elem = ioopm_iterator_current(itr_names);
		option_t current_merch_option = ioopm_hash_table_lookup(ht_merch, current_name_elem);
		elem_t current_merch_elem = current_merch_option.value;
		option_t stock_option = check_stock(shop, current_name_elem, ioopm_iterator_current(itr_values).int_value);
		merch_t *current_merch = current_merch_elem.ptr;
		ioopm_list_t *current_merch_locations = current_merch->locs;
		if (stock_option.success && stock_option.value.int_value == 0)
		{
			ioopm_list_t *temp_locs = ioopm_hash_table_keys(ht_shelf);
			ioopm_list_iterator_t *location_iterator = ioopm_list_iterator(temp_locs);
			for (size_t n = 0; n < ioopm_linked_list_size(temp_locs); n++)
			{
				if (strcmp(ioopm_hash_table_lookup(ht_shelf, ioopm_iterator_current(location_iterator)).value.string_value, current_name_elem.string_value) == 0)
				{
					size_t answer = get_num_of_item(shop, current_name_elem);
					ioopm_shop_remove(shop, answer);
				}
				if (ioopm_iterator_has_next(location_iterator))
				{
					ioopm_iterator_next(location_iterator);
				}
			}
			ioopm_iterator_destroy(location_iterator);
			ioopm_linked_list_destroy(temp_locs);
		}
		else
		{
			elem_t current_checkout_value_elem = ioopm_iterator_current(itr_values);
			ioopm_list_iterator_t *current_merch_locations_iterator = ioopm_list_iterator(current_merch_locations);
			int checkout_counter = current_checkout_value_elem.int_value;
			int current_location_index = 0;
			while (checkout_counter > 0)
			{
				elem_t current_location_elem = ioopm_iterator_current(current_merch_locations_iterator);
				location_t *current_location = current_location_elem.ptr;
				int current_location_quantity = current_location->quant;
				if (current_location_quantity >= checkout_counter)
				{
					int change_value_temp = current_location_quantity - checkout_counter;
					current_location->quant = change_value_temp;
					if (current_location->quant == 0)
					{
						ioopm_linked_list_remove(current_merch_locations, current_location_index);
					}
					checkout_counter = 0;
				}
				else
				{
					int change_value_temp = checkout_counter - current_location_quantity;
					checkout_counter = change_value_temp;
					ioopm_linked_list_remove(current_merch_locations, current_location_index);
					change_value_temp = current_location_index + 1;
					current_location_index = change_value_temp;
				}
				ioopm_iterator_destroy(current_merch_locations_iterator);
			}
		}
		ioopm_iterator_next(itr_names);
		ioopm_iterator_next(itr_values);
	}
	ioopm_remove_cart(list_of_carts, calculate_index_of_cart(list_of_carts, cart));
	destroy_lists_and_itrs(names, values, itr_names, itr_values);
}

