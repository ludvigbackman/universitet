#include <stdbool.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
//#include "../inlupp1/iterator.h"
#include "../inlupp1/linked_list.h"
#include "../inlupp1/hash_table.h"
#include "../inlupp1/common.h"
#include "shop_backend.h"
#include "utils.h"
#include "internal_data_structures.h"

int init_suite(void)
{
	return 0;
}

int clean_suite(void)
{
	return 0;
}

void test_shop_add_one(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_shop_add(shop, "Cookie", "Crunchy tasty!", 420);
	option_t test_case = ioopm_hash_table_lookup(m_ht, string_elem("Cookie"));
	CU_ASSERT(Successful(test_case));
	ioopm_merch_destroy(test_case.value.ptr);
	ioopm_shop_destroy(shop);
}

void test_shop_add_invalid(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	option_t test_case = ioopm_hash_table_lookup(m_ht, string_elem("Cookie"));
	CU_ASSERT(Unsuccessful(test_case));
	ioopm_shop_destroy(shop);
}

void test_shop_add_several(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_shop_add(shop, "Cookie", "Crunchy tasty!", 420);
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_case1 = ioopm_hash_table_lookup(m_ht, string_elem("Cookie"));
	CU_ASSERT(Successful(test_case1));
	option_t test_case2 = ioopm_hash_table_lookup(m_ht, string_elem("Cake"));
	CU_ASSERT(Successful(test_case2));
	option_t test_case3 = ioopm_hash_table_lookup(m_ht, string_elem("Buns"));
	CU_ASSERT(Successful(test_case3));
	ioopm_merch_destroy(test_case1.value.ptr);
	ioopm_merch_destroy(test_case2.value.ptr);
	ioopm_merch_destroy(test_case3.value.ptr);
	ioopm_shop_destroy(shop);
}

void test_shop_remove_middle(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *s_ht = shop->ht_shelf;
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_shop_add(shop, "Cake", "Crunchy tasty!", 420);
	ioopm_shop_add(shop, "Cookie", "Yummy!", 120);
	option_t test_case1 = ioopm_hash_table_lookup(m_ht, string_elem("Cookie"));
	CU_ASSERT(Successful(test_case1));
	option_t test_case2 = ioopm_hash_table_lookup(m_ht, string_elem("Cake"));
	CU_ASSERT(Successful(test_case2));
	option_t test_replenish1 = ioopm_shop_replenish(shop, 0, "A33", 12);
	CU_ASSERT(Successful(test_replenish1));
	option_t test_replenish2 = ioopm_shop_replenish(shop, 1, "B53", 4);
	CU_ASSERT(Successful(test_replenish2));
	option_t test_case3 = ioopm_hash_table_lookup(s_ht, string_elem("A33"));
	CU_ASSERT(Successful(test_case3));
	option_t test_case4 = ioopm_hash_table_lookup(s_ht, string_elem("B53"));
	CU_ASSERT(Successful(test_case4));
	option_t test_remove = ioopm_shop_remove(shop, 1);
	CU_ASSERT(Successful(test_remove));
	option_t test_case5 = ioopm_hash_table_lookup(m_ht, string_elem("Cookie"));
	CU_ASSERT(Unsuccessful(test_case5));
	option_t test_case6 = ioopm_hash_table_lookup(m_ht, string_elem("Cake"));
	CU_ASSERT(Successful(test_case6));
	option_t test_case7 = ioopm_hash_table_lookup(s_ht, string_elem("A33"));
	CU_ASSERT(Successful(test_case7));
	option_t test_case8 = ioopm_hash_table_lookup(s_ht, string_elem("B53"));
	CU_ASSERT(Unsuccessful(test_case8));
	option_t test_remove1 = ioopm_shop_remove(shop, 0);
	CU_ASSERT(Successful(test_remove1));
	ioopm_shop_destroy(shop);
}

void test_shop_remove_last(void) 
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_hash_table_t *s_ht = shop->ht_shelf;
	ioopm_shop_add(shop, "Cookie", "Crunchy tasty!", 420);
	option_t test_case1 = ioopm_hash_table_lookup(m_ht, string_elem("Cookie"));
	option_t test_replenish1 = ioopm_shop_replenish(shop, 1, "A33", 7);
	CU_ASSERT(Successful(test_replenish1));
	CU_ASSERT(Successful(test_case1));
	option_t test_remove = ioopm_shop_remove(shop, 1);
	CU_ASSERT(Successful(test_remove));
	option_t test_case3 = ioopm_hash_table_lookup(m_ht, string_elem("Cookie"));
	CU_ASSERT(Unsuccessful(test_case3));
	option_t test_case4 = ioopm_hash_table_lookup(s_ht, string_elem("A33"));
	CU_ASSERT(Unsuccessful(test_case4));
	ioopm_shop_destroy(shop);
}

void test_shop_remove_invalid(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 1, "A33", 7);
	CU_ASSERT(Successful(test_replenish1));
	option_t test_remove = ioopm_shop_remove(shop, 2);
	CU_ASSERT(Unsuccessful(test_remove));
	option_t test_case = ioopm_hash_table_lookup(m_ht, string_elem("Cake"));
	CU_ASSERT(Successful(test_case));
	option_t test_remove1 = ioopm_shop_remove(shop, 0);
	CU_ASSERT(Successful(test_remove1));
	ioopm_shop_destroy(shop);
}

void test_shop_edit_several(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_hash_table_t *s_ht = shop->ht_shelf;
	ioopm_shop_add(shop, "Cookie", "Crunchy tasty!", 420);
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 1, "A33", 7);
	CU_ASSERT(Successful(test_replenish1));
	option_t test_replenish2 = ioopm_shop_replenish(shop, 2, "B53", 4);
	CU_ASSERT(Successful(test_replenish2));
	option_t test_replenish3 = ioopm_shop_replenish(shop, 3, "Y53", 5);
	CU_ASSERT(Successful(test_replenish3));
	option_t test_edit1 = ioopm_shop_edit(shop, "Cake", "Bananas", "Yellow Fruit", 22);
	CU_ASSERT(Successful(test_edit1));
	option_t test_case_m1 = ioopm_hash_table_lookup(m_ht, string_elem("Bananas"));
	CU_ASSERT(Successful(test_case_m1));
	option_t test_case_s1 = ioopm_hash_table_lookup(s_ht, string_elem("A33"));
	CU_ASSERT(Successful(test_case_s1));
	option_t test_edit2 = ioopm_shop_edit(shop, "Buns", "Apples", "Red Fruit", 11);
	CU_ASSERT(Successful(test_edit2));
	option_t test_case_m2 = ioopm_hash_table_lookup(m_ht, string_elem("Apples"));
	CU_ASSERT(Successful(test_case_m2));
	option_t test_case_s2 = ioopm_hash_table_lookup(s_ht, string_elem("B53"));
	CU_ASSERT(Successful(test_case_s2));
	option_t test_edit3 = ioopm_shop_edit(shop, "Cookie", "Pears", "Green Fruit", 7);
	CU_ASSERT(Successful(test_edit3));
	option_t test_case_m3 = ioopm_hash_table_lookup(m_ht, string_elem("Pears"));
	CU_ASSERT(Successful(test_case_m3));
	option_t test_case_s3 = ioopm_hash_table_lookup(s_ht, string_elem("B53"));
	CU_ASSERT(Successful(test_case_s3));
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_destroy(shop);
}

void test_shop_edit_invalid(void)
{
	shop_t *shop = ioopm_shop_create();
	option_t test_case1 = ioopm_shop_edit(shop, "Cookie", "Apple Pie", "Yummy Pie!", 1337);
	CU_ASSERT(Unsuccessful(test_case1));
	ioopm_shop_destroy(shop);
}

void test_shop_replenish_invalid(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *m_ht = shop->ht_merch;
	ioopm_hash_table_t *s_ht = shop->ht_shelf;
	ioopm_shop_add(shop, "Football", "Round", 111);
	option_t get_merch = ioopm_hash_table_lookup(m_ht, string_elem("Football"));
	CU_ASSERT(Successful(get_merch));
	option_t test_case1 = ioopm_shop_replenish(shop, 1, "a3a", 33);
	CU_ASSERT(Unsuccessful(test_case1));
	ioopm_hash_table_insert(s_ht, string_elem("a11"), string_elem("Shoe"));
	option_t test_case2 = ioopm_shop_replenish(shop, 1, "a11", 11);
	CU_ASSERT(Unsuccessful(test_case2));
	ioopm_shop_remove(shop, 0);
	ioopm_shop_destroy(shop);
}

void test_shop_replenish_make_shelf(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_hash_table_t *ht_shelf = shop->ht_shelf;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	option_t get_merch = ioopm_hash_table_lookup(ht_merch, string_elem("Cake"));
	CU_ASSERT(Successful(get_merch));
	option_t test_replenish = ioopm_shop_replenish(shop, 0, "A33", 12);
	CU_ASSERT(Successful(test_replenish));
	option_t test_ht_shelf = ioopm_hash_table_lookup(ht_shelf, string_elem("A33"));
	CU_ASSERT(Successful(test_ht_shelf));
	ioopm_shop_remove(shop, 0);
	ioopm_shop_destroy(shop);
}

void test_shop_replenish_existing(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	option_t get_merch = ioopm_hash_table_lookup(ht_merch, string_elem("Cake"));
	CU_ASSERT(Successful(get_merch));
	option_t test_replenish1 = ioopm_shop_replenish(shop, 0, "A33", 21);
	CU_ASSERT(Successful(test_replenish1));
	option_t test_replenish2 = ioopm_shop_replenish(shop, 0, "A33", 12);
	CU_ASSERT(Successful(test_replenish2));
	option_t get_merch2 = ioopm_hash_table_lookup(ht_merch, string_elem("Cake"));
	CU_ASSERT(Successful(get_merch2));
	merch_t *merch = get_merch.value.ptr;
	ioopm_list_t *locs = merch->locs;
	location_t *locc = ioopm_linked_list_get(locs, 0).ptr;
	CU_ASSERT_EQUAL(locc->quant, 33);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_destroy(shop);
}

void test_shop_replenish_several()
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_shelf = shop->ht_shelf;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 0, "A33", 7);
	CU_ASSERT(Successful(test_replenish1));
	option_t test_replenish2 = ioopm_shop_replenish(shop, 1, "B53", 4);
	CU_ASSERT(Successful(test_replenish2));
	option_t test_replenish3 = ioopm_shop_replenish(shop, 2, "Y53", 5);
	CU_ASSERT(Successful(test_replenish3));
	//ioopm_shop_list(shop);
	option_t test_lookup1 = ioopm_hash_table_lookup(ht_shelf, string_elem("A33"));
	CU_ASSERT_EQUAL(test_lookup1.value.string_value, "Cake");
	option_t test_lookup2 = ioopm_hash_table_lookup(ht_shelf, string_elem("B53"));
	CU_ASSERT_EQUAL(test_lookup2.value.string_value, "Buns");
	option_t test_lookup3 = ioopm_hash_table_lookup(ht_shelf, string_elem("Y53"));
	CU_ASSERT_EQUAL(test_lookup3.value.string_value, "Cookie");
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_destroy(shop);

}

void test_cart_add_one() 
{
	shop_t *shop = ioopm_shop_create();
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 0, "A33", 7);
	CU_ASSERT(Successful(test_replenish1));
	option_t test_replenish2 = ioopm_shop_replenish(shop, 1, "B53", 4);
	CU_ASSERT(Successful(test_replenish2));
	option_t test_replenish3 = ioopm_shop_replenish(shop, 2, "Y53", 5);
	CU_ASSERT(Successful(test_replenish3));
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add = ioopm_add_to_cart(shop, cart, 2, 3);
	CU_ASSERT(Successful(test_add));
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_remove_cart(list_of_carts, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}

void test_cart_add_several() 
{
	shop_t *shop = ioopm_shop_create();
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	ioopm_shop_add(shop, "Apples", "Red Fruit", 11);
	ioopm_shop_add(shop, "Pears", "Green Fruit", 7);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 0, "A33", 7);
	option_t test_replenish2 = ioopm_shop_replenish(shop, 1, "B53", 4);
	option_t test_replenish3 = ioopm_shop_replenish(shop, 2, "Y53", 5);
	option_t test_replenish4 = ioopm_shop_replenish(shop, 3, "J11", 22);
	option_t test_replenish5 = ioopm_shop_replenish(shop, 4, "U33", 56);
	CU_ASSERT(Successful(test_replenish1));
	CU_ASSERT(Successful(test_replenish2));
	CU_ASSERT(Successful(test_replenish3));
	CU_ASSERT(Successful(test_replenish4));
	CU_ASSERT(Successful(test_replenish5));
	//ioopm_shop_list(shop);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(int_eq);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add1 = ioopm_add_to_cart(shop, cart, 0, 6);
	CU_ASSERT(Successful(test_add1));
	option_t test_add2 = ioopm_add_to_cart(shop, cart, 1, 5);
	CU_ASSERT(Unsuccessful(test_add2));
	option_t test_add3 = ioopm_add_to_cart(shop, cart, 2, 2);
	CU_ASSERT(Successful(test_add3));
	option_t test_add4 = ioopm_add_to_cart(shop, cart, 3, 3);
	CU_ASSERT(Successful(test_add4));
	option_t test_add5 = ioopm_add_to_cart(shop, cart, 4, 44);
	CU_ASSERT(Successful(test_add5));
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_remove_cart(list_of_carts, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}

void test_cart_add_invalid()
{
	shop_t *shop = ioopm_shop_create();
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	option_t test_replenish = ioopm_shop_replenish(shop, 1, "A33", 7);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add = ioopm_add_to_cart(shop, cart, 3, 3);
	CU_ASSERT(Unsuccessful(test_add));
	ioopm_shop_remove(shop, 0);
	ioopm_remove_cart(list_of_carts, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}

void test_cart_add_existing()
{
	shop_t *shop = ioopm_shop_create();
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 1, "A33", 7);
	option_t test_replenish2 = ioopm_shop_replenish(shop, 2, "B53", 4);
	option_t test_replenish3 = ioopm_shop_replenish(shop, 3, "Y53", 5);
	//ioopm_shop_list(shop);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add1 = ioopm_add_to_cart(shop, cart, 2, 1);
	CU_ASSERT(Successful(test_add1));
	option_t test_add2 = ioopm_add_to_cart(shop, cart, 2, 3);
	CU_ASSERT(Successful(test_add2));
	ioopm_list_t *current_item_cart = ioopm_hash_table_keys(cart);
	ioopm_list_t *current_quant_in_cart = ioopm_hash_table_values(cart);
	CU_ASSERT_EQUAL(ioopm_linked_list_get(current_item_cart, 0).string_value,"Cookie");
	CU_ASSERT_EQUAL(ioopm_linked_list_get(current_quant_in_cart, 0).int_value, 4);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_remove_cart(list_of_carts, 0);
	ioopm_linked_list_destroy(current_item_cart);
	ioopm_linked_list_destroy(current_quant_in_cart);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);

}

void test_cart_remove() 
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_hash_table_t *ht_shelf = shop->ht_shelf;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 1, "A33", 7);
	option_t test_replenish2 = ioopm_shop_replenish(shop, 2, "B53", 4);
	option_t test_replenish3 = ioopm_shop_replenish(shop, 3, "Y53", 5);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add1 = ioopm_add_to_cart(shop, cart, 1, 3);
	option_t test_add2 = ioopm_add_to_cart(shop, cart, 2, 4);
	option_t test_remove1 = ioopm_remove_from_cart(cart, 0, 2);
	CU_ASSERT(Successful(test_remove1));
	option_t test_lookup1 = ioopm_hash_table_lookup(cart, test_add1.value);
	CU_ASSERT(Successful(test_lookup1));
	CU_ASSERT(test_lookup1.value.int_value == 1);
	option_t test_remove2 = ioopm_remove_from_cart(cart, 0, 1);
	CU_ASSERT(Successful(test_remove2));
	option_t test_lookup2 = ioopm_hash_table_lookup(cart, test_add1.value);
	CU_ASSERT(Unsuccessful(test_lookup2));
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_remove_cart(list_of_carts, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}

void test_cart_remove_invalid()
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_hash_table_t *ht_shelf = shop->ht_shelf;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 1, "A33", 7);
	option_t test_replenish2 = ioopm_shop_replenish(shop, 2, "B53", 4);
	option_t test_replenish3 = ioopm_shop_replenish(shop, 3, "Y53", 5);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add1 = ioopm_add_to_cart(shop, cart, 1, 3);
	option_t test_add2 = ioopm_add_to_cart(shop, cart, 2, 4);
	option_t test_remove1 = ioopm_remove_from_cart(cart, 3, 2);
	CU_ASSERT(Unsuccessful(test_remove1));
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_remove_cart(list_of_carts, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}

void test_cart_cost_one_item()
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_hash_table_t *ht_shelf = shop->ht_shelf;
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 1, "A33", 7);
	CU_ASSERT(Successful(test_replenish1));
	//ioopm_shop_list(shop);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add = ioopm_add_to_cart(shop, cart, 0, 5);
	CU_ASSERT(Successful(test_add));
	CU_ASSERT_EQUAL(ioopm_cost_of_cart(shop, cart), 145);
	ioopm_shop_remove(shop, 0);
	ioopm_remove_cart(list_of_carts, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}


void test_cart_cost_several_items()
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_hash_table_t *ht_shelf = shop->ht_shelf;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	ioopm_shop_add(shop, "Apples", "Red Fruit", 11);
	ioopm_shop_add(shop, "Pears", "Green Fruit", 7);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 0, "A33", 7);
	option_t test_replenish2 = ioopm_shop_replenish(shop, 1, "B53", 4);
	option_t test_replenish3 = ioopm_shop_replenish(shop, 2, "Y53", 5);
	option_t test_replenish4 = ioopm_shop_replenish(shop, 3, "J11", 22);
	option_t test_replenish5 = ioopm_shop_replenish(shop, 4, "U33", 56);
	CU_ASSERT(Successful(test_replenish1));
	CU_ASSERT(Successful(test_replenish2));
	CU_ASSERT(Successful(test_replenish3));
	CU_ASSERT(Successful(test_replenish4));
	CU_ASSERT(Successful(test_replenish5));
	//ioopm_shop_list(shop);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add1 = ioopm_add_to_cart(shop, cart, 0, 5);
	CU_ASSERT(Successful(test_add1));
	option_t test_add2 = ioopm_add_to_cart(shop, cart, 1, 2);
	CU_ASSERT(Successful(test_add2));
	option_t test_add3 = ioopm_add_to_cart(shop, cart, 2, 2);
	CU_ASSERT(Successful(test_add3));
	CU_ASSERT_EQUAL(ioopm_cost_of_cart(shop, cart), 704);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_remove_cart(list_of_carts, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}

void test_checkout_one_item(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_hash_table_t *ht_shelf = shop->ht_shelf;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 0, "A33", 7);
	CU_ASSERT(Successful(test_replenish1));
	option_t test_replenish2 = ioopm_shop_replenish(shop, 1, "B53", 4);
	CU_ASSERT(Successful(test_replenish2));
	option_t test_replenish3 = ioopm_shop_replenish(shop, 2, "Y53", 5);
	CU_ASSERT(Successful(test_replenish3));
	//ioopm_shop_list(shop);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add = ioopm_add_to_cart(shop, cart, 2, 3);
	CU_ASSERT(Successful(test_add));
	ioopm_checkout_cart(shop, list_of_carts, cart);
	ioopm_list_t *items = ioopm_hash_table_keys(ht_merch);
	CU_ASSERT_EQUAL("Cookie", ioopm_linked_list_get(items, 2).string_value);
	option_t lookup = ioopm_hash_table_lookup(ht_merch, ioopm_linked_list_get(items, 2));
	CU_ASSERT(Successful(lookup));
	merch_t *merch = lookup.value.ptr;
	ioopm_list_t *loc = merch->locs;
	location_t *locc = ioopm_linked_list_get(merch->locs, 0).ptr;
	CU_ASSERT_EQUAL(2, locc->quant);
	ioopm_linked_list_destroy(items);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}

void test_checkout_whole_stock(void) 
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 0, "A33", 7);
	CU_ASSERT(Successful(test_replenish1));
	option_t test_replenish2 = ioopm_shop_replenish(shop, 1, "B53", 4);
	CU_ASSERT(Successful(test_replenish2));
	option_t test_replenish3 = ioopm_shop_replenish(shop, 2, "Y53", 5);
	CU_ASSERT(Successful(test_replenish3));
	//ioopm_shop_list(shop);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	ioopm_list_t *items = ioopm_hash_table_keys(ht_merch);
	CU_ASSERT_EQUAL("Cookie", ioopm_linked_list_get(items, 2).string_value);
	option_t test_add = ioopm_add_to_cart(shop, cart, 2, 5);
	CU_ASSERT(Successful(test_add));
	ioopm_checkout_cart(shop, list_of_carts, cart);
	option_t lookup = ioopm_hash_table_lookup(ht_merch, ioopm_linked_list_get(items, 2));
	CU_ASSERT(Unsuccessful(lookup));
	ioopm_linked_list_destroy(items);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}

void test_checkout_several_items(void)
{
	shop_t *shop = ioopm_shop_create();
	ioopm_hash_table_t *ht_merch = shop->ht_merch;
	ioopm_shop_add(shop, "Cake", "Yummy!", 120);
	ioopm_shop_add(shop, "Cookie", "Crunchy!", 29);
	ioopm_shop_add(shop, "Buns", "Yummy!", 45);
	option_t test_replenish1 = ioopm_shop_replenish(shop, 0, "A33", 7);
	CU_ASSERT(Successful(test_replenish1));
	option_t test_replenish2 = ioopm_shop_replenish(shop, 1, "B53", 4);
	CU_ASSERT(Successful(test_replenish2));
	option_t test_replenish3 = ioopm_shop_replenish(shop, 2, "Y53", 5);
	CU_ASSERT(Successful(test_replenish3));
	//ioopm_shop_list(shop);
	ioopm_list_t *list_of_carts = ioopm_linked_list_create(NULL);
	ioopm_hash_table_t *cart = ioopm_create_cart(list_of_carts);
	option_t test_add1 = ioopm_add_to_cart(shop, cart, 0, 3);
	CU_ASSERT(Successful(test_add1));
	option_t test_add2 = ioopm_add_to_cart(shop, cart, 1, 3);
	CU_ASSERT(Successful(test_add2));
	option_t test_add3 = ioopm_add_to_cart(shop, cart, 2, 5);
	CU_ASSERT(Successful(test_add3));
	ioopm_list_t *items = ioopm_hash_table_keys(ht_merch);
	ioopm_checkout_cart(shop, list_of_carts, cart);
	CU_ASSERT_EQUAL("Cake", ioopm_linked_list_get(items, 0).string_value);
	option_t lookup1 = ioopm_hash_table_lookup(ht_merch, ioopm_linked_list_get(items, 0));
	CU_ASSERT(Successful(lookup1));
	merch_t *merch1 = lookup1.value.ptr;
	ioopm_list_t *loc1 = merch1->locs;
	location_t *locc1 = ioopm_linked_list_get(loc1, 0).ptr;
	CU_ASSERT_EQUAL(4, locc1->quant);
	CU_ASSERT_EQUAL("Buns", ioopm_linked_list_get(items, 1).string_value);
	option_t lookup2 = ioopm_hash_table_lookup(ht_merch, ioopm_linked_list_get(items, 1));
	CU_ASSERT(Successful(lookup2));
	merch_t *merch2 = lookup2.value.ptr;
	ioopm_list_t *loc2 = merch2->locs;
	location_t *locc2 = ioopm_linked_list_get(loc2, 0).ptr;
	CU_ASSERT_EQUAL(1, locc2->quant);
	option_t lookup3 = ioopm_hash_table_lookup(ht_merch, ioopm_linked_list_get(items, 2));
	CU_ASSERT(Unsuccessful(lookup3));
	ioopm_linked_list_destroy(items);
	ioopm_shop_remove(shop, 0);
	ioopm_shop_remove(shop, 0);
	ioopm_linked_list_destroy(list_of_carts);
	ioopm_shop_destroy(shop);
}



int main()
{
	CU_pSuite suite_add = NULL;
	CU_pSuite suite_remove = NULL;
	CU_pSuite suite_edit = NULL;
	CU_pSuite suite_replenish = NULL;
	CU_pSuite suite_cart_add = NULL;
	CU_pSuite suite_cart_remove = NULL;
	CU_pSuite suite_cart_cost = NULL;
	CU_pSuite suite_cart_checkout = NULL;
	

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	suite_add = CU_add_suite("Add", init_suite, clean_suite);
	suite_remove = CU_add_suite("Remove", init_suite, clean_suite);
	suite_edit = CU_add_suite("Edit", init_suite, clean_suite);
	suite_replenish = CU_add_suite("Replenish", init_suite, clean_suite);
	suite_cart_add = CU_add_suite("Add to cart", init_suite, clean_suite);
	suite_cart_remove = CU_add_suite("Remove from cart", init_suite, clean_suite);
	suite_cart_cost = CU_add_suite("Calculate cost of cart", init_suite, clean_suite);
	suite_cart_checkout = CU_add_suite("Checkout Cart", init_suite, clean_suite);
	
	if (NULL == suite_add || suite_remove == NULL || suite_edit == NULL || suite_replenish == NULL || suite_cart_add == NULL || suite_cart_remove == NULL || suite_cart_cost == NULL || suite_cart_checkout == NULL)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		(NULL == CU_add_test(suite_add, "Add one", test_shop_add_one)) ||
		(NULL == CU_add_test(suite_add, "Add none", test_shop_add_invalid)) ||
		(NULL == CU_add_test(suite_add, "Add several", test_shop_add_several))) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		(NULL == CU_add_test(suite_remove, "Middle", test_shop_remove_middle)) ||
		(NULL == CU_add_test(suite_remove, "Last", test_shop_remove_last)) ||
		(NULL == CU_add_test(suite_remove, "Empty table", test_shop_remove_invalid))) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		(NULL == CU_add_test(suite_edit, "Several", test_shop_edit_several)) ||
		(NULL == CU_add_test(suite_edit, "Empty", test_shop_edit_invalid))) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		(NULL == CU_add_test(suite_replenish, "Invalid", test_shop_replenish_invalid)) ||
		(NULL == CU_add_test(suite_replenish, "Existing", test_shop_replenish_make_shelf)) ||
		(NULL == CU_add_test(suite_replenish, "Make shelf", test_shop_replenish_existing)) ||
		(NULL == CU_add_test(suite_replenish, "Replenish Several", test_shop_replenish_several)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		(NULL == CU_add_test(suite_cart_add, "Add one", test_cart_add_one)) ||
		(NULL == CU_add_test(suite_cart_add, "Add several", test_cart_add_several)) ||
		(NULL == CU_add_test(suite_cart_add, "Add Invalid", test_cart_add_invalid)) ||
		(NULL == CU_add_test(suite_cart_add, "Add Existing", test_cart_add_existing)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		(NULL == CU_add_test(suite_cart_remove, "Remove one", test_cart_remove)) ||
		(NULL == CU_add_test(suite_cart_remove, "Remove several", test_cart_remove_invalid)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		(NULL == CU_add_test(suite_cart_cost, "Calculate cost of one item", test_cart_cost_one_item)) ||
		(NULL == CU_add_test(suite_cart_cost, "Calculate cost of several items", test_cart_cost_several_items)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (
		(NULL == CU_add_test(suite_cart_checkout, "Checkout one item", test_checkout_one_item)) ||
		(NULL == CU_add_test(suite_cart_checkout, "Checkout whole stock for item", test_checkout_whole_stock)) ||
		(NULL == CU_add_test(suite_cart_checkout, "Checkout several items", test_checkout_several_items)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
