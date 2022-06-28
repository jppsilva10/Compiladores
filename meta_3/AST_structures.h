#ifndef STRUCTURES_H

#define STRUCTURES_H



typedef struct _s24 {

	int l;

	int c;
	
	char* tipo;

        char* type;
        


} Terminal;



typedef struct _s18 Expression;



typedef struct _s22 {

	int l;

	int c;

	char* tipo;

        Expression* ex;

} Plus;



typedef struct _s21 {

	int l;

	int c;

	char* tipo;

        Expression* ex;

} Minus;



typedef struct _s20 {

	int l;

	int c;

	char* tipo;

        Expression* ex;

} Not;



typedef struct _s19 {

	int l;

	int c;

	char* tipo;

	char* type;

        Expression* ex1;

	Expression* ex2;

}  Operator;



typedef struct _s18 {

	int l;

	int c;

	char* tipo;

	char* tipo2;

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
	int l;

	int c;

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

	int l;

	int c;

        char* id;

	Expression* ex;

	struct _s4* next;

} Declarator_list;



typedef struct _s3 {

	int l;

	int c;

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

	int l;

	int c;
	
	char* TypeSpec;

        char* id;

	struct _s7* next;

} ParamDeclaration;



typedef struct _s6 {

	ParamDeclaration* list;

} Paramlist;



typedef struct _s9 {

	int l;
	
	int c;
	
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



Program* insert_Program(Function_And_Declaration_list* list);



Function_And_Declaration_list* insert_Function_And_Declaration_list(Function_And_Declaration_list* head, Fad* fad);



Fad* insert_Fad(char* type, Function_Definition* fdef, Function_Declaration* fdec, Variable_Declaration* vdec);



Variable_Declaration* insert_Variable_Declaration(char* TypeSpec, Declarator_list* list, int c, int l);



Declarator_list* insert_Declarator_list(char* id, Expression* ex, Declarator_list* head, int c, int l);



Function_Declaration* insert_Function_Declaration(char* TypeSpec, Function_Declarator* fd);



Paramlist* insert_Paramlist(ParamDeclaration* list);



ParamDeclaration* insert_ParamDeclaration(char* TypeSpec, char* id, ParamDeclaration* head, int c, int l);



Function_Definition* insert_Function_Definition(char* TypeSpec, Function_Declarator* fd, FuncBody* fb);



Function_Declarator* insert_Function_Declarator(char* id, Paramlist* list, int c, int l);



FuncBody* insert_FuncBody(Declarations_And_Statements* list);



Declarations_And_Statements* insert_Declarations_And_Statements(Das* das, Declarations_And_Statements* head);



Das* insert_Das(char* type, Stat* s, Variable_Declaration* dec);



StatList* insert_StatList(Stat* s, StatList* head);



Stat* insert_Stat(char* type, If* if_, While* while_, Return* return_, StatList* list, Expression* ex);



If* insert_If(Expression* ex, Stat* s, Else* else_);



Else* insert_Else(Stat* s);



While* insert_While(Expression* ex, Stat* s);



Return* insert_Return(Expression* ex, int c, int l);



Expression* insert_Expression(char* type, Operator* op, Not* not, Minus* minus, Plus* plus, Terminal* term, Expression* ex, char* id, int c, int l);



Operator* insert_Operator(char* type, Expression* ex1, Expression* ex2, int c, int l);



Not* insert_Not(Expression* ex, int c, int l);



Minus* insert_Minus(Expression* ex, int c, int l);



Plus* insert_Plus(Expression* ex, int c, int l);



Terminal* insert_Terminal(char* type, int c, int l);



void print_Program(Program* node, int option);
void print_Function_And_Declaration_list(int i, Function_And_Declaration_list* node, int option);
void print_Fad(int i, Fad* node, int option);
void print_Variable_Declaration(int i, Variable_Declaration* node, int option);
void print_Declarator_list(int i, Declarator_list* node, int option);
void print_Fad(int i, Fad* node, int option);
void print_Variable_Declaration(int i, Variable_Declaration* node, int option);
void print_Declarator_list(int i, Declarator_list* node, int option);
void print_Function_Declaration(int i, Function_Declaration* node, int option);
void print_Paramlist(int i, Paramlist* node, int option);
void print_ParamDeclaration(int i, ParamDeclaration* node, int option);
void print_Function_Definition(int i, Function_Definition* node, int option);
void print_Function_Declarator(int i, Function_Declarator* node, int option);
void print_FuncBody(int i, FuncBody* node, int option);
void print_Declarations_And_Statements(int i, Declarations_And_Statements* node, int option);
void print_Das(int i, Das* node, int option);
void print_Stat(int i, Stat* node, int option);
void print_StatList(int i, StatList* node, int option);
void print_If(int i, If* node, int option);
void print_Else(int i, Else* node, int option);
void print_While(int i, While* node, int option);
void print_Return(int i, Return* node, int option);
void print_Expression(int i, Expression* node, int option, int flag);
void print_Operator(int i, Operator* node, int option, int flag);
void print_Not(int i, Not* node, int option);
void print_Minus(int i, Minus* node, int option);
void Print_Plus(int i, Plus* node, int option);
void print_Terminal(int i, Terminal* node, int option);



#endif

