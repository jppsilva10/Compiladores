

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include "AST_structures.h"



Program* insert_Program(Function_And_Declaration_list* list)

{

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



Variable_Declaration* insert_Variable_Declaration(char* TypeSpec, Declarator_list* list, int c, int l)

{

	Variable_Declaration* node=(Variable_Declaration*)malloc(sizeof(Variable_Declaration));
	
	node->l = l;
	node->c = c;

	if(TypeSpec[0])TypeSpec[0] += ('A'-'a');
	node->TypeSpec = TypeSpec;

	node->list = list;



	return node;

}



Declarator_list* insert_Declarator_list(char* id, Expression* ex, Declarator_list* head, int c, int l)

{

        Declarator_list* node = (Declarator_list*)malloc(sizeof(Declarator_list));

	node->c = c;
	
	node->l = l;

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


	if(TypeSpec[0])TypeSpec[0] += ('A'-'a');
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



ParamDeclaration* insert_ParamDeclaration(char* TypeSpec, char* id, ParamDeclaration* head, int c, int l)

{

        ParamDeclaration* node = (ParamDeclaration*)malloc(sizeof(ParamDeclaration));

	node->l = l;
	node->c = c;

	if(TypeSpec[0])TypeSpec[0] += ('A'-'a');
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

	if(TypeSpec[0])TypeSpec[0] += ('A'-'a');
	node->TypeSpec = TypeSpec;



	return node;

}



Function_Declarator* insert_Function_Declarator(char* id, Paramlist* list,int c,int l)

{

	Function_Declarator* node=(Function_Declarator*)malloc(sizeof(Function_Declarator));

	node->c = c;
	
	node->l = l;

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



Return* insert_Return(Expression* ex, int c, int l)

{

	Return* node=(Return*)malloc(sizeof(Return));

	node->l = l;
	node->c = c;
	
	if(ex !=NULL){
		node->l = ex->l;
		node->c = ex->c;
	}

	node->ex= ex;



	return node;

}



Expression* insert_Expression(char* type, Operator* op, Not* not, Minus* minus, Plus* plus, Terminal* term, Expression* ex, char* id, int c, int l)

{

	Expression* node=(Expression*)malloc(sizeof(Expression));
	node->type= type;
	node->tipo = "";
	node->tipo2 = "";

	if(!strcmp(node->type,"plus"))
	{
		node->l = plus->l;
		node->c = plus->c;
	}
	
	else if(!strcmp(node->type,"minus"))
	{
		node->l = minus->l;
		node->c = minus->c;
	}
	
	
	else if(!strcmp(node->type,"not"))
	{
		node->l = not->l;
		node->c = not->c;
	}
	
	else if(!strcmp(node->type,"op"))
	{
		node->l = op->l;
		node->c = op->c;
	}
	else if(!strcmp(node->type,"ex")){
		node->l = ex->l;
		node->c = ex->c;
	}
	else if(!strcmp(node->type,"term")){
		node->l = term->l;
		node->c = term->c;
	}
	else {
		node->l = l;
		node->c = c;
	} 


	node->op= op;

	node->not= not;

	node->minus= minus;

	node->plus= plus;

	node->term= term;

	node->id= id;

	node->ex= ex;



	return node;

}



Operator* insert_Operator(char* type, Expression* ex1, Expression* ex2, int c, int l)

{

	Operator* node=(Operator*)malloc(sizeof(Operator));
	node->tipo = "";

	node->c = c;
	
	node->l = l;

	node->type= type;

	node->ex1= ex1;

	node->ex2= ex2;



	return node;

}



Not* insert_Not(Expression* ex,int c, int l)

{

	Not* node=(Not*)malloc(sizeof(Not));
	node->tipo = "";

	node->c = c;
	
	node->l = l;

	node->ex= ex;



	return node;

}



Minus* insert_Minus(Expression* ex,int c, int l)

{

	Minus* node=(Minus*)malloc(sizeof(Minus));
	node->tipo = "";

	node->c = c;
	
	node->l = l;

	node->ex= ex;



	return node;

}



Plus* insert_Plus(Expression* ex,int c,int l)

{

	Plus* node=(Plus*)malloc(sizeof(Plus));
	node->tipo = "";

	node->c = c;
	
	node->l = l;

	node->ex= ex;



	return node;

}



Terminal* insert_Terminal(char* type, int c, int l)

{

	Terminal* node=(Terminal*)malloc(sizeof(Terminal));
	node->tipo = "";

	node->c = c;
	
	node->l = l;

	node->type= type;



	return node;

}



void print_ponto(int n){
	for(int i =0; i<n; i++){
	printf(".");
	}
}
void print_Program(Program* node, int option)
{
	if(!option) return;
	if(node==NULL) return;
	if(option) printf("Program\n");
	int i = 2;
	print_Function_And_Declaration_list(i, node->list, option);
	//free(str);
	free(node);
}

void print_Function_And_Declaration_list(int i, Function_And_Declaration_list* node, int option)
{	
	if(node==NULL) return;
        Function_And_Declaration_list* tmp= node;
	Function_And_Declaration_list* tmp2= node;

	while(tmp!=NULL){
		print_Fad(i, tmp->fad, option);
		tmp2 = tmp;
		tmp= tmp->next;
		free(tmp2);
	}
}

void print_Fad(int i, Fad* node, int option)
{
        if(node==NULL) return;

		if(!strcmp(node->type, "fdef")){
			print_Function_Definition(i, node->fdef, option);
		}
		else if(!strcmp(node->type, "fdec")){
			print_Function_Declaration(i, node->fdec, option);
		}
		else{
			print_Variable_Declaration(i, node->vdec, option);
		}
	free(node);
}

void print_Variable_Declaration(int i, Variable_Declaration* node, int option)
{
	if(node==NULL) return;
	
	i+=2;

	Declarator_list* tmp;
	
	do{
		if(option){print_ponto(i-2); printf("Declaration\n");}
		if(option){print_ponto(i); printf("%s\n",node->TypeSpec);}
		//Declarator_list* tmp = node->list;
		//for(tmp->next!=NULL);
		print_Declarator_list(i, node->list, option);
		tmp = node->list;
		node->list = node->list->next;
		free(tmp);
	}while(node->list!=NULL);
	
	//free(str2);
}

void print_Declarator_list(int i, Declarator_list* node, int option)
{
	if(node==NULL) return;
	
		if(option){print_ponto(i); printf("Id(%s)\n" ,node->id);}
		print_Expression(i, node->ex, option, 1);
	
}

void print_Function_Declaration(int i, Function_Declaration* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("FuncDeclaration\n");}
	i+=2;
	if(option){
		print_ponto(i);
		printf("%s\n", node->TypeSpec);
		
	}
	
	print_Function_Declarator(i, node->fd, option);
	//free(str2);
	free(node);
}

void print_Paramlist(int i, Paramlist* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("ParamList\n");}

	i+=2;	
	print_ParamDeclaration(i, node->list, option);
	//free(str2);
	free(node);
}

void print_ParamDeclaration(int i, ParamDeclaration* node, int option)
{
	if(node==NULL) return;
        ParamDeclaration* tmp= node;
	ParamDeclaration* tmp2;
	
	i+=2;

	while(tmp!=NULL){
		if(option){
			print_ponto(i-2);
			printf("ParamDeclaration\n");
			print_ponto(i);
			printf("%s\n", tmp->TypeSpec);
			if(strcmp(tmp->id,"")){print_ponto(i); printf("Id(%s)\n", tmp->id); } //
		}
		tmp2 = tmp;
		tmp= tmp->next;
		free(tmp2);
	}
	//free(str2);
}

void print_Function_Definition(int i, Function_Definition* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("FuncDefinition\n");}

	i+=2;
	if(option){
		print_ponto(i);
		printf("%s\n", node->TypeSpec);
	}
	print_Function_Declarator(i, node->fd, option);
	print_FuncBody(i, node->fb, option);
	//free(str2);
	free(node);
}

void print_Function_Declarator(int i, Function_Declarator* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("Id(%s)\n", node->id);}

	print_Paramlist(i, node->list, option);
	//free(str2);
	free(node);
}

void print_FuncBody(int i, FuncBody* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("FuncBody\n");}

	i+=2;
	print_Declarations_And_Statements(i, node->list, option);
	//free(str2);
	free(node);
}

void print_Declarations_And_Statements(int i, Declarations_And_Statements* node, int option)
{
	if(node==NULL)return;
	Declarations_And_Statements* tmp= node;
	Declarations_And_Statements* tmp2;
	
	while(tmp!=NULL){
		print_Das(i, tmp->das, option);
		tmp2 = tmp;
		tmp= tmp->next;
		free(tmp2);
	}
}

void print_Das(int i, Das* node, int option)
{
	if(node==NULL) return;
	if(!strcmp(node->type, "dec")){
			print_Variable_Declaration(i, node->dec, option);
		}
		else{
			print_Stat(i, node->s, option);
		}
	free(node);
}

void print_Stat(int i, Stat* node, int option)
{
	if(node==NULL) return;
	
		if(!strcmp(node->type, "if_")){
			print_If(i, node->if_, option);
		}
		else if(!strcmp(node->type, "while_")){
			print_While(i, node->while_, option);
		}
		else if(!strcmp(node->type, "list")){
			if(node->list==NULL){
				if(option){print_ponto(i); printf("Null\n");}
			}
			print_StatList(i, node->list, option);
		}
		else if(!strcmp(node->type, "ex")){
			print_Expression(i, node->ex, option, 1);
		}
		else{
			print_Return(i, node->return_, option);
		}
	//free(str2);
	free(node);
}

void print_StatList(int i, StatList* node, int option)
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
		if(option){print_ponto(i); printf("Null\n");}
		return;
	}
	if(count>1){ 
	print_ponto(i);
	printf("StatList\n");
	
	i+=2;
	}
	while(tmp!=NULL){
		print_Stat(i, tmp->s, option);
		tmp2=tmp;
		tmp= tmp->next;
		free(tmp2);
	}
	
}

void print_If(int i, If* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("If\n");}
	
	i+=2;
	
	//str=str2;

	print_Expression(i, node->ex, option, 1);
	
	if(node->s==NULL){
		if(option){print_ponto(i-2); printf("..Null\n");}
		
	}
	else{
		print_Stat(i, node->s, option);
	}
	if(node->else_->s==NULL){ 
		if(option){
			print_ponto(i-2);
			printf("..Null\n");
		}
	}
	else{
		print_Else(i, node->else_, option);
	}
	//free(str2);
	free(node);
}

void print_Else(int i, Else* node, int option)
{
	if(node==NULL) return;
	
	//if(option){if(node->s==NULL) printf("%sNull\n", str);}
	
	print_Stat(i, node->s, option);
	//free(str2);
	free(node);
}


void print_While(int i, While* node, int option)
{
	if(node==NULL) return;

	if(option){print_ponto(i); printf("While\n");}

	i+=2;
	//str=str2;

	print_Expression(i, node->ex, option, 1);
	
	if(node->s==NULL){
		if(option){print_ponto(i-2); printf("..Null\n");}
		free(node);
		return;
	}
	print_Stat(i, node->s, option);
	//free(str2);
	free(node);
}

void print_Return(int i, Return* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i), printf("Return\n");}

	i+=2;

	if(option){if(node->ex==NULL){print_ponto(i); printf("Null\n");}}
	print_Expression(i, node->ex, option, 1);
	//free(str2);
	free(node);
}

void print_Expression(int i, Expression* node, int option, int flag)
{
	if(node==NULL) return;
	if(!strcmp(node->type, "op")){
		print_Operator(i, node->op, option, flag);
	}
	else if(!strcmp(node->type, "not")){
		print_Not(i, node->not, option);
	}
	else if(!strcmp(node->type, "minus")){
		print_Minus(i, node->minus, option);
	}
	else if(!strcmp(node->type, "plus")){
		Print_Plus(i, node->plus, option);
	}
	else if(!strcmp(node->type, "id")){
		if(option){print_ponto(i); printf("Id(%s)", node->id);if(node->tipo[0]) printf(" - %s", node->tipo); printf("\n");}
	}
	else if(!strcmp(node->type, "ex")){
		print_Expression(i, node->ex, option, 1);
	}
	else if(!strcmp(node->type, "call")){
		if(option){print_ponto(i); printf("Call"); if(node->tipo[0]) printf(" - %s", node->tipo); printf("\n");}
		i+=2;
		if(option){print_ponto(i); printf("Id(%s)", node->id); if(node->tipo2[0]) printf(" - %s", node->tipo2); printf("\n");}
		print_Expression(i, node->ex, option, 0);
	}
	else if(!strcmp(node->type, "term")){
		print_Terminal(i, node->term, option);
	}
	free(node);
}

void print_Operator(int i, Operator* node, int option, int flag)
{
	if(node==NULL) return;
			
	if(!strcmp(node->type, "Comma")){
		if(flag){
			if(option){print_ponto(i); printf("%s", node->type);if(node->tipo[0]) printf(" - %s", node->tipo); printf("\n");}
			i+=2;
		}
	}else{
		if(option){print_ponto(i); printf("%s", node->type);if(node->tipo[0]) printf(" - %s", node->tipo); printf("\n");}
		flag=1;
		i+=2;
	}
	

	print_Expression(i, node->ex1, option, flag);
	print_Expression(i, node->ex2, option, flag);
	//free(str2);
	free(node);
}

void print_Not(int i, Not* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("Not"); if(node->tipo[0]) printf(" - %s", node->tipo); printf("\n");}

	i+=2;
	print_Expression(i, node->ex, option, 1);
	//free(str2);
	free(node);
}

void print_Minus(int i, Minus* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("Minus");if(node->tipo[0]) printf(" - %s", node->tipo); printf("\n");}

	i+=2;
	print_Expression(i, node->ex, option, 1);
	//free(str2);
	free(node);
}

void Print_Plus(int i, Plus* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("Plus");if(node->tipo[0]) printf(" - %s", node->tipo); printf("\n");}

	i+=2;
	print_Expression(i, node->ex, option, 1);
	//free(str2);
	free(node);
}

void print_Terminal(int i, Terminal* node, int option)
{
	if(node==NULL) return;
	if(option){print_ponto(i); printf("%s", node->type); if(node->tipo[0]) printf(" - %s", node->tipo); printf("\n");}
	free(node);
}
