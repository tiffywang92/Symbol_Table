#include "stdio.h"
#include "string.h"

#define struct node node
{
	char val[100];
	int scopeId;
	struct node* next;
}

int main()
{
	FILE* fin = fopen("p0input.txt");
	bool curr = false;
	int i, j;
	
	while (fscanf(fin, "%s", str) != EOF)
	{
		if (strcmp(str, "{") == 0)
		{
			// start a block
		}
		else if (strcmp(str, "}") == 0)
		{
			// close a block
		}
		else	// string looks like an id
		{
			curr = find_in_current(node.val, node.scopeId);
			if (!curr)
			{
				insert(node.val, node.scopeId);
				find_in_all(node.val)	// to check if anywhere else in the table
			}
		}
	}
	printf("Symbol Table\n");
	for (i = 0; i < 3; i++)
	{
		// print scope block 1, 2, 3...
	}
}