#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "shop_backend.h"
#include "utils.h"
#include "internal_data_structures.h"

/**
 * @file shop_frontend.h
 * @author Sofia Alfsson and Ludvig Bäckman
 * @date 31Oct 2021
 * @brief Functions for the shop UI.
 *
 * This header file defines functions regarding the UI aspect of the shop. 
 * Functions are defined for listing all the merch in the shop, putting in a new merch in the shop, 
 * remove an item from the shop, edit an item in the shop, showing the stock for an item, replenish an item.
 * 
 * On the cart side of things functions are defined for removing a cart, adding a merch to a cart,
 * removing an item from a cart, calculating the cost of a cart, and cheching out a cart. 
 * 
 * Lastly a function that uses all the other functions in the file in order to run the program is defined. 
 * 
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gf5efa1610dfd73b58fef071f6c1d7a90
 */

/// @brief Lists all the merchandise in the hash table as a side effect
/// @param shop the shop containing the merchandise
void ioopm_shop_list(shop_t *shop);

/// @brief Asks the user for information for a new item to put in the shop
/// @param shop the shop containing the merchandise
void ioopm_input_merch(shop_t *shop);

/// @brief Asks the user for an item to remove in the shop
/// @param shop the shop containing the merchandise
void ioopm_remove_item_frontend(shop_t *shop);

/// @brief Asks the user for an item to edit in the shop
/// @param shop the shop containing the merchandise
void ioopm_edit_item_frontend(shop_t *shop);

/// @brief Prints the stock for a chosen item as a side effect
/// @param shop the shop containing the merchandise
/// @param item_chosen the number corresponding to the item whose stock is to be shown.
void ioopm_show_stock(shop_t *shop, size_t item_chosen);

/// @brief Asks for which item in the shop a stock will be shown for. 
/// @param shop the shop containing the merchandise
void ioopm_show_stock_question(shop_t *shop);

/// @brief Asks for which item in the shop the stock should be replenished for. 
/// @param shop the shop containing the merchandise
void ioopm_replenish_merch(shop_t *shop);

/// @brief Asks which cart in the system should be removed 
/// @param list_of_carts the list of carts in the system.
void ioopm_remove_cart_frontend(ioopm_list_t *list_of_carts);

/// @brief Makes the user chose a cart to add an item to and then choose the item and quantity of it to be added to the cart
/// @param shop the shop containing the merchandise
/// @param list_of_carts the list of carts in the system.
void ioopm_add_to_cart_frontend(shop_t *shop, ioopm_list_t *list_of_carts);

/// @brief Makes the user chose a cart to remove an item from and then choose the item and quantity of it to be removed from the cart
/// @param shop the shop containing the merchandise
/// @param list_of_carts the list of carts in the system.
void ioopm_remove_item_from_cart_frontend(shop_t *shop, ioopm_list_t *list_of_carts);

/// @brief Makes the user chose a cart to calculate the cost of and then calculates the cost of the cart. 
/// @param shop the shop containing the merchandise
/// @param list_of_carts the list of carts in the system
void ioopm_calculate_cost_frontend(shop_t *shop, ioopm_list_t *list_of_carts);

/// @brief Makes the user chose a cart to checkout in the system and then checks out the cart. 
/// @param shop the shop containing the merchandise
/// @param list_of_carts the list of carts in the system
void ioopm_checkout_frontend(shop_t *shop, ioopm_list_t *list_of_carts);
