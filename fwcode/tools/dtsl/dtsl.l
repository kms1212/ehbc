%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dtsl.tab.h"
%}

%option noyywrap

COMMENT [^\r\n]*
ANY_CHAR ([^\\\"]|\\.)
ANY_STR {ANY_CHAR}*
WHITESPACE [ \t\r\n]*
LETTER [a-zA-Z]
DIGIT_DEC [0-9]
DIGIT_HEX [0-9a-fA-F]
DIGIT_OCT [0-7]
DIGIT_BIN [01]
SYMBOL_NAME ({LETTER}|_)({LETTER}|{DIGIT_DEC}|_)*

%%
"#"{COMMENT}                    ;

\"{ANY_STR}\"                   {
    int len = strnlen(yytext, 257);
    yylval.string = (char*)malloc(len - 2);
    strncpy(yylval.string, yytext, len);
    return L_STRING;
}
{DIGIT_DEC}+                    {
    yylval.literal = (char*)malloc(strlen(yytext));
    strcpy(yylval.literal, yytext);
    return L_INTEGER;
}
0[xX]{DIGIT_HEX}+               {
    yylval.literal = (char*)malloc(strlen(yytext));
    strcpy(yylval.literal, yytext);
    return L_INTEGER;
}
0[oO]{DIGIT_OCT}+               {
    yylval.literal = (char*)malloc(strlen(yytext));
    strcpy(yylval.literal, yytext);
    return L_INTEGER;
}
0[bB]{DIGIT_BIN}+               {
    yylval.literal = (char*)malloc(strlen(yytext));
    strcpy(yylval.literal, yytext);
    return L_INTEGER;
}

system                          return T_SYSTEM;
component                       return T_COMPONENT;
property                        return T_PROPERTY;


{SYMBOL_NAME}                   {
    yylval.literal = (char*)malloc(strlen(yytext));
    strcpy(yylval.literal, yytext);
    return T_SYMBOL;
}

"{"                             return '{';
"}"                             return '}';
"["                             return '[';
"]"                             return ']';
"("                             return '(';
")"                             return ')';
","                             return ',';
":"                             return ':';
"."                             return '.';
"@"                             return '@';

"+"                             return '+';
"-"                             return '-';
"*"                             return '*';
"/"                             return '/';
"%"                             return '%';

"|"                             return '|';
"&"                             return '&';
"^"                             return '^';
"~"                             return '~';

"<<"                            return O_2LT;
">>"                            return O_2GT;

{WHITESPACE}                    ;

.                               { printf("Line %d: Unexpected character \"%s\"\n", yylineno, yytext); };

%%