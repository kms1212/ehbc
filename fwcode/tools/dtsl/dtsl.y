%require "3.2"
%language "c"

%locations
%define parse.error detailed
%define parse.trace
%define parse.lac full
%verbose

%code top {
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int yylineno;

int yylex(void);
void yyerror (char const *msg) {
    fprintf (stderr, "%s\n", msg);
}

extern FILE* yyin;
}

%code {

#include "node.h"

}

%union {
    size_t                  symbol;
    char*                   string;
    uint64_t                integer;

    struct node*            node;
}

%token<string>  T_STRING
%token<integer> T_INTEGER
%token<symbol>  T_SYMBOL

%token          T_BUS T_CACHE T_COPROCESSOR T_DEVICE T_DMA T_INTERRUPT
%token          T_MEMORY T_PERIPHERAL T_PROCESSOR T_PROPERTY T_TIMER

%token<node>    

%start file_root
%%
file_root: toplvl_expr_list

// File Root Closure
toplvl_expr_list
    : toplvl_expr
    | toplvl_expr_list toplvl_expr 
    ;

toplvl_expr
    : '@' T_SYMBOL T_STRING
    | T_SYSTEM stmt_group
    ;

////////////////////////////////////////////////////////////////////////////////
// Grouping 
////////////////////////////////////////////////////////////////////////////////
// Statement Group
statement_group
    : '{' stmt_list '}'
    | '{' '}' 

// Parameter Group
parameter_group
    : '(' expr_list ')'
    | '(' ')'
    ;

// Value Group
value_group
    : '{' expr_list '}'
    | '{' '}'
    ;

stmt_list
    : statement ';'
    | statement ';' stmt_list
    ;

expr_list
    : expression
    | expression ',' expr_list
    ;

////////////////////////////////////////////////////////////////////////////////
// Expressions
////////////////////////////////////////////////////////////////////////////////
expression
    : '(' expression ')'
    | value_expr
    | ref_expr
    | unary_expr
    | binary_expr
    | expression parameter_group
    | value_group
    ;

unary_expr
    : '~' expression
    | '-' expression
    ;

binary_expr
    : expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '%' expression
    | expression '|' expression
    | expression '^' expression
    | expression '.' expression
    | expression O_2LT expression
    | expression O_2GT expression
    | expression '[' expression ']'
    ;

value_expr
    : L_STRING
    | L_INTEGER
    | '{' expr_list '}'
    ;

ref_expr
    : '$' T_SYMBOL
    ;

////////////////////////////////////////////////////////////////////////////////
// Statements
////////////////////////////////////////////////////////////////////////////////
statement
    : substitution
    | definition
    ;

substitution
    : T_PROPERTY T_SYMBOL ':' expression
    ;

definition
    : def_keyword T_SYMBOL parameter_group statement_group
    ;

def_keyword
    : T_PROCESSOR
    | T_MEMORY
    | T_COPROCESSOR
    | T_CACHE
    | T_BUS
    | T_DEVICE
    | T_PERIPHERAL
    | T_INTERRUPT
    | T_DMA
    | T_TIMER
    ;

%%

int main(int argc, char** argv) {
    if ( argc > 1 )
        yyin = fopen( argv[1], "r" );
    else
        yyin = stdin;

    yyparse();

    return tree_print(&srctree);
}
