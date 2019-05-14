%option noyywrap
/* avoid dependency with library fl */

%{
#include "y.tab.h"
#include "src/Table_des_symboles.h"
#include <stdio.h>

%}

whitespace          [ \t\r\n\f]+

digit               [0-9]
alpha               [a-zA-Z]
alphanum            [a-zA-Z0-9]

integer             [[:digit:]]+
float               [[:digit:]]+\.[[:digit:]]*
boolean             "true"|"false"

escape              \\([\\"'ntbr ])
string              \"({escape}|[^"\\])*\"

identifier          [[:alpha:]][[:alnum:]_]*

%%
"++"         {return CONCAT;}
"+"          {return PLUS;}
"-"          {return MOINS;}
"*"          {return MULT;}
"/"          {return DIV;}
"="          {return EQ;}
"<"          {return ISLT;}
">"          {return ISGT;}
"<="         {return ISLEQ;}
">="         {return ISGEQ;}
"=="         {return ISEQ;}

"let"        {return LET;}
"in"         {return IN;}
"if"         {return IF;}
"then"       {return THEN;}
"else"       {return ELSE;}


{boolean}    {yylval.val.type = BOOL_T;
              if (strcmp(yytext, "true")) {
                yylval.val.value.bool_value = 0;
              } else {
                yylval.val.value.bool_value = 1;
              }
              yylval.val.reg_num = new_reg();
              return BOOL;}

"("          {return LPAR;}
")"          {return RPAR;}
"["          {return LBR;}
"]"          {return RBR;}
","          {return VIR;}
";"          {return PV;}

{float}      {  yylval.val.type = FLOAT_T;
                yylval.val.value.float_value = atof(yytext);
                yylval.val.reg_num = new_reg();
                return FLOAT; }

{integer}    {  yylval.val.type = INT_T;
                yylval.val.value.int_value = atoi(yytext);
                yylval.val.reg_num = new_reg();
                return NUM; }

{identifier} {  yylval.sid = string_to_sid(yytext);
                return ID;}

{string}     {  yylval.val.type = STRING_T;
                yylval.val.value.string_value = strdup(yytext);
                yylval.val.reg_num = new_reg();
                return STRING; }

{whitespace} ;
