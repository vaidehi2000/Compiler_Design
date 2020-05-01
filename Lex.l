%{
  #include<stdio.h>
  #include "y.tab.h"
  #include<stdlib.h>
%}

%option noyywrap

  
%%
int  {return INT;}
char {return CHAR;}
if	{return IF;}
return  {return RTN;}
read {return RD;}
write {return WT;}
writeln {return WTL;}
break {return BR;}
else  {return ELSE;}
while {return WHILE;}
[0-9]+	{return NUM;}
[a-z][a-zA-Z0-9_]*	{return ID;}
[ \t\f\v\n] {;}
"  "   {return EPS;}
"<=" {return LE;}
">=" {return GE;}
"==" {return EQ;}
"!=" {return NE;}
"||" {return OR;}
"&&" {return AND;}

. {return yytext[0];}
%%

