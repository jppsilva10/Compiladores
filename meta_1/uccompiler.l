 //João Pedro Pacheco Silva Nº 218298731
 //Luís Carlos Lopes Loureiro Nº 2018297934
%{
int option;
int linha=1;
int coluna=1;
int linha2=1;
int coluna2=1;
int comment=0;
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
"/*"				{BEGIN Comentario1; coluna2=coluna; linha2=linha; coluna+=yyleng; comment=1;}
<Comentario1>.			{coluna+=yyleng;;}
<Comentario1>\n			{linha++; coluna=1;}
<Comentario1>"*/"		{BEGIN 0; coluna+=yyleng; comment=0;}

"//"				{BEGIN Comentario2; coluna+=yyleng;}
<Comentario2>.			{coluna+=yyleng;}
<Comentario2>"\n"		{BEGIN 0; linha++; coluna=1;}

"char"				{if(option) printf("CHAR\n"); coluna+=yyleng;}
"else"				{if(option) printf("ELSE\n"); coluna+=yyleng;}
"while"				{if(option) printf("WHILE\n"); coluna+=yyleng;}
"if"				{if(option) printf("IF\n"); coluna+=yyleng;}
"int"				{if(option) printf("INT\n"); coluna+=yyleng;}
"short"				{if(option) printf("SHORT\n"); coluna+=yyleng;}
"double"			{if(option) printf("DOUBLE\n"); coluna+=yyleng;}
"return"			{if(option) printf("RETURN\n"); coluna+=yyleng;}
"void"				{if(option) printf("VOID\n"); coluna+=yyleng;}
"&&"				{if(option) printf("AND\n"); coluna+=yyleng;}
"&"				{if(option) printf("BITWISEAND\n"); coluna+=yyleng;}
"||"				{if(option) printf("OR\n"); coluna+=yyleng;}
"|"				{if(option) printf("BITWISEOR\n"); coluna+=yyleng;}
"^"				{if(option) printf("BITWISEXOR\n"); coluna+=yyleng;}
"=="				{if(option) printf("EQ\n"); coluna+=yyleng;}
"="				{if(option) printf("ASSIGN\n"); coluna+=yyleng;}
"*"				{if(option) printf("MUL\n"); coluna+=yyleng;}
","				{if(option) printf("COMMA\n"); coluna+=yyleng;}
"/"				{if(option) printf("DIV\n"); coluna+=yyleng;}
">="				{if(option) printf("GE\n"); coluna+=yyleng;}
">"				{if(option) printf("GT\n"); coluna+=yyleng;}
"{"				{if(option) printf("LBRACE\n"); coluna+=yyleng;}
"<="				{if(option) printf("LE\n"); coluna+=yyleng;}
"("				{if(option) printf("LPAR\n"); coluna+=yyleng;}
"<"				{if(option) printf("LT\n"); coluna+=yyleng;}
"-"				{if(option) printf("MINUS\n"); coluna+=yyleng;}
"%"				{if(option) printf("MOD\n"); coluna+=yyleng;}
"!="				{if(option) printf("NE\n"); coluna+=yyleng;}
"!"				{if(option) printf("NOT\n"); coluna+=yyleng;}
"+"				{if(option) printf("PLUS\n"); coluna+=yyleng;}
"}"				{if(option) printf("RBRACE\n"); coluna+=yyleng;}
")"				{if(option) printf("RPAR\n"); coluna+=yyleng;}
";"				{if(option) printf("SEMI\n"); coluna+=yyleng;}
{RESERVED}			{if(option) printf("RESERVED(%s)\n", yytext); coluna+=yyleng;}
{ID}				{if(option) printf("ID(%s)\n", yytext); coluna+=yyleng;}
{INTLIT}			{if(option) printf("INTLIT(%s)\n", yytext); coluna+=yyleng;}
{REALLIT}			{if(option) printf("REALLIT(%s)\n", yytext); coluna+=yyleng;}
'{CHRLIT}'			{if(option) printf("CHRLIT(%s)\n", yytext); coluna+=yyleng;}
{INVALIDCHAR}			{printf("Line %d, col %d: invalid char constant (%s)\n", linha, coluna, yytext); coluna+=yyleng;}
{UNTERMINATEDCHAR}		{printf("Line %d, col %d: unterminated char constant\n", linha, coluna); linha++; coluna=1;}
\n				{linha++; coluna=1;}
"\r"				{;}
.				{printf("Line %d, col %d: illegal character (%s)\n", linha, coluna, yytext); coluna+=yyleng;}

%%
int main(int argc, char** argv)
{
	option=0;
	if(argc>1){
		if(!strncmp(argv[1],"-l",3)){
			option=1;
		}
	}
	yylex(); 
	return 0;
}
int yywrap() {
	if(comment){
		printf("Line %d, col %d: unterminated comment\n", linha2, coluna2);
	}
	return 1;
}
