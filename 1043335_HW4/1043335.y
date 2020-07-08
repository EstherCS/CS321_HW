%{

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string>
#include <map>
#include "1043335.cpp"

#include "y.tab.h"
extern char* yytext;

//#define YYSTYPE double /* double type for Yacc stack */
extern int yylex();
void yyerror(char *);
int count = 1;
%}

%union 
{
	int num;
	char *var;
}
%token INPUT OUTPUT
%token < num> NUMBER
%token < var > OPERATOR
%token < var > TWO_OP


%type < num > expression
%type < num > term

%%
lines
: /* empty */
| lines '\n' {count++;}
| lines expression '\n' { count++; }
;

expression
: INPUT '(' term ')'   
	{ 
	$$ = $3; 
	in.push_back($3); 
	Inline++;
	}
| OUTPUT'(' term ')'    
	{ 
	$$ = $3; 
	output.push_back($3); 
	Outline++;
	}
| term '=' OPERATOR '(' term ')'
	{
	gate.push_back($1); 
	gate.push_back(0); 
	name.push_back($3);
	gate.push_back($5); 
	gate.push_back('.'); 
	Gcount +=4;
	}
| term '=' TWO_OP '(' term ',' term ')' 
	{
	gate.push_back($1); 
	gate.push_back(0); 
	name.push_back($3);
	gate.push_back($5); 
	gate.push_back($7); 
	Gcount +=4;
	}

;

term
: NUMBER { $$ = $1; }

%%
void yyerror(char *s) 
{
	std::cout << "Line " << count << " syntax error with token \" " << yytext << " \" \n";
}

int main()
{
	yyparse();
	vector< vector<int> >route;
	route.push_back(vector<int>());
	int level = 0;
	FindLevel(Gcount, level, route);
	Draw(Gcount, level, route);
    return 0;
}

