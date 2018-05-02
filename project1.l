%option noyywrap
%{
	#include <stdio.h>
	#include "SymbolTable.h"
	#include <math.h>
%}
Boolean			"T"|"F"
keywords		"Program"|"Function"|"return"|"if"|"then"|"else"|"while"|"do"|"or"|"and"|"print"
identifier		[a-z,A-Z]|[a-z,A-Z][a-z,A-Z,0-9]|[a-z,A-Z][a-z,A-Z,0-9][a-z,A-Z,0-9]|[a-z,A-Z][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9]|[a-z,A-Z][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9]|[a-z,A-Z][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9]
integer			0|[-]?[ ]*[1-9][0-9]*
float			0.[0]+|[-]?[ ]*0"."[0]*[1-9]+[0-9]*|[-]?[ ]*[1-9][0-9]*"."[0-9]+
character-string	\([a-z,A-Z,0-9,\n]+\)
symbols			\{|\}|\(|\)|\=|\+|\-|\*|\/|\%|\=\=|\>|\<|\>\=|\<\=|\!\=
whitespace		[ \t\n]+

%%
{Boolean}		printf("Boolean: %s\n", yytext);
{identifier}		printf("Identifier: %s\n", yytext);
{integer}		printf("Integer: %d\n", atoi(yytext));
{float}			printf("Float: %f\n", atof(yytext));
{character-string}	printf("Character-String: %s\n", yytext);
{whitespace}		//ignore whitespace
{keywords}		printf("Keywords: %s\n", yytext);
{symbols}		printf("Symbols: %s\n", yytext);
%%

int main()
{
	yylex();	

	return 0;
}
