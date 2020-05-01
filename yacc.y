%token ID NUM IF THEN ELSE LE GE EQ NE OR AND WHILE INT CHAR RTN RD WT WTL BR EPS
%right '='
%left AND OR
%left '<' '>' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'
%start Program
%{
  #include<stdio.h>
  #include<stdlib.h>
%}


%%
Program : VarDec1List FunDec1List {printf("Program accepted\n"); exit(0);}
;

VarDec1List : VarDec1 VarDec1List
	| EPS
	;
	
VarDec1 : Type ID ';'
	| Type ID '[' NUM ']' ';'
	;

FunDec1List : FunDec1
	| FunDec1 FunDec1List
;

FunDec1 : Type ID '(' ParamDecList ')' Block
;

ParamDecList : EPS
	| ParamDec1ListTail
	;

ParamDec1ListTail : ParamDec1
	| ParamDec1 ',' ParamDec1ListTail
	;
	
ParamDec1 : Type ID
	| Type ID'['']'
	;

Block : '{' VarDec1List StmtList '}'
;

Type: INT
	| CHAR
;

StmtList : Stmt
	| Stmt StmtList
;

Stmt : ';'
	| Expr ';'
	| RTN Expr ';'
	| RD ID ';'
	| WT Expr ';'
	| WTL ';'
	| BR ';'
	| IF '(' Expr ')' Stmt ELSE Stmt
	| WHILE '(' Expr ')' Stmt
	| Block
;
Expr : Primary
	| '-' Expr
	| '!' Expr
	| Expr '+' Expr
	| Expr '-' Expr
	| Expr '*' Expr
	| Expr '/' Expr
	| Expr EQ Expr
	| Expr NE Expr
	| Expr '<' Expr
	| Expr LE Expr
	| Expr '>' Expr
	| Expr GE Expr
	| Expr AND Expr
	| Expr OR Expr
	| ID '=' Expr
	| ID '['Expr']' '=' Expr
;
Primary : ID
	| NUM
	| '(' Expr ')'
	| ID '[' Expr ']'
	| ID '(' ExprList ')'
;

ExprList : EPS
	| ExprListTail
	;

ExprListTail : Expr
	| Expr ',' ExprListTail
	;

%%
int yyerror(char* msg)
{
printf("Invalid Expression\n");
}

#include "lex.yy.c"

int main()
{
printf("Enter the statement: ");
yyparse();
return 0;
}
