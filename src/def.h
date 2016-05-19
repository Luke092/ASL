#ifndef DEF_H
#define DEF_H




/* 
 * Node type definition
 */
typedef enum {
    T_NONTERM,
            T_ID,
            T_INTCONST,
            T_BOOLCONST,
            T_STRCONST,
            T_INTEGER,
            T_STRING,
            T_BOOLEAN,
            
            T_ATOMICDOMAIN,
            T_MODE
} Typenode;

typedef enum{
    N_PROGRAM,
            N_OPTTYPESECT,
            N_DECL,
            N_IDLIST,
            N_DOMAIN,
            N_DOMAINARRAY,
            N_OPTVARSECT,
            N_OPTCONSTSECT,
            N_CONST,
            N_ARRAYCONST,
            N_OPTMODULELIST,
            N_MODULELIST,
            N_PROCDECL,
            N_FUNCDECL,
            N_OPTFORMALLIST,
            N_FORMALDECL,
            N_STATBODY,
            N_EXPRBODY,
            N_STATLIST,
            N_STAT,
            N_ASSIGNSTAT,
            N_LHS,
            N_INDEXING,
            N_IFSTAT,
            N_OPTELSEIFSTATLIST,
            N_WHILESTAT,
            N_REPEATSTAT,
            N_FORSTAT,
            N_INPUTSTAT,
            N_OUTPUTSTAT,
            N_MODULECALL,
            N_OPTEXPRLIST
} Nonterminal;


/*
 * Value definition
 */


    // nodi per la funzione di hash

typedef struct nodo nodo;

struct nodo{
    char *stringa;
    nodo *fratello;
};

//typedef struct nodo nodo;

#define TOT 1987
#define SHIFT 4

//nodo *tabella[TOT - 1];

typedef union{
    int ival;
    char *sval;
    enum {TRUE, FALSE} bval;
    //nodo* hval;
} Value;

/*
 * Node structure definition
 */

typedef struct snode* pnode;

struct snode{
    Typenode type;
    Value val;
    struct snode* child; 
    struct snode* brother;
};



/*
 * Function definition
 */
pnode nontermnode(Nonterminal),
        idnode(),
        keynode(Typenode),
        intconstnode(),
        strconstnode(),
        boolconstnode(),
        newnode(Typenode);
        
        //funzioni per la tabella di hash degli id

char* insertFind(int h, char *id);

nodo* creaNodo(char *id);

int hash(char *id);
        

#endif /* DEF_H */

