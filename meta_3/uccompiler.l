%{
//João Pedro Pacheco Silva Nº 218298731
 //Luís Carlos Lopes Loureiro Nº 2018297934
#include "y.tab.h"
typedef struct token_ {
	int linha;
	int coluna;
	char* id;
} Token;
int option;
int opt, parse, smantic;
int linha=1;
int coluna=1;
int linha2=1;
int coluna2=1;
int col=1;
int lin=1;
int comment=0;
int erro=0;
void create_token(char* id);
%}

%X Comentario1 Comentario2 Chrlit
alph				[a-z]|[A-Z]|"_"
INTLIT				[0-9]+
ID				({alph}+{INTLIT}*)+
CHRLIT				[^"\\'\n\r"]|"\\n"|"\t"|"\\t"|"\""|"\\\""|"\\'"|"\\\\"|"\\"[0-7]{1,3}
exp				(e|E)("+"|"-")?{INTLIT}
REALLIT				((({INTLIT}".")|("."{INTLIT})){INTLIT}?{exp}?)|({INTLIT}{exp})
RESERVED			"["|"]"|"++"|"--"|auto|break|case|const|continue|default|do|long|register|signed|sizeof|static|struct|switch|typedef|union|unsigned|volatile|enum|extern|float|for|goto
INVALIDCHAR			'({CHRLIT}|("\\".))*'
UNTERMINATEDCHAR		'({CHRLIT}|("\\".))*("\n"|"\\\n"|"\r"|"\\\r"|"\r\n"|"\\\r\n")
%%
\t|" "				{coluna+=yyleng;}
"/*"				{BEGIN Comentario1; coluna2=coluna; col = coluna; linha2=linha; coluna+=yyleng; comment=1;}
<Comentario1>.			{coluna+=yyleng;;}
<Comentario1>\n			{col = coluna; linha++; coluna=1;}
<Comentario1>"*/"		{BEGIN 0; coluna+=yyleng; comment=0;}

"//"				{BEGIN Comentario2; col = coluna; coluna+=yyleng;}
<Comentario2>.			{coluna+=yyleng;}
<Comentario2>"\n"		{BEGIN 0; col=coluna; linha++; coluna=1;}

"char"				{if(option) printf("CHAR\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return CHAR;}
"else"				{if(option) printf("ELSE\n"); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return ELSE;}
"while"				{if(option) printf("WHILE\n"); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return WHILE;}
"if"				{if(option) printf("IF\n"); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return IF;}
"int"				{if(option) printf("INT\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return INT;}
"short"				{if(option) printf("SHORT\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return SHORT;}
"double"			{if(option) printf("DOUBLE\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return DOUBLE;}
"return"			{if(option) printf("RETURN\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return RETURN;}
"void"				{if(option) printf("VOID\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return VOID;}
"&&"				{if(option) printf("AND\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return AND;}
"&"				{if(option) printf("BITWISEAND\n"); create_token((char*)strdup(yytext)) ; coluna+=yyleng; return BITWISEAND;}
"||"				{if(option) printf("OR\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return OR;}
"|"				{if(option) printf("BITWISEOR\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return BITWISEOR;}
"^"				{if(option) printf("BITWISEXOR\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return BITWISEXOR;}
"=="				{if(option) printf("EQ\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return EQ;}
"="				{if(option) printf("ASSIGN\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return ASSIGN;}
"*"				{if(option) printf("MUL\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return MUL;}
","				{if(option) printf("COMMA\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return COMMA;}
"/"				{if(option) printf("DIV\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return DIV;}
">="				{if(option) printf("GE\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return GE;}
">"				{if(option) printf("GT\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return GT;}
"{"				{if(option) printf("LBRACE\n"); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return LBRACE;}
"<="				{if(option) printf("LE\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return LE;}
"("				{if(option) printf("LPAR\n"); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return LPAR;}
"<"				{if(option) printf("LT\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return LT;}
"-"				{if(option) printf("MINUS\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return MINUS;}
"%"				{if(option) printf("MOD\n");create_token((char*)strdup(yytext)); coluna+=yyleng; return MOD;}
"!="				{if(option) printf("NE\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return NE;}
"!"				{if(option) printf("NOT\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return NOT;}
"+"				{if(option) printf("PLUS\n"); create_token((char*)strdup(yytext)); coluna+=yyleng; return PLUS;}
"}"				{if(option) printf("RBRACE\n"); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return RBRACE;}
")"				{if(option) printf("RPAR\n"); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return RPAR;}
";"				{if(option) printf("SEMI\n"); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return SEMI;}
{RESERVED}			{if(option) printf("RESERVED(%s)\n", yytext); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return RESERVED;}
{ID}				{if(option) printf("ID(%s)\n", yytext); create_token((char*)strdup(yytext));coluna+=yyleng; return ID;}
{INTLIT}			{if(option) printf("INTLIT(%s)\n", yytext); create_token((char*)strdup(yytext)); coluna+=yyleng; return INTLIT;}
{REALLIT}			{if(option) printf("REALLIT(%s)\n", yytext); create_token((char*)strdup(yytext)); coluna+=yyleng; return REALLIT;}
'{CHRLIT}'			{if(option) printf("CHRLIT(%s)\n", yytext); create_token((char*)strdup(yytext)); coluna+=yyleng; return CHRLIT;}
{INVALIDCHAR}			{printf("Line %d, col %d: invalid char constant (%s)\n", linha, coluna, yytext); yylval.id=(char*)strdup(yytext); coluna+=yyleng; return INVALIDCHAR;}
{UNTERMINATEDCHAR}		{col = coluna; printf("Line %d, col %d: unterminated char constant\n", linha, coluna); yylval.id=(char*)strdup(yytext); linha++; coluna=1; return UNTERMINATEDCHAR;}
\n				{col = coluna; lin = linha; linha++; coluna=1;}
"\r"				{;}
.				{printf("Line %d, col %d: illegal character (%s)\n", linha, coluna, yytext); yylval.id=(char*)strdup(yytext); coluna+=yyleng;}

%%

int main(int argc, char** argv)
{
	
	option = 0;
	parse=1;
	opt =0;
	smantic = 0;
	if(argc>1){
		if(!strncmp(argv[1],"-l",3)){
			option=1;
			parse=0;
			opt =0;
			smantic = 0;
		}
		else if(!strncmp(argv[1],"-e1",3)){
			option=0;
			parse=0;
			opt =0;
			smantic = 0;
		}
		else if(!strncmp(argv[1],"-e2",3)){
			option = 0;
			parse=1;
			opt =0;
			smantic = 0;
		}
		else if(!strncmp(argv[1],"-t",3)){
			option=0;
			opt = 1;
			parse=1;
			smantic = 0;

		}
		else if(!strncmp(argv[1],"-s",3)){
			option=0;
			opt = 1;
			parse=1;
			smantic = 1;

		}
	}
	yyparse();
	return 0;
}

int yywrap() {
	if(comment){
		printf("Line %d, col %d: unterminated comment\n", linha2, coluna2);
	}
	return 1;
}
void create_token(char* id)
{
	yylval.t = (struct token_*)malloc(sizeof(struct token_));
	
	yylval.t->coluna = coluna;
	
	yylval.t->linha = linha;
	
	yylval.t->id = id;


}

