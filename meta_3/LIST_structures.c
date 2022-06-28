#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LIST_structures.h"
#include "AST_structures.h"

int hash(char* var, declaration_node* tabela[], int len){
	int Hash = 0;
	for (char* aux = var; *aux!=0; aux++) {
		Hash = ((Hash << 5) - Hash) + *aux; 
		Hash = Hash & Hash; 
	} 
	if (Hash<0) Hash *=-1;
	Hash = Hash % len;
	while(tabela[Hash]!=NULL){
		if(!strcmp(tabela[Hash]->dec.nome, var)) return Hash; 
		Hash+=1;
		Hash = Hash % len;
	}
	return Hash; 
	//remover
}

void compareArg(environment_node* env, char* args, Expression* ex, int l, int c, char* nome){
	declaration_list* tmp = NULL;
	if(env!=NULL) tmp = env->list;
	int a1 = 0;
	int a2 = 0;
	while(tmp!=NULL){
		
		if(!(tmp->dec->dec.param) || tmp->dec->dec.tipo[0] == 'v') break;
		a1++;
		tmp=tmp->next;
	}
	while(*args){
		a2++;
		while((*args) && (*args)!=','){ args++;}
		if(*args) args ++;
	}
	if(a1!=a2) printf("Line %d, col %d: Wrong number of arguments to function %s (got %d, required %d)\n", l, c, nome, a2, a1);
}

char* get_args(environment_node* env){
	declaration_list* tmp = env->list;
	char* str = tmp->dec->dec.tipo;
	char* str2;
	tmp = tmp->next;
	while(tmp!=NULL){
		str2 = (char*)malloc(sizeof(str) + sizeof(tmp->dec->dec.tipo) + sizeof(char));
		sprintf(str2, "%s,%s", str, tmp->dec->dec.tipo);
		if(tmp->dec->dec.param){ str = str2;}
		else break;
		tmp = tmp->next;
	}
	return str;
}

char* get_args2(ParamDeclaration* node){
	ParamDeclaration* tmp= node;
	char* args="";
	char* args2;
	int error=0;
	while(tmp!=NULL){
		char* str;
		if(tmp->id[0]!=0){
			str = tmp->id;
		}
		else{
			
			str= "";
		}
		char* str2 = (char*) strdup(tmp->TypeSpec);
		str2[0] = str2[0] + ('a'-'A'); // passar a minuscula
		
		if((str2[0] == 'v' && str[0]!=0) || (str2[0] == 'v' && args[0]!=0) || (str2[0] == 'v' && tmp->next!=NULL)){
			//... remover void se nada
			printf("Line %d, col %d: Invalid use of void type in declaration\n", tmp->l, tmp->c);
			error=1;
		}
		args2 = (char*)malloc(sizeof(str2) + sizeof(args) + sizeof(char));
		if(args[0]!=0) sprintf(args2, "%s,%s", args, str2);
		else sprintf(args2, "%s", str2);
		args = args2;
		tmp= tmp->next;
	}
	if (error){ return "";}
	return args;
}

declaration new_declaration(char* nome, char* tipo){
	declaration dec;
	dec.nome = nome;
	dec.tipo = tipo;
	dec.param = 0;
	dec.notified = 0;
	return dec;
}

environment new_environment(char* nome, char* ret){
	environment env;
	env.nome = nome;
	env.ret = ret;
	return env;
}

void insert_environment(environment_list* header, char* nome, char* ret){
	
	environment_node* node = (environment_node*) malloc(sizeof(environment_node));
	node->env = new_environment(nome, ret);
	node->list = NULL;
	node->last = NULL;
	if(header->last!=NULL) header->last->next = node;
	header->last = node;
	if(header->list==NULL) header->list = node;
	header->last->previous = header->current;
	header->current = header->last;
}

char* get_tipo(char* nome, declaration_node* tabela[], int len, int l, int c){
	int index = hash(nome, tabela, len);
	declaration_node* node = tabela[index];
	if(node != NULL){
		if(node->env!=NULL) return node->dec.tipo;
		else return "undef";
	}
	else{
		return "undef";
	}
	return "";
}

int insert_element(declaration_node* tabela[], char* nome, char* tipo, environment_node* env, int len){
	if(nome[0]==0){
		declaration_node* node = (declaration_node*) malloc(sizeof(declaration_node));
		node->env=NULL;
		node->function=NULL;
		node->next = NULL;
		node->dec = new_declaration(nome, tipo);
		declaration_list* node2 = (declaration_list*) malloc(sizeof(declaration_list));
		node2->dec=NULL;
		node2->next = NULL;
		node2->dec = node;
		if(env->last!=NULL) env->last->next = node2;
		if(env->list==NULL) env->list = node2;
		env->last = node2;
		node->env = env;
		return 0;
	}
	int index = hash(nome, tabela, len);
	declaration_node* node = tabela[index];
	if(node == NULL){
		node = (declaration_node*) malloc(sizeof(declaration_node));
		node->env=NULL;
		node->function=NULL;
		node->next = NULL;
		node->dec = new_declaration(nome, tipo);
		tabela[index] = node;
		declaration_list* node2 = (declaration_list*) malloc(sizeof(declaration_list));
		node2->dec=NULL;
		node2->next = NULL;
		node2->dec = node;
		if(env->last!=NULL) env->last->next = node2;
		if(env->list==NULL) env->list = node2;
		env->last = node2;
		node->env = env;
	}
	else{
		if(env != node->env ){
			node = (declaration_node*) malloc(sizeof(declaration_node));
			node->env=NULL;
			node->function=NULL;
			node->next = NULL;
			node->dec = new_declaration(nome, tipo);
			if(tabela[index]->env!=NULL) node->next = tabela[index];
			tabela[index] = node;
			declaration_list* node2 = (declaration_list*) malloc(sizeof(declaration_list));
			node2->dec=NULL;
			node2->next = NULL;
			node2->dec = node;
			if(env->last!=NULL) env->last->next = node2;
			if(env->list==NULL) env->list = node2;
			env->last = node2;
			node->env = env;
		}
		else return 1;
	}
	return 0;
}

void remove_environment(declaration_node* tabela[], environment_node* env, int len){
	declaration_list* list = env->list;
	int index;
	//printf("%s\n", env->env.nome);
	while(list!=NULL){
		if(list->dec==NULL) return;
		//printf("%ld\n",list->dec->dec.nome);
		if(list->dec->dec.nome==NULL) return;
		if(list->dec->dec.nome[0]==0);
		else{
			index = hash(list->dec->dec.nome, tabela, len);
			if(tabela[index]->next!=NULL) tabela[index]= tabela[index]->next;
			else tabela[index]->env = NULL;
		}
		list = list->next;
	}
}

void print_environment_list(environment_list header){
	environment_node* node = header.list;
	environment_node* tmp;
	print_environment2(node);
	tmp = node;
	node = node->next;
	free(tmp);
	while(node!=NULL){
		if(node->defined) print_environment(node);
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

void print_environment(environment_node* node){
	printf("===== Function %s Symbol Table =====\n", node->env.nome);
	if(node->env.ret[0]!=0) printf("return\t%s\n", node->env.ret);

	declaration_list* list = node->list;
	declaration_list* tmp;
	while(list!=NULL){
		print_declaration(list->dec);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	printf("\n");
}

void print_environment2(environment_node* node){
	printf("===== %s Symbol Table =====\n", node->env.nome);
	if(node->env.ret[0]!=0) printf("return\t%s\n", node->env.ret);

	declaration_list* list = node->list;
	declaration_list* tmp;
	while(list!=NULL){
		if(list->dec==NULL) return;
		print_declaration(list->dec);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	printf("\n");
}

void print_declaration(declaration_node* node){
	if(node->dec.nome[0]==0){ free(node); return;}
	printf("%s\t%s", node->dec.nome, node->dec.tipo);
	if(node->dec.param) printf("\tparam");
	if(node->function!=NULL){
		declaration_list* tmp = node->function->list;
		printf("(%s",tmp->dec->dec.tipo);
		tmp = tmp->next;
		while(tmp!=NULL){
			if(tmp->dec==NULL) return;
			if(tmp->dec->dec.param) printf(",%s",tmp->dec->dec.tipo);
			else break;
			tmp = tmp->next;
		}
		printf(")");
	}
	printf("\n");
	free(node);
}

void delete_declaration(declaration_node* node){
	free(node);
}

void delete_environment(declaration_list* list){

	declaration_list* tmp;
	while(list!=NULL){
		delete_declaration(list->dec);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}



void create_environment_list(environment_list* header, declaration_node** tabela, int len, Program* node)
{
	tabela= (declaration_node**)malloc(len*sizeof(declaration_node*));
	insert_environment(header, "Global", "");
	header->current->defined=1;
	
	insert_element(tabela, "putchar", "int", header->current, len);
	insert_environment(header, "putchar", "int");
	tabela[hash("putchar", tabela, len)]->function = header->current;
	insert_element(tabela, "", "int", header->current, len);
	header->current->last->dec->dec.param = 1;
	remove_environment(tabela, header->current, len);
	header->current = header->current->previous;
	insert_element(tabela, "getchar", "int", header->current, len);
	insert_environment(header, "getchar", "int");
	tabela[hash("getchar", tabela, len)]->function = header->current;
	insert_element(tabela, "", "void", header->current, len);
	header->current->last->dec->dec.param = 1;
	remove_environment(tabela, header->current, len);
	header->current = header->current->previous;
	
	if(node==NULL) return;
	check_Function_And_Declaration_list(header, tabela, len, node->list);
}

void check_Function_And_Declaration_list(environment_list* header, declaration_node* tabela[], int len, Function_And_Declaration_list* node)
{	
	if(node==NULL) return;
        Function_And_Declaration_list* tmp= node;
	while(tmp!=NULL){
		check_Fad(header, tabela, len, tmp->fad);
		tmp= tmp->next;
	}
}

void check_Fad(environment_list* header, declaration_node* tabela[], int len, Fad* node)
{
        if(node==NULL) return;
		//print_environment_list(*header);
		if(!strcmp(node->type, "fdef")){
			char* str = node->fdef->fd->id;
			
			char* str2 = (char*) strdup(node->fdef->TypeSpec);
			str2[0] = str2[0] + ('a'-'A'); // passar a minuscula
			
			if(get_args2(node->fdef->fd->list->list)[0]!=0){
			if(insert_element(tabela, str, str2, header->current, len)){
				environment_node* n = tabela[hash(str, tabela, len)]->function;
				if(n == NULL){
					if (get_args2(node->fdef->fd->list->list)[0]==0) return;
					printf("Line %d, col %d: Symbol %s already defined\n", node->fdef->fd->l, node->fdef->fd->c, str);
					//free(str2);
					return;
				}
				if(!n->defined){ 
					char* s1 = get_args2(node->fdef->fd->list->list);
					char* s2 = get_args(n);
					if( s1[0]!=0){
						
						if(strcmp(s1,s2) || strcmp(n->env.ret, str2)){
							printf("Line %d, col %d: Conflicting types (got %s(%s), expected %s(%s))\n", node->fdef->fd->l,  node->fdef->fd->c, str2, s1, n->env.ret, s2);
							//free(s1);
							//free(s2);
							//free(str2);
							return;
						}
					}
					else{ 
						//free(s1);
						//free(s2);
						//free(str2);
						return;
					}
				}
				else{
					// ...
					char* s1 = get_args2(node->fdef->fd->list->list);
					char* s2 = get_args(n);
					printf("Line %d, col %d: Symbol %s already defined\n", node->fdef->fd->l, node->fdef->fd->c, n->env.nome);
					if(strcmp(s1,s2) || strcmp(n->env.ret, str2)){ 
						//free(s1);
						//free(s2);
						//free(str2);
						return;
					}
					
				}
				n->defined = 1;
				n->previous = header->current;
				header->current = n;
			}
			else{
				
				insert_environment(header, str, str2);
				header->current->defined = 1;
				
				
			}
			}
			
			tabela[hash(str, tabela, len)]->function = header->current;
			check_Function_Definition(header, tabela, len, node->fdef);
			remove_environment(tabela, header->current, len);
			header->current = header->current->previous;
		}
		else if(!strcmp(node->type, "fdec")){
			char* str = node->fdec->fd->id;
			
			char* str2 = (char*) strdup(node->fdec->TypeSpec);
			str2[0] = str2[0] + ('a'-'A'); // passar a minuscula
			if (get_args2(node->fdec->fd->list->list)[0]==0) return;
			if(insert_element(tabela, str, str2, header->current, len)){
				environment_node* n = tabela[hash(str, tabela, len)]->function;
				if(n == NULL){
					printf("Line %d, col %d: Symbol %s already defined\n", node->fdec->fd->l, node->fdec->fd->c, str);
					//free(str2);
					return;
				}
				// ...
				//check_Function_Declaration(header, tabela, len, node->fdec);
				if(!n->defined){ 
					char* s1 = get_args2(node->fdec->fd->list->list);
					char* s2 = get_args(n);
					if( s1[0]!=0){
						if(strcmp(s1,s2) || strcmp(n->env.ret, str2)){
							printf("Line %d, col %d: Conflicting types (got %s(%s), expected %s(%s))\n", node->fdec->fd->l,  node->fdec->fd->c, str2, s1, n->env.ret, s2);
							//free(s1);
							//free(s2);
							//free(str2);
							return;
						}
						//free(s1);
						//free(s2);
					}
					else{
						//free(s2);
						//free(str2);
						return;
					}
				}
				else{
					printf("Line %d, col %d: Symbol %s already defined\n", node->fdec->fd->l, node->fdec->fd->c, n->env.nome);
					return;
				}
				n->previous = header->current;
				header->current = n;
			}
			else{
					insert_environment(header, str, str2);
			}
			tabela[hash(str, tabela, len)]->function = header->current;
			check_Function_Declaration(header, tabela, len, node->fdec);
			remove_environment(tabela, header->current, len);
			header->current = header->current->previous;
		}
		else{
			check_Variable_Declaration(header, tabela, len, node->vdec);
		}
}

void check_Variable_Declaration(environment_list* header, declaration_node* tabela[], int len, Variable_Declaration* node)
{
	if(node==NULL) return;
	Declarator_list* tmp = node->list;
	if(node->TypeSpec[0] == 'V'){
		do{
		check_Declarator_list(header, tabela, len, tmp);
		printf("Line %d, col %d: Invalid use of void type in declaration\n", tmp->l, tmp->c);

		tmp = tmp->next;
		}while(tmp!=NULL);
		return;
	}
		char* str2 = (char*) strdup(node->TypeSpec);
		str2[0] = str2[0] + ('a'-'A'); // passar a minuscula
	do{
		check_Declarator_list(header, tabela, len, tmp);

		char* str = tmp->id;

		if(insert_element(tabela,str, str2, header->current, len)) {
			char* t = get_tipo(str, tabela, len, tmp->l, tmp->c);
			//if(!(tabela[hash(str, tabela, len)]->dec.notified)){printf("Line %d, col %d: Symbol %s already defined\n", tmp->l, tmp->c, str); tabela[hash(str, tabela, len)]->dec.notified = 1;}
			
			if( (strcmp(tabela[hash(str, tabela, len)]->env->env.nome,"Global"))) printf("Line %d, col %d: Symbol %s already defined\n", tmp->l, tmp->c, str);
			else if((t[0] != 'd' && str2[0]=='d') || (t[0] == 'd' && str2[0]!='d')) printf("Line %d, col %d: Conflicting types (got %s, expected %s)\n", tmp->l, tmp->c, str2, t);
			//free(str2);
			/*
			else if(str2[0] == 'd' && t[0]!='u' && t[0]!='v') printf("Line %d, col %d: Symbol %s already defined\n", tmp->l, tmp->c, str);
			else if(str2[0] == 'i' && t[0]!='d' && t[0]!='u' && t[0]!='v') printf("Line %d, col %d: Symbol %s already defined\n", tmp->l, tmp->c, str);
			else if(str2[0] == 'c' && t[0]!='d' && t[0]!='i' && t[0]!='u'&& str2[0]!='v') printf("Line %d, col %d: Symbol %s already defined\n", tmp->l, tmp->c, str);
			else printf("Line %d, col %d: Conflicting types (got %s, expected %s)\n", tmp->l, tmp->c, str2, t);
			*/
		}
		tmp = tmp->next;
	}while(tmp!=NULL);
		/*	
	tmp = node->list;
	
	do{

		char* str = (char*) strdup(&(tmp->id[3]));
		char* aux;
		for(aux = str; *aux!=')'; aux ++);
		*aux = 0;
		if(get_tipo(str, tabela, len, tmp->l, tmp->c)[0]!='u') tabela[hash(str, tabela, len)]->dec.notified = 0;
		
		tmp = tmp->next;
	}while(tmp!=NULL);
	*/
}

void check_Declarator_list(environment_list* header, declaration_node* tabela[], int len, Declarator_list* node)
{
	if(node==NULL) return;
	check_Expression(header, tabela, len, node->ex, 1, NULL);
	
}

void check_Function_Declaration(environment_list* header, declaration_node* tabela[], int len, Function_Declaration* node)
{
	if(node==NULL) return;
	
	check_Function_Declarator(header, tabela, len, node->fd);
}

void check_Paramlist(environment_list* header, declaration_node* tabela[], int len, Paramlist* node)
{
	if(node==NULL) return;
	
	check_ParamDeclaration(header, tabela, len, node->list); 
}

void check_ParamDeclaration(environment_list* header, declaration_node* tabela[], int len, ParamDeclaration* node)
{
	if(node==NULL) return;
        ParamDeclaration* tmp= node;
	if(header->current->list == NULL){
		while(tmp!=NULL){
			char* str;
			if(tmp->id[0]!=0){
				str = tmp->id;
			}
			else{
				
				str= "";
			}

			char* str2 = (char*) strdup(tmp->TypeSpec);
			str2[0] = str2[0] + ('a'-'A'); // passar a minuscula
			if(insert_element(tabela,str, str2, header->current, len)){
				
				//...
				printf("Line %d, col %d: Symbol %s already defined\n", tmp->l, tmp->c, str);
				insert_element(tabela,"", str2, header->current, len);
				header->current->last->dec->dec.param = 1;
				//free(str2);
			}
			else{
				header->current->last->dec->dec.param = 1;
			}
			
			tmp= tmp->next;
		}
		//..... (,)
	}
	else{
		header->current->list = NULL;
		while(tmp!=NULL){
			char* str;
			if(tmp->id[0]!=0){
				str = tmp->id;
			}
			else{
				str= "";
			}
			char* str2 = (char*) strdup(tmp->TypeSpec);
			str2[0] = str2[0] + ('a'-'A'); // passar a minuscula

			if(insert_element(tabela,str, str2, header->current, len)){
			//...
				printf("Line %d, col %d: Symbol %s already defined\n", tmp->l, tmp->c, str);
				insert_element(tabela,"", str2, header->current, len);
				header->current->last->dec->dec.param = 1;
				//free(str2);
			}
			else{
				header->current->last->dec->dec.param = 1;
			}
			tmp= tmp->next;
		}
	}
}

void check_Function_Definition(environment_list* header, declaration_node* tabela[], int len, Function_Definition* node)
{
	if(node==NULL) return;

	check_Function_Declarator(header, tabela, len, node->fd);
	check_FuncBody(header, tabela, len, node->fb);
}

void check_Function_Declarator(environment_list* header, declaration_node* tabela[], int len, Function_Declarator* node)
{
	if(node==NULL) return;

	check_Paramlist(header, tabela, len, node->list);

}

void check_FuncBody(environment_list* header, declaration_node* tabela[], int len, FuncBody* node)
{
	if(node==NULL) return;

	check_Declarations_And_Statements(header, tabela, len, node->list);

}

void check_Declarations_And_Statements(environment_list* header, declaration_node* tabela[], int len, Declarations_And_Statements* node)
{
	if(node==NULL)return;
	Declarations_And_Statements* tmp= node;
	while(tmp!=NULL){
		check_Das(header, tabela, len, tmp->das);
		tmp= tmp->next;
	}
}

void check_Das(environment_list* header, declaration_node* tabela[], int len, Das* node)
{
	if(node==NULL) return;
	if(!strcmp(node->type, "dec")){
			check_Variable_Declaration(header, tabela, len, node->dec);
		}
		else{
			check_Stat(header, tabela, len, node->s);
		}
}

void check_Stat(environment_list* header, declaration_node* tabela[], int len, Stat* node)
{
	if(node==NULL) return;
	
		if(!strcmp(node->type, "if_")){
			check_If(header, tabela, len, node->if_);
		}
		else if(!strcmp(node->type, "while_")){
			check_While(header, tabela, len, node->while_);
		}
		else if(!strcmp(node->type, "list")){
			check_StatList(header, tabela, len, node->list);
		}
		else if(!strcmp(node->type, "ex")){
			check_Expression(header, tabela, len, node->ex, 1, NULL);
		}
		else{
			check_Return(header, tabela, len, node->return_);
		}

}

void check_StatList(environment_list* header, declaration_node* tabela[], int len, StatList* node)
{
	if(node==NULL) return;
	StatList* tmp = node;

	while(tmp!=NULL){
		check_Stat(header, tabela, len, tmp->s);
		tmp= tmp->next;
	}
	
}

void check_If(environment_list* header, declaration_node* tabela[], int len, If* node)
{
	if(node==NULL) return;

	char* str= check_Expression(header, tabela, len, node->ex, 1, NULL);
	if(str[0]=='d' || str[0]=='u' || str[0]=='v') printf("Line %d, col %d: Conflicting types (got %s, expected int)\n", node->ex->l, node->ex->c, str);
	
	check_Stat(header, tabela, len, node->s);
	check_Else(header, tabela, len, node->else_);
}

void check_Else(environment_list* header, declaration_node* tabela[], int len, Else* node)
{
	if(node==NULL) return;
	
	check_Stat(header, tabela, len, node->s);

}


void check_While(environment_list* header, declaration_node* tabela[], int len, While* node)
{
	if(node==NULL) return;


	char* str= check_Expression(header, tabela, len, node->ex, 1, NULL);

	if(str[0]=='d' || str[0]=='u' || str[0]=='v') printf("Line %d, col %d: Conflicting types (got %s, expected int)\n", node->ex->l, node->ex->c, str);
	
	check_Stat(header, tabela, len, node->s);

}

void check_Return(environment_list* header, declaration_node* tabela[], int len, Return* node)
{
	if(node==NULL) return;
	char* str= check_Expression(header, tabela, len, node->ex, 1, NULL);
	if(node->ex == NULL) str = "void";

	if(header->current->env.ret[0] == str[0]);
	else if(header->current->env.ret[0] == 'd' && str[0]!='u' && str[0]!='v');
	else if((header->current->env.ret[0] == 'i' || header->current->env.ret[0] == 'c' || header->current->env.ret[0] == 's') && str[0]!='d' && str[0]!='u' && str[0]!='v');
	else printf("Line %d, col %d: Conflicting types (got %s, expected %s)\n", node->l, node->c, str, header->current->env.ret);
}

char* check_Expression(environment_list* header, declaration_node* tabela[], int len, Expression* node, int flag, char* list)
{
	if(node==NULL) return "";
	
	if(!strcmp(node->type, "op")){
		node->tipo = check_Operator(header, tabela, len, node->op, flag, list);
		return node->tipo;
	}
	else if(!strcmp(node->type, "not")){
		node->tipo = check_Not(header, tabela, len, node->not);
	}
	else if(!strcmp(node->type, "minus")){
		node->tipo = check_Minus(header, tabela, len, node->minus);
	}
	else if(!strcmp(node->type, "plus")){
		node->tipo = check_Plus(header, tabela, len, node->plus);
	}
	else if(!strcmp(node->type, "id")){
		char* str = node->id;
		node->tipo = get_tipo(str, tabela, len, node->l, node->c);
		if(node->tipo[0] == 'u'){
			printf("Line %d, col %d: Unknown symbol %s\n", node->l, node->c, str);
		}
	}
	else if(!strcmp(node->type, "ex")){
		node->tipo = check_Expression(header, tabela, len, node->ex, 1, NULL);
	}
	else if(!strcmp(node->type, "call")){
		char* str = node->id;
		node->tipo = get_tipo(str, tabela, len, node->l, node->c);
		
		if(!strcmp(node->tipo, "undef")){
			printf("Line %d, col %d: Unknown symbol %s\n", node->l, node->c, str);
			node->tipo2 = "undef";
			char* s = check_Expression(header, tabela, len, node->ex, 0, "");
			compareArg(NULL, s, node->ex, node->l, node->c, str);
		}
		else{
			environment_node* env = tabela[hash(str, tabela, len)]->function;
			if(env == NULL){
				//printf("Line %d, col %d: Symbol %s is not a function\n", node->l, node->c, str); //
				node->tipo2 =  node->tipo;
				char* s = check_Expression(header, tabela, len, node->ex, 0, "");
				compareArg(NULL, s, node->ex, node->l, node->c, str);
			}
			else{
				char* args = get_args(env); 
				node->tipo2 = (char*) malloc(sizeof(node->tipo)+sizeof(args)+2*sizeof(char));
				sprintf(node->tipo2, "%s(%s)", node->tipo, args);
			
				char* s = check_Expression(header, tabela, len, node->ex, 0, args);
				compareArg(env, s, node->ex, node->l, node->c, str);
			}
		}
	}
	else if(!strcmp(node->type, "term")){
		node->tipo = check_Terminal(header, tabela, len, node->term);
	}
	if(!flag){	
		char c = list[0];
		if(c){
			if(c == node->tipo[0]);
			else if(c == 'd' && node->tipo[0]!='u' && node->tipo[0]!='v');
			else if((c == 'i' || c == 'c' || c == 's') && node->tipo[0]!='d' && node->tipo[0]!='u' && node->tipo[0]!='v');
			else { 
				char* s;
				if(c == 'd') s = "double";
				else if(c == 'i') s = "int";
				else if(c == 's') s = "short";
				else if(c == 'c') s = "char";
				//else if(c == 'v') s = "void";
				else s = "undef";
				if(c != 'v') printf("Line %d, col %d: Conflicting types (got %s, expected %s)\n", node->l, node->c, node->tipo, s);
			}
		}
	}
	return node->tipo;
}

char* check_Operator(environment_list* header, declaration_node* tabela[], int len, Operator* node, int flag, char* list)
{
	if(node==NULL) return "";
	char* tipo = "";
	char* tipo1, *tipo2;
	if(!strcmp(node->type, "Comma")){
		if(!flag){
			
			tipo1 = check_Expression(header, tabela, len, node->ex1, 0, list);
			while((*list) && (*list)!=','){ list++;}
			if(*list) list ++;
			char c = list[0];
			tipo2 = check_Expression(header, tabela, len, node->ex2, 1, NULL);

			
			if(c){
				if(c == tipo2[0]);
				else if(c == 'd' && tipo2[0]!='u' && tipo2[0]!='v');
				else if((c == 'i' || c == 'c' || c == 's') && tipo2[0]!='d' && tipo2[0]!='u' && tipo2[0]!='v');
				else { 
					char* s;
					if(c == 'd') s = "double";
					else if(c == 'i') s = "int";
					else if(c == 's') s = "short";
					else if(c == 'c') s = "char";
					//else if(c == 'v') s = "void";
					else s = "undef";
					if(c != 'v') printf("Line %d, col %d: Conflicting types (got %s, expected %s)\n", node->ex2->l, node->ex2->c, tipo2, s);
				}
			}
			tipo = (char*)malloc(sizeof(tipo1)+sizeof(tipo2)+ sizeof(char));
			sprintf(tipo,"%s,%s", tipo1, tipo2);
		}
		else{
			tipo1 = check_Expression(header, tabela, len, node->ex1, 1, NULL);
			tipo2 = check_Expression(header, tabela, len, node->ex2, 1, NULL);
			if(!strcmp(tipo1,"double") || !strcmp(tipo2,"double")) tipo = "double";
			else if(!strcmp(tipo1,"int") || !strcmp(tipo2,"int")) tipo = "int";
			else if(!strcmp(tipo1,"short") || !strcmp(tipo2,"short")) tipo = "short";
			else tipo = "char";
		}
	}else{
		tipo1 = check_Expression(header, tabela, len, node->ex1, 1, NULL);
		tipo2 = check_Expression(header, tabela, len, node->ex2, 1, NULL);
		if(!strcmp(tipo1,"undef") || !strcmp(tipo2,"undef") || !strcmp(tipo1,"void") || !strcmp(tipo2,"void")){
			tipo = "undef";
			if(!strcmp(node->type,"Store")){ tipo = tipo1; printf("Line %d, col %d: Operator = cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2);}
			else if(!strcmp(node->type, "Add")) printf("Line %d, col %d: Operator + cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2);
			else if(!strcmp(node->type, "Sub")) printf("Line %d, col %d: Operator - cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2);
			else if(!strcmp(node->type, "Mul")) printf("Line %d, col %d: Operator * cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2);
			else if(!strcmp(node->type, "Div")) printf("Line %d, col %d: Operator / cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2);
			else if(!strcmp(node->type, "Mod")){ tipo = "int"; printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", node->l, node->c, "%", tipo1, tipo2); }
			else if(!strcmp(node->type, "Or")){ tipo = "int"; printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "And")){ tipo = "int"; printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "BitWiseOr")){ tipo = "int"; printf("Line %d, col %d: Operator | cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "BitWiseAnd")){ tipo = "int"; printf("Line %d, col %d: Operator & cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "BitWiseXor")){ tipo = "int"; printf("Line %d, col %d: Operator ^ cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "Le")){ tipo = "int"; printf("Line %d, col %d: Operator <= cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "Ge")){ tipo = "int"; printf("Line %d, col %d: Operator >= cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "Lt")){ tipo = "int"; printf("Line %d, col %d: Operator < cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "Gt")){ tipo = "int"; printf("Line %d, col %d: Operator > cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "Eq") && ( (!strcmp(tipo1,"undef") && strcmp(tipo2,"undef")) 
								|| (strcmp(tipo1,"undef") && !strcmp(tipo2,"undef")) 
								|| (!strcmp(tipo1,"void") && strcmp(tipo2,"void")) 
								|| (strcmp(tipo1,"void") && !strcmp(tipo2,"void")) ) )
				{ tipo = "int"; printf("Line %d, col %d: Operator == cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else if(!strcmp(node->type, "Ne") && ( (!strcmp(tipo1,"undef") && strcmp(tipo2,"undef")) 
								|| (strcmp(tipo1,"undef") && !strcmp(tipo2,"undef")) 
								|| (!strcmp(tipo1,"void") && strcmp(tipo2,"void")) 
								|| (strcmp(tipo1,"void") && !strcmp(tipo2,"void")) ) )
				{ tipo = "int"; printf("Line %d, col %d: Operator != cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2); }
			else tipo = "int";
		}
	
		else if(!strcmp(node->type,"Store")){
			tipo = tipo1;
			if(!strcmp(tipo2,"double") && strcmp(tipo1,"double")){
				printf("Line %d, col %d: Operator = cannot be applied to types %s, %s\n", node->l, node->c, tipo1, tipo2);
			}
			else if(strcmp(node->ex1->type,"id")){
				printf("Line %d, col %d: Lvalue required\n", node->ex1->l, node->ex1->c);
			}
		}
		else if(!strcmp(node->type, "Add") || !strcmp(node->type,"Sub") || !strcmp(node->type,"Mul") || !strcmp(node->type,"Div")){
			if(!strcmp(tipo1,"double") || !strcmp(tipo2,"double")) tipo = "double";
			else if(!strcmp(tipo1,"int") || !strcmp(tipo2,"int")) tipo = "int";
			else if(!strcmp(tipo1,"short") || !strcmp(tipo2,"short")) tipo = "short";
			else tipo = "char";
	
		}
		else if(!strcmp(node->type,"Mod") || !strcmp(node->type,"Or") || !strcmp(node->type,"And") || !strcmp(node->type,"BitWiseAnd") || !strcmp(node->type,"BitWiseOr") || !strcmp(node->type,"BitWiseXor")){
			char* o;
			if(node->type[0]=='M') o = "%";
			else if(node->type[0]=='O') o = "||";
			else if(node->type[0]=='A') o = "&&";
			else if(node->type[7]=='O') o = "|";
			else if(node->type[7]=='A') o = "&";
			else o = "^";
			tipo="int";
			if(!strcmp(tipo1,"double") || !strcmp(tipo2,"double")) printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", node->l, node->c, o, tipo1, tipo2);
		}
		else tipo = "int";
	}	
	
	node->tipo = tipo;
	//check_Expression(header, tabela, len, node->ex2, 1);
	return tipo;
}

char* check_Not(environment_list* header, declaration_node* tabela[], int len, Not* node)
{
	if(node==NULL) return "";
	
	node->tipo = check_Expression(header, tabela, len, node->ex, 1, NULL);
	if(node->tipo[0] == 'u'){
		printf("Line %d, col %d: Operator ! cannot be applied to type undef\n", node->l, node->c);
	}
	else if(node->tipo[0] == 'v') printf("Line %d, col %d: Operator ! cannot be applied to type void\n", node->l, node->c);
	node->tipo = "int";
	return node->tipo;
}

char* check_Minus(environment_list* header, declaration_node* tabela[], int len, Minus* node)
{
	if(node==NULL) return "";
	node->tipo = check_Expression(header, tabela, len, node->ex, 1, NULL);
	if(node->tipo[0] == 'v'){ printf("Line %d, col %d: Operator - cannot be applied to type void\n", node->l, node->c);}
	else if(node->tipo[0] == 'u') printf("Line %d, col %d: Operator - cannot be applied to type undef\n", node->l, node->c);
	return node->tipo;
}

char* check_Plus(environment_list* header, declaration_node* tabela[], int len, Plus* node)
{
	if(node==NULL) return "";
	node->tipo = check_Expression(header, tabela, len, node->ex, 1, NULL);
	if(node->tipo[0] == 'v'){ printf("Line %d, col %d: Operator + cannot be applied to type void\n", node->l, node->c);}
	else if(node->tipo[0] == 'u') printf("Line %d, col %d: Operator + cannot be applied to type undef\n", node->l, node->c);
	return node->tipo;
}

char* check_Terminal(environment_list* header, declaration_node* tabela[], int len, Terminal* node)
{
	if(node==NULL) return "";
	if(node->type[0] == 'I') node->tipo = "int";
	else if(node->type[0] == 'C') node->tipo = "int";
	else if(node->type[0] == 'R') node->tipo = "double";
	return node->tipo;
}



