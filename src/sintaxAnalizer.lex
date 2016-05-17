%{
    #include "def.h"
    #include "uthash.h"
    int line = 1;
    Value lexval;
%}

%option noyywrap

spacing [ \t]+
letter [A-Za-z]
digit [0-9]
intconst {digit}+
strconst \"([^\"])*\"
boolconst true|false
id {letter}({letter}|{digit})* 
sugar [(),:;\[\]]

%%

{spacing}       ;
\n              { line++; }
{sugar}         { return yytext[0]; }
=               { return (ASSIGN); }
==              { return (EQUAL); }
!=              { return (NE); }
>               { return (G); }
>=              { return (GE); }
<               { return (L); }
<=              { return (LE); }
+               { return (PLUS); }
-               { return (MINUS); }
*               { return (MUL); }
/               { return (DIV); }
program         { return (PROGRAM); }
type            { return (TYPE); }
var             { return (VAR); }
const           { return (CONST); }
proc            { return (PROC); }
func            { return (FUNC); }
out             { return (OUT); }
inout           { return (INOUT); }
begin           { return (BEGIN); }
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
intconst        { lexval.ival = atoi(yytext); return (INTCONST); }
strconst        { lexval.sval = new_string(yytext); return (STRCONST); }
boolconst       { lexval.bval = ( yytext[0] == 'f' ? FALSE : TRUE); return (BOOLCONST); }
{id}            { lexval.hval = assign_id(yytext); return (ID); }           
.               { stampaErrore(line) }

%%
/*
int assign_id(char *s){ 
    
    int line;
    if((line = lookup(s)) == 0) line = insert(s);
    return line;
}*/

nodo *assign_id(char *s){
    
}

char *new_string(char *s){
    char *p;
    printf("numero %d",s);
    p = malloc(strlen(s)+1);
    strcpy(p, s);
    return(p);
}

void stampaErrore(int l){
    printf("Errore alla linea %d",l);

}