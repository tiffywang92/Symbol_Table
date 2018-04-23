%option noyywrap
%{
	#include<stdio.h>
%}
program				"{" "Program" program-name function-definitions statements "}"
program-name			identifier
function-definitions		(function-definition)*
function-definition		"{" "Function" function-name arguments statements "return" return-arg "}"
function-name			identifier
arguments			(argument)*
argument			identifier
return-arg			identifier | ""
statements			(statement)+
statement			assignment-stmt | function-call | if-stmt | while-stmt
assignment-stmt			"{" "=" identifier parameter "}"
function-call			"{" function-name parameters "}" | "{" predefined-function parameters "}"
predefined-function		"+" | "–" | "*" | "/" | "%" | "print"
parameters			(parameter)*
parameter			function-call | identifier | number | character-string | Boolean
number				integer | float
if-stmt				"{" "if" expression "then" statements "else" statements "}"
while-stmt			"{" "while" expression "do" statements "}"
expression			"{"comparison-operator parameter parameter "}" | "{"Boolean-operator expression expression "}" | Boolean
comparison-operator		"==" | ">" | "<" | ">=" | "<=" | "!="
Boolean-operator		"or" | "and"

identifier			[a-zA-Z]([a-zA-Z0-9] | [a-zA-Z0-9][a-zA-Z0-9] | [a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9] | [a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9] | [a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9])
integer				0 | [- ]*[1-9][0-9]*
float				0.0 | [- ]*[1-9][0-9]*"."[0-9]+
character-string		"(" [a-zA-Z0-9,.?:;'\"\n]+ ")"
Boolean				"T" | "F"
%%
{"+" number (number)+}				number + number (+ number)+
{"-" number (number)+}				number - number (- number)+
{"*" number (number)+}				number * number (* number)+
{"/" number ([- ]*[1-9][0-9]*("."[0-9]+)*)+}	number / [- ]*[1-9][0-9]*("."[0-9]+)* (/ [- ]*[1-9][0-9]*("."[0-9]+)*)+
{"%" integer [1-9][0-9]*}			integer % [1-9][0-9]*
{"print" "(" "\" ")" | parameter+}		{printf("%s\n", yytext);}
"(" "\" ")"					"\n"

{"==" parameter parameter}			parameter == parameter
{">" parameter parameter}			parameter > parameter
{"<" parameter parameter}			parameter < parameter
{">=" parameter parameter}			parameter >= parameter
{"<=" parameter parameter}			parameter <= parameter
{"!=" parameter parameter}			parameter != parameter
{"|" parameter parameter}			parameter | parameter
{"&" parameter parameter}			parameter & parameter
%%
int main()
{
	yylex();
	return 0;
}