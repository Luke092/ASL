/*
 * Author: andrea
 */

#include "def.h"
#include "def_symbtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* tabtypes[] =
{
            "T_NONTERM",
            "T_ID",
            "T_INTCONST",
            "T_BOOLCONST",
            "T_STRCONST",
            
            "T_ATOMICDOMAIN",
            "T_MODE",
                    
            "T_LOGICEXPR",
            "T_COMPEXPR",
            "T_MATHEXPR",
            "T_NEGEXPR",
            "T_MODCALL",
            
            "T_EXIT",
            "T_BREAK"
};

char* domaintypes[]=
{
            "D_INTEGER",
            "D_STRING",
            "D_BOOLEAN"
};

char* modetypes[]=
{
            "M_IN",
            "M_OUT",
            "M_INOUT"
};

char* exprtype[]={
            "E_AND",
            "E_OR",
            "E_EQ",
            "E_NE",
            "E_GT",
            "E_GE",
            "E_LT",
            "E_LE",
            "E_PLUS",
            "E_MINUS",
            "E_MUL",
            "E_DIV",
            "E_UMINUS",
            "E_NOT",
            "E_FUNC",
            "E_PROC"
            
};

char* tabnonterm[] =
{
               "N_PROGRAM",
            "N_OPTTYPESECT",
            "N_DECL",
            "N_IDLIST",
            "N_DOMAIN",
            "N_ARRAYDOMAIN",
            "N_CONST",
            
            "N_OPTVARSECT",
            
            "N_OPTCONSTSECT",
            "N_ARRAYCONST",
            
            "N_OPTMODULELIST",
            
            "N_PROCDECL",
            "N_FUNCDECL",
            
            "N_FORMALDECL",
            
            "N_STATBODY",
            "N_STATLIST",
            "N_STAT",
            
            "N_CONDEXPR",
            
            "N_EXPRBODY",
                   
                    
            "N_ASSIGNSTAT",
            "N_LHS",
            "N_INDEXING",
            
            "N_IFSTAT",
            "N_OPTELSEIFSTAT",
            
            "N_WHILESTAT",
            "N_REPEATSTAT",
            "N_FORSTAT",
            
            "N_INPUTSTAT",
            "N_OUTPUTSTAT",
            
            "N_OPTELSEIFEXPR",
            
            "N_OPTFORMALLIST",
            "N_OPTELSESTAT"
};

void treeprint(pnode root, int indent,FILE *fp)
{      
  int j;
  pnode p;
  
  for(j=0; j<indent; j++)
    fprintf(fp,"    ");
  
  fprintf(fp,"%s", (root->type == T_NONTERM ? tabnonterm[root->val.ival] : tabtypes[root->type]));
  if(root->type == T_ID || root->type == T_STRCONST)
    fprintf(fp," (%s)", root->val.sval);
  else if(root->type == T_INTCONST)
    fprintf(fp," (%d)", root->val.ival);
  else if(root->type == T_BOOLCONST)
    fprintf(fp," (%s)", (root->val.ival == TRUE ? "true" : "false"));
  else if(root->type == T_ATOMICDOMAIN){      
      fprintf(fp," (%s)", domaintypes[root->val.ival]);}
  else if(root->type == T_MODE){    
      fprintf(fp," (%s)",modetypes[root->val.ival]);
  }
  else if(root->type == T_LOGICEXPR || root->type == T_COMPEXPR || root->type == T_MATHEXPR || root->type == T_NEGEXPR || root->type == T_MODCALL){
      fprintf(fp," (%s)",exprtype[root->val.ival]);
  }
  fprintf(fp,"\n");
  for(p=root->child; p != NULL; p = p->brother)
  {
      treeprint(p, indent+1,fp);
  }
}

char* domtypes[]=
{
            "S_INTEGER",
            "S_STRING",
            "S_BOOLEAN",
            "S_ARRAY"
};

char* classe[]=
{
      "S_TYPE",
      "S_VAR",
      "S_CONST",
      "S_FUNC",
      "S_PROC",
      "S_IN", 
      "S_OUT",
      "S_INOUT"      
};



void stampa2(pstLine stab[],FILE *sp){
   
    fprintf(sp,"\n \n *******STAMPA STAB******** \n \n");
    int i;
   
    for(i =0; i<TOT;i++){
        fprintf(sp,"\n#%d\n",i);
        if(stab[i]){
            
            fprintf(sp,"\noid:%d\nid:%s \n",stab[i]->oid,stab[i]->name);
            if(stab[i]->root!=NULL){printType(stab[i]->root,sp);}
            if(stab[i]->formals1!=0){fprintf(sp,"\tn formali:%d",stab[i]->formals1);}
            fprintf(sp,"\t classe:%s",classe[stab[i]->classe]);
            pstLine parente = stab[i]->next;
            while(parente!=NULL){
         
                fprintf(sp,"\n \t oid:%d id:%s \n",parente->oid,parente->name);
                if(parente->root!=NULL){printType(parente->root,sp);}
                if(parente->formals1!=0){fprintf(sp,"\tn formali:%d",parente->formals1);}
                fprintf(sp,"\tclasse:%s",classe[parente->classe]);
                parente = parente->next;
            }
        }
    }
    fprintf(sp,"\n \n *******FINE******** \n \n");
}


void printType(ptypeS type, FILE *sp){
    
  fprintf(sp,"    ");
  fprintf(sp,"%s ",domtypes[type->domain]);
  if(type->domain==3){
      fprintf(sp,"[%d]",type->dim);
      printType(type->child,sp);
  }
  fprintf(sp,"\n");
  
}
/*
void stampa2(pstLine stab[]){
   
    printf("\n \n *******STAMPA STAB******** \n \n");
    int i;
   
    for(i =0; i<TOT;i++){
        printf("\n#%d\n",i);
        if(stab[i]){
            
            printf("\noid:%d\nid:%s \n",stab[i]->oid,stab[i]->name);
            if(stab[i]->root!=NULL){printType(stab[i]->root);}
            if(stab[i]->formals1!=0){printf("\tn formali:%d",stab[i]->formals1);}
            printf("\t classe:%s",classe[stab[i]->classe]);
            pstLine parente = stab[i]->next;
            while(parente!=NULL){
         
                printf("\n \t oid:%d id:%s \n",parente->oid,parente->name);
                if(parente->root!=NULL){printType(parente->root);}
                if(parente->formals1!=0){printf("\tn formali:%d",parente->formals1);}
                printf("\tclasse:%s",classe[parente->classe]);
                parente = parente->next;
            }
        }
    }
    printf("\n \n *******FINE******** \n \n");
}


void printType(ptypeS type){
    
  printf("    ");
  printf("%s ",domtypes[type->domain]);
  if(type->domain==3){
      printf("[%d]",type->dim);
      printType(type->child);
  }
  printf("\n");
  
}*/


/*
void printError(char *errorMex){
    printf("\nERRORE: %s \n",errorMex);
}*/