#include <stdio.h>
#include <stdlib.h>

//The following is a very basic version of a stack
//with very basic functionality

int stack[1000000];
int stackCount = -1; //Keeps track of current scope
int stackCurrent = -1; //index of the current stack location

void push(int x)
{
    stackCurrent++;
    stack[stackCurrent] = x;
}

void pop()
{
    stackCurrent--;
}

int top()
{
    return stack[stackCurrent];
}

// Global Variables
typedef struct node
{
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

//Displays the entire hash table and all of the linked list nodes
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
    return -1;
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
