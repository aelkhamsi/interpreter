/*
 *  Table des symboles.h
 *
 *  Created by Janin on 12/10/10.
 *  Copyright 2010 LaBRI. All rights reserved.
 *
 *  Associative array encoded as linked list of pair (symbol_name, symbol_value).
 *  To be used only with getter get_symbol_value and setter set_symbol_value.
 *
 *  Symbol_value_type (defined in Attribut.h) can be customized.
 *
 *  Symbol names must be valid sid from Table des chaines.
 *
 */

#ifndef TABLE_DES_SYMBOLES_H
#define TABLE_DES_SYMBOLES_H

#include "Table_des_chaines.h"
#include "Attribut.h"

/* type of values stored with symbols */

/* The storage structure is implemented as a linked chain */



/* linked element def */
typedef struct elem {
	sid symbol_name;
	symb_value_type symbol_value;
	struct elem * next;
} elem;

/* linked chain initial element */
static elem * storage = NULL;

/* linked stack to store a backup of an elem if its value is changed in a let statment */
static elem * letStack = NULL;

/* flag that indicates if we are in a let statment (set_symbol_value behaves differently) */
static int letFlag = 1;


/* get the symbol value of symb_id from the symbol table */
symb_value_type get_symbol_value(sid symb_id);

/* set the value of symbol symb_id to value */
symb_value_type set_symbol_value(sid symb_id, symb_value_type value, int push);

/* push an elem into the letStack */
void push_elem(elem * element);

/* restore the subsequent value of the elem in the head of the letStack, and pull it from the there */
void restore_elem();

#endif
