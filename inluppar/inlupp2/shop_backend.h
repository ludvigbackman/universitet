#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "../inlupp1/common.h"
#include "../inlupp1/hash_table.h" 
#include "../inlupp1/linked_list.h"  
//#include "../inlupp1/iterator.h" 
#include "internal_data_structures.h"

/**
 * @file shop_backend.h
 * @author Sofia Alfsson and Ludvig Bäckman
 * @date 31 Oct 2021
 * @brief Backend functions to a simple web store. 
 *
 *  This header file defines functions regarding the backend side of a simple web store.
 *  Functions are defined for creating a shop, creating items in the shop, removing items in the shop, 
 *  repleneshing items, editing items, creating shopping carts, adding items to carts, removing items from carts,
 *  removing carts, calculating the cost of carts and checking out carts.
 *  
 *  @see $CANVAS_OBJECT_REFERENCE$/assignments/gf5efa1610dfd73b58fef071f6c1d7a90
 */

/// @brief Creates a new shop that holds merch items including all it's information. 
/// @return A new, empty shop 
shop_t *ioopm_shop_create();

/// @brief Destroys a shop and free's it's allocated memory.
/// @param shop the shop to be destroyed 
void ioopm_shop_destroy(shop_t *shop);

/// @brief Create a new merch item in the warehouse
/// @param shop the shop containing all the items
/// @param name name of the item to add
/// @param desc description of the item to add
/// @param price price of the item to add
void ioopm_shop_add(shop_t *shop, char *name, char *desc, int price);

/// @brief Removes an item in the shop, including all of it's stock
/// @param shop the shop containing all the items
/// @param answer the number corresponding to the item to be removed 
/// @return False in the return struct if answer did not correspond to an existing item, True in the return struct and the item removed if the item was removable.
option_t ioopm_shop_remove(shop_t *shop, size_t answer);


/// @brief Edits the name, description and price of a merch. Does not affect the merch's stock. 
/// @param shop the shop containing all the items
/// @param oldname the old name of the merch to be edited
/// @param name the new name of the merch to be edited
/// @param desc the new description of the merch to be edited 
/// @param price the new price of the merch to be edited 
/// @return False in the return struct if oldname did not correspond to an existing item, True in the return struct and the edited item if the item was editable
option_t ioopm_shop_edit(shop_t *shop, char *oldname, char *name, char *desc, int price);

/// @brief Replenishes the quantity of a merch and if chosen also adds a new storage location for the merch. 
/// @param shop the shop containing all the items
/// @param item_to_replenish the number corresponding to the merch to be replenished
/// @param shelf the name of the shelf to increase quantity of merch on. Could be a new or already existing shelf
/// @param quantity The quantity of which to increase the item with. 
/// @return False in the return struct if item_to_replenish did not correspond to an existing item, True in the return struct and the quantity of the merch if it existed. 
option_t ioopm_shop_replenish(shop_t *shop, int item_to_replenish, char *shelf, int quantity);

/// @brief Creates a new cart that holds merch to be bought by a customer. 
/// @param list_of_carts a list of carts in the system
/// @return A new, empty cart 
ioopm_hash_table_t *ioopm_create_cart(ioopm_list_t *list_of_carts);

/// @brief Removes a cart completely, including all the merch inside.  
/// @param cart_list A list containing all the active carts in the system. 
/// @param cart_to_remove the index corresponding to the cart to be removed in cart_list.
void ioopm_remove_cart(ioopm_list_t *cart_list, int cart_to_remove);

/// @brief Adds a chosen merch to a cart  
/// @param shop the shop containing all the items
/// @param cart the cart that the merch will be added to. 
/// @param choice_of_merch the number corresponding to the merch to be added to cart
/// @param quantity the quantity of the merch to be added to cart. 
/// @return False in the return struct if choice_of_merch did not correspond to a existing merch, True in the return struct and merch to be added if the merch was addable. 
option_t ioopm_add_to_cart(shop_t *shop, ioopm_hash_table_t *cart, size_t choice_of_merch, int quantity);

/// @brief Removes 0 or more of a chosen merch from the cart 
/// @param cart the cart that the merch will be removed from. 
/// @param item_to_remove the number corresponding to the merch to be removed from cart
/// @param quantity_to_remove the quantity of the merch to be removed from cart. 
/// @return False in the return struct if item_to_remove did not correspond to a existing merch, True in the return struct and the removed merch if the merch was removable. 
option_t ioopm_remove_from_cart(ioopm_hash_table_t *cart, size_t item_to_remove, int quantity_to_remove);

/// @brief Calculates the cost of a shopping cart 
/// @param shop the shop containing all the items
/// @param cart the cart which cost will be calculated 
/// @return The total cost of the cart 
int ioopm_cost_of_cart(shop_t *shop, ioopm_hash_table_t *cart);

/// @brief Checks out a cart from the system by removing the cart and decreasing the stock of the merch checked out in the cart in shop
/// @param shop the shop containing all the items
/// @param list_of_carts list containing all carts in the system
/// @param cart the cart which will be checked out
void ioopm_checkout_cart(shop_t *shop, ioopm_list_t *list_of_carts, ioopm_hash_table_t *cart);

/// @brief Frees the allocated memory of a merch item in the shop
/// @param merch the merch to be free'd
void ioopm_merch_destroy(merch_t *merch);

/// @brief Compares two elem_t's which have a valid string_value. Used in creating a new hash table. 
/// @param e1 The first string to be compared. 
/// @param e2 The second string to be compared.
/// @param extra argument that is ignored
/// @return False if the strings are not equal, true if they are. 
bool string_eq(elem_t e1, elem_t e2, void *extra);

/// @brief Hashing function for ioopm_hash_table_t. 
/// @param key Key to be hashed.  
/// @param value_ignored Value of the key, which is ignored in the function. 
/// @param x argument that is ignored
/// @return False if the hashing was successfull, true if it was not. 
bool string_key_equiv(elem_t key, elem_t value_ignored, void *x);