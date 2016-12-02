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
    struct stLine *back;//puntatore alla symb tab del padre
    int formals1;
    struct stLine **formals2;//array di puntatori ai parametri formali/attuali
    struct stLine *next;//puntatore al nodo successivo della hash table
   
} StructstLine;

typedef  StructstLine *pstLine;

typedef struct st{
    pstLine tab[TOT];//hash table
    struct st *back;//puntatore alla hash del padre
    int oidC;//counter per gli oid
} symbolTable;

typedef  symbolTable *pST;//pointer Symbol Table

void stampa2(pstLine[]),
        start(pnode,pST,ptypeS*),
        nDomain(pnode,ptypeS*),
        decl(pST, pnode,int,ptypeS*),
        printSemanticError(),
        printType(ptypeS),
        optTypeSect_var_const(pnode,int),
        optModuleList(pnode),
        nStatBody(pnode),
        controllaParametroChiamata(pstLine, pnode);
        
ptypeS 
        createType(int,ptypeS,int),
        controllaEsistenzaTipo(pnode),
        modCall(pnode),
        figliExpr(pnode),
        expr(pnode),
        exprBody( pnode),
        nArrayConst(pnode),
        lhs(pnode);

pstLine createLine(char*,int,int,ptypeS,pstLine,int,pstLine[],pstLine),
        insertFindLine(pstLine[],int , char*, int,int,ptypeS,pstLine,int,pstLine[]),
        controllaEsistenzaId(pnode),
        findInSt(pstLine[],char *id);

pST createSymbTab(pST);

int controlConstType(ptypeS,pnode),
        controllaCompatibilitaTipi(ptypeS ,ptypeS),
        assignStat(pnode);
        
pstLine* recuperaFormali(pST,int);

#endif /* DEF_SYMBTAB_H */

