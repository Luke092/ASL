/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Author: andrea
 */

#ifndef DEF_SYMBTAB_H
#define DEF_SYMBTAB_H
#include "def_codegen.h"
#include "utilities.h"

extern int stampaSymbtab;
extern FILE *sp;

/*
 * Lista concatenata per le varibili che non si possono assegnare
 */
typedef struct varS{
    char *varId;
    struct varS *next;
   
} varStruct;

typedef  varStruct *pvarS;

typedef struct typeS{
    enum {S_INTEGER,S_STRING,S_BOOLEAN,S_ARRAY} domain;
    int costante;//se diventa 1 vuol dire che rappresenta il tipo di una costante
    int dim;
    struct typeS *child; 
   
} TypeStruct;

typedef  TypeStruct *ptypeS;

typedef struct stLine{ //stLine = symbol table line
    char *name;
    int oid;
    enum {S_TYPE,S_VAR,S_CONST,S_FUNC,S_PROC,S_IN, S_OUT,S_INOUT} classe;
    ptypeS root;//puntatore al tipo
    struct stLine *local;//puntatore alla symb tab locale
    //struct stLine *back;//puntatore alla symb tab del padre
    int formals1;
    struct stLine **formals2;//array di puntatori ai parametri formali/attuali
    struct stLine *next;//puntatore al nodo successivo della hash table
    
    int mid; // module id, univoco in tutto il codice
} StructstLine;

typedef  StructstLine *pstLine;

typedef struct st{
    pstLine tab[TOT];//hash table
    struct st *back;//puntatore alla hash del padre
    int oidC;//counter per gli oid
    int aux_count; // numero di paramentri ausiliari
    int offset;
} symbolTable;

typedef  symbolTable *pST;//pointer Symbol Table

void stampa2(pstLine[], FILE*),
        treeprint(pnode , int, FILE*),
        nDomain(pnode,ptypeS*),
        nArrayConst(pnode,ptypeS*),
        printSemanticError(),
        pulisciSymbTab(pST),
        printType(ptypeS, FILE*),
        aggiungiProibita(pnode),
        rimuoviProibita(pnode);

Code start(pnode,pST,ptypeS*),
        optTypeSect_var_const(pnode,int),
        decl(pST, pnode,int,ptypeS*),
        statList(pnode),
        assignStat(pnode),
        lhs(pnode,ptypeS*),
        exprBody( pnode,ptypeS*),
        expr(pnode,ptypeS*),
        condExpr(pnode,ptypeS*),
        ifStat(pnode),
        whileStat(pnode),
        repeatStat(pnode),
        forStat(pnode),
        optModuleList(pnode),
        modCall(pnode,ptypeS*),
        controllaParametroChiamata(pstLine, pnode);
        
ptypeS 
        createType(int,ptypeS,int),
        controllaEsistenzaTipo(pnode);
       

pstLine createLine(char*,int,int,ptypeS,pstLine,int,pstLine[],pstLine),
        insertFindLine(pstLine[],int , char*, int,int,ptypeS,pstLine,int,pstLine[]),
        controllaEsistenzaId(char*, int*, int*, int*),
        findInSt(pstLine[],char *id);

pST createSymbTab(pST);

int controlConstType(ptypeS,pnode),
        optFormalList(pST,pnode),
        controllaCompatibilitaTipi(ptypeS ,ptypeS);
        
        
pstLine* recuperaFormali(pST,int);

int controllaProibite(pnode),
    count_local_objs(pstLine[]); // funzione per contare gli oggetti locali

char* getArrayFormat(ptypeS);

#endif /* DEF_SYMBTAB_H */

