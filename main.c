/*
 GROUP MEMBERS
 
 Lawrence Lee jq2773
 Hanjun Zhou jn2294
 Tiffany Wang rd7359
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

// the stack and it's functions
char stack[1000000];
int current = -1;
int stackCount = -1;
void push(char x)
{
    current++;
    stack[current] = x;
}
void pop()
{
    current--;
}

// Global Variables
typedef struct node {
    char val[100];
    int scopeId;
    struct node* next;
} node;

const int tableSize = 31;

//displays every scope and every identifier within those scopes
void displayScopes(struct node* array[], int arraySize, int highestScope)
{
    struct node* nodeptr;
    int i, j, k;
    for(j = 0; j < highestScope + 1; j++)
    {
        printf("Scope %d: ", j);
          
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

//the following displays the entire hash table and all of the linked list nodes
void displayHashTable(struct node* array[], int arraySize)
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

//puts specific identifier's scope value onto array
void find_in_all_scopes(struct node* array[], int arraySize, char str[], int listIndices[])
{
      struct node* nodeptr;
      int i, j = 0;

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
                            listIndices[j] = nodeptr->scopeId;
                            printf("[%s %d] ", nodeptr->val, nodeptr->scopeId);
                            j++;
                        }

                        nodeptr = nodeptr->next;
                  }
            }
            printf("\n");
      }
}

//method for determining a identifier's hash value
int hashMethod(char str[])
{
    int i, j, hash;
    int length = strlen(str);
    int sum = 0;
    int product = 1;
    
    for (i = 0; i < length; i++)
    {
        for (j = length; j > 0; j--)
        {
            product *= 128;
        }
        sum += (str[i] - '\0') * product;
    }
    
    hash = (int)sum % 31;
    return hash;
}

//checks if identifier already exists in a specific scope
int find_in_current_scope(struct node* array[], int arraySize, int currentScope, char str[])
{   
    struct node* nodeptr;
    int i, index = 0, hash;
    hash = hashMethod(str);
    nodeptr = array[hash];
    while(nodeptr != NULL)
    {
        ++index;
        if(nodeptr->scopeId == currentScope)
        {
            if(strcmp(nodeptr->val, str) == 0)
            {
                return index;
            }
        }
        nodeptr = nodeptr->next;
    }
    
}

//insert a identifier along with it's scope onto a node in the hash table
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

int main()
{
    FILE* fin;                  // input file
    node* symTable[31];         // hash table/array
    int i;                      // increment
    int scopeCount = 0;         // counter for scopes
    int excep;                  // to handle exceptions
    char buffer[100];           // string to hold read-in data
    int foundIn[100];

    fin = fopen("inputTest1.txt", "r");

    // initialize all pointers in table
    for (i = 0; i < 31; i++)
    {
        symTable[i] = NULL;
    }
    for(i = 0; i < 100; i++)
    {
        foundIn[i] = -1;
    }

    // loop through input file
    printf("Processing input file...\n\n");
    while (fscanf(fin, "%s", buffer) != EOF) {  // while not end of file
        
        if (strcmp(buffer, "{") == 0 || strcmp(buffer, "OPEN") == 0) {         // if OPEN new scope
            // start a block
            stackCount++;
            push(stackCount);
            ++scopeCount;//printf("%c", stack[current]);
            //
        }
        else if (strcmp(buffer, "}") == 0 || strcmp(buffer, "CLOSE") == 0) {    // if CLOSE current scope
            // end a block
            //
            pop();
            --scopeCount;
        }
        else {                                  // all else are string values
            // process strings
            excep = find_in_current_scope(symTable, tableSize, stack[current], buffer);
            if (excep > 0){
                printf("Duplicate found. Nothing inserted.\n");}
            else if(excep == 0){
                excep = insert(symTable, stack[current], buffer);}
            else if (excep == -1){
                printf("Empty string found. Nothing inserted.\n");}
        }
    }

    // print out symbol table
    displayScopes(symTable, tableSize, stackCount);
    //displayHashTable(symTable, tableSize);

    
    //the following calls the find_in_all_scopes function and
    //returns a list of scopes in which the identifier is found
    /*
    find_in_all_scopes(symTable, tableSize, "a", foundIn);
    printf("\n\nFound in scopes:\n");
    for (i = 0; i < sizeof(foundIn)/sizeof(int); i++) {
        if (foundIn[i] != -1)
            printf("%d\n", foundIn[i]);
    }
     */
            

    return 0;
}
