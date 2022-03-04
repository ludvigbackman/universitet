#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../inlupp1/hash_table.h"

/**
 * @file internal_data_structures.h
 * @author Ludvig Bäckman and Sofia Alfsson
 * @date 3 Nov 2021
 * @brief Here are structs and typedefs defined used throughout the program
 *
 *  This header file defines structs and their typedefs, 
 *  used througout the other files in the program.
 *
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gf5efa1610dfd73b58fef071f6c1d7a90
 */

/// @struct option
/// @brief struct that makes up an option
/// @var option::success
/// Member 'success' contains a boolean value
/// @var option::value
/// Member 'value' contains a value of the type elem_t
struct option
{
	bool success;
	elem_t value;
};

/// @struct shop
/// @brief struct that makes up a shop in the webstore
/// @var shop::ht_merch
/// Member 'ht_merch' contains a hash table that contains items in the store
/// @var shop::ht_shelf
/// Member 'ht_shelf' contains a hash table that contains shelves and the items on them in the store
struct shop
{
	ioopm_hash_table_t *ht_merch;
	ioopm_hash_table_t *ht_shelf;
};

/// @struct merch
/// @brief struct defining the different aspects of a merch
/// @var merch::name
/// Member 'name' contains a char that is the name of the merch
/// @var merch::desc
/// Member 'desc' contains a char that is the description of the merch
/// @var merch::price
/// Member 'price' contains an int that is the price of the merch
/// @var merch::locs
/// Member 'locs' contains a linked list that which elements are locations of the merch in the store
struct merch
{
	char *name;
	char *desc;
	int price;
	ioopm_list_t *locs;
};

/// @struct location
/// @brief struct that makes up a location of a merch
/// @var location::shelf
/// Member 'shelf' contains a char that is the shelf the merch is located on
/// @var location::quant
/// Member 'quant' contains an int that is the quantity of the merch on the shelf
struct location
{
	char *shelf;
	int quant;
};

/** 
 * @typedef option_t
 * @brief typedef for the struct option
 */
typedef struct option option_t;

/** 
 * @typedef shop_t
 * @brief typedef for the struct shop
*/
typedef struct shop shop_t;

/**
 * @typedef merch_t
 * @brief typedef for the struct merch
 */
typedef struct merch merch_t; 

/**
 * @typedef location_t
 * @brief typedef for the struct location
 */
typedef struct location location_t;