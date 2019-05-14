/*
 *  Attribut.h
 *
 *  Module for handling attributes
 *
 */

#ifndef ATTRIBUT_H
#define ATTRIBUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *test_c;
extern FILE *test_h;

//Le type symb_value_type
/////////////////////////
typedef union {
    int int_value;
    float float_value;
    char* string_value;
    int bool_value;
} symb_value;

typedef enum {INT_T, FLOAT_T, STRING_T, BOOL_T} symb_type;

typedef struct{
  symb_value value;
  symb_type type;
  int reg_num;
} symb_value_type;

//Le type aff (affectation)
///////////////////////////
typedef struct{
  symb_value_type exp;
  char* id;
} aff_type;


symb_value_type plus(symb_value_type a, symb_value_type b );
symb_value_type mult(symb_value_type a, symb_value_type b );
symb_value_type reverse(symb_value_type a);
symb_value_type concat(symb_value_type a, symb_value_type b);
void print_exp(symb_value_type a);
void print_aff(aff_type aff);

int new_reg();
void generate_code_aff(aff_type aff);
void generate_code_exp(symb_value_type exp);
void generate_code_arith_exp(symb_value_type exp, symb_value_type expL, symb_value_type expR, char* operation);
void generate_code_cond(symb_value_type bool, symb_value_type expL, symb_value_type expR, char* operation);
void generate_code_control_exp(symb_value_type exp, symb_value_type bool, symb_value_type expThen, symb_value_type expElse);

symb_value_type logical_or(symb_value_type a, symb_value_type b);
symb_value_type logical_and(symb_value_type a, symb_value_type b);
symb_value_type logical_not(symb_value_type a);
symb_value_type islt_comp(symb_value_type exp1, symb_value_type exp2);
symb_value_type isgt_comp(symb_value_type exp1, symb_value_type exp2);
symb_value_type isleq_comp(symb_value_type exp1, symb_value_type exp2);
symb_value_type isgeq_comp(symb_value_type exp1, symb_value_type exp2);
symb_value_type iseq_comp(symb_value_type exp1, symb_value_type exp2);

symb_value_type control_exp(symb_value_type bool, symb_value_type expThen, symb_value_type expElse);


#endif
