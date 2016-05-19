%{
    
    #include "parser.h"
    #include "def.h"
    int line = 1;
    Value lexval;
    char* newstring(char* s);
    void stampaErrore(int l);
    int assign_id(char* s);
    nodo *tabella[TOT - 1];
    int prova;
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
"="             { return (ASSIGN); }
"=="            { return (EQUAL); }
"!="            { return (NE); }
">"             { return (G); }
">="            { return (GE); }
"<"             { return (L); }
"<="            { return (LE); }
"+"             { return (PLUS); }
"-"             { return (MINUS); }
"*"             { return (MUL); }
"/"             { return (DIV); }
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
while           { printf("while");return (WHILE); }           
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
{strconst}      { lexval.sval = newstring(yytext); return (STRCONST); }
{boolconst}     { lexval.bval = ( yytext[0] == 'f' ? FALSE : TRUE); return (BOOLCONST); }
{id}            { lexval.ival = assign_id(yytext); printf("ID");return (ID); }           
.               { stampaErrore(line); }

%%

main(){
    yylex();
    
}


int assign_id(char *s){
    
    int puntatore;
    puntatore = insertFind(hash(s),s);
    return puntatore;
}

char *newstring(char *s){
    
    char *p = malloc(strlen(s)+1);
    strcpy(p, s);
    return p;
}

void stampaErrore(int l){
    printf("Errore alla linea %d",l);

}

int hash(char *id){
    int h = 0;
    int i= 0;

    for(i = 0; id[i] != '\0'; i++){
        
        h = ((h << SHIFT)+id[i])%TOT;
        
    }
    //printf("stringa %s HASH %d\n",id,h);
    return h;
    
}

nodo* creaNodo(char *id){
    struct nodo *nuovoNodo;
    nuovoNodo = malloc(sizeof(struct nodo));
    char *p = malloc(strlen(id)+1);
    strcpy(p,id);
    nuovoNodo->stringa = p;
    return nuovoNodo;
}


char* insertFind(int h, char *id){
    char *p;
    nodo *nuovoNodo, *parente;
    if(!tabella[h]){ // se non c'è già un nodo con quell'hash
        
        nuovoNodo = creaNodo(id);
        tabella[h] = nuovoNodo;
        
        
    }else{ // se c'è già un nodo con quell'hash
        
        int trovato = 0;
        int nullo = 0;
        parente = tabella[h];
        while(!nullo && !trovato){
            
            if((strcmp(parente->stringa,id)) == 0){ // controllo il valore della stringa del nodo
                //se trovo un nodo già presente con l stessa stringa
                
                p = parente->stringa;
                return p;

            }else{ //se il nodo ha stringa diversa passo oltre        
                
                    if(parente->fratello != 0){ // se il puntatore è assegnato passo al nodo successivo
                    
                        parente = parente->fratello;
                    
                    }else{//altrimenti sono arrivato in fondo senza trovare un nodo con la stringa uguale  e devo uscire dal while e crearne uno nuovo nodo
                   
                        nullo = 1;
                    }
                
            }
            
        }
        
        nuovoNodo = creaNodo(id);
        parente->fratello = nuovoNodo;
       
    }
    p = nuovoNodo->stringa;
    return p;
}

void stampa(){
    int i;
    for(i =0; i<TOT;i++){
        if(tabella[i]){
            printf("%d stringa:%s \n",i,tabella[i]->stringa);
            nodo *parente = tabella[i]->fratello;
            while(parente){
                printf("CREDIAMOCI");
                printf("%d stringa interna:%s \n",i,parente->stringa);
                parente = parente->fratello;
            }
        }else{
            printf("%d UN CAZZO\n",i);
        }
    }
}