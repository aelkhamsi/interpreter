/*
 *  Table des symboles.c
 *
 *  Created by Janin on 12/10/10.
 *  Copyright 2010 LaBRI. All rights reserved.
 *
 */

#include "Table_des_symboles.h"

#include <stdlib.h>
#include <stdio.h>


/* get the symbol value of symb_id from the symbol table */
symb_value_type get_symbol_value(sid symb_id) {
	elem * tracker=storage;

	/* look into the linked list for the symbol value */
	while (tracker) {
		if (tracker -> symbol_name == symb_id) return tracker -> symbol_value;
		tracker = tracker -> next;
	}

	/* if not found does cause an error */
	fprintf(stderr,"Error : symbol %s have no defined value\n",(char *) symb_id);
	exit(-1);
}

/* set the value of symbol symb_id to value */
symb_value_type set_symbol_value(sid symb_id, symb_value_type value, int push) {

	elem * tracker;

	/* (optionnal) check that sid is valid symbol name and exit error if not */
	if (! sid_valid(symb_id)) {
		fprintf(stderr,"Error : symbol id %p is not have no valid sid\n",symb_id);
		exit(-1);
	}

	/* look for the presence of symb_id in storage */
	tracker = storage;
	while (tracker) {
		if (tracker -> symbol_name == symb_id) {
			if (push)
				push_elem(tracker); //We save the elem by pushing it in the letStack
			tracker -> symbol_value = value;
			return tracker -> symbol_value;
		}
		tracker = tracker -> next;
	}

	/* otherwise insert it at head of storage with proper value */
	tracker = malloc(sizeof(elem));
	tracker -> symbol_name = symb_id;
	tracker -> symbol_value = value;
	tracker -> next = storage;
	storage = tracker;
	return storage -> symbol_value;
}

/* push an element in the letStack*/
void push_elem(elem * element) {
	elem * newElem;

	newElem = malloc(sizeof(elem));
	newElem -> symbol_name = element -> symbol_name;
	newElem -> symbol_value = element -> symbol_value;
	newElem -> next = letStack;
	letStack = newElem;
}

/* restore the subsequent value of the elem in the head of the letStack, and pull it from the there */
void restore_elem() {
	elem * head;

	head = letStack;
	letStack = letStack -> next;
	set_symbol_value(head -> symbol_name, head -> symbol_value, 0);
	free(head);

}
