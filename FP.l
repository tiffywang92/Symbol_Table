%option noyywrap
%{
	#include <stdio.h>
	#include "SymbolTable.h"
	#include <math.h>

    FILE* fin;                  // input file
    node* symTable[31];         // hash table/array
    int i;                      // increment
    int scopeCount = 0;         // counter for scopes
    int excep;                  // to handle exceptions
    char buffer[100];           // string to hold read-in data
    int foundIn[100];




%}
keywords		"Program"|"Function"|"return"|"if"|"then"|"else"|"while"|"do"|"or"|"and"|"print"
Boolean			"T"|"F"
identifier		[a-z,A-Z]|[a-z,A-Z][a-z,A-Z,0-9]|[a-z,A-Z][a-z,A-Z,0-9][a-z,A-Z,0-9]|[a-z,A-Z][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9]|[a-z,A-Z][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9]|[a-z,A-Z][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9][a-z,A-Z,0-9]
integer			0|[-]?[ ]*[1-9][0-9]*
float			0.[0]+|[-]?[ ]*0"."[0]*[1-9]+[0-9]*|[-]?[ ]*[1-9][0-9]*"."[0-9]+
character-string	\([ a-z,A-Z,0-9,\n]+\)
symbols			\{|\}|\(|\)|\=|\+|\-|\*|\/|\%|\=\=|\>|\<|\>\=|\<\=|\!\=
whitespace		[ \t\n]+

%%
{Boolean}		printf("Boolean: %s\n", yytext);
{keywords}		printf("Keywords: %s\n", yytext);
{identifier}		printf("Identifier: %s\n", yytext); insert(symTable, stackCurrent, yytext);
{integer}		printf("Integer: %d\n", atoi(yytext));
{float}			printf("Float: %f\n", atof(yytext));
{character-string}	printf("Character-String: %s\n", yytext);
{whitespace}		//ignore whitespace
{symbols}		printf("Symbols: %s\n", yytext); scopeFunction(yytext);
%%

void scopeFunction(char str[])
{
	if(str[0] == '{')
	{
		stackCurrent++;
		stackCount++;
	}
		
	else if(str[0] == '}')
	{
		stackCurrent--;
	}
}


int main()
{
	//there are currently some problems with the definitions for integers (like '-  32432')
	//should probably do some more error checking with the definitions

    const int tableSize = 31;

    fin = fopen("sample", "r");

    for (i = 0; i < 31; i++)
    {
        symTable[i] = NULL;
    }
    for(i = 0; i < 100; i++)
    {
        foundIn[i] = -1;
    }


    yylex();	

	displayHashTable(symTable, tableSize);

    return 0;
}
/*
int insertST(node* table[], int scope, char str[])
{
// check if string is empty
    if (str == NULL)
        return -1;

    node* head;                         // to mark head of a chain
    node* curr = malloc(sizeof(node));  // to mark new node
    int i, j, hash;
    int length = sizeof(str);           // length of string
    int sum = 0;                        // hold a sum for hash
    int product = 1;                    // hold a product for exponents

    hash = hashMethod(str);
    
    // insert the string
    head = table[hash];
    if (head == NULL) {
        head = curr;
        head->next = NULL;
    }
    else {
        curr->next = head;
        head = curr;
    }
    table[hash] = head;
    strcpy(table[hash]->val, str);
    table[hash]->scopeId = scope;

    // insert successful
    return 0;
}
*/
