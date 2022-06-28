%{
//João Pedro Pacheco Silva Nº 218298731
 //Luís Carlos Lopes Loureiro Nº 2018297934
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

extern int linha, coluna, opt, parse, col, lin, comment, linha2, coluna2, erro;
extern char* yytext;

int yylex (void);
void yyerror(char* s);

typedef struct _s18 Expression;

typedef struct _s24 {
        char* type;
} Terminal;

typedef struct _s22 {
        Expression* ex;
} Plus;

typedef struct _s21 {
        Expression* ex;
} Minus;

typedef struct _s20 {
        Expression* ex;
} Not;

typedef struct _s19 {
	char* type;
        Expression* ex1;
	Expression* ex2;
}  Operator;

typedef struct _s18 {
	char* type;
        Operator* op;
	Not* not;
	Minus* minus;
	Plus* plus;
	Terminal* term;
	char* id;
	Expression* ex;
} Expression;

typedef struct _s17 {
        Expression* ex;
} Return;

typedef struct _s12 Stat;

typedef struct _s16 {
        Expression* ex;
	Stat* s;
} While;

typedef struct _s15 {
	Stat* s;
} Else;

typedef struct _s14 {
        Expression* ex;
	Stat* s;
	Else* else_;
} If;

typedef struct _s13 {
	Stat* s;
	struct _s13* next;
} StatList;

typedef struct _s12 {
	char* type;
        If* if_;
	While* while_;
	Return* return_;
	StatList* list;
	Expression* ex;
} Stat;

typedef struct _s4 {
        char* id;
	Expression* ex;
	struct _s4* next;
} Declarator_list;

typedef struct _s3 {
	char* TypeSpec;
        Declarator_list* list;
} Variable_Declaration;

typedef struct _s25 {
        char* type;
	Stat* s;
	Variable_Declaration* dec;
} Das;

typedef struct _s11 {
        Das* das;
	struct _s11* next;
} Declarations_And_Statements;

typedef struct _s10 {
       Declarations_And_Statements* list;
} FuncBody;

typedef struct _s7 {
	char* TypeSpec;
        char* id;
	struct _s7* next;
} ParamDeclaration;

typedef struct _s6 {
	ParamDeclaration* list;
} Paramlist;

typedef struct _s9 {
	char* id;
	Paramlist* list;
} Function_Declarator;

typedef struct _s8 {
        char* TypeSpec;
        Function_Declarator* fd;
	FuncBody* fb;
} Function_Definition;

typedef struct _s5 {
	char* TypeSpec;
	Function_Declarator* fd;
} Function_Declaration;

typedef struct _26 {
	char* type;
	Function_Definition* fdef;
	Function_Declaration* fdec;
	Variable_Declaration* vdec;
} Fad;

typedef struct _s2 {
        Fad* fad;
        struct _s2* next;
} Function_And_Declaration_list;

typedef struct _s1 {
    Function_And_Declaration_list* list;
} Program;

Program* raiz;

// functions

Program* insert_Program(Function_And_Declaration_list* list)
{
	if(list==NULL) printf("a\n");
	Program* node=(Program*)malloc(sizeof(Program));

	node->list= list;

	return node;
}

Function_And_Declaration_list* insert_Function_And_Declaration_list(Function_And_Declaration_list* head, Fad* fad)
{
        Function_And_Declaration_list* node = (Function_And_Declaration_list*)malloc(sizeof(Function_And_Declaration_list));
        Function_And_Declaration_list* tmp;

        node->fad = fad;
        node->next=NULL;

        if(head==NULL)
                return node;

        for(tmp=head; tmp->next; tmp=tmp->next);
        tmp->next=node;

        return head;
}

Fad* insert_Fad(char* type, Function_Definition* fdef, Function_Declaration* fdec, Variable_Declaration* vdec)
{
        Fad* node = (Fad*)malloc(sizeof(Fad));

        node->type = type;
	node->fdef = fdef;
	node->fdec = fdec;
	node->vdec = vdec;

        return node;
}

Variable_Declaration* insert_Variable_Declaration(char* TypeSpec, Declarator_list* list)
{
	Variable_Declaration* node=(Variable_Declaration*)malloc(sizeof(Variable_Declaration));

	node->TypeSpec = TypeSpec;
	node->list = list;

	return node;
}

Declarator_list* insert_Declarator_list(char* id, Expression* ex, Declarator_list* head)
{
        Declarator_list* node = (Declarator_list*)malloc(sizeof(Declarator_list));

        node->id = id;
	node->ex = ex;
        node->next=NULL;

        if(head==NULL)
                return node;

        node->next = head;

        return node;
}

Function_Declaration* insert_Function_Declaration(char* TypeSpec, Function_Declarator* fd)
{
	Function_Declaration* node=(Function_Declaration*)malloc(sizeof(Function_Declaration));

	node->TypeSpec = TypeSpec;
	node->fd = fd;

	return node;
}


Paramlist* insert_Paramlist(ParamDeclaration* list)
{
        Paramlist* node = (Paramlist*)malloc(sizeof(Paramlist));

	node->list = list;

        return node;
}

ParamDeclaration* insert_ParamDeclaration(char* TypeSpec, char* id, ParamDeclaration* head)
{
        ParamDeclaration* node = (ParamDeclaration*)malloc(sizeof(ParamDeclaration));

        node->TypeSpec = TypeSpec;
	node->id = id;
        node->next=head;

        return node;
}

Function_Definition* insert_Function_Definition(char* TypeSpec, Function_Declarator* fd, FuncBody* fb)
{
	Function_Definition* node=(Function_Definition*)malloc(sizeof(Function_Definition));

	node->fd= fd;
	node->fb= fb;
	node->TypeSpec = TypeSpec;

	return node;
}

Function_Declarator* insert_Function_Declarator(char* id, Paramlist* list)
{
	Function_Declarator* node=(Function_Declarator*)malloc(sizeof(Function_Declarator));

	node->list= list;
	node->id= id;

	return node;
}

FuncBody* insert_FuncBody(Declarations_And_Statements* list)
{
	FuncBody* node=(FuncBody*)malloc(sizeof(FuncBody));

	node->list= list;

	return node;
}

Declarations_And_Statements* insert_Declarations_And_Statements(Das* das, Declarations_And_Statements* head)
{
        Declarations_And_Statements* node = (Declarations_And_Statements*)malloc(sizeof(Declarations_And_Statements));
	Declarations_And_Statements* tmp;

        node->das= das;
        node->next=NULL;

        if(head==NULL)
                return node;

        for(tmp=head; tmp->next; tmp=tmp->next);
        tmp->next=node;

        return head;
}

Das* insert_Das(char* type, Stat* s, Variable_Declaration* dec)
{
        Das* node = (Das*)malloc(sizeof(Das));

        node->type = type;
	node->s = s;
	node->dec = dec;
	return node;
}

StatList* insert_StatList(Stat* s, StatList* head)
{
	if(s == NULL) return head;
	if(!strcmp(s->type, "ex") && s->ex==NULL) return head;
	if(!strcmp(s->type, "list") && s->list==NULL) return head;
	StatList* node = (StatList*)malloc(sizeof(StatList));
	StatList* tmp;

	node->s = s;
        node->next=NULL;

        if(head==NULL)
                return node;

        for(tmp=head; tmp->next; tmp=tmp->next);
        tmp->next=node;

        return head;
}

Stat* insert_Stat(char* type, If* if_, While* while_, Return* return_, StatList* list, Expression* ex)
{
	if(!strcmp(type, "list") && list==NULL) return NULL;
	if(!strcmp(type, "ex") && ex==NULL) return NULL;
	Stat* node=(Stat*)malloc(sizeof(Stat));

	node->type= type;
	node->if_= if_;
	node->while_= while_;
	node->return_= return_;
	node->list = list;
	node->ex = ex;
	return node;
}

If* insert_If(Expression* ex, Stat* s, Else* else_)
{
	If* node=(If*)malloc(sizeof(If));

	node->ex= ex;
	node->s= s;
	node->else_= else_;

	return node;
}

Else* insert_Else(Stat* s)
{
	Else* node=(Else*)malloc(sizeof(Else));

	node->s= s;

	return node;
}

While* insert_While(Expression* ex, Stat* s)
{
	While* node=(While*)malloc(sizeof(While));

	node->ex= ex;
	node->s= s;

	return node;
}

Return* insert_Return(Expression* ex)
{
	Return* node=(Return*)malloc(sizeof(Return));

	node->ex= ex;

	return node;
}

Expression* insert_Expression(char* type, Operator* op, Not* not, Minus* minus, Plus* plus, Terminal* term, Expression* ex, char* id)
{
	Expression* node=(Expression*)malloc(sizeof(Expression));

	node->type= type;
	node->op= op;
	node->not= not;
	node->minus= minus;
	node->plus= plus;
	node->term= term;
	node->id= id;
	node->ex= ex;

	return node;
}

Operator* insert_Operator(char* type, Expression* ex1, Expression* ex2)
{
	Operator* node=(Operator*)malloc(sizeof(Operator));

	node->type= type;
	node->ex1= ex1;
	node->ex2= ex2;

	return node;
}

Not* insert_Not(Expression* ex)
{
	Not* node=(Not*)malloc(sizeof(Not));

	node->ex= ex;

	return node;
}

Minus* insert_Minus(Expression* ex)
{
	Minus* node=(Minus*)malloc(sizeof(Minus));

	node->ex= ex;

	return node;
}

Plus* insert_Plus(Expression* ex)
{
	Plus* node=(Plus*)malloc(sizeof(Plus));

	node->ex= ex;

	return node;
}

Terminal* insert_Terminal(char* type)
{
	Terminal* node=(Terminal*)malloc(sizeof(Terminal));

	node->type= type;

	return node;
}



// imprimir




void print_Program(Program* node, int option);
void print_Function_And_Declaration_list(char* str, Function_And_Declaration_list* node, int option);
void print_Fad(char* str, Fad* node, int option);
void print_Variable_Declaration(char* str, Variable_Declaration* node, int option);
void print_Declarator_list(char* str, Declarator_list* node, int option);
void print_Fad(char* str, Fad* node, int option);
void print_Variable_Declaration(char* str, Variable_Declaration* node, int option);
void print_Declarator_list(char* str, Declarator_list* node, int option);
void print_Function_Declaration(char* str, Function_Declaration* node, int option);
void print_Paramlist(char* str, Paramlist* node, int option);
void print_ParamDeclaration(char* str, ParamDeclaration* node, int option);
void print_Function_Definition(char* str, Function_Definition* node, int option);
void print_Function_Declarator(char* str, Function_Declarator* node, int option);
void print_FuncBody(char* str, FuncBody* node, int option);
void print_Declarations_And_Statements(char* str, Declarations_And_Statements* node, int option);
void print_Das(char* str, Das* node, int option);
void print_Stat(char* str, Stat* node, int option);
void print_StatList(char* str, StatList* node, int option);
void print_If(char* str, If* node, int option);
void print_Else(char* str, Else* node, int option);
void print_While(char* str, While* node, int option);
void print_Return(char* str, Return* node, int option);
void print_Expression(char* str, Expression* node, int option, int flag);
void print_Operator(char* str, Operator* node, int option, int flag);
void print_Not(char* str, Not* node, int option);
void print_Minus(char* str, Minus* node, int option);
void Print_Plus(char* str, Plus* node, int option);
void print_Terminal(char* str, Terminal* node, int option);

void print_Program(Program* node, int option)
{
	if(!option) return;
	if(node==NULL) return;
	if(option) printf("Program\n");
	char* str= (char*)malloc(sizeof(3*sizeof(char)));
	sprintf(str, "..");
	print_Function_And_Declaration_list(str, node->list, option);
	//free(str);
	free(node);
}

void print_Function_And_Declaration_list(char* str, Function_And_Declaration_list* node, int option)
{	
	if(node==NULL) return;
        Function_And_Declaration_list* tmp= node;
	Function_And_Declaration_list* tmp2= node;

	while(tmp!=NULL){
		print_Fad(str, tmp->fad, option);
		tmp2 = tmp;
		tmp= tmp->next;
		free(tmp2);
	}
}

void print_Fad(char* str, Fad* node, int option)
{
        if(node==NULL) return;

		if(!strcmp(node->type, "fdef")){
			print_Function_Definition(str, node->fdef, option);
		}
		else if(!strcmp(node->type, "fdec")){
			print_Function_Declaration(str, node->fdec, option);
		}
		else{
			print_Variable_Declaration(str, node->vdec, option);
		}
	free(node);
}

void print_Variable_Declaration(char* str, Variable_Declaration* node, int option)
{
	if(node==NULL) return;
	
	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);

	Declarator_list* tmp;
	
	do{
		if(option) printf("%sDeclaration\n", str);
		if(option) printf("%s%s\n",str2 ,node->TypeSpec);
		//Declarator_list* tmp = node->list;
		//for(tmp->next!=NULL);
		print_Declarator_list(str2, node->list, option);
		tmp = node->list;
		node->list = node->list->next;
		free(tmp);
	}while(node->list!=NULL);
	
	//free(str2);
}

void print_Declarator_list(char* str, Declarator_list* node, int option)
{
	if(node==NULL) return;
	
		if(option) printf("%s%s\n",str ,node->id);
		print_Expression(str, node->ex, option, 1);
	
}

void print_Function_Declaration(char* str, Function_Declaration* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%sFuncDeclaration\n", str);
	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
	if(option){
		printf("%s%s\n", str, node->TypeSpec);
		
	}
	
	print_Function_Declarator(str, node->fd, option);
	//free(str2);
	free(node);
}

void print_Paramlist(char* str, Paramlist* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%sParamList\n", str);

	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;	
	print_ParamDeclaration(str, node->list, option);
	//free(str2);
	free(node);
}

void print_ParamDeclaration(char* str, ParamDeclaration* node, int option)
{
	if(node==NULL) return;
        ParamDeclaration* tmp= node;
	ParamDeclaration* tmp2;
	
	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	//str=str2;

	while(tmp!=NULL){
		if(option){
			printf("%sParamDeclaration\n", str);
			printf("%s%s\n", str2, tmp->TypeSpec);
			if(strcmp(tmp->id,""))printf("%s%s\n", str2, tmp->id);  //
		}
		tmp2 = tmp;
		tmp= tmp->next;
		free(tmp2);
	}
	//free(str2);
}

void print_Function_Definition(char* str, Function_Definition* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%sFuncDefinition\n", str);

	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
	if(option){
		printf("%s%s\n", str, node->TypeSpec);
	}
	print_Function_Declarator(str, node->fd, option);
	print_FuncBody(str, node->fb, option);
	//free(str2);
	free(node);
}

void print_Function_Declarator(char* str, Function_Declarator* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%s%s\n", str, node->id);

	print_Paramlist(str, node->list, option);
	//free(str2);
	free(node);
}

void print_FuncBody(char* str, FuncBody* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%sFuncBody\n", str);

	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
	print_Declarations_And_Statements(str, node->list, option);
	//free(str2);
	free(node);
}

void print_Declarations_And_Statements(char* str, Declarations_And_Statements* node, int option)
{
	if(node==NULL)return;
	Declarations_And_Statements* tmp= node;
	Declarations_And_Statements* tmp2;
	
	while(tmp!=NULL){
		print_Das(str, tmp->das, option);
		tmp2 = tmp;
		tmp= tmp->next;
		free(tmp2);
	}
}

void print_Das(char* str, Das* node, int option)
{
	if(node==NULL) return;
	if(!strcmp(node->type, "dec")){
			print_Variable_Declaration(str, node->dec, option);
		}
		else{
			print_Stat(str, node->s, option);
		}
	free(node);
}

void print_Stat(char* str, Stat* node, int option)
{
	if(node==NULL) return;
	
		if(!strcmp(node->type, "if_")){
			print_If(str, node->if_, option);
		}
		else if(!strcmp(node->type, "while_")){
			print_While(str, node->while_, option);
		}
		else if(!strcmp(node->type, "list")){
			if(node->list==NULL){
				if(option) printf("%sNull\n", str);
			}
			print_StatList(str, node->list, option);
		}
		else if(!strcmp(node->type, "ex")){
			print_Expression(str, node->ex, option, 1);
		}
		else{
			print_Return(str, node->return_, option);
		}
	//free(str2);
	free(node);
}

void print_StatList(char* str, StatList* node, int option)
{
	if(node==NULL) return;
	StatList* tmp = node;
	StatList* tmp2;
	int count =0;
	while(tmp!=NULL){
		count++;
		tmp= tmp->next;
	}
	tmp = node;
	if(count==0){
		if(option) printf("%sNull\n", str);
		return;
	}
	if(count>1){ 
	
	printf("%sStatList\n", str);
	
	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
	}
	while(tmp!=NULL){
		print_Stat(str, tmp->s, option);
		tmp2=tmp;
		tmp= tmp->next;
		free(tmp2);
	}
	
}

void print_If(char* str, If* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%sIf\n", str);
	
	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	
	//str=str2;

	print_Expression(str2, node->ex, option, 1);
	
	if(node->s==NULL){
		if(option) printf("%s..Null\n", str);
		
	}
	else{
		print_Stat(str2, node->s, option);
	}

	if(node->else_->s==NULL){ 
		printf("%s..Null\n", str);
	}
	else{
		print_Else(str2, node->else_, option);
	}
	//free(str2);
	free(node);
}

void print_Else(char* str, Else* node, int option)
{
	if(node==NULL) return;
	
	//if(option){if(node->s==NULL) printf("%sNull\n", str);}
	
	print_Stat(str, node->s, option);
	//free(str2);
	free(node);
}


void print_While(char* str, While* node, int option)
{
	if(node==NULL) return;

	if(option) printf("%sWhile\n", str);

	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	//str=str2;

	print_Expression(str2, node->ex, option, 1);
	
	if(node->s==NULL){
		if(option) printf("%s..Null\n", str);
		free(node);
		return;
	}
	print_Stat(str2, node->s, option);
	//free(str2);
	free(node);
}

void print_Return(char* str, Return* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%sReturn\n", str);

	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;

	if(option){if(node->ex==NULL) printf("%sNull\n", str);}
	print_Expression(str, node->ex, option, 1);
	//free(str2);
	free(node);
}

void print_Expression(char* str, Expression* node, int option, int flag)
{
	if(node==NULL) return;
	if(!strcmp(node->type, "op")){
		print_Operator(str, node->op, option, flag);
	}
	else if(!strcmp(node->type, "not")){
		print_Not(str, node->not, option);
	}
	else if(!strcmp(node->type, "minus")){
		print_Minus(str, node->minus, option);
	}
	else if(!strcmp(node->type, "plus")){
		Print_Plus(str, node->plus, option);
	}
	else if(!strcmp(node->type, "id")){
		if(option) printf("%s%s\n", str, node->id);
	}
	else if(!strcmp(node->type, "ex")){
		print_Expression(str, node->ex, option, 1);
	}
	else if(!strcmp(node->type, "call")){
		if(option) printf("%sCall\n", str);
		char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
		if(option) printf("%s%s\n", str, node->id);
		print_Expression(str, node->ex, option, 0);
	}
	else if(!strcmp(node->type, "term")){
		print_Terminal(str, node->term, option);
	}
	free(node);
}

void print_Operator(char* str, Operator* node, int option, int flag)
{
	if(node==NULL) return;
			
	if(!strcmp(node->type, "Comma")){
		if(flag){
			if(option) printf("%s%s\n", str, node->type);
			char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
		}
	}else{
		if(option) printf("%s%s\n", str, node->type);
		flag=1;
		char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
	}
	

	print_Expression(str, node->ex1, option, flag);
	print_Expression(str, node->ex2, option, flag);
	//free(str2);
	free(node);
}

void print_Not(char* str, Not* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%sNot\n", str);

	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
	print_Expression(str, node->ex, option, 1);
	//free(str2);
	free(node);
}

void print_Minus(char* str, Minus* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%sMinus\n", str);

	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
	print_Expression(str, node->ex, option, 1);
	//free(str2);
	free(node);
}

void Print_Plus(char* str, Plus* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%sPlus\n", str);

	char* str2 = (char*)malloc(sizeof(str)+2*sizeof(char));
	sprintf(str2, "..%s", str);
	str=str2;
	print_Expression(str, node->ex, option, 1);
	//free(str2);
	free(node);
}

void print_Terminal(char* str, Terminal* node, int option)
{
	if(node==NULL) return;
	if(option) printf("%s%s\n", str, node->type);
	free(node);
}

%}

//%token COMMA ASSIGN OR AND BITWISEOR BITWISEXOR BITWISEAND EQ NE GT GE LT LE PLUS MINUS MUL DIV MOD NOT ID INTLIT CHRLIT REALLIT LPAR RPAR RETURN WHILE IF ELSE LBRACE RBRACE SEMI CHAR INT VOID SHORT DOUBLE
%token <id> COMMA ASSIGN OR AND BITWISEOR BITWISEXOR BITWISEAND EQ NE GT GE LT LE PLUS MINUS MUL DIV MOD NOT ID INTLIT CHRLIT REALLIT LPAR RPAR RETURN WHILE IF ELSE LBRACE RBRACE SEMI CHAR INT VOID SHORT DOUBLE
%token RESERVED INVALIDCHAR UNTERMINATEDCHAR

%type <id> TypeSpec Id
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

Program: FunctionsAndDeclarations	{raiz = insert_Program($1); print_Program(raiz,opt);};

FunctionsAndDeclarations: FunctionsAndDeclarations Fad	{$$= insert_Function_And_Declaration_list($1, $2);}
	| Fad						{$$= insert_Function_And_Declaration_list(NULL, $1);}
	;

Fad: FunctionDefinition		{$$ =  insert_Fad("fdef", $1, NULL, NULL);}
	| FunctionDeclaration	{$$ =  insert_Fad("fdec", NULL, $1, NULL);}
	| Declaration		{$$ =  insert_Fad("vdec", NULL, NULL, $1);}
	;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody	{$$ = insert_Function_Definition($1, $2, $3);}
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

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI	{$$ = insert_Function_Declaration($1, $2);}
	;

FunctionDeclarator: ID LPAR ParameterList RPAR	{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$ = insert_Function_Declarator(str, $3);}
	;

ParameterList: ParameterDeclaration			{$$ = insert_Paramlist($1);}
	;

ParameterDeclaration: TypeSpec Id Pd	{$$ = insert_ParamDeclaration($1, $2, $3);}
	;	

Pd: COMMA ParameterDeclaration {$$= $2;}
	| /*empty*/	{$$ = NULL;}
	;

Id: ID			{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$=str;}
	| /*empty*/	{$$="";}
	;

Declaration: Dec SEMI	{$$=$1;}
	;

Dec: TypeSpec DeclaratorEnum 	{$$ = insert_Variable_Declaration($1 , $2);}
	| error	%prec ERROR		 {$$ = insert_Variable_Declaration("" , NULL); opt = 0;}
	;
	
DeclaratorEnum: ID Assign COMMA DeclaratorEnum		{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$ = insert_Declarator_list(str, $2, $4);}
	| ID COMMA DeclaratorEnum			{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$ = insert_Declarator_list(str, NULL, $3);}
	| ID						{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$ = insert_Declarator_list(str, NULL, NULL);}
	| ID Assign					{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$ = insert_Declarator_list(str, $2, NULL);}
	;

TypeSpec: CHAR 		{$$ = "Char";}
	| INT 		{$$ = "Int";}
	| VOID 		{$$ = "Void";}
	| SHORT 	{$$ = "Short";}
	| DOUBLE	{$$ = "Double";}
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

Return: RETURN Expr SEMI	{$$ = insert_Return($2);}
	| RETURN SEMI		{$$ = insert_Return(NULL);}
	;

IfElse: ELSE Statement	{$$ = insert_Else($2);}
	| %prec Y/*empty*/	{$$ = insert_Else(NULL);}
	;

StatementList: StatementList Statement	{$$ = insert_StatList($2, $1);}
	| Statement			{$$ = insert_StatList($1, NULL);}
	;

Expr: Operator			{$$ = insert_Expression("op", $1, NULL, NULL, NULL, NULL, NULL, "");}
	| Plus			{$$ = insert_Expression("plus", NULL, NULL, NULL, $1, NULL, NULL, "");}
	| Minus			{$$ = insert_Expression("minus", NULL, NULL, $1, NULL, NULL, NULL, "");}
	| Not			{$$ = insert_Expression("not", NULL, $1, NULL, NULL, NULL, NULL, "");}
	| ID			{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$ = insert_Expression("id", NULL, NULL, NULL, NULL, NULL, NULL, str);}
	| ID LPAR Expr RPAR	{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$ = insert_Expression("call", NULL, NULL, NULL, NULL, NULL, $3, str);}
	| ID LPAR RPAR		{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$ = insert_Expression("call", NULL, NULL, NULL, NULL, NULL, NULL, str);}
	| ID LPAR error RPAR	{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "Id(%s)", $1); $$ = insert_Expression("error", NULL, NULL, NULL, NULL, NULL, NULL, str); opt = 0;}
	| Terminal		{$$ = insert_Expression("term", NULL, NULL, NULL, NULL, $1, NULL, "");}
	| LPAR Expr RPAR	{$$ = insert_Expression("ex", NULL, NULL, NULL, NULL, NULL, $2, "");}
	| LPAR error RPAR 	{$$ = insert_Expression("error", NULL, NULL, NULL, NULL, NULL, NULL, ""); opt = 0;}
	;

Terminal: INTLIT 		{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "IntLit(%s)", $1); $$ = insert_Terminal(str);}
	| CHRLIT 		{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "ChrLit(%s)", $1); $$ = insert_Terminal(str);}
	| REALLIT 		{char* str=(char*)malloc(50*sizeof(char)); sprintf(str, "RealLit(%s)", $1); $$ = insert_Terminal(str);}
	;


Not: NOT Expr	%prec NOT	{$$ = insert_Not($2);};
Minus: MINUS Expr %prec NOT	{$$ = insert_Minus($2);};
Plus: PLUS Expr	%prec NOT	{$$ = insert_Plus($2);};


Operator: Expr Assign		{$$= insert_Operator("Store", $1, $2);}
	| Expr COMMA Expr	{$$= insert_Operator("Comma", $1, $3);}
	| Expr PLUS Expr	{$$= insert_Operator("Add", $1, $3);}
	| Expr MINUS Expr	{$$= insert_Operator("Sub", $1, $3);}
	| Expr MUL Expr		{$$= insert_Operator("Mul", $1, $3);}
	| Expr DIV Expr		{$$= insert_Operator("Div", $1, $3);}
	| Expr MOD Expr		{$$= insert_Operator("Mod", $1, $3);}
	| Expr OR Expr		{$$= insert_Operator("Or", $1, $3);}
	| Expr AND Expr		{$$= insert_Operator("And", $1, $3);}
	| Expr BITWISEAND Expr	{$$= insert_Operator("BitWiseAnd", $1, $3);}
	| Expr BITWISEOR Expr	{$$= insert_Operator("BitWiseOr", $1, $3);}
	| Expr BITWISEXOR Expr	{$$= insert_Operator("BitWiseXor", $1, $3);}
	| Expr EQ Expr		{$$= insert_Operator("Eq", $1, $3);}
	| Expr NE Expr		{$$= insert_Operator("Ne", $1, $3);}
	| Expr LE Expr		{$$= insert_Operator("Le", $1, $3);}
	| Expr GE Expr		{$$= insert_Operator("Ge", $1, $3);}
	| Expr LT Expr		{$$= insert_Operator("Lt", $1, $3);}
	| Expr GT Expr		{$$= insert_Operator("Gt", $1, $3);}
	;
Assign: ASSIGN Expr {$$=$2;};
%%

void yyerror ( char * s ) {
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


