/*
Heather Bradfield
Lab 6 Task 1
3/6/16
*/

#include "parser.h"

void print_full(AST_NODE *root);
void print_abstract(AST_NODE *root);

int main(void)
{
	AST_NODE *root = program();
	printf("\n");
	print_full(root);
	printf("\n");
	print_abstract(root);
	free_tree(root);
	return 0;
}

void print_full(AST_NODE *root)
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
    node = root;
    int children;

	if ((node->left_node == NULL && node->right_node == NULL)
		|| node->type == ADDOP || node->type == MULTOP)
	{
		children = 0;
	}
	else if (node->right_node == NULL)
	{
		children = 1;
	}
	else if (node->left_node != NULL && node->right_node != NULL &&
		(node->right_node->type == ADDOP || node->right_node->type == MULTOP))
	{
		children = 3;
	}
	else
	{
		children = 2;
	}
	printf("Traversing tree.. ");	
	switch(node->type)
	{
		case IDENTIFIER: printf("idNode: children %d, data: %s",children,node->data.identifier); break;
		case NUMBER: printf("numberNode: children %d, data: %.0f",children,node->data.number); break;
		case EXPR: printf("expr: children %d",children); break;
		case TERM: printf("term: children %d",children); break;
		case ASSIGN_STMT: printf("assignStmt: children %d",children); break;
		case REPEAT_STMT: printf("repeatStmt: children %d",children); break;
		case PRINT_STMT: printf("printStmt: children %d",children); break;
		case FACTOR: printf("factor: children %d",children); break;
		case ADDOP: printf("addOpNode: children %d, data: %c",children,node->data.addOp); break;
		case MULTOP: printf("multOpNode: children %d, data: %c",children,node->data.multOp); break;
		case PROGRAM: printf("program: children %d",children); break;
		case STATEMENT: printf("statement: children %d",children); break;
		default: printf("Invalid node."); break;
	}
 	printf("\n");
	if (node->left_node != NULL)
		print_full(node->left_node);
	if (node->right_node != NULL)
		print_full(node->right_node);

}

void print_abstract(AST_NODE *root)
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
    node = root;
    int children = 0;
    if ((node->left_node == NULL && node->right_node == NULL)
    	|| node->type == ADDOP || node->type == MULTOP)
	{
		children = 0;
	}
	else if (node->right_node == NULL)
	{
		children = 1;
	}
	else if (node->left_node != NULL && node->right_node != NULL &&
		(node->right_node->type == ADDOP || node->right_node->type == MULTOP))
	{
		children = 3;
	}
	else
	{
		children = 2;
	}

	switch(node->type)
	{
		case IDENTIFIER: printf("Abstract traverse tree.. idNode: children %d, data: %s\n",children,node->data.identifier); break;
		case NUMBER: printf("Abstract traverse tree.. numberNode: children %d, data: %.0f\n",children,node->data.number); break;
		case ASSIGN_STMT: printf("Abstract traverse tree.. assignStmt: children %d\n",children); break;
		case REPEAT_STMT: printf("Abstract traverse tree.. repeatStmt: children %d\n",children); break;
		case PRINT_STMT: printf("Abstract traverse tree.. printStmt: children %d\n",children); break;
		case ADDOP: printf("Abstract traverse tree.. addOpNode: children %d, data: %c\n",children,node->data.addOp); break;
		case MULTOP: printf("Abstract traverse tree.. multOpNode: children %d, data: %c\n",children,node->data.multOp); break;
		default: break;
	}
	//printf("\n");
	if (node->left_node != NULL)
		print_abstract(node->left_node);
	if (node->right_node != NULL)
		print_abstract(node->right_node);
}

