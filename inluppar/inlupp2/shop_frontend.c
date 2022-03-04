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

// FUNCTIONS // 

void ioopm_input_merch(shop_t *shop) 
{
    char *name = ask_question_string("\nWhat's the name of your item?\n");
    char *description = ask_question_string("\nGive a description of your item:\n");
    int price = ask_question_int("\nWhat is the price of the product?\n");
    ioopm_shop_add(shop, name, description, price);
    //free(description);
    //free(name);
    //printf("\nThe item %s with the description %s and price %d was added to the shop.\n", name, description, price);
    return;
}

void ioopm_shop_list(shop_t *shop) 
{
    ioopm_hash_table_t *ht_merch = shop->ht_merch;
    if (ioopm_hash_table_is_empty(ht_merch))
    {
        printf("\nThere are no items available in the store!\n");
        return;
    }
	size_t ht_size = ht_merch->size;
	ioopm_list_t *merch_names = ioopm_hash_table_keys(ht_merch);
	ioopm_list_iterator_t *itr_merch = ioopm_list_iterator(merch_names);
	size_t counter = 0;
	char *answer;
    char *test = "q";
	do
	{
		for(size_t i = 0; counter < ht_size && i < 20; i++)
		{
			printf("\n%lu: %s\n", counter, ioopm_iterator_current(itr_merch).string_value);
			ioopm_iterator_next(itr_merch);
			counter++;
            if (counter == 20)
            {
                answer = ask_question_string("\nIf you wish to continue, enter Yes. Enter q to exit: \n");

            }
		}
	} while (counter < ht_size && *answer != *test);
	ioopm_linked_list_destroy(merch_names);
	ioopm_iterator_destroy(itr_merch);
}

void ioopm_remove_item_frontend(shop_t *shop)
{
    if (shop->ht_merch->size == 0)
    {
        printf("\nThere are no items in the store to remove! Try adding an item and try again!\n");
        return;
    }
    ioopm_hash_table_t *ht_merch = shop->ht_merch;
    ioopm_shop_list(shop);
    size_t item_to_remove = ask_question_int("\nWhich item do you want to remove? Choose by number:\n");
    size_t size_ht = ioopm_hash_table_size(ht_merch);
    if (item_to_remove < size_ht)
    {
        ioopm_shop_remove(shop, item_to_remove);
        printf("\nThe item and it's stock was removed from the shop.\n");
    }
    else 
    {
        printf("\nThe number entered does not correspond with an existing item. Please try again.\n");
    }
}

void ioopm_edit_item_frontend(shop_t *shop)
{
    if (shop->ht_merch->size == 0)
    {
        printf("\nThere are no items in the store to edit! Try adding an item and try again!\n");
        return;
    }
    ioopm_shop_list(shop);
    char *item_to_edit = ask_question_string("\nWhich item do you want to edit? Please enter the name of the item: \n");
    char *new_name = ask_question_string("\nEnter the new name of the item: \n");
    char *new_desc = ask_question_string("\nEnter the new description of the item: \n");
    int new_price = ask_question_int("\nEnter the new price of the item: \n");
    option_t edit = ioopm_shop_edit(shop, item_to_edit, new_name, new_desc, new_price);
    if (Unsuccessful(edit))
    {
        printf("\nThe item you put in was a not an editable item! Please try again!\n");
        return;
    }
    if (Successful(edit))
    {
        printf("\n%s was edited to have the name %s, description %s and price %d.\n", item_to_edit, new_name, new_desc, new_price);
    }
}

void ioopm_show_stock(shop_t *shop, size_t item_chosen)
{
    ioopm_hash_table_t *ht_merch = shop->ht_merch;
    ioopm_list_t *merch_names = ioopm_hash_table_keys(ht_merch);
	ioopm_list_iterator_t *itr_merch = ioopm_list_iterator(merch_names);
	size_t size = ioopm_linked_list_size(merch_names);
	if (item_chosen < size)
	{
		for(size_t i = 0; i < item_chosen; i++)
		{
			ioopm_iterator_next(itr_merch);
		}
		elem_t value = ioopm_iterator_current(itr_merch);
        option_t value_lookup = ioopm_hash_table_lookup(ht_merch, value);
        merch_t *merch = value_lookup.value.ptr;
        ioopm_list_t *locs = merch->locs;
        size_t size_locs = ioopm_linked_list_size(locs);
        if (size_locs == 0)
        {
            printf("\nThis item currently has no stock. Try repleneshing it and try again.\n");
            ioopm_linked_list_destroy(merch_names);
		    ioopm_iterator_destroy(itr_merch);
		    merch_names = NULL;
		    itr_merch = NULL;
            return;
        }
        for(size_t i = 0; i < size_locs; i++)
		{
			location_t *loc = ioopm_linked_list_get(locs, i).ptr;
            printf("Shelf: %s \nQuantity: %d \n", loc->shelf, loc->quant);   
		}
		ioopm_linked_list_destroy(merch_names);
		ioopm_iterator_destroy(itr_merch);
		merch_names = NULL;
		itr_merch = NULL;
	}
	else
	{
		ioopm_linked_list_destroy(merch_names);
		ioopm_iterator_destroy(itr_merch);
        merch_names = NULL;
        itr_merch = NULL; 
		printf("\nNumber given outside given range! Please try again.\n");
	}
}

void ioopm_show_stock_question(shop_t *shop)
{
    ioopm_hash_table_t *ht_merch = shop->ht_merch;
    if (ht_merch->size == 0)
    {
        printf("\nThere are no items in the shop to show stock for!\n");
        return;
    }
    ioopm_shop_list(shop);
    size_t item_chosen = ask_question_int("\nEnter the number of the item you want to show the stock for: \n");
    //if (item_chosen >= ht_merch->size)
    //printf("\nThe number you chose does not correspond to a valid item. Please try again.\n");
    ioopm_show_stock(shop, item_chosen);
}

void ioopm_replenish_merch(shop_t *shop)
{
    if (shop->ht_merch->size == 0)
    {
        printf("\nThere are no items in the store to replenish! Try adding an item and try again.\n");
        return;
    }
    ioopm_shop_list(shop);
    size_t item_to_replenish = ask_question_int("\nEnter the number of the item to replenish: \n");
    if (item_to_replenish >= shop->ht_merch->size)
    {
        printf("\nInvalid number choice!\n");
        return;
    }
    char *answer_q = ask_question_string("\nEnter the name of the shelf you want to replenish on. You can enter a new shelf number if you want.\n");
    int quantity = ask_question_int("\nAmount of item to be replenished: \n");
    option_t replenish_result = ioopm_shop_replenish(shop, item_to_replenish, answer_q, quantity);
    if (Unsuccessful(replenish_result))
    {
        printf("\nInvalid input! Please try again:\n"); 
    }
    if (Successful(replenish_result))
    {
        printf("\nThe item was replenished.\n");
    }
}

// FRONTEND CART FUNCTIONS // 

void ioopm_remove_cart_frontend(ioopm_list_t *list_of_carts)
{
    size_t no_of_carts = ioopm_linked_list_size(list_of_carts);
    if (no_of_carts == 0)
    {
        printf("\nThere are no carts in the system to remove!\n");
        return;
    }
    printf("\nThere are %ld cart(s) in the system, starting with number 0.\n", no_of_carts);
    size_t choice = ask_question_int("\nEnter which cart you want to remove by it's number: \n");
    if(choice >= ioopm_linked_list_size(list_of_carts))
    {
        printf("\nInvalid choice! Try again.\n");
        return;
    }
    ioopm_remove_cart(list_of_carts, choice);
    printf("\nCart number %ld is now deleted.\n", choice);
}

static ioopm_hash_table_t *find_cart_in_cart_list(ioopm_list_t *list_of_carts, size_t choice)
{
    return ioopm_linked_list_get(list_of_carts, choice).ptr;
}

void ioopm_add_to_cart_frontend(shop_t *shop, ioopm_list_t *list_of_carts)
{
    if (shop->ht_merch->size == 0)
    {
        printf("\nThere are no items available in the store! Please try another time!\n");
        return;
    }
    size_t no_of_carts = ioopm_linked_list_size(list_of_carts);
    if (no_of_carts == 0)
    {
        printf("\nThere are no carts in the system to add to! Try creating one.\n");
        return;
    }
    printf("\nThere are %ld cart(s) in the system, starting with number 0. \n", no_of_carts);
    size_t choice = ask_question_int("\nEnter which cart you want to add an item to by it's number: \n");
    if (choice >= ioopm_linked_list_size(list_of_carts))
    {
        printf("\nInvalid choice of cart! Please try again!");
        return;
    }
    ioopm_hash_table_t *cart = find_cart_in_cart_list(list_of_carts, choice);
    ioopm_shop_list(shop);
    size_t item_to_add = ask_question_int("\nEnter the number of the item to add to your cart: \n");
    if (item_to_add >= shop->ht_merch->size)
    {
        printf("\nInvalid item choice! Please try again.\n");
        return;
    }
    int quantity_of_item = ask_question_int("\nEnter the quantity you want of the item: \n");
    option_t result = ioopm_add_to_cart(shop, cart, item_to_add, quantity_of_item);
    if (Unsuccessful(result))
    {
        printf("\nQuantity chosen is higher than what's in stock! Please try again:\n");
    }
    if (Successful(result))
    {
        printf("\nThe item was added to your cart.\n");
    }
}

static void print_cart_contents(ioopm_hash_table_t *cart)
{
    ioopm_list_t *items = ioopm_hash_table_keys(cart);
    ioopm_list_t *quantity = ioopm_hash_table_values(cart);
    ioopm_list_iterator_t *itr_items = ioopm_list_iterator(items);
    ioopm_list_iterator_t *itr_quantity = ioopm_list_iterator(quantity);
    size_t size = ioopm_linked_list_size(items);
    int counter = 0;
    for (size_t i = 0; i<size; i++)
    {
        printf("%d. Item: %s Quantity: %d", counter, ioopm_iterator_current(itr_items).string_value,ioopm_iterator_current(itr_quantity).int_value);
        counter++;
        ioopm_iterator_next(itr_items);
        ioopm_iterator_next(itr_quantity);
    }
    destroy_lists_and_itrs(items, quantity, itr_items, itr_quantity);
}

void ioopm_remove_item_from_cart_frontend(shop_t *shop, ioopm_list_t *list_of_carts)
{
    size_t no_of_carts = ioopm_linked_list_size(list_of_carts);
    if (no_of_carts == 0)
    {
        printf("\nThere are no carts in the system to remove from!\n");
        return;
    }
    printf("\nThere are %ld cart(s) in the system, starting with number 0. \n", no_of_carts);
    size_t choice = ask_question_int("\nEnter which cart you want to remove an item from by it's number: \n");
    if (choice >= ioopm_linked_list_size(list_of_carts))
    {
        printf("\nInvalid choice of cart! Please try again!");
        return;
    }
    ioopm_hash_table_t *cart = find_cart_in_cart_list(list_of_carts, choice);
    if (cart->size == 0)
    {
        printf("\nThis cart does not have any items in it to remove! Try adding an item to it first.\n");
        return;
    }
    print_cart_contents(cart);
    size_t item_to_remove = ask_question_int("\nEnter the number of the item to remove from your cart: \n");
    if (item_to_remove >= cart->size)
    {
        printf("\nInvalid choice of item to remove! Please try again.\n");
        return;
    }
    int quantity_of_item = ask_question_int("\nEnter the quantity you want to remove of the item: \n");
    option_t remove = ioopm_remove_from_cart(cart, item_to_remove, quantity_of_item);
    if (Unsuccessful(remove))
    {
        printf("\nThe quantity chosen is more than what's in stock of the item! Please try again.\n");
        //ioopm_remove_item_from_cart_frontend(shop, list_of_carts);
        return;
    }
    if (Successful(remove))
    {
        printf("\nThe item was removed from the cart.\n");
    }
}

void ioopm_calculate_cost_frontend(shop_t *shop, ioopm_list_t *list_of_carts)
{
    size_t no_of_carts = ioopm_linked_list_size(list_of_carts);
    if (no_of_carts == 0)
    {
        printf("\nThere are no carts in the system to calculate the cost of!\n");
        return;
    }
    printf("\nThere are %ld cart(s) in the system, starting with number 0. \n", no_of_carts);
    size_t choice = ask_question_int("\nEnter which cart you want to calculate the cost of by entering it's number: \n");
    if (choice >= ioopm_linked_list_size(list_of_carts))
    {
        printf("\nInvalid choice of cart! Please try again!");
        return;
    }
    ioopm_hash_table_t *cart = find_cart_in_cart_list(list_of_carts, choice);
    if (cart->size == 0)
    {
        printf("\nThere are no items in this cart to calculate the cost of! Please add an item and try again.\n");
        return;
    }
    printf("\nThe cost of the cart is %d.\n", ioopm_cost_of_cart(shop, cart));
}

void ioopm_checkout_frontend(shop_t *shop, ioopm_list_t *list_of_carts)
{
    size_t no_of_carts = ioopm_linked_list_size(list_of_carts);
    if (no_of_carts == 0)
    {
        printf("\nThere are no carts in the system to checkout!\n");
        return;
    }
    printf("\nThere are %ld cart(s) in the system, starting with number 0. \n", no_of_carts);
    size_t choice = ask_question_int("\nEnter which cart you want to checkout by entering it's number: \n");
    if (choice >= ioopm_linked_list_size(list_of_carts))
    {
        printf("\nInvalid choice of cart to checkout! Please try again!\n");
        return;
    }
    ioopm_hash_table_t *cart = find_cart_in_cart_list(list_of_carts, choice);
    if (cart->size == 0)
    {
        printf("\nThere are no items in this cart! Please add an item and try again.\n");
        return;
    }
    else 
    {
        ioopm_checkout_cart(shop, list_of_carts, cart);
        printf("\nThe cart was checked out. Thank you for shopping.\n");
    }

}

// MENU FUNCTIONS // 

static void print_menu_internal(void)
{   
    char *add = "[A]dd an item";
    char *del = "[R]emove an item";
    char *edit = "[E]dit an item";
    char *show = "[S]how stock for an item";
    char *replenish = "Re[P]lenish an item";
    char *ang = "[U]ndo action";
    char *list = "[L]ist all items";
    char *enter_shopping = "E[N]ter shopping mode";
    char *quit = "[Q]uit";
    printf("\n %s \n %s \n %s \n %s \n %s \n %s \n %s \n %s \n %s \n", add, del, edit, show, replenish, ang, list, enter_shopping, quit);
}

static void print_menu_shopping()
{
    char *create_cart = "[C]reate cart";
    char *remove_cart = "Re[M]ove Cart";
    char *list = "[L]ist all items in the store";
    char *add_to_cart = "A[D]d to cart"; 
    char *remove_from_cart = "Remove [I]tem from cart"; 
    char *calculate_cost = "Calcula[T]e cost of cart";
    char *checkout = "Chec[K]out cart";
    char *quit = "[Q]uit";
    printf("\n %s \n %s\n %s \n %s \n %s \n %s \n %s \n %s\n",  create_cart, remove_cart, list, add_to_cart, remove_from_cart, calculate_cost, checkout, quit);
}

static bool check_menu_internal(char *buf)
{
    char *string = "LlRrAaSsEePpQqUuNn";
    if (strlen(buf)==1)
    {
        for (size_t i = 0; i < strlen(string); i++)
        {
            if (buf[0] == string[i])
            {   
                return true;
            }
        }
    }
    return false;
}

static bool check_menu_shopping(char *buf)
{
    char *string = "CcMmDdIiTtKkQqLl";
    if (strlen(buf)==1)
    {
        for (size_t i = 0; i < strlen(string); i++)
        {
            if (buf[0] == string[i])
            {   
                return true;
            }
        }
    }
    return false;
}


static char ask_question_menu_internal(void)
{
    print_menu_internal();
    char answer[355]={0};
    do
    {
        printf("\nYour choice: \n");
        read_string(answer,855);
    } while (!check_menu_internal(answer));

    return toupper(answer[0]);
}

static char ask_question_menu_shopping(void)
{
    print_menu_shopping();
    char answer[855]={0};
    do
    {
        printf("\nYour choice: \n");
        read_string(answer,55);
    } while (!check_menu_shopping(answer));

    return toupper(answer[0]);
}


// EVENT LOOP FUNCTIONS // 

static void event_loop_shopping(shop_t *shop)
{
    ioopm_list_t *list_of_carts = ioopm_linked_list_create(int_eq);
    bool q = true;
    while (q)
    {
        char choice = ask_question_menu_shopping();
        if (choice == 'C')
        {
            ioopm_create_cart(list_of_carts);
            printf("\nA new cart was created.\n");
        }
        else if (choice == 'M')
        {
            ioopm_remove_cart_frontend(list_of_carts);
        }
        else if (choice == 'L')
        {
            ioopm_shop_list(shop);
        }
        else if (choice == 'D')
        {
            ioopm_add_to_cart_frontend(shop, list_of_carts);
        }
        else if (choice == 'I')
        {
            ioopm_remove_item_from_cart_frontend(shop, list_of_carts);
        }
        else if (choice == 'T')
        {
            ioopm_calculate_cost_frontend(shop, list_of_carts);
        }
        else if (choice == 'K')
        {
            ioopm_checkout_frontend(shop, list_of_carts);
        }
        else if (choice == 'Q')
        {
            printf("\nThank you, have a nice day! \n");
            ioopm_linked_list_destroy(list_of_carts);
            q = false;
        }
    }
}

void ioopm_event_loop()
{   shop_t *shop = ioopm_shop_create();
    bool q = true;
    while (q)
    {
        char choice = ask_question_menu_internal();
        if (choice == 'A')
        {
            ioopm_input_merch(shop);
        }
        else if (choice == 'R')
        {
            ioopm_remove_item_frontend(shop);
        }
        else if (choice == 'E')
        {
            ioopm_edit_item_frontend(shop);
        }
        else if (choice == 'S')
        {
            ioopm_show_stock_question(shop);
        }
        else if (choice == 'P')
        {
            ioopm_replenish_merch(shop);
        }
        else if (choice == 'U')
        {
            printf("\nNot yet implemented!\n");
        }
        else if (choice == 'L')
        {
            ioopm_shop_list(shop);   
        }
        else if (choice == 'N')
        {
            printf("\nYou will now enter shopping mode:\n");
            event_loop_shopping(shop);
        }
        else if (choice == 'Q')
        {
            printf("\nThank you, have a nice day! \n");
            ioopm_shop_destroy(shop);
            q = false;
        }
    }
    
}


// MAIN // 

int main(void)
{
    ioopm_event_loop();
    return 0;
}