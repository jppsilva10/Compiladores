#include "AST_structures.h"

typedef struct list_item {
	int notified;
        char* nome;
	char* tipo;
	int param;
} declaration;

typedef struct list3 environment_node;

typedef struct list1 {
        declaration dec;
	environment_node* env;
	environment_node* function;
	struct list1* next;
} declaration_node;

typedef struct list_item2 {
        char* nome;
	char* ret;
} environment;

typedef struct list2 {
        declaration_node* dec;
	struct list2* next;
	struct list2* previous;
} declaration_list;

typedef struct list3 {
	int defined;
        environment env;
	declaration_list* list;
	declaration_list* last;
	struct list3* next;
	struct list3* previous;
} environment_node;

typedef struct list4 {
        environment_node* list;
	environment_node* current;
	environment_node* last;
	int erro;
} environment_list;

int hash(char* var, declaration_node* tabela[], int len);

void compareArg(environment_node* env, char* args, Expression* ex, int l, int c, char* nome);

declaration new_declaration(char* nome, char* tipo);

environment new_environment(char* nome, char* ret);

void insert_environment(environment_list* header, char* nome, char* ret);

char* get_tipo(char* nome, declaration_node* tabela[], int len, int l, int c);

int insert_element(declaration_node* tabela[], char* nome, char* tipo, environment_node* env, int len);

void remove_environment(declaration_node* tabela[], environment_node* env, int len);

void print_environment_list(environment_list header);

void print_environment(environment_node* node);

void print_environment2(environment_node* node);

void print_declaration(declaration_node* node);

void create_environment_list(environment_list* header, declaration_node** tabela, int len, Program* node);

void check_Function_And_Declaration_list(environment_list* header, declaration_node* tabela[], int len, Function_And_Declaration_list* node);

void check_Fad(environment_list* header, declaration_node* tabela[], int len, Fad* node);

void check_Variable_Declaration(environment_list* header, declaration_node* tabela[], int len, Variable_Declaration* node);

void check_Declarator_list(environment_list* header, declaration_node* tabela[], int len, Declarator_list* node);

void check_Function_Declaration(environment_list* header, declaration_node* tabela[], int len, Function_Declaration* node);

void check_Paramlist(environment_list* header, declaration_node* tabela[], int len, Paramlist* node);

void check_ParamDeclaration(environment_list* header, declaration_node* tabela[], int len, ParamDeclaration* node);

void check_Function_Definition(environment_list* header, declaration_node* tabela[], int len, Function_Definition* node);

void check_Function_Declarator(environment_list* header, declaration_node* tabela[], int len, Function_Declarator* node);

void check_FuncBody(environment_list* header, declaration_node* tabela[], int len, FuncBody* node);

void check_Declarations_And_Statements(environment_list* header, declaration_node* tabela[], int len, Declarations_And_Statements* node);

void check_Das(environment_list* header, declaration_node* tabela[], int len, Das* node);

void check_Stat(environment_list* header, declaration_node* tabela[], int len, Stat* node);

void check_StatList(environment_list* header, declaration_node* tabela[], int len, StatList* node);

void check_If(environment_list* header, declaration_node* tabela[], int len, If* node);

void check_Else(environment_list* header, declaration_node* tabela[], int len, Else* node);

void check_While(environment_list* header, declaration_node* tabela[], int len, While* node);

void check_Return(environment_list* header, declaration_node* tabela[], int len, Return* node);

char* check_Expression(environment_list* header, declaration_node* tabela[], int len, Expression* node, int flag, char* list);

char* check_Operator(environment_list* header, declaration_node* tabela[], int len, Operator* node, int flag, char* list);

char* check_Not(environment_list* header, declaration_node* tabela[], int len, Not* node);

char* check_Minus(environment_list* header, declaration_node* tabela[], int len, Minus* node);

char* check_Plus(environment_list* header, declaration_node* tabela[], int len, Plus* node);

char* check_Terminal(environment_list* header, declaration_node* tabela[], int len, Terminal* node);

