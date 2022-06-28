%{
//João Pedro Pacheco Silva Nº 218298731
 //Luís Carlos Lopes Loureiro Nº 2018297934
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST_structures.h"
#include "LIST_structures.h"
#include "llvm.h"
#include "y.tab.h"

extern int linha, coluna, opt, parse, smantic, col, lin, comment, linha2, coluna2, erro, e3;
extern char* yytext;

int yylex (void);
void yyerror(char* s);
int c,l;
typedef struct token_ {
	int linha;
	int coluna;
	char* id;
}Token;
Program* raiz;
int count = 0;
int astErro=1;
environment_list header;
declaration_node** tabela;
%}

%token <id> LPAR RPAR WHILE IF ELSE LBRACE RBRACE SEMI
%token RESERVED INVALIDCHAR UNTERMINATEDCHAR
%token <t> COMMA ASSIGN OR AND BITWISEOR BITWISEXOR BITWISEAND EQ NE GT GE LT LE PLUS MINUS MUL DIV MOD NOT ID CHAR INT VOID SHORT DOUBLE INTLIT CHRLIT REALLIT RETURN

%type <id> Id
%type <t> TypeSpec
%type <fadlist> FunctionsAndDeclarations
%type <vardec> Dec Declaration
%type <declist> DeclaratorEnum
%type <fundec> FunctionDeclaration
%type <parlist> ParameterList
%type <pardec> ParameterDeclaration  Pd
%type <funcdef> FunctionDefinition
%type <funcdec> FunctionDeclarator
%type <funcb> FunctionBody
%type <decstat> DeclarationsAndStatements
%type <st> Statement
%type <stlist> StatementList
%type <iff> If
%type <el> IfElse
%type <whi> While
%type <ret> Return
%type <exp> Expr Assign
%type <oper> Operator
%type <not_> Not
%type <min> Minus
%type <pl> Plus
%type <termin> Terminal
%type <das_> Das
%type <fad_> Fad

%union{
	int value;
	char* id;
	struct token_* t;
	struct _s2* fadlist;
	struct _s3* vardec;
	struct _s4* declist;
	struct _s5* fundec;
	struct _s6* parlist;
	struct _s7* pardec;
	struct _s8* funcdef;
	struct _s9* funcdec;
	struct _s10* funcb;
	struct _s11* decstat;
	struct _s12* st;
	struct _s13* stlist;
	struct _s14*  iff;
	struct _s15* el;
	struct _s16* whi;
	struct _s17* ret;
	struct _s18* exp;
	struct _s19* oper;
	struct _s20* not_;
	struct _s21* min;
	struct _s22* pl;
	struct _s24* termin;
	struct _s25* das_;
	struct _26* fad_;
}
%nonassoc ERROR
%nonassoc Y
%nonassoc ELSE
%nonassoc SEMI


%left COMMA
%right ASSIGN
%left OR
%left AND
%left BITWISEOR
%left BITWISEXOR
%left BITWISEAND
%left EQ NE
%left GT GE LT LE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT

%%

Program: FunctionsAndDeclarations	{raiz = insert_Program($1); if(astErro) create_environment_list(&header, tabela, count + count, raiz); if(smantic && opt){print_environment_list(header);} if(astErro && opt){if(header.erro)Convert_Program(raiz);} print_Program(raiz,opt);};

FunctionsAndDeclarations: FunctionsAndDeclarations Fad	{$$= insert_Function_And_Declaration_list($1, $2);}
	| Fad						{$$= insert_Function_And_Declaration_list(NULL, $1);}
	;

Fad: FunctionDefinition		{$$ =  insert_Fad("fdef", $1, NULL, NULL); count++;}
	| FunctionDeclaration	{$$ =  insert_Fad("fdec", NULL, $1, NULL); count++;}
	| Declaration		{$$ =  insert_Fad("vdec", NULL, NULL, $1); count++;}
	;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody	{$$ = insert_Function_Definition($1->id, $2, $3); free($1);}
	;

FunctionBody: LBRACE DeclarationsAndStatements RBRACE	{$$ = insert_FuncBody($2);}
	| LBRACE RBRACE					{$$ = insert_FuncBody(NULL);}
	;

DeclarationsAndStatements: DeclarationsAndStatements Das	{$$ = insert_Declarations_And_Statements($2, $1);}
	| Das							{$$ = insert_Declarations_And_Statements($1, NULL);}
	; 

Das: Statement	{$$ = insert_Das("s", $1, NULL);}
	| Declaration	{$$ = insert_Das("dec", NULL, $1);}
	; 

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI	{$$ = insert_Function_Declaration($1->id, $2); free($1);}
	;

FunctionDeclarator: ID LPAR ParameterList RPAR	{char* str= $1->id; $$ = insert_Function_Declarator(str, $3,$1->coluna,$1->linha); free($1); count++;}
	;

ParameterList: ParameterDeclaration			{$$ = insert_Paramlist($1);}
	;

ParameterDeclaration: TypeSpec Id Pd	{$$ = insert_ParamDeclaration($1->id, $2, $3, $1->coluna, $1->linha); free($1); count++;}
	;	

Pd: COMMA ParameterDeclaration {$$= $2;}
	| /*empty*/	{$$ = NULL;}
	;

Id: ID			{char* str= $1->id; $$=str; free($1);}
	| /*empty*/	{$$="";}
	;

Declaration: Dec SEMI	{$$=$1;}
	;

Dec: TypeSpec DeclaratorEnum 	{$$ = insert_Variable_Declaration($1->id , $2, $1->coluna, $1->linha); free($1);}
	| error	%prec ERROR		 {$$ = insert_Variable_Declaration("" , NULL, 0, 0); opt = 0;}
	;
	
DeclaratorEnum: ID Assign COMMA DeclaratorEnum		{char* str=  $1->id; $$ = insert_Declarator_list(str, $2, $4, $1->coluna,$1->linha); count++; free($1); }
	| ID COMMA DeclaratorEnum			{char* str= $1->id; $$ = insert_Declarator_list(str, NULL, $3, $1->coluna,$1->linha); count++; free($1);}
	| ID						{char* str= $1->id; $$ = insert_Declarator_list(str, NULL, NULL, $1->coluna,$1->linha); count++; free($1);}
	| ID Assign					{char* str= $1->id; $$ = insert_Declarator_list(str, $2, NULL, $1->coluna,$1->linha); count++; free($1);}
	;

TypeSpec: CHAR 		{$$ = $1;}
	| INT 		{$$ = $1;}
	| VOID 		{$$ = $1;}
	| SHORT 	{$$ = $1;}
	| DOUBLE	{$$ = $1;}
	;

Statement: Expr SEMI				{$$ = insert_Stat("ex", NULL, NULL, NULL, NULL, $1);}
	| SEMI					{$$ = insert_Stat("ex", NULL, NULL, NULL, NULL, NULL);}
	| LBRACE StatementList RBRACE		{$$ = insert_Stat("list", NULL, NULL, NULL, $2, NULL);}
	| LBRACE RBRACE				{$$ = NULL;}
	| LBRACE error RBRACE			{$$ = insert_Stat("list", NULL, NULL, NULL, NULL, NULL); opt = 0;}
	| If					{$$ = insert_Stat("if_", $1, NULL, NULL, NULL, NULL);}
	| While					{$$ = insert_Stat("while_", NULL, $1, NULL, NULL, NULL);}
	| Return				{$$ = insert_Stat("return_", NULL, NULL, $1, NULL, NULL);}
	| error SEMI 				{$$ = insert_Stat("ex", NULL, NULL, NULL, NULL, NULL); opt = 0;}
	;

If: IF LPAR Expr RPAR Statement	IfElse	{$$= insert_If($3, $5, $6);};

While: WHILE LPAR Expr RPAR Statement	{$$= insert_While($3, $5);};

Return: RETURN Expr SEMI	{$$ = insert_Return($2, $1->coluna, $1->linha); free($1);}
	| RETURN SEMI		{$$ = insert_Return(NULL, $1->coluna, $1->linha); free($1);}
	;

IfElse: ELSE Statement	{$$ = insert_Else($2);}
	| %prec Y/*empty*/	{$$ = insert_Else(NULL);}
	;

StatementList: StatementList Statement	{$$ = insert_StatList($2, $1);}
	| Statement			{$$ = insert_StatList($1, NULL);}
	;

Expr: Operator			{$$ = insert_Expression("op", $1, NULL, NULL, NULL, NULL, NULL, "", 0, 0);}
	| Plus			{$$ = insert_Expression("plus", NULL, NULL, NULL, $1, NULL, NULL, "", 0, 0);}
	| Minus			{$$ = insert_Expression("minus", NULL, NULL, $1, NULL, NULL, NULL, "", 0, 0);}
	| Not			{$$ = insert_Expression("not", NULL, $1, NULL, NULL, NULL, NULL, "", 0, 0);}
	| ID			{char* str= $1->id; $$ = insert_Expression("id", NULL, NULL, NULL, NULL, NULL, NULL, str, $1->coluna, $1->linha); free($1);}
	| ID LPAR Expr RPAR	{char* str= $1->id; $$ = insert_Expression("call", NULL, NULL, NULL, NULL, NULL, $3, str, $1->coluna, $1->linha); free($1);}
	| ID LPAR RPAR		{char* str= $1->id; $$ = insert_Expression("call", NULL, NULL, NULL, NULL, NULL, NULL, str, $1->coluna, $1->linha); free($1);}
	| ID LPAR error RPAR	{char* str= $1->id; $$ = insert_Expression("error", NULL, NULL, NULL, NULL, NULL, NULL, str, $1->coluna, $1->linha); opt = 0; free($1);}
	| Terminal		{$$ = insert_Expression("term", NULL, NULL, NULL, NULL, $1, NULL, "", 0, 0);}
	| LPAR Expr RPAR	{$$ = insert_Expression("ex", NULL, NULL, NULL, NULL, NULL, $2, "", 0, 0);}
	| LPAR error RPAR 	{$$ = insert_Expression("error", NULL, NULL, NULL, NULL, NULL, NULL, "", 0, 0); opt = 0;}
	;

Terminal: INTLIT 		{char* str=(char*)malloc(sizeof($1)+8*sizeof(char)); sprintf(str, "IntLit(%s)", $1->id); $$ = insert_Terminal(str, $1->coluna, $1->linha); free($1);}
	| CHRLIT 		{char* str=(char*)malloc(sizeof($1)+8*sizeof(char)); sprintf(str, "ChrLit(%s)", $1->id); $$ = insert_Terminal(str, $1->coluna, $1->linha); free($1);}
	| REALLIT 		{char* str=(char*)malloc(sizeof($1)+9*sizeof(char)); sprintf(str, "RealLit(%s)", $1->id); $$ = insert_Terminal(str, $1->coluna, $1->linha); free($1);}
	;


Not: NOT Expr	%prec NOT	{$$ = insert_Not($2,$1->coluna,$1->linha); free($1);};
Minus: MINUS Expr %prec NOT	{$$ = insert_Minus($2,$1->coluna,$1->linha); free($1);};
Plus: PLUS Expr	%prec NOT	{$$ = insert_Plus($2,$1->coluna,$1->linha); free($1);};


Operator: Expr Assign		{$$= insert_Operator("Store", $1, $2,c,l);}
	| Expr COMMA Expr	{$$= insert_Operator("Comma", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr PLUS Expr	{$$= insert_Operator("Add", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr MINUS Expr	{$$= insert_Operator("Sub", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr MUL Expr		{$$= insert_Operator("Mul", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr DIV Expr		{$$= insert_Operator("Div", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr MOD Expr		{$$= insert_Operator("Mod", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr OR Expr		{$$= insert_Operator("Or", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr AND Expr		{$$= insert_Operator("And", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr BITWISEAND Expr	{$$= insert_Operator("BitWiseAnd", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr BITWISEOR Expr	{$$= insert_Operator("BitWiseOr", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr BITWISEXOR Expr	{$$= insert_Operator("BitWiseXor", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr EQ Expr		{$$= insert_Operator("Eq", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr NE Expr		{$$= insert_Operator("Ne", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr LE Expr		{$$= insert_Operator("Le", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr GE Expr		{$$= insert_Operator("Ge", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr LT Expr		{$$= insert_Operator("Lt", $1, $3,$2->coluna,$2->linha); free($2);}
	| Expr GT Expr		{$$= insert_Operator("Gt", $1, $3,$2->coluna,$2->linha); free($2);}
	;
Assign: ASSIGN Expr {c=$1->coluna; l=$1->linha; $$=$2; free($1);};
%%

void yyerror ( char * s ) {
	smantic = 0;
	astErro=0;
	if(parse) {
		
		if(comment){
			printf("Line %d, col %d: %s: %s\n", linha2, coluna2, s, yytext);
		}
		else if(strlen(yytext)==0){
			
			printf("Line %d, col %d: %s: %s\n", linha, coluna, s, yytext);
		}
		else{
			printf("Line %d, col %d: %s: %s\n", linha, (int)(coluna-strlen(yytext)), s, yytext);
		}
	}
}


