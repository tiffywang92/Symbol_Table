#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

typedef struct node {
    char val[100];
	int scopeId;
	struct node* next;
} node;

void display(struct node* array[], int arraySize)
{
      struct node* nodeptr;
      for(int i = 0; i < arraySize; i++)
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
      for(int i = 0; i < arraySize; i++)
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
      for(int i = 0; i < arraySize; i++)
      {
            if(array[i] != NULL)
            {
                  nodeptr = array[i];
                  while(nodeptr != NULL)
                  {
                        if(nodeptr->scopeId == currentScope /*&& !strcmp(nodeptr->val, str)*/)
                        {
                            if(strcmp(nodeptr->val, str) == 0)
                            {
                                return 1;
                            }
                        }
                        
                        nodeptr = nodeptr->next;
                  }
            }
            
      }    
      return 0;
}

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
    //printf("hash: %d\n", hash);

    // insert the string
    head = table[hash];
    
    //printf("%d", hash);
    /*
    struct node* nodeptr;
    nodeptr = table[hash];
    int duplicate = 0;
    
    while(nodeptr != NULL)
    {
        printf("\n");
        if(strcmp(nodeptr->val, str))
        {
            printf(nodeptr->val);
            duplicate = 1;
            break;
        }
      nodeptr = nodeptr->next;
    }
     */
     
    
    
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
    //FILE* fin = fopen("p0input.txt", "r");
    node* symTable[31];
	//bool curr = false;
	int i, j;

	for (i = 0; i < 31; i++) {
        symTable[i] = NULL;
	}

    // loop through input file


    // test insert one
    insert(symTable, "hello", 0);
    insert(symTable, "hello", 1);
    insert(symTable, "hola", 15);
    insert(symTable, "test", 3);
    insert(symTable, "hello", 3);
    insert(symTable, "anotherTest", 3);
    insert(symTable, "anotherTest", 3);
    
    //display(symTable, 31);
    //find_in_all_scopes(symTable, 31, "hello");
    
    
    if(find_in_current_scope(symTable, 31, 3, "test") == 1){ printf("yes"); }
    /*
    char test1[4];
    char test2[5];
    strcpy(test1, "hi");
    strcpy(test2, "hfi");
    if(!strcmp(test1, test2) != 0)
    {
        printf("yes");
    }
    */
    
/*
    for (i = 0; i < 31; i++) {
        while (symTable[i] != NULL) {
            printf("val: %s\n", symTable[i]->val);
            printf("scope: %d\n", symTable[i]->scopeId);
            symTable[i] = symTable[i]->next;
        }
	}
 * */

	return 0;
}
