
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "llvm.h"
#include "AST_structures.h"


void ConvertType(char* TypeSpec){
	if(!strcmp(TypeSpec, "Int") || !strcmp(TypeSpec, "Char") || !strcmp(TypeSpec, "Short")) printf("i32"); 
	else if(!strcmp(TypeSpec, "Double")) printf("double");
}

void GetType(char* str){
	if( str[0] =='c' || str[0]=='i' || str[0] == 's') printf("i32");
	else printf("double");
	
}

void ConvertId(char* id){
	char* str2 = id;
	printf("%s%s", "%", str2);
}

void ConvertIdF(char* id){
	char* str2 = id;
	printf("%s", str2);
}

void Convert_Program(Program* node) // feito
{
	if(node==NULL) return;
	printf("declare i32 @putchar(i32)\n");
	printf("declare i32 @getchar()\n\n");
	
	int OpNumber = 1;
	char* str = ""; 
	Convert_Function_And_Declaration_list(str, node->list, &OpNumber);
}

void Convert_Function_And_Declaration_list(char* str, Function_And_Declaration_list* node, int* OpNumber) // feito
{	
	if(node==NULL) return;
        Function_And_Declaration_list* tmp= node;

	while(tmp!=NULL){
		Convert_Fad(str, tmp->fad, OpNumber);
		tmp= tmp->next;
	}
}

void Convert_Fad(char* str, Fad* node, int* OpNumber) // feito
{
        if(node==NULL) return;

		if(!strcmp(node->type, "fdef")){
			Convert_Function_Definition(str, node->fdef, OpNumber);
		}
		else if(!strcmp(node->type, "fdec")){
			Convert_Function_Declaration(str, node->fdec, OpNumber);
			printf("\n");
		}
		else{
			Convert_Variable_Declaration(str, node->vdec, OpNumber);
		}
}

void Convert_Variable_Declaration(char* str, Variable_Declaration* node, int* OpNumber) //feito
{
	if(node==NULL) return;
	
	Declarator_list* tmp;
	tmp = node->list;
	do{
		
		if(tmp!=NULL) Convert_Expression(str, tmp->ex, 1, OpNumber);
		Convert_Declarator_list(str, tmp, OpNumber);
		ConvertType(node->TypeSpec);
		printf(", i32 1\n");
		if(tmp!=NULL){
			if(tmp->ex!=NULL){
				printf("%sstore ", str);
				ConvertType(node->TypeSpec);
				printf(" %s%d, ", "%", *OpNumber-1);
				ConvertType(node->TypeSpec);
				printf("* ");
				ConvertId(tmp->id);
				printf("\n");
				
			}
		}
		printf("\n");
		tmp = tmp->next;
	}while(tmp!=NULL);
}

void Convert_Declarator_list(char* str, Declarator_list* node, int* OpNumber) // feito
{
	if(node==NULL) return;
	printf("%s",str);
	ConvertId(node->id);
	printf(" = alloca ");
}

void Convert_Function_Declaration(char* str, Function_Declaration* node, int* OpNumber)
{
	if(node==NULL) return;
	
	Convert_Function_Declarator(str, node->fd, OpNumber);
}

void Convert_Paramlist(char* str, Paramlist* node, int* OpNumber) // feito
{
	if(node==NULL) return;	
	Convert_ParamDeclaration(str, node->list, OpNumber);
}

void Convert_ParamDeclaration(char* str, ParamDeclaration* node, int* OpNumber) //feito
{
	if(node==NULL) return;
        ParamDeclaration* tmp= node;

	while(tmp!=NULL){
		ConvertType(node->TypeSpec);
		if(strcmp(node->TypeSpec,"Void")){
			printf(" ");
			ConvertId(node->id);
			if(tmp->next!=NULL) printf(", ");
		}
		
		tmp= tmp->next;
	}
}

void Convert_Function_Definition(char* str, Function_Definition* node, int* OpNumber) //feito
{
	if(node==NULL) return;
	printf("%sdefine ", str);
	ConvertType(node->TypeSpec);
	printf(" ");
	
	Convert_Function_Declarator(str, node->fd, OpNumber);
	printf("{\n");
	printf("\n");

	char* str2 = (char*)malloc(sizeof(str)+1*sizeof(char));
	sprintf(str2, "  %s", str);

	Convert_FuncBody(str2, node->fb, OpNumber);
	printf("%s}\n", str);

	free(str2);
}

void Convert_Function_Declarator(char* str, Function_Declarator* node, int* OpNumber) //feito
{
	if(node==NULL) return;

	printf("%s@", str);
	ConvertIdF(node->id);
	
	printf("(");
	Convert_Paramlist(str, node->list, OpNumber);
	printf(")");
}

void Convert_FuncBody(char* str, FuncBody* node, int* OpNumber) // feito
{
	if(node==NULL) return;
	//int* i = (int*)malloc(sizeof(int));
	int i = 0;
	Convert_Declarations_And_Statements(str, node->list, &i, OpNumber);
}

void Convert_Declarations_And_Statements(char* str, Declarations_And_Statements* node, int* count, int* OpNumber) // feito
{
	if(node==NULL)return;
	Declarations_And_Statements* tmp= node;
	
	while(tmp!=NULL){
		Convert_Das(str, tmp->das, count, OpNumber);
		tmp= tmp->next;
	}
}

void Convert_Das(char* str, Das* node, int* count, int* OpNumber) // feito
{
	if(node==NULL) return;
	if(!strcmp(node->type, "dec")){
			Convert_Variable_Declaration(str, node->dec, OpNumber);
		}
		else{
			Convert_Stat(str, node->s, count, OpNumber);
		}
}

void Convert_Stat(char* str, Stat* node, int* count, int* OpNumber)
{
	if(node==NULL) return;
	
		if(!strcmp(node->type, "if_")){
			Convert_If(str, node->if_, count, OpNumber);
		}
		else if(!strcmp(node->type, "while_")){
			Convert_While(str, node->while_, count, OpNumber);
		}
		else if(!strcmp(node->type, "list")){
			Convert_StatList(str, node->list, count, OpNumber);
		}
		else if(!strcmp(node->type, "ex")){
			Convert_Expression(str, node->ex, 1, OpNumber);
		}
		else{
			Convert_Return(str, node->return_, OpNumber);
		}
}

void Convert_StatList(char* str, StatList* node, int* count, int* OpNumber)
{
	if(node==NULL) return;
	StatList* tmp = node;

	while(tmp!=NULL){
		Convert_Stat(str, tmp->s, count, OpNumber);
		tmp= tmp->next;
	}
	
}

void Convert_If(char* str, If* node, int* count, int* OpNumber)
{
	if(node==NULL) return;
	int i = *count;
	(*count)++;

	Convert_Expression(str, node->ex, 1, OpNumber);
	printf("\n");
	printf("%s%s%d = icmp ne i32 0, %s%d\n", str, "%", *OpNumber, "%", *OpNumber-1);
	printf("%sbr i1 %s%d, label %sthen%d, label %selse%d\n\n", str, "%", *OpNumber, "%", i ,"%", i);
	(*OpNumber)++;

	printf("%sthen%d:\n", str, i);
	
	char* str2 = (char*)malloc(sizeof(str)+1*sizeof(char));
	sprintf(str2, "  %s", str);

	if(node->s==NULL){
		
		
	}
	else{
		Convert_Stat(str2, node->s, count, OpNumber);
	}
	printf("%sbr label %sifcont%d\n", str2, "%", i);
	printf("\n");

	printf("%selse%d:\n", str, i);
	if(node->else_->s==NULL){ 
		
	}
	else{
		Convert_Else(str2, node->else_, count, OpNumber);
	}
	printf("%sbr label %sifcont%d\n", str2, "%", i);
	printf("\n");
	printf("%sifcont%d:\n", str, i);
}

void Convert_Else(char* str, Else* node, int* count, int* OpNumber)
{
	if(node==NULL) return;

	Convert_Stat(str, node->s, count, OpNumber);
}


void Convert_While(char* str, While* node, int* count, int* OpNumber)
{
	if(node==NULL) return;
	int i = *count;
	(*count)++;

	printf("%sbr label %swhile%d\n", str, "%", i);
	printf("%swhile%d:\n", str, i);

	char* str2 = (char*)malloc(sizeof(str)+1*sizeof(char));
	sprintf(str2, "  %s", str);

	Convert_Expression(str2, node->ex, 1, OpNumber);
	printf("\n");
	printf("%s%s%d = icmp eq i1 0, %s%d\n", str2, "%", *OpNumber, "%", *OpNumber-1);
	printf("%sbr i1 %s%d, label %sbreak%d, label %sthen%d\n", str2, "%", *OpNumber, "%", i, "%", i);
	printf("%sthen%d:\n", str2, i);
	(*OpNumber)++;
	printf("\n");
	
	if(node->s==NULL){
		
	}
	Convert_Stat(str2, node->s, count, OpNumber);

	printf("%sbr label %swhile%d\n", str2, "%", i);
	printf("\n");
	printf("%sbreak%d:\n", str, i);
}

void Convert_Return(char* str, Return* node, int* OpNumber)
{

	if(node==NULL) return;
	Convert_Expression(str, node->ex, 1, OpNumber);
	if(node->ex==NULL) return;
	if(node->ex->tipo[0]=='i' || node->ex->tipo[0]=='c' || node->ex->tipo[0]=='s') printf("%sret i32 %s%d\n", str, "%", *OpNumber-1);
	else printf("%sret double %s%d\n", str, "%", *OpNumber-1);

}

char* Convert_Expression(char* str, Expression* node, int flag, int* OpNumber)
{
	if(node==NULL) return "";
	
	if(!strcmp(node->type, "op")){
		char* s = Convert_Operator(str, node->op, flag, OpNumber);
		if(!flag) return s;
		
	}
	else if(!strcmp(node->type, "not")){
		Convert_Not(str, node->not, flag, OpNumber);
	}
	else if(!strcmp(node->type, "minus")){
		Convert_Minus(str, node->minus, flag, OpNumber);
	}
	else if(!strcmp(node->type, "plus")){
		Convert_Plus(str, node->plus, flag, OpNumber);
	}
	else if(!strcmp(node->type, "id")){
		if(node->tipo[0]=='i' || node->tipo[0]=='c' || node->tipo[0]=='s')printf("%s%s%d = load i32, i32* ", str, "%", *OpNumber);
		else
		ConvertId(node->id);
		printf("\n");
		//if(!flag) printf("%s%sv%d = add i32 0, %s1\n", str, "%", count, "%");
		(*OpNumber)++;

	}
	else if(!strcmp(node->type, "ex")){
		Convert_Expression(str, node->ex, 1, OpNumber);
	}
	else if(!strcmp(node->type, "call")){
		char* s = Convert_Expression(str, node->ex, 0, OpNumber);
		if(node->tipo[0]=='i' || node->tipo[0]=='c' || node->tipo[0]=='s') printf("%s%s%d = call i32 @", str, "%", *OpNumber);
		else printf("%s%s%d = call double @", str, "%", *OpNumber);
		ConvertIdF(node->id);
		printf("(%s)\n", s);
		(*OpNumber)++;
	}
	else if(!strcmp(node->type, "term")){
		Convert_Terminal(str, node->term, flag, OpNumber);
	}
	char* s = (char*)malloc(sizeof(char)*10);//erro
	if(node->tipo2[0]=='i' || node->tipo2[0]=='c' || node->tipo2[0]=='s') sprintf(s,"i32 %s%d", "%", *OpNumber-1);
	else if(node->tipo[0]!='v') sprintf(s,"double %s%d", "%", *OpNumber-1);
	return s;
}

char* Convert_Operator(char* str, Operator* node, int flag, int* OpNumber)
{
	if(node==NULL) return "";
	int exp1, exp2;	
	char* s="";
	char*s2="";
	if(!strcmp(node->type, "Comma")){
		if(!flag){
			s = Convert_Expression(str, node->ex1, flag, OpNumber);
			exp1 = *OpNumber-1;
			s2 = Convert_Expression(str, node->ex2, 1, OpNumber);
			(*OpNumber)--;
			exp2 = *OpNumber-1;
			char* s3 = (char*)malloc(sizeof(s)+sizeof(s2)+ 2*sizeof(char));
			sprintf(s3,"%s, %s", s, s2);
			s = s3;
		}
		else{
			Convert_Expression(str, node->ex1, flag, OpNumber);
			exp1 = *OpNumber-1;
			Convert_Expression(str, node->ex2, flag, OpNumber);
			exp2 = *OpNumber-1;
		}
	}else{
		if(!strcmp(node->type, "Store")){
			Convert_Expression(str, node->ex2, 1, OpNumber);
			(*OpNumber)--;
		}
		else{
			Convert_Expression(str, node->ex1, 1, OpNumber);
			exp1 = *OpNumber-1;
			Convert_Expression(str, node->ex2, 1, OpNumber);
			exp2 = *OpNumber-1;
		}
	}
	if(node->tipo[0]=='i' || node->tipo[0]=='c' || node->tipo[0]=='s'){
	if(!strcmp(node->type, "Store")){ printf("%sstore i32 %s%d, i32* ", str, "%", *OpNumber); ConvertId(node->ex1->id); printf("\n");}
	else if(!strcmp(node->type, "Add")) printf("%s%s%d = add i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Sub")) printf("%s%s%d = sub i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Mul")) printf("%s%s%d = mul i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Div")) printf("%s%s%d = div i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "BitWiseAnd")) printf("%s%s%d = and i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "BitWiseOr")) printf("%s%s%d = or i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Eq")) printf("%s%s%d = icmp eq i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Ne")) printf("%s%s%d = icmp ne i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Le")) printf("%s%s%d = icmp sle i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Ge")) printf("%s%s%d = icmp sge i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Lt")) printf("%s%s%d = icmp slt i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Gt")) printf("%s%s%d = icmp sgt i32 %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);	
	}
	else{
	if(!strcmp(node->type, "Store")){ printf("%sstore double %s%d, double* ", str, "%", *OpNumber); ConvertId(node->ex1->id); printf("\n");}
	else if(!strcmp(node->type, "Add")) printf("%s%s%d = add double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Sub")) printf("%s%s%d = sub double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Mul")) printf("%s%s%d = mul double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Div")) printf("%s%s%d = div double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "BitWiseAnd")) printf("%s%s%d = and double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "BitWiseOr")) printf("%s%s%d = or double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Eq")) printf("%s%s%d = icmp eq double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Ne")) printf("%s%s%d = icmp ne double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Le")) printf("%s%s%d = icmp sle double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Ge")) printf("%s%s%d = icmp sge double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Lt")) printf("%s%s%d = icmp slt double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	else if(!strcmp(node->type, "Gt")) printf("%s%s%d = icmp sgt double %s%d, %s%d\n", str, "%", *OpNumber, "%", exp1, "%", exp2);
	}
	//if(!flag) printf("%s%sv%d = add i32 0, %s1\n", str, "%", count, "%");
	(*OpNumber)++;
	return s;
}

void Convert_Not(char* str, Not* node, int flag, int* OpNumber)
{
	if(node==NULL) return;
	Convert_Expression(str, node->ex, 1, OpNumber);

	printf("%s%s%d = icmp eq i1 0, %s%d\n", str, "%", *OpNumber, "%", *OpNumber-1);
	//if(!flag) printf("%s%sv%d = add i32 0, %s1\n", str, "%", count, "%");
	(*OpNumber)++;
}

void Convert_Minus(char* str, Minus* node, int flag, int* OpNumber)
{
	if(node==NULL) return;
	Convert_Expression(str, node->ex, 1, OpNumber);

	if(node->tipo[0]=='i' || node->tipo[0]=='c' || node->tipo[0]=='s')printf("%s%s%d = sub i32 0, %s%d\n", str, "%", *OpNumber, "%", *OpNumber);
	else printf("%s%s%d = double i32 0, %s%d\n", str, "%", *OpNumber, "%", *OpNumber);
	//if(!flag) printf("%s%sv%d = add i32 0, %s1\n", str, "%", count, "%");
	(*OpNumber)++;
}

void Convert_Plus(char* str, Plus* node, int flag, int* OpNumber)
{
	if(node==NULL) return;
	Convert_Expression(str, node->ex, 1, OpNumber);

	if(node->tipo[0]=='i' || node->tipo[0]=='c' || node->tipo[0]=='s') printf("%s%s%d = sub i32 0, %s%d\n", str, "%", *OpNumber, "%", *OpNumber-1);
	else printf("%s%s%d = sub double 0, %s%d\n", str, "%", *OpNumber, "%", *OpNumber-1);
	//if(!flag) printf("%s%sv%d = add i32 0, %s1\n", str, "%", count, "%");
	(*OpNumber)++;
}

void Convert_Terminal(char* str, Terminal* node, int flag, int* OpNumber)
{
	if(node==NULL) return;
	printf("%s%s%d = add ", str, "%", *OpNumber);
	if(node->type[0]=='I' || node->type[0]=='C'){ 
		printf("i32 0, ");
		ConvertIdF(&(node->type[4]));
	}
	else{
		printf("double 0, ");
		ConvertIdF(&(node->type[4]));
	}
	printf("\n");
	//if(!flag) printf("%s%sv%d = add i32 0, %s1\n", str, "%", count, "%");
	(*OpNumber)++;	
}

