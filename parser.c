/*
Heather Bradfield
Lab 6 Task 1
3/3/16

<program> ::= <statement> | <statement> <program>
<statement> ::= <assignStmt> | <repeatStmt> | <printStmt>
<assignStmt> ::= <id> = <expr> ;
<repeatStmt> ::= repeat ( <expr> ) <stmt>
<printStmt> ::= print <expr> ;
<expr> ::= <term> | <term> <addOp> <expr>
<term> ::= <factor> | <factor> <multOp> <term>
<factor> ::= <id> | <number> | - <factor> | ( <expr> )
*/

#include "parser.h"

AST_NODE *program()
{
	printf("funcProg : ");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = PROGRAM;
	node->left_node = statement();
	printf("\n");
	if (node->left_node != NULL)
		node->right_node = program();
	return node;
}

AST_NODE *statement()
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = STATEMENT;
	TOKEN *currentToken = (TOKEN *)scannerAdHoc();
	if (currentToken != NULL)
	{
		switch(currentToken->type)
		{
			case IDENTTOKEN: node->left_node = assignStmt(currentToken); break;
			case REPEAT: node->left_node = repeatStmt(currentToken); break;
			case PRINT: node->left_node = printStmt(currentToken); break;
			default: error(); break;
		}
	}
	else node = NULL;
	freeToken(&currentToken);
	return node;
}

AST_NODE *assignStmt(TOKEN *currToken)
{
	printf("funcAssign: ");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = ASSIGN_STMT;
	node->left_node = id(currToken);
	currToken = (TOKEN*)scannerAdHoc();
	if(currToken->type == ASSIGNMENT)
	{
		printf("to ");
		node->right_node = expr(currToken);
		currToken = (TOKEN*)scannerAdHoc();
		if (currToken->type != SEMICOLON) error();
	}
	else error();
	return node;

}

AST_NODE *repeatStmt(TOKEN *currToken)
{
	printf("funcRepeat: ");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = REPEAT_STMT;
	currToken = (TOKEN*)scannerAdHoc();
	if (currToken->type == LPAREN)
	{
		node->left_node = expr(currToken);
		currToken = (TOKEN *)scannerAdHoc();
		if(currToken->type != RPAREN) error();
		printf("statement: ");
		node->right_node = statement();
	}
	else error();
	return node;

}

AST_NODE *printStmt(TOKEN *currToken)
{
	printf("funcPrint: ");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = PRINT_STMT;
	node->left_node = expr(currToken);
	currToken = (TOKEN *) scannerAdHoc();
	if (currToken->type != SEMICOLON) error();
	return node;

}

AST_NODE *expr(TOKEN *currToken)
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = EXPR;
	node->left_node = term(currToken);
	currToken = (TOKEN *)scannerAdHoc();
	if (currToken->type == PLUS || currToken->type == MINUS)
		node->right_node = addOp(currToken);
	else ungetToken(&currToken);
	return node;

}

AST_NODE *term(TOKEN *currToken)
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = TERM;
	node->left_node = factor(currToken);
	currToken = (TOKEN*)scannerAdHoc();
	if(currToken->type == MULT || currToken->type == DIV || currToken->type == MOD)
	{
		node->right_node = multOp(currToken);
	}
	else ungetToken(&currToken);
	return node;

}

AST_NODE *factor(TOKEN *currToken)
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = FACTOR;
	currToken = (TOKEN *) scannerAdHoc();
	switch ( currToken->type )
	{
		case IDENTTOKEN: node->left_node = id(currToken); break;
		case NUMBERTOKEN: node->left_node = number(currToken); break;
		case MINUS: node->left_node = factor(currToken); break;
		case LPAREN:
	      node->left_node = expr(currToken);
	      currToken = (TOKEN*)scannerAdHoc();
	      if (currToken->type != RPAREN) error();
			break;
		default: error(); break;
	}
	return node;

}

AST_NODE *id(TOKEN *currToken)
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = IDENTIFIER;
	if (currToken->type == IDENTTOKEN)
	{
		strcpy(node->data.identifier,currToken->strVal);
		printf("ID(%s) ",node->data.identifier);
	} 
	else error();
	return node;

}

AST_NODE *number(TOKEN *currToken)
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = NUMBER;
	if(currToken->type == NUMBERTOKEN) 
	{
		node->data.number = atol(currToken->strVal);
		printf("INT(%.0f) ",node->data.number);
	}
	else error();
	return node;
}

AST_NODE *addOp(TOKEN *currToken) 
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = ADDOP;
	node->data.addOp = currToken->strVal[0];
	printf("addOp(%c) ",node->data.addOp);
	node->right_node = expr(currToken);
	if(node->right_node == NULL) error();
	return node;
}

AST_NODE *multOp(TOKEN *currToken)
{
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = MULTOP;
	node->data.multOp = currToken->strVal[0];
	printf("multOp(%c) ",node->data.multOp);
	node->right_node = term(currToken);
	if(node->right_node == NULL) error();
	return node;
}

void error()
{
	fprintf(stderr, "ERROR ");
}

void free_tree(AST_NODE *root) 
{
	if (root != NULL) 
	{
		free_tree(root->left_node);
		free_tree(root->right_node);
	    free(root);
	}
	root = NULL;
}