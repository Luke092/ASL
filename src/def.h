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
typedef union{
    int ival;
    char* sval;
    enum {TRUE, FALSE} bval;
} Value;

/*
 * Node structure definition
 */
struct snode{
    Typenode type;
    Value val;
    struct snode* child, brother;
};

typedef struct snode* pnode;

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
        

#endif /* DEF_H */

