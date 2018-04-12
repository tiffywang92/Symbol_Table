#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

// Global variables
typedef struct node {
    char val[100];
	int scopeId;
	struct node* next;
} node;

const int tableSize = 31;


void display(struct node* array[], int arraySize)
{
      struct node* nodeptr;
      int i;

      for(i = 0; i < arraySize; i++)
      {
            printf("[%d]", i);
            if(array[i] != NULL)
            {
                  nodeptr = array[i];
                  while(nodeptr != NULL)
                  {
                        printf("[%s %d] ", nodeptr->val, nodeptr->scopeId);

                        nodeptr = nodeptr->next;
                  }
            }
            printf("\n");
      }
}

void find_in_all_scopes(struct node* array[], int arraySize, char str[])
{
      struct node* nodeptr;
      int i;

      for(i = 0; i < arraySize; i++)
      {
            printf("[%d]", i);
            if(array[i] != NULL)
            {
                  nodeptr = array[i];
                  while(nodeptr != NULL)
                  {
                        if(!strcmp(nodeptr->val, str))
                        {
                            printf("[%s %d] ", nodeptr->val, nodeptr->scopeId);
                        }

                        nodeptr = nodeptr->next;
                  }
            }
            printf("\n");
      }
}

int find_in_current_scope(struct node* array[], int arraySize, int currentScope, char str[])
{
      struct node* nodeptr;
      int i, index = 0;

      for(i = 0; i < arraySize; i++)
      {
            if(array[i] != NULL)
            {
                  nodeptr = array[i];
                  while(nodeptr != NULL)
                  {
                      ++index;
                        if(nodeptr->scopeId == currentScope /*&& !strcmp(nodeptr->val, str)*/)
                        {
                            if(strcmp(nodeptr->val, str) == 0)
                            {
                                return index;   // place along linked list
                            }
                        }

                        nodeptr = nodeptr->next;
                  }
            }

      }
      return 0;
}

int insert(node* table[], int scope, char str[])
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

    // hash method using the 128-base formula
    for (i = 0; i < length; i++) {
        for (j = length; j > 0; j--) {   // count down number of times
            // to multiply base 128
            product *= 128;
        }
        // and sum up
        sum += (str[i] - '\0') * product;
    }
    hash = (int)sum % 31;

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

int main()
{
    FILE* fin;                  // input file
    node* symTable[31];         // hash table/array
	int i;                      // increment
	int scopeCount = 0;         // counter for scopes
	int excep;                  // to handle exceptions
	char buffer[100];           // string to hold read-in data

	fin = fopen("p0input.txt", "r");

	// initialize all pointers in table
	for (i = 0; i < 31; i++) {
        symTable[i] = NULL;
	}

    // loop through input file
    printf("Processing input file...\n\n");
    while (fscanf(fin, "%s", buffer) != EOF) {  // while not end of file
        // if OPEN, count new scope
        if (strcmp(buffer, "{") == 0 || strcmp(buffer, "OPEN") == 0)
            ++scopeCount;
        // if CLOSE current scope, return to previous scope
        else if (strcmp(buffer, "}") == 0 || strcmp(buffer, "CLOSE") == 0)
            --scopeCount;
        else {                                  // all else are string values
            // process strings
            excep = find_in_current_scope(symTable, tableSize, scopeCount, buffer);
            if (excep > 0)
                printf("Duplicate found. Nothing inserted.\n");
            excep = insert(symTable, scopeCount, buffer);
            if (excep == -1)
                printf("Empty string found. Nothing inserted.\n");
        }
    }

    // print out symbol table
    printf("\n\n");
    display(symTable, tableSize);

	return 0;
}
