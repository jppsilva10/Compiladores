#include "AST_structures.h"


void ConvertType(char* TypeSpec);

void ConvertId(char* id);

void Convert_Program(Program* node);

void Convert_Function_And_Declaration_list(char* str, Function_And_Declaration_list* node, int* OpNumber);

void Convert_Fad(char* str, Fad* node, int* OpNumber);

void Convert_Variable_Declaration(char* str, Variable_Declaration* node, int* OpNumber);

void Convert_Declarator_list(char* str, Declarator_list* node, int* OpNumber);

void Convert_Function_Declaration(char* str, Function_Declaration* node, int* OpNumber);

void Convert_Paramlist(char* str, Paramlist* node, int* OpNumber);

void Convert_ParamDeclaration(char* str, ParamDeclaration* node, int* OpNumber);

void Convert_Function_Definition(char* str, Function_Definition* node, int* OpNumber);

void Convert_Function_Declarator(char* str, Function_Declarator* node, int* OpNumber);

void Convert_FuncBody(char* str, FuncBody* node, int* OpNumber);

void Convert_Declarations_And_Statements(char* str, Declarations_And_Statements* node, int* count, int* OpNumber);

void Convert_Das(char* str, Das* node, int* count, int* OpNumber);

void Convert_Stat(char* str, Stat* node, int* count, int* OpNumber);

void Convert_StatList(char* str, StatList* node, int* count, int* OpNumber);

void Convert_If(char* str, If* node, int* count, int* OpNumber);

void Convert_Else(char* str, Else* node, int* count, int* OpNumber);


void Convert_While(char* str, While* node, int* count, int* OpNumber);

void Convert_Return(char* str, Return* node, int* OpNumber);

char* Convert_Expression(char* str, Expression* node, int flag, int* OpNumber);

char* Convert_Operator(char* str, Operator* node, int flag, int* OpNumber);

void Convert_Not(char* str, Not* node, int flag, int* OpNumber);

void Convert_Minus(char* str, Minus* node, int flag, int* OpNumber);

void Convert_Plus(char* str, Plus* node, int flag, int* OpNumber);

void Convert_Terminal(char* str, Terminal* node, int flag, int* OpNumber);

