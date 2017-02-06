%{
#include "def.h"

#define YYSTYPE pnode
extern char *yytext;
extern Value lexval;
extern int line;
extern FILE *yyin;
extern pnode root;
%}

%token ASSIGN
%token EQUAL
%token NE
%token GT
%token GE
%token KT
%token KE
%token PLUS
%token MINUS
%token MUL
%token DIV
%token PROGRAM
%token TYPE
%token VAR
%token CONST
%token PROC
%token FUNC
%token IN
%token OUT
%token INOUT
%token T_BEGIN
%token END
%token BREAK
%token EXIT
%token IF
%token THEN
%token ELSE
%token ELSIF
%token WHILE
%token DO
%token REPEAT
%token UNTIL
%token FOR
%token TO
%token INPUT
%token OUTPUT
%token AND
%token OR
%token NOT
%token INTEGER
%token STRING
%token BOOLEAN
%token INTCONST
%token BOOLCONST
%token STRCONST
%token ID
%token ERROR
%token ARRAY
%token OF


%%

program :           PROGRAM ID {$$ = idnode();} 
                    opt-type-sect //$4
                    opt-var-sect //$5
                    opt-const-sect //$6
                    opt-module-list //$7
                    stat-body '.'//$8
                    {root=$$=nontermnode(N_PROGRAM); 
                     $$->child=$3; 
                     $3->brother=$4;
                     $4->brother=$5;
                     $5->brother=$6;
                     $6->brother=$7;
                     $7->brother=$8;
                    }
                    ;

opt-type-sect :     TYPE decl-list  {$$=nontermnode(N_OPTTYPESECT);$$->child=$2;}
                    | {$$=nontermnode(N_OPTTYPESECT);}
                    ;

decl-list :         decl ';' decl-list {$$=$1; $1->brother=$3;}
                    |decl ';' {$$=$1;}
                    ;

decl :              id-list ':' domain {$$=nontermnode(N_DECL);$$->child=nontermnode(N_IDLIST);$$->child->brother=$3;$$->child->child=$1;}
                    ;

id-list :           ID {$$ = idnode();} ',' id-list {$$=$2;$2->brother=$4;}
                    |ID {$1=idnode();$$=$1;}
                    ;

domain :            atomic-domain {$$=nontermnode(N_DOMAIN);$$->child=$1;}
                    |array-domain {$$=nontermnode(N_DOMAIN);$$->child=$1;}
                    |ID {$$=nontermnode(N_DOMAIN);$1=idnode();$$->child=$1;}
                    ;

atomic-domain :     INTEGER {$$=atomicnode(D_INTEGER);}
                    |STRING {$$=atomicnode(D_STRING);}
                    |BOOLEAN {$$=atomicnode(D_BOOLEAN);}
                    ;

array-domain :      ARRAY '[' INTCONST {$$=intconstnode();}']' OF domain {$$=nontermnode(N_ARRAYDOMAIN);$$->child=$4;$$->child->brother=$7;}
                    ;

opt-var-sect :      VAR decl-list  {$$=nontermnode(N_OPTVARSECT);$$->child=$2;}
                    |  {$$=nontermnode(N_OPTVARSECT);}
                    ;

opt-const-sect :    CONST const-list-decl {$$=nontermnode(N_OPTCONSTSECT);$$->child=$2;}
                    |  {$$=nontermnode(N_OPTCONSTSECT);}
                    ;

const-list-decl :   const-decl const-list-decl  {$$=$1;$1->brother->brother=$2;}
                    |const-decl  {$$=$1;}
                    ;

const-decl :        decl ASSIGN const ';'  {$$=$1;$1->brother=$3;}
                    ;

const :             INTCONST  {$$=nontermnode(N_CONST);$$->child=intconstnode();}
                    |STRCONST  {$$=nontermnode(N_CONST);$$->child=strconstnode();}
                    |BOOLCONST {$$=nontermnode(N_CONST);$$->child=boolconstnode();}
                    |array-const  {$$=nontermnode(N_CONST);$$->child=nontermnode(N_ARRAYCONST);$$->child->child=$1;}
                    ;

array-const :       '[' const-list ']'{$$=$2;}
                    ;

const-list :        const ',' const-list {$$=$1;$1->brother=$3;}
                    |const {$$=$1;}
                    ;

opt-module-list :   module-list {$$=nontermnode(N_OPTMODULELIST);$$->child=$1;}
                    | {$$=nontermnode(N_OPTMODULELIST);}
                    ;

module-list :       module-decl module-list {$$=$1;$1->brother=$2;}
                    |module-decl {$$=$1;}
                    ;

module-decl :       procedure-decl {$$=$1;}
                    |function-decl {$$=$1;}
                    ;

procedure-decl :    PROC ID {$$=idnode();} '(' opt-formal-list ')' opt-type-sect opt-var-sect opt-const-sect opt-module-list stat-body ';' 
                        {$$=nontermnode(N_PROCDECL);$$->child=$3;$3->brother=$5;//$5 opt-formal-list
                        $5->brother=$7;//$7=opt-type-sect
                        $7->brother=$8;//$8=opt-var-sect
                        $8->brother=$9;//$9=opt-const-sect
                        $9->brother=$10;//$10=opt-module-list
                        $10->brother=$11;//$11=stat-body
                        }
                        

function-decl :     FUNC ID {$$=idnode();} '(' opt-formal-list ')' ':' domain opt-type-sect opt-const-sect opt-module-list expr-body';'
                        {$$=nontermnode(N_FUNCDECL);$$->child=$3;$3->brother=$5;//$5 opt-formal-list
                         $5->brother=$8;//$8=domain
                         $8->brother=$9;//$9=opt-type-sect
                         $9->brother=$10;//$10=opt-const-sect
                         $10->brother=$11;//$11=opt-module-list
                         $11->brother=$12;}
                     

opt-formal-list :   formal-list {$$=nontermnode(N_OPTFORMALLIST);$$->child=$1;}
                    | {$$=nontermnode(N_OPTFORMALLIST);}
                    ;

formal-list :       formal-decl ',' formal-list {$$=$1;$1->brother=$3;}
                    |formal-decl {$$=$1;}
                    ;

formal-decl :       mode decl {$$=nontermnode(N_FORMALDECL);$$->child=$1;$1->brother=$2;}
                    ;

mode :              {$$ = modenode(M_IN);}
                    | OUT {$$ = modenode(M_OUT);}
                    | INOUT {$$ = modenode(M_INOUT);}
                    ;

stat-body :         T_BEGIN ID {$$=idnode();} stat-list END ID {$$=idnode();} 
                        {$$=nontermnode(N_STATBODY);$$->child=$3;$3->brother=nontermnode(N_STATLIST);$3->brother->child=$4;$3->brother->brother=$7;
                            if($3->val.sval != $7->val.sval){printError($3->val.sval);}
                        }
                    ;

expr-body :         T_BEGIN ID {$$=idnode();} expr END ID {$$=idnode();} 
                        {$$=nontermnode(N_EXPRBODY);$$->child=$3;$3->brother=$4;$3->brother->brother=$7;
                            if($3->val.sval != $7->val.sval){printError($3->val.sval);}
                        }
                    ;

stat-list :         stat ';' stat-list {$$=$1;$1->brother=$3;}
                    |stat ';' {$$=$1;}
                    ;

stat :              assign-stat {$$=nontermnode(N_STAT);$$->child=$1;}
                    |if-stat {$$=nontermnode(N_STAT);$$->child=$1;}
                    |while-stat {$$=nontermnode(N_STAT);$$->child=$1;}
                    |repeat-stat {$$=nontermnode(N_STAT);$$->child=$1;}
                    |for-stat {$$=nontermnode(N_STAT);$$->child=$1;}
                    |input-stat {$$=nontermnode(N_STAT);$$->child=$1;}
                    |output-stat {$$=nontermnode(N_STAT);$$->child=$1;}
                    |module-call {$$=nontermnode(N_STAT);$$->child=$1;$1->val.ival=E_PROC;}
                    |BREAK {$$=nontermnode(N_STAT);$1=newnode(T_BREAK);$$->child=$1;}
                    |EXIT {$$=nontermnode(N_STAT);$1=newnode(T_EXIT);$$->child=$1;}
                    ;

input-stat :        INPUT ID {$$=nontermnode(N_INPUTSTAT);$2=idnode();$$->child=$2;}
                    ;

output-stat :       OUTPUT expr {$$=nontermnode(N_OUTPUTSTAT);$$->child=$2;}
                    ;

for-stat :          FOR ID {$$=idnode();} ASSIGN expr TO expr DO stat-list END
                    {$$=nontermnode(N_FORSTAT);
                     $$->child=$3; $3->brother=$5;$5->brother=$7;$7->brother=nontermnode(N_STATLIST);
                     $7->brother->child=$9;
                    }
                    ;

while-stat :        WHILE expr DO stat-list END {$$=nontermnode(N_WHILESTAT);$$->child=$2;$2->brother=nontermnode(N_STATLIST);$2->brother->child=$4;}
                    ;

repeat-stat :       REPEAT stat-list UNTIL expr 
                    {$$=nontermnode(N_REPEATSTAT);
                     $$->child=nontermnode(N_STATLIST);
                     $$->child->child=$2; 
                     $$->child->brother=$4;
                    }
                    ;

if-stat :           IF expr THEN stat-list opt-elsif-stat-list opt-else-stat END 
                    {$$=nontermnode(N_IFSTAT);$$->child=$2;$2->brother=nontermnode(N_STATLIST);
                    $2->brother->child = $4;
                    $2->brother->brother=nontermnode(N_OPTELSEIFSTAT);
                    $2->brother->brother->brother=$6;
                    $2->brother->brother->child=$5;}
                    ;

opt-elsif-stat-list : ELSIF expr THEN stat-list opt-elsif-stat-list {$$=$2;$2->brother=nontermnode(N_STATLIST);$2->brother->child=$4;$2->brother->brother=$5;}
                    | {$$=NULL;}
                    ;

opt-else-stat :     ELSE stat-list {$$=nontermnode(N_STATLIST);$$->child=$2;}
                    | {$$=NULL;}
                    ;

assign-stat :       left-hand-side ASSIGN expr {$$=nontermnode(N_ASSIGNSTAT);$$->child=$1;$1->brother=$3;}
                    ;

left-hand-side :    ID {$$=nontermnode(N_LHS);$1=idnode();$$->child=$1;}
                    |indexing {$$=nontermnode(N_LHS);$$->child=$1;}
                    ;

indexing :          left-hand-side '[' expr ']' {$$=nontermnode(N_INDEXING);$$->child=$1;$1->brother=$3;}
                    ;

expr :              expr bool-op bool-term {$$=$2;$2->child=$1;$1->brother=$3;}
                    |bool-term {$$=$1;}
                    ;

bool-op :           AND {$$=exprnode(T_LOGICEXPR,E_AND);}
                    |OR {$$=exprnode(T_LOGICEXPR,E_OR);}
                    ;

bool-term :         comp-term comp-op comp-term {$$=$2;$1->brother=$3;$2->child=$1;}
                    |comp-term {$$=$1;}
                    ;

comp-op :           EQUAL {$$=exprnode(T_COMPEXPR,E_EQ);}
                    |NE {$$=exprnode(T_COMPEXPR,E_NE);}
                    |GT {$$=exprnode(T_COMPEXPR,E_GT);}
                    |GE {$$=exprnode(T_COMPEXPR,E_GE);}
                    |KT {$$=exprnode(T_COMPEXPR,E_LT);}
                    |KE {$$=exprnode(T_COMPEXPR,E_LE);}
                    ;

comp-term :         comp-term add-op term {$$=$2;$2->child=$1;$1->brother=$3;}
                    |term {$$=$1;}
                    ;

add-op :            PLUS {$$=exprnode(T_MATHEXPR,E_PLUS);}
                    |MINUS {$$=exprnode(T_MATHEXPR,E_MINUS);}
                    ;

term :              term mul-op factor {$$=$2;$2->child=$1;$1->brother=$3;}
                    |factor {$$=$1;}
                    ;

mul-op :            MUL {$$=exprnode(T_MATHEXPR,E_MUL);}
                    |DIV {$$=exprnode(T_MATHEXPR,E_DIV);}
                    ;

factor :            unary-op factor {$$=$1;$1->child=$2;}
                    |'(' expr ')' {$$=$2;}
                    |left-hand-side {$$=$1;}
                    |const {$$=$1;}
                    |cond-expr {$$=$1;}
                    |module-call {$$=$1;$1->val.ival=E_FUNC;}
                    ;

unary-op :          MINUS {$$=exprnode(T_NEGEXPR,E_UMINUS);}
                    |NOT {$$=exprnode(T_NEGEXPR,E_NOT);} 
                    ;

cond-expr :         IF expr THEN expr opt-elsif-expr-list ELSE expr END 
                    {$$=nontermnode(N_CONDEXPR);$$->child=$2;$2->brother=$4;
                    $4->brother=nontermnode(N_OPTELSEIFEXPR);$4->brother->brother=$7;
                    $4->brother->child=$5;}
                    ;

opt-elsif-expr-list : ELSIF expr THEN expr opt-elsif-expr-list {$$=$2;$2->brother=$4;$4->brother=$5;}
                      | {$$=NULL;}
                      ;

module-call :       ID {$$=idnode();} '(' opt-expr-list ')' {$$=newnode(T_MODCALL);$$->child=$2;$2->brother=$4;}
                    ;

opt-expr-list :     expr-list {$$=$1;}
                    | {$$=NULL;}
                    ;

expr-list :         expr ',' expr-list {$$=$1;$1->brother=$3;}
                    |expr {$$=$1;}
                    ;

%%

void yyerror(){
    fprintf(stderr, "Errore lessicale sul simbolo '%s' alla linea %d\n\n",yytext,line);
}