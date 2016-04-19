# ci-lisp

#### Grammar
Grammar for a simple programming language::
```
<program> ::= <statement> | <program> <statement>
<statement> ::= <assignStmt> | <repeatStmt> | <printStmt>
<assignStmt> ::= <id> = <expr> ;
<repeatStmt> ::= repeat ( <expr> ) <stmt>
<printStmt> ::= print <expr> ;
<expr> ::= <term> | <expr> <addOp> <term>
<term> ::= <factor> | <term> <multOp> <factor>
<factor> ::= <id> | <number> | - <factor> | ( <expr> )
```
#### Description

Implemented a recursive descent parser for the grammar. Parser builds an abstract syntax tree and shows how the input program is derived from the grammar by printing the sequence of productions. Created a struct AST_NODE that holds abstract tree nodes. Each node has a type, and a union part that is specialized for specific nodes in the tree (e.g., a node for print statement, repeat statement, expressions, etc.).