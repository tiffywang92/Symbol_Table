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

void displayScopes(struct node* array[], int arraySize)
{
    struct node* nodeptr;
      int i;
      int highestScope = 0;
      for(i = 0; i < arraySize; i++)
      {
          if(array[i] != NULL)
          {
              nodeptr = array[i];
              while(nodeptr != NULL)
              {
                  if(nodeptr->scopeId > highestScope)
                  {
                      highestScope = nodeptr->scopeId;
                  }
                  nodeptr = nodeptr->next;
              }
          }
      }
      
      int j;
      int k;
      for(j = 0; j < highestScope + 1; j++)
      {
          printf("Scope %d:", j);
          
          for(k = 0; k < arraySize; k++)
          {
              if(array[k] != NULL)
              {
                  nodeptr = array[k];
                  while(nodeptr != NULL)
                  {
                      if(nodeptr->scopeId == j)
                      {
                      printf("%s ", nodeptr->val);
                      }
                      nodeptr = nodeptr->next;
                  }
              }
          }
          
          printf("\n");
      }
      
      
      
}

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
    int i, hash;
    int sum = 0;                        // hold a sum for hash
    //int countdown = sizeof(str);
    //double sum = 0.0;

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

    // working hash method
    for (i = 0; i < sizeof(str); i++) {
        sum += str[i] - '\0';
    }
    hash = (int)sum % 31;
    //printf("hash: %d\n", hash);

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

    // test insert one
//    insert(symTable, "hello", 0);
//    insert(symTable, "hello", 1);
//    insert(symTable, "ayy", 0);
//
//    for (i = 0; i < 31; i++) {
//        while (symTable[i] != NULL) {
//            printf("val: %s\n", symTable[i]->val);
//            printf("scope: %d\n", symTable[i]->scopeId);
//            symTable[i] = symTable[i]->next;
//        }
//	}

    // loop through input file
    while (fscanf(fin, "%s", buffer) != EOF) {  // while not end of file
        if (strcmp(buffer, "{") == 0) {         // if OPEN new scope
            // start a block
            ++scopeCount;
            //
        }
        else if (strcmp(buffer, "}") == 0) {    // if CLOSE current scope
            // end a block
            //
            --scopeCount;
        }
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
    displayScopes(symTable, tableSize);
    

	return 0;
}