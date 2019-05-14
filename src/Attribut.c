/*
 *  Attribut.c
 *
 */

#include "Attribut.h"

symb_value_type plus(symb_value_type a, symb_value_type b ) {
    symb_value_type result;
    if (a.type == INT_T && b.type == INT_T ) {
        result.type = INT_T;
        result.value.int_value = a.value.int_value + b.value.int_value;
        result.reg_num = new_reg();
    }
    else if (a.type == INT_T && b.type == FLOAT_T) {
        result.type = FLOAT_T;
        result.value.float_value = a.value.int_value + b.value.float_value;
        result.reg_num = new_reg();
    }
    else if (a.type == FLOAT_T && b.type == INT_T) {
        result.type = FLOAT_T;
        result.value.float_value = a.value.float_value + b.value.int_value;
        result.reg_num = new_reg();
    }
    else {
        result.type = FLOAT_T;
        result.value.float_value = a.value.float_value + b.value.float_value;
        result.reg_num = new_reg();
    }
    return result;
}

symb_value_type mult(symb_value_type a, symb_value_type b ) {
    symb_value_type result;
    if (a.type == INT_T && b.type == INT_T ) {
        result.type = INT_T;
        result.value.int_value = a.value.int_value * b.value.int_value;
        result.reg_num = new_reg();
    }
    else if (a.type == INT_T && b.type == FLOAT_T) {
        result.type = FLOAT_T;
        result.value.float_value = a.value.int_value * b.value.float_value;
        result.reg_num = new_reg();
    }
    else if (a.type == FLOAT_T && b.type == INT_T) {
        result.type = FLOAT_T;
        result.value.float_value = a.value.float_value * b.value.int_value;
        result.reg_num = new_reg();
    }
    else {
        result.type = FLOAT_T;
        result.value.float_value = a.value.float_value * b.value.float_value;
        result.reg_num = new_reg();
    }
    return result;
}

symb_value_type reverse(symb_value_type a) {
    symb_value_type result;
    if (a.type == INT_T ) {
        result.type = INT_T;
        result.value.int_value =  -1 * a.value.int_value ;
        result.reg_num = new_reg();
    }
    else {
        result.type = FLOAT_T;
        result.value.float_value =  -1 * a.value.float_value;
        result.reg_num = new_reg();
    }
    return result;
}

symb_value_type concat(symb_value_type a, symb_value_type b ) {
    symb_value_type result;
    result.type = STRING_T;
    strcpy(result.value.string_value, a.value.string_value);
    strcat(result.value.string_value, b.value.string_value);
    return result;
}

//Ecrit le type et la valeur d'une expression
//Fct auxiliaire
void print_type_value(symb_value_type a) {
    if (a.type == INT_T)
        printf("de type <int> vaut %d\n", a.value.int_value);
    else if (a.type == FLOAT_T)
        printf("de type <float> vaut %f\n", a.value.float_value);
    else
        printf("de type <string> vaut %s\n", a.value.string_value);

}

//Une affirmation est la combinaison d'un identificateur et d'une expression
//Ecrit le type de l'identificateur et sa valeur après avoir évaluer l'expression
void print_aff(aff_type aff) {
    printf("%s ", aff.id);
    print_type_value(aff.exp);
}

//Ecrit : <exp> + le type et la valeur d'une expression
void print_exp(symb_value_type a) {
    printf("<exp> ");
    fprintf(test_c, "   printf(\"<exp> ");
    if (a.type == INT_T) {
        printf("de type <int> vaut %d\n", a.value.int_value);
        fprintf(test_c, "de type <int> vaut %%d\\n\", r%d);\n", a.reg_num);
    } else if (a.type == FLOAT_T) {
        printf("de type <float> vaut %f\n", a.value.float_value);
        fprintf(test_c, "de type <float> vaut %%f\\n\", r%d);\n", a.reg_num);
    } else {
        printf("de type <string> vaut %s\n", a.value.string_value);
        fprintf(test_c, "de type <string> vaut %%s\\n\", r%d);\n", a.reg_num);
    }
}

int new_reg() {
    static int reg = 0;
    return ++reg;
}

void generate_code_aff(aff_type aff) {
    //search the type
    switch(aff.exp.type) {
            case INT_T:
            //Generate test.h code
            fprintf(test_h, "%s _%s;\n", "int", aff.id);
            //Generate test.c code
            fprintf(test_c, "   _%s = r%d;\n", aff.id, aff.exp.reg_num);
            fprintf(test_c, "   printf(\"%s de type <%s> vaut %%d\\n\", _%s);\n", aff.id, "int", aff.id);
            break;
        case FLOAT_T:
            //Generate test.h code
            fprintf(test_h, "%s _%s;\n", "float", aff.id);
            //Generate test.c code
            fprintf(test_c, "   _%s = r%d;\n", aff.id, aff.exp.reg_num);
            fprintf(test_c, "   printf(\"%s de type <%s> vaut %%f\\n\", _%s);\n", aff.id, "float", aff.id);
            break;
        case STRING_T:
            //Generate test.h code
            fprintf(test_h, "%s _%s;\n", "char *", aff.id);
            //Generate test.c code
            fprintf(test_c, "   _%s = r%d;\n", aff.id, aff.exp.reg_num);
            fprintf(test_c, "   printf(\"%s de type <%s> vaut %%s\\n\", _%s);\n", aff.id, "string", aff.id);
            break;
    }
}

void generate_code_exp(symb_value_type exp) {
    switch(exp.type) {
        case INT_T:
            //Generate test.h code
            fprintf(test_h, "%s r%d;\n", "int", exp.reg_num);
            //Generate test.c code
            fprintf(test_c, "   r%d = %d;\n", exp.reg_num, exp.value.int_value);
            break;
        case FLOAT_T:
            //Generate test.h code
            fprintf(test_h, "%s r%d;\n", "float", exp.reg_num);
            //Generate test.c code
            fprintf(test_c, "   r%d = %f;\n", exp.reg_num, exp.value.float_value);
            break;
        case STRING_T:
            //Generate test.h code
            fprintf(test_h, "%s r%d;\n", "char *", exp.reg_num);
            //Generate test.c code
            fprintf(test_c, "   r%d = %s;\n", exp.reg_num, exp.value.string_value);
            break;
    }
}

void generate_code_arith_exp(symb_value_type exp, symb_value_type expL, symb_value_type expR, char* operation ) {
    //Generate test.h code
    switch (exp.type) {
        case INT_T:
            fprintf(test_h, "%s r%d;\n", "int", exp.reg_num);
            break;
        case FLOAT_T:
            fprintf(test_h, "%s r%d;\n", "float", exp.reg_num);
            break;
        case STRING_T:
            fprintf(test_h, "%s r%d;\n", "char *", exp.reg_num);
            break;
    }

    //Generate test.c code
    if (exp.type == STRING_T) {
        fprintf(test_c, "   strcpy(r%d, r%d);\n   strcat(r%d, r%d);\n", exp.reg_num, expL.reg_num, exp.reg_num, expR.reg_num);
    } else {
        if (strcmp(operation, "-")) {
            fprintf(test_c, "   r%d = r%d %s r%d;\n", exp.reg_num, expL.reg_num, operation, expR.reg_num);
        } else {
            fprintf(test_c, "   r%d = -1 * r%d;\n", exp.reg_num, expL.reg_num);
        }
    }
}

void generate_code_cond(symb_value_type bool, symb_value_type expL, symb_value_type expR, char* operation) {
    //Generate test.h code
    fprintf(test_h, "%s r%d;\n", (bool.type == INT_T) ? "int" : "float", bool.reg_num);
    //Generate test.c code
    if (!strcmp(operation, "!"))
        fprintf(test_c, "   r%d = %sr%d;\n", bool.reg_num, operation, expL.reg_num);
    else if (!strcmp(operation, "null"))
        fprintf(test_c, "   r%d = %d;\n", bool.reg_num, expL.value.bool_value);
    else
        fprintf(test_c, "   r%d = r%d %s r%d;\n", bool.reg_num, expL.reg_num, operation, expR.reg_num);
}

void generate_code_control_exp(symb_value_type exp, symb_value_type bool, symb_value_type expThen, symb_value_type expElse) {
    //Generate test.h code
    fprintf(test_h, "%s r%d;\n", (exp.type == INT_T) ? "int" : "float", exp.reg_num);
    //Generate test.c code
    fprintf(test_c, "   if (!r%d) goto l%d;\n", bool.reg_num, expElse.reg_num);
    fprintf(test_c, "   l%d:\n    r%d = r%d;\n    goto l%d;\n", expThen.reg_num, exp.reg_num, expThen.reg_num, exp.reg_num);
    fprintf(test_c, "   l%d:\n    r%d = r%d;\n", expElse.reg_num, exp.reg_num, expElse.reg_num);
    fprintf(test_c, "   l%d:\n", exp.reg_num);
}

symb_value_type logical_or(symb_value_type a, symb_value_type b) {
    symb_value_type result;
    result.type = BOOL_T;
    if (a.value.bool_value == 0 && b.value.bool_value == 0 ) {
        result.value.bool_value = 0;
    } else {
        result.value.bool_value = 1;
    }
    result.reg_num = new_reg();
    return result;
}

symb_value_type logical_and(symb_value_type a, symb_value_type b) {
    symb_value_type result;
    result.type = BOOL_T;
    result.value.bool_value = a.value.bool_value * b.value.bool_value;
    result.reg_num = new_reg();
    return result;
}

symb_value_type logical_not(symb_value_type a) {
    symb_value_type result;
    result.type = BOOL_T;
    if (a.value.bool_value == 1) {
        result.value.bool_value = 0;
    } else {
        result.value.bool_value = 1;
    }
    result.reg_num = new_reg();
    return result;
}

symb_value_type islt_comp(symb_value_type exp1, symb_value_type exp2) {
    symb_value_type result;
    result.type = BOOL_T;
    if (exp1.type == INT_T && exp1.type == INT_T ) {
        if ( exp1.value.int_value < exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == INT_T && exp2.type == FLOAT_T) {
        if ( exp1.value.int_value < exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == FLOAT_T && exp1.type == INT_T) {
        if ( exp1.value.float_value < exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else {
        if ( exp1.value.float_value < exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    result.reg_num = new_reg();
    return result;
}

symb_value_type isgt_comp(symb_value_type exp1, symb_value_type exp2) {
    symb_value_type result;
    result.type = BOOL_T;
    if (exp1.type == INT_T && exp1.type == INT_T ) {
        if ( exp1.value.int_value > exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == INT_T && exp2.type == FLOAT_T) {
        if ( exp1.value.int_value > exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == FLOAT_T && exp1.type == INT_T) {
        if ( exp1.value.float_value > exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else {
        if ( exp1.value.float_value > exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    result.reg_num = new_reg();
    return result;
}

symb_value_type isleq_comp(symb_value_type exp1, symb_value_type exp2) {
    symb_value_type result;
    result.type = BOOL_T;
    if (exp1.type == INT_T && exp1.type == INT_T ) {
        if ( exp1.value.int_value <= exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == INT_T && exp2.type == FLOAT_T) {
        if ( exp1.value.int_value <= exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == FLOAT_T && exp1.type == INT_T) {
        if ( exp1.value.float_value <= exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else {
        if ( exp1.value.float_value <= exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    result.reg_num = new_reg();
    return result;
}

symb_value_type isgeq_comp(symb_value_type exp1, symb_value_type exp2) {
    symb_value_type result;
    result.type = BOOL_T;
    if (exp1.type == INT_T && exp1.type == INT_T ) {
        if ( exp1.value.int_value >= exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == INT_T && exp2.type == FLOAT_T) {
        if ( exp1.value.int_value >= exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == FLOAT_T && exp1.type == INT_T) {
        if ( exp1.value.float_value >= exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else {
        if ( exp1.value.float_value >= exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    result.reg_num = new_reg();
    return result;
}

symb_value_type iseq_comp(symb_value_type exp1, symb_value_type exp2) {
    symb_value_type result;
    result.type = BOOL_T;
    if (exp1.type == INT_T && exp2.type == INT_T ) {
        if ( exp1.value.int_value == exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == INT_T && exp2.type == FLOAT_T) {
        if ( exp1.value.int_value == exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else if (exp1.type == FLOAT_T && exp2.type == INT_T) {
        if ( exp1.value.float_value == exp2.value.int_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    else {
        if ( exp1.value.float_value == exp2.value.float_value )
            result.value.bool_value = 1;
        else
            result.value.bool_value = 0;
    }
    result.reg_num = new_reg();
    return result;
}

symb_value_type control_exp(symb_value_type bool, symb_value_type expThen, symb_value_type expElse) {
    symb_value_type result;
    if (bool.value.bool_value) {
        if (expThen.type == FLOAT_T) {
            result.type = FLOAT_T;
            result.value.float_value = expThen.value.float_value;
        } else if (expThen.type == INT_T && expElse.type == FLOAT_T) {
            result.type = FLOAT_T;
            result.value.float_value = expThen.value.int_value;
        } else {
            result.type = INT_T;
            result.value.int_value = expThen.value.int_value;
        }
    } else {
        if (expElse.type == FLOAT_T) {
            result.type = FLOAT_T;
            result.value.float_value = expElse.value.float_value;
        } else if (expElse.type == INT_T && expThen.type == FLOAT_T) {
            result.type = FLOAT_T;
            result.value.float_value = expElse.value.int_value;
        } else {
            result.type = INT_T;
            result.value.int_value = expElse.value.int_value;
        }
    }
    result.reg_num = new_reg();
    return result;
}
