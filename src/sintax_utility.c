/*
 * Author: andrea
 */

#include "def.h"

extern Value lexval;
extern int line;

pnode nontermnode(Nonterminal nonterm){
    
    pnode p = newnode(T_NONTERM);
    p->val.ival = nonterm;
    return (p);
}

pnode keynode(Typenode key){
    
    return (newnode(key));
}

pnode idnode(){
     
    pnode p = newnode(T_ID);
    p->val.sval = lexval.sval;
    return (p);
}

pnode intconstnode(){

    pnode p = newnode(T_INTCONST);
    p->val.ival = lexval.ival;
    return (p);
}

pnode strconstnode(){

    pnode p = newnode(T_STRCONST);
    p->val.sval = lexval.sval;
    return (p);
}

pnode boolconstnode(){
    
    pnode p = newnode(T_BOOLCONST);
    p->val.bval = lexval.bval;
    return (p);
}

pnode modenode(mode m){
    pnode p;
    
    p = newnode(T_MODE);
    p->val.ival = m;
    
    return p;
}

pnode atomicnode(domain d){
    pnode p;
    
    p = newnode(T_ATOMICDOMAIN);
    p->val.ival = d;
    
    return p;
}

pnode exprnode(Typenode t,expr_type e){
    pnode p;
    
    p = newnode(t);
    p->val.ival = e;
    
    return p;
}

pnode newnode(Typenode tnode){
    
    pnode p = malloc(sizeof(Node));
    p->line = line;
    p->type = tnode;
    p->child = p->brother = NULL;
    return (p);
}

void printError(char *id){
    printf("ERRORE: l'id %s non coincide tra begin e end\n",id);
    exit(-1);
}