#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

typedef struct node {
    char val[100];
	int scopeId;
	struct node* next;
} node;

int insert(node* table[], char str[], int scope)
{
    if (str == NULL)
        return -1;
    /*if (find(table, str, scope))
        return -2;*/

    node* head, *curr = malloc(sizeof(node));
    int i, hash, countdown = sizeof(str);
    //double sum = 0.0;
    int sum = 0;

    // hash method using the 128-base formula
//    for (i = 0; i < sizeof(str); i++) {
//        sum += atof(str[i]) * pow(128.0, (double)countdown);
//        countdown--;
//    }

    // alt hash method
//    for (i = 0; i < sizeof(str); i++) {
//        sum += atof(str[i]) * pow(31.0, (double)countdown);
//        countdown--;
//    }
    for (i = 0; i < sizeof(str); i++) {
        sum += str[i] - '\0';
    }
    hash = (int)sum % 31;

    // insert the string
    head = table[hash];
    if (head == NULL) {
        head = curr;
        head->next = NULL;
    }
    else {
        head->next = curr;
        curr->next = NULL;
    }
    strcpy(head->val, str);
    head->scopeId = scope;

    // insert successful
    return 0;
}

int main()
{
    //FILE* fin = fopen("p0input.txt", "r");
    node* symTable[31];
	//bool curr = false;
	int i, j;

	for (i = 0; i < 31; i++) {
        symTable[i] = NULL;
	}

    // loop through input file


    // test insert one
    if (insert(symTable, "hello", 0) == 0)
        printf("Inserted.\n");

    // print out values
    for (i = 0; i < 31; i++) {
        if (symTable[i] != NULL) {
            printf("%s, %d\n", symTable[i]->val, symTable[i]->scopeId);
        }
    }

	return 0;
}
