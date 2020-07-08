%{

#include <cstdlib>
#include <string>
#include "y.tab.h"

%}

%%
[0-9]+"."[0-9]+ { yylval.num = atof(yytext); return NUMBER; }
[0-9]+          { yylval.num = atof(yytext); return NUMBER; }
"++"            { yylval.str = new std::string(yytext); return PLUS; }
"--"            { yylval.str = new std::string(yytext); return LESS; }
neg	            { yylval.num = atof(yytext); return NEG; }
cos	            { yylval.num = atof(yytext); return COS; }
sin	            { yylval.num = atof(yytext); return SIN; }
abs	            { yylval.num = atof(yytext); return ABS; }
log            	{ yylval.num = atof(yytext); return LOG; }

[a-zA-Z]([a-zA-Z]|[0-9])* { yylval.str = new std::string(yytext); return VAR; }
[ \t] ;
[\n]            { return '\n'; }
.               { return yytext[0]; }

%%
int yywrap()
{
	return 1;
}
