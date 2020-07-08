%{

//#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string>
#include <map>

#include "y.tab.h"
extern char* yytext;

//#define YYSTYPE double /* double type for Yacc stack */
extern int yylex();
void yyerror(char *);

static std::map<std::string, double> vars;
static std::map<std::string, bool> check;
int count = 1;

%}

%union 
{
	double num;
	std::string *str;
}
%token < num > NUMBER
%token < num > ABS
%token < num > LOG
%token < num > SIN
%token < num > COS
%token < num > NEG
%token < str > VAR
%token < str > LESS
%token < str > PLUS

%left '='
%left '+' '-'
%left '*' '/' '%'
%left '^' NEG ABS COS SIN LOG LESS PLUS 

%type < num > expression

%%
lines
: /* empty */
| lines expression '\n' { printf("%lf\n", $2); count++; }
;

expression                    
: NUMBER { $$ = $1; }

| expression '+' expression { $$ = $1 + $3; }
| expression '-' expression { $$ = $1 - $3; }
| expression '*' expression { $$ = $1 * $3; }
| expression '/' expression { $$ = $1 / $3; }
| expression '%' expression { $$ = (int)$1 % (int)$3; }
| expression '^' expression { $$ = pow($1,$3); }

| ABS '(' expression ')'    { $$ = abs($3); }
| LOG '(' expression ')'    { $$ = log10($3); }
| SIN '(' expression ')'    { $$ = sin($3); }
| COS '(' expression ')'    { $$ = cos($3); }
| NEG '(' expression ')'    { $$ = -$3; }

| VAR { if(check[*$1])
        {
          $$ = vars[*$1];
        }
        else
        {
		  std::cout << "Line " << count << " : " << *$1 << " is undefined. " << std::endl;
		  return 0;
        }
      }
| VAR '=' expression        { $$ = vars[*$1] = $3; check[*$1] = 1; delete $1; }

| PLUS VAR                  { $$ = ++vars[*$2]; }
| VAR PLUS                  { $$ = ++vars[*$1]; }
| LESS VAR                  { $$ = --vars[*$2]; }
| VAR LESS                  { $$ = --vars[*$1]; }

| '(' expression ')' { $$ = $2; }
;

%%
void yyerror(char *s) 
{
	std::cout << "Line " << count << " syntax error with token \" " << yytext << " \" \n";
}
int main(void)
{
    yyparse();
    return 0;
}
