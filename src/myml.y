%token PV LPAR RPAR LBR RBR LET IN VIR

%code requires {

#include "src/Table_des_symboles.h"
#include "src/Attribut.h"
extern FILE* yyin;
}

%{
#include <stdio.h>

extern int yylex();
extern int yyparse();

FILE * test_c=NULL;
FILE * test_h=NULL;

void yyerror (char* s) {
  printf("\n%s\n",s);
}

%}

%union {
  symb_value_type val;
  char * sid;
  aff_type aff;
}

%token <val> NUM FLOAT STRING BOOL
%token <sid> ID
%type <val> exp atom_exp arith_exp list_exp control_exp let_exp bool
%type <aff> aff aff_id

%token IF THEN ELSE
%token ISLT ISGT ISLEQ ISGEQ ISEQ
%left ISEQ
%left ISLT ISGT ISLEQ ISGEQ
%token AND OR NOT
%left OR
%left AND
%left MULT

%token PLUS MOINS MULT DIV EQ
%left PLUS
%left CONCAT
%nonassoc UNA    /* pseudo token pour assurer une priorite locale */

%start prog



%%

prog : inst PV
| prog inst PV
;

inst : aff {print_aff($1);
            generate_code_aff($1);
}
| exp {print_exp($1);
       generate_code_exp($1);

}
;


aff : aff_id {$$ = $1; }
| aff_fun
;

aff_id : ID EQ exp {    set_symbol_value($1, $3, 1);
                        $$.exp = $3;
                        $$.id = sid_to_string($1);}
;

aff_fun : fun_head EQ exp  {}
;

fun_head : ID id_list {

}
;

id_list : ID
| id_list ID
;


exp : arith_exp { $$ = $1; }
| atom_exp { $$ = $1; }
| control_exp {$$ = $1;}
| let_exp {$$ = $1; }
| LPAR funcall_exp RPAR
;

arith_exp : MOINS exp %prec UNA {$$ = reverse($2);
                                 generate_code_arith_exp($$, $2, $2, "-");
}
| exp PLUS exp {$$ = plus($1, $3);
                generate_code_arith_exp($$, $1, $3, "+");
}
| exp MULT exp {$$ = mult($1, $3);
                generate_code_arith_exp($$, $1, $3, "*");
}

| exp CONCAT exp {$$ = concat($1, $3);
                  generate_code_arith_exp($$, $1, $3, "++");
}
;

atom_exp : NUM {$$ = $1;
                generate_code_exp($1);
}
| FLOAT {$$ = $1;
         generate_code_exp($1);
}
| STRING {$$ = $1;
          generate_code_exp($1);
}
| ID {$$ = get_symbol_value($1);
}
| list_exp
| LPAR exp RPAR { $$ = $2; }
;

control_exp : IF bool THEN atom_exp ELSE atom_exp {$$ = control_exp($2, $4, $6);
                                                   generate_code_control_exp($$, $2, $4, $6);
}
;

let_exp : LET aff IN atom_exp {
    $$ = $4;
    restore_elem();
}


funcall_exp : ID atom_list
;

atom_list : atom_exp
| atom_list atom_exp
;


list_exp : LBR exp_list RBR
;

exp_list : exp
| exp_list VIR exp
;

bool : BOOL {$$ = $1;
             generate_code_cond($$, $1, $1, "null");}
| bool OR bool {$$ = logical_or($1, $3);
                generate_code_cond($$, $1, $3, "||");}
| bool AND bool {$$ = logical_and($1, $3);
                 generate_code_cond($$, $1, $3, "&&");}
| NOT bool %prec UNA {$$ = logical_not($2);
                      generate_code_cond($$, $2, $2, "!");}
| exp ISLT exp {$$ = islt_comp($1, $3);
                generate_code_cond($$, $1, $3, "<");}
| exp ISGT exp {$$ = isgt_comp($1, $3);
                generate_code_cond($$, $1, $3, ">");}
| exp ISLEQ exp {$$ = isleq_comp($1, $3);
                 generate_code_cond($$, $1, $3, "<=");}
| exp ISGEQ exp {$$ = isgeq_comp($1, $3);
                 generate_code_cond($$, $1, $3, ">=");}
| exp ISEQ exp {$$ = iseq_comp($1, $3);
                generate_code_cond($$, $1, $3, "==");}
| LPAR bool RPAR {$$ = $2;}
;

%%
int main (int argc, char* argv[]) {
  ++argv, --argc;       /* skip over program name */
  if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;
  
  test_c = fopen("test.c", "w");
  test_h = fopen("test.h", "w");
  
  fprintf(test_c, "%s\n", "#include \"test.h\"");
  fprintf(test_c, "\n%s\n", "int main() {");
  fprintf(test_h, "%s\n", "#ifndef TEST_H");
  fprintf(test_h, "%s\n\n", "#define TEST_H");
  fprintf(test_h, "%s\n", "#include <stdio.h> ");
  fprintf(test_h, "%s\n", "#include <string.h> ");
  
  yyparse ();
  
  fprintf(test_c, "%s", "}\n");
  fprintf(test_h, "\n%s", "#endif");
  
  fclose(test_c);
  fclose(test_h);
  
  return 1;
}
