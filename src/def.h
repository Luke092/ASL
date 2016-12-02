/*
 * Author: andrea
 */

#ifndef DEF_H
#define DEF_H
#include <stdlib.h>
#include <stdio.h>
/* 
 * Node type definition
 */
typedef enum {
            T_NONTERM,
            T_ID,
            T_INTCONST,
            T_BOOLCONST,
            T_STRCONST,
            
            T_ATOMICDOMAIN,
            T_MODE,
                    
            T_LOGICEXPR,
            T_COMPEXPR,
            T_MATHEXPR,
            T_NEGEXPR,
            T_MODCALL,
            
            T_EXIT,
            T_BREAK
} Typenode;

typedef enum{
            D_INTEGER,
            D_STRING,
            D_BOOLEAN
} domain;

typedef enum{
            M_IN,
            M_INOUT,
            M_OUT
} mode;

typedef enum{
            E_AND,
            E_OR,
            E_EQ,
            E_NE,
            E_GT,
            E_GE,
            E_LT,
            E_LE,
            E_PLUS,
            E_MINUS,
            E_MUL,
            E_DIV,
            E_UMINUS,
            E_NOT,
            E_FUNC,
            E_PROC
} expr_type;

typedef enum{
            N_PROGRAM,
            N_OPTTYPESECT,
            N_DECL,
            N_IDLIST,
            N_DOMAIN,
            N_ARRAYDOMAIN,
            N_CONST,
            
            N_OPTVARSECT,
            
            N_OPTCONSTSECT,
            N_ARRAYCONST,
            
            N_OPTMODULELIST,
            
            N_PROCDECL,
            N_FUNCDECL,
            
            N_FORMALDECL,
            
            N_STATBODY,
            N_STATLIST,
            N_STAT,
            
            N_CONDEXPR,
                    
            N_EXPRBODY,
                   
                    
            N_ASSIGNSTAT,
            N_LHS,
            N_INDEXING,
            
            N_IFSTAT,
            N_OPTELSEIFSTAT,
            
            N_WHILESTAT,
            N_REPEATSTAT,
            N_FORSTAT,
            
            N_INPUTSTAT,
            N_OUTPUTSTAT,
            
            N_OPTELSEIFEXPR,
            
            N_OPTFORMALLIST,
            N_OPTELSESTAT
} Nonterminal;


/*
 * Value definition
 */

typedef union{
    int ival;
    char *sval;
    enum {TRUE, FALSE} bval;
    
} Value;

/*
 * Node structure definition
 */

typedef struct snode{
    Typenode type;
    Value val;
    int line;
    struct snode *child; 
    struct snode *brother;
} Node;


typedef  Node *pnode;
/*
 * Function definition
 */
pnode nontermnode(Nonterminal),
        idnode(),
        keynode(Typenode),
        intconstnode(),
        strconstnode(),
        boolconstnode(),
        atomicnode(domain),
        modenode(mode),
        exprnode(Typenode,expr_type),
        newnode(Typenode);
  
void printError(char*);

/*
  * definizioni per la tabella di hash
  */

#define TOT 20
#define SHIFT 4

typedef struct nodo nodo;

struct nodo{
    char *stringa;
    nodo *fratello;
};


int hash(char *id);

nodo* creaNodo(char *id);

char* insertFind(int h, char *id);

void stampa();




#endif /* DEF_H */

