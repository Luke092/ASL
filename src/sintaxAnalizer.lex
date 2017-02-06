%{
    #include "parser.h"
    #include "def.h"
    int line = 1;
    Value lexval;
%}

%option noyywrap

spacing ([ \t])+
letter [A-Za-z]
digit [0-9]
intconst -?{digit}+
strconst \"([^\"])*\"
boolconst true|false
id {letter}(_?({letter}|{digit})+)* 
sugar [;(),:\[\].]

%%
{spacing}       ;
{sugar}         { return yytext[0]; }     
\n              { line++; }
"=="            { return (EQUAL); }
"="             { return (ASSIGN); }
"!="            { return (NE); }
">"             { return (GT); }
">="            { return (GE); }
"<"             { return (KT); }
"<="            { return (KE);}
"+"             { return (PLUS); }
"-"             { return (MINUS); }
"*"             { return (MUL); }
"/"             { return (DIV); }
program         { return (PROGRAM); }
type            { return (TYPE); }
var             { return (VAR); }
array           { return (ARRAY); }
of              { return (OF); }
const           { return (CONST); }
proc            { return (PROC); }
func            { return (FUNC); }
in              { return (IN); }
out             { return (OUT); }
inout           { return (INOUT); }
begin           { return (T_BEGIN); }
end             { return (END); }
break           { return (BREAK); }
exit            { return (EXIT); }
if              { return (IF); }
then            { return (THEN); }
else            { return (ELSE); }
elsif           { return (ELSIF); }
while           { return (WHILE); }           
do              { return (DO); }
repeat          { return (REPEAT); }
until           { return (UNTIL); }
for             { return (FOR); }
to              { return (TO); }
input           { return (INPUT); }
output          { return (OUTPUT); }
and             { return (AND); }
or              { return (OR); }
not             { return (NOT); }
integer         { return (INTEGER); }
string          { return (STRING); }
boolean         { return (BOOLEAN); }
{intconst}      { lexval.ival = atoi(yytext); return (INTCONST); }
{strconst}      { lexval.sval = assign_id_str(yytext); return (STRCONST); }
{boolconst}     { lexval.bval = ( yytext[0] == 'f' ? FALSE : TRUE); return (BOOLCONST); }
{id}            { lexval.sval = assign_id_str(yytext);return (ID); }      
.               { return (ERROR); }

%%

int assign_id_str(char *s){
    
    int puntatore;
    puntatore = insertFind(hash(s),s);
    return puntatore;
}

int newstring(char *s)
{
  char *p;
  p = malloc(strlen(s)+1);
  strcpy(p, s);
  return(p);
}


