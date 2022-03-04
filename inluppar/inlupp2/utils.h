#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../inlupp1/linked_list.h"
#include "../inlupp1/iterator.h"
/*#include "../inlupp1/hash_table.h"
#include "../inlupp1/common.h"
*/

/*!
* @brief includes strdup in the file
*/
#define _XOPEN_SOURCE 700

/**
 * @file utils.h
 * @author Ludvig Bäckman and Sofia Alfsson
 * @date 31 Oct 2021
 * @brief Functions for utility functions regarding the shop.
 *
 *  This header file defines simple functions regarding basic utilities.
 *  Functions that are defined include asking questions and getting a user answer,
 *  checking convertability of strings aswell as converting them; both to int and float values,
 *  checking whether a string is empty or not, reading a user input string into a buffer,
 *  aswell as clearing the input buffer.
 *
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gf5efa1610dfd73b58fef071f6c1d7a90
 */

/**
 * @typedef answer_t
 * @brief typedef for answer_t of the union answer
 */
typedef union answer answer_t;

/** 
 * @brief typedef for a function that checks if char * holds the condition in check_func and returns a bool
 */
typedef bool(*check_func)(char *);

/**
 * @brief typedef for a function that converts char * according to convert_func and returns an answer_t
 */
typedef answer_t(*convert_func)(char *);


/// @brief destroys and frees the allocated memory for a list and a iterator.
/// @param list The list to be destroyed and free'd
/// @param itr The iterator to be destroyed and free'd
void destroy_list_and_itr(ioopm_list_t* list, ioopm_list_iterator_t *itr);

/// @brief destroys and frees the allocated memory for two lists and two iterators.
/// @param list1 The first list to be destroyed and free'd
/// @param list2 The second list to be destroyed and free'd
/// @param itr1 The first iterator to be destroyed and free'd
/// @param itr2 The second iterator to be destroyed and free'd
void destroy_lists_and_itrs(ioopm_list_t* list1, ioopm_list_t *list2, ioopm_list_iterator_t *itr1, ioopm_list_iterator_t *itr2);

/// @brief destroys and frees the allocated memory for two lists 
/// @param list1 The first list to be destroyed and free'd
/// @param list2 The second list to be destroyed and free'd
void destroy_two_lists(ioopm_list_t* list1, ioopm_list_t* list2);

/// @brief Reads input from terminal into an adress buf
/// @param buf The address that should be written to
/// @param buf_siz The size of the buffer
/// @return The index for the last character
int read_string(char *buf, int buf_siz);

/// @brief Finds whether or not a string can be converted to an int
/// @param str The address of the string that should be used
/// @return Returns true if the string can be converted to an int
bool is_number(char *str);

/// @brief Prints a question in the terminal and returns a user input that can only be an int
/// @param question The address to the question that should be asked
/// @return The integer value that the user entered
int ask_question_int(char *question);

/// @brief Prints a question in the terminal and returns a user input that can only be a string
/// @param question The address to the question that should be asked
/// @return The string that the user entered
char *ask_question_string(char *question);

/// @brief Clears out the input buffer as a side effect
void clear_input_buffer();

/// @brief Makes a float from a string
/// @param str The address to be converted to float value
/// @return A struct where the float value is saved
answer_t make_float(char *str);

/// @brief Checks whether or not a string is empty
/// @param str The address to the string to be checked
/// @return Returns false if empty, true if not
bool not_empty(char *str);

/// @brief Finds whether or not a string can be converted to a float
/// @param str The address of the string that should be used
/// @return Returns true if the string can be converted to a float
bool is_float(char *str);

/// @brief Makes an int from a string
/// @param str The address to be converted to float value
/// @return A struct where the integer value is saved
answer_t make_int(char *str);

/// @brief Prints a question in the terminal and returns a user input
/// @param question The address to the question that should be asked
/// @param check A function that checks that the user input matches desired type
/// @param convert A function that converts the user input to your desired type
/// @return A struct where the integer value is saved
answer_t ask_question(char *question, check_func check, convert_func convert);

/// @brief Prints a question in the terminal and returns a user input that can only be a float
/// @param str The address to the question that should be asked
/// @return The float value that the user entered
double ask_question_float(char *str);

#endif