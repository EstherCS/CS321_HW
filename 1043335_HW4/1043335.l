%{
/* some initial C programs */ 
#include <stdio.h>
#include "y.tab.h"
%}  
/* regular definitions */
Digit [0-9]
Letter [a-zA-Z]
IntLit {Digit}+
Id {Letter}({Letter}|{Digit}|_)*

%%


"#".*      {}
"="             {return yytext[0];}
"("             {return yytext[0];}
")"             {return yytext[0];}
","             {return yytext[0];}
{IntLit}                 {yylval.num = atof(yytext); return NUMBER;}
[Ii][Nn][Pp][Uu][Tt] { return INPUT;}
[Oo][Uu][Tt][Pp][Uu][Tt] {return OUTPUT;}
BUFF            { yylval.var = strdup(yytext); return OPERATOR; }
NOT             { yylval.var = strdup(yytext); return OPERATOR; }
NOR	            { yylval.var = strdup(yytext); return TWO_OP; }
XNOR	        { yylval.var = strdup(yytext); return TWO_OP; }
AND	            { yylval.var = strdup(yytext); return TWO_OP; }
NAND	        { yylval.var = strdup(yytext); return TWO_OP; }
OR            	{ yylval.var = strdup(yytext); return TWO_OP; }
XOR            	{ yylval.var = strdup(yytext); return TWO_OP; }

[ \t] ;
[\n] { return '\n'; }
. { return yytext[0]; }

%%
int yywrap()
{
	return 1;
}
