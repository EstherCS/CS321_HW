%{
/* some initial C programs */ 

unsigned linecount = 1;
unsigned end = 0;
%}  
/* regular definitions */
Digit [0-9]
Letter [a-zA-Z]
IntLit {Digit}+
Id {Letter}({Letter}|{Digit}|_)*
%%
"%%".*               {/* skip white spaces */ /* if the comment is start with %% */}
"//".*               {/* skip white spaces */ /* if the comment is start with // */}
[ \t]                {/* skip white spaces */}
\n                   linecount++; 
<<EOF>> 	     {return(30);}
"{%"	             {return(0);}    /* if the comment is {% .... %}, let end = 1 */
"%}"	             {return(58);}   /* let end = 0, because comment is finished  */
"{*"	             {return(0);}    /* if the comment is {* .... *}, let end = 1 */
"*}"	             {return(58);}   /* let end = 0, because comment is finished  */

 /* because of rule, these key words should before ID */
[Bb][Ee][Gg][Ii][Nn]                 {return(10);}
[Ee][Nn][Dd]                         {return(11);}
[Rr][Ee][Aa][Dd]                     {return(12);}
[Ww][Rr][Ii][Tt][Ee]                 {return(13);}
[Ii][Ff]                             {return(14);}
[Tt][Hh][Ee][Nn]                     {return(15);}
[Ee][Ll][Ss][Ee]                     {return(16);}
[Ee][Nn][Dd][Ii][Ff]                 {return(17);}
[Ff][Oo][Rr]                         {return(18);}
[Tt][Oo]                             {return(19);}
[Ee][Nn][Dd][Ff][Oo][Rr]             {return(20);}
[Ww][Hh][Ii][Ll][Ee]                 {return(21);}
[Ee][Nn][Dd][Ww][Hh][Ii][Ll][Ee]     {return(22);}
[Rr][Ee][Pp][Ee][Aa][Tt]             {return(23);}
[Rr][Ee][Pp][Ee][Aa][Tt][Ee][Nn][Dd] {return(24);}
[Dd][Ee][Cc][Ll][Aa][Rr][Ee]         {return(25);}
[Aa][Ss]                             {return(26);}
[Ii][Nn][Tt][Ee][Gg][Ee][Rr]         {return(27);}
[Rr][Ee][Aa][Ll]                     {return(28);}
[Bb][Oo][Oo][Ll]                     {return(29);}
[Ss][Cc][Aa][Nn][Ee][Oo][Ff]         {return(30);}

 /* because of rule, the number which start with 0 should before other integers */
 /* illegal integer error */
[0]+{Digit}+                         {return (61);}

{Id}                  {return(1);} 
{IntLit}              {return(2);}
({IntLit}[.]{IntLit}) {return(3);}
({IntLit}[.]{IntLit})([Ee][+-]?{IntLit})? {return(4);}
\"[^\"\n]*\" {stripquotes(); return(5);}

 /* these return number is from PDF */
","          {return(6);}
";"          {return(7);}
"("          {return(8);}
")"          {return(9);}
":="         {return(31);}
"+"          {return(32);}
"-"          {return(33);}
"*"          {return(34);}
"/"          {return(35);}
"!="         {return(36);}
">"          {return(37);}
"<"          {return(38);}
">="         {return(39);}
"<="         {return(40);}
"=="         {return(41);}
"++"         {return(42);}
"--"         {return(43);}
"%"          {return(44);}
"&&"         {return(45);}
"||"         {return(46);}
"!"          {return(49);}
"+="         {return(50);}
"-="         {return(51);}
"*="         {return(52);}
"/="         {return(53);}
"%="         {return(54);}
"&"          {return(55);}
"|"          {return(56);}
"^"          {return(57);}

 /* find illegal declare */
 /* illegal token error */
{Letter}+(,|[.])(,|[.])+{Letter}+	                 {return (59);}
 /* illegal ID error */
{Digit}+{Letter}+({Letter}|{Digit})+                     {return (60);} 
 /* illegal float point error */ 
({Letter}+[.]{Digit}+|{Digit}+[.]{Letter}+|[.]{Digit}+|{Digit}+[.]|{Digit}+[.]{Digit}+{Letter}+|{Letter}+{Digit}+[.]{Digit}+)     {return(62);}
 /*  illegal exponential float point error */
({IntLit}[.]{IntLit})([Ee][-]?{IntLit}{Letter}+)?        {return(63);}
 /* illegal string error */
\"[^\"\n]*                                               {stripquotes(); return(64);} 
 /* illegal operator error */
([*]|[/]|[+]|[-])([*]|[/]|[+]|[-])+                      {return(65);}
 /* illegal assignment error */
":="([,]|[;]|[:=]|[+]|[-]|[*]|[/]|[>]|[<]|[%])+          {return(66);}
 /* illegal comparisons error */
(([>=]|[<=])[=]+)|([=]+([>=]|[<=])|([>]|[<])([>]|[<])+)  {return(67);}
%%
/* some final C programs */
stripquotes()
{
  /* handling string within a quoted string */
  int frompos, topos=0, numquotes = 2;
  for(frompos=1; frompos<yyleng; frompos++){
    yytext[topos++] = yytext[frompos];
  }
  yyleng -= numquotes;
  yytext[yyleng] = '\0';
}

const char S[] = "          ";
void main()
{
  int i;
  
  i = yylex();
  while (i > -1 && i < 68) 
  {
    if(i == 30 && end == 0)
    {
	printf("Token number : 30, value : \"SCANEOF\"   , line %2d\n", linecount);
	printf("End of the execution\n");
	break;
    }
    else if(i == 0)
	end = 1;
    else if(i == 58)
	end = 0;
    else if(i == 59)
	printf("\n<<< Line %2d, \"%s\" is an illegal token error.\n\n", linecount, yytext);
    else if(i == 60)
	printf("\n<<< Line %2d, \"%s\" is an illegal ID error.\n\n", linecount, yytext);
    else if(i == 61)
 	printf("\n<<< Line %2d, \"%s\" is an illegal integer error.\n\n", linecount, yytext);
    else if(i == 62)
	printf("\n<<< Line %2d, \"%s\" is an illegal float point error.\n\n", linecount, yytext);
    else if(i == 63)
	printf("\n<<< Line %2d, \"%s\" is an illegal exponential float point error.\n\n", linecount, yytext);
    else if(i == 64)
	printf("\n<<< Line %2d, \"%s\" is an illegal string error.\n\n", linecount, yytext);
    else if(i == 65)
	printf("\n<<< Line %2d, \"%s\" is an illegal operator error.\n\n", linecount, yytext);
    else if(i == 66)
	printf("\n<<< Line %2d, \"%s\" is an illegal assignment error.\n\n", linecount, yytext);
    else if(i == 67)
	printf("\n<<< Line %2d, \"%s\" is an illegal comparisons error.\n\n", linecount, yytext);
    else if(end == 0)
	printf("Token number : %2d, value : \"%s\"%s, line %2d\n", i, yytext, (yyleng < 11) ? &S[yyleng] : " ", linecount);

    i = yylex(); 
  }
}
