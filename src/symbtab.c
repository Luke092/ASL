/*
 * Author: andrea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "def_symbtab.h"

char *idErr;//id della var che da errore
int line;//linea dell'errore

void printSemanticError(){
    printf("ERRORE #%d: causato probabilmente da %s\n",line,idErr);
}

pST stab;//puntatore alla symbtab locale

ptypeS tipoIntero;//ptypeS che rappresenta un intero
ptypeS tipoString;//ptypeS che rappresenta una stringa
ptypeS tipoBoolean;//ptypeS che rappresenta un bool

pST createSymbTab(pST back){
    printf("createSymbTab\n");
    
    tipoIntero=createType(0,NULL,0);
    tipoString=createType(1,NULL,0);
    tipoBoolean=createType(2,NULL,0);
    
    pST s=malloc(sizeof(symbolTable));//symbol table
    pulisciSymbTab(s);//settiamo a NULL le celle della hash table per sicurezza
    s->back=back;//puntatore alla symb tab padre
    s->oidC = 0;
    
    return s;
    
}

/*
 * funzione che gestisce il prog, le definizioni di proc e func
 * torna qualcosa != da NULL solo in caso di una func
 */
void start(pnode root, pST s, ptypeS* tipoRitornato){
    printf("start\n");
    
    stab = s;
    
    pnode idRoot = root->child;
    char *nomeRoot = idRoot->val.sval;
    
    idErr = nomeRoot;
    line = idRoot->line;
    
    pnode nodoCorrente = idRoot->brother;
    while(nodoCorrente){
      
        switch(nodoCorrente->val.ival){
            case N_OPTTYPESECT:
                optTypeSect_var_const(nodoCorrente,0);
                break;
            case N_OPTVARSECT: 
                optTypeSect_var_const(nodoCorrente,1);
                break;
            case N_OPTCONSTSECT:
                optTypeSect_var_const(nodoCorrente,2);
                break;
            case N_OPTMODULELIST:
                optModuleList(nodoCorrente);
                break;
            case N_STATBODY:
      
                //l'id usato per la root deve coincidere con quello che segue BEGIN
                if(strcmp(nomeRoot,nodoCorrente->child->val.sval)!=0){
                    printSemanticError();
                    printf("ERRORE #%d: l'id %s non coincide con quello di begin e end\n",idRoot->line,nomeRoot);
                    exit(0);
                }
                nStatBody(nodoCorrente);
                break;
            case N_EXPRBODY:
                if(strcmp(nomeRoot,nodoCorrente->child->val.sval)!=0){
                    printf("ERRORE #%d: l'id %s non coincide con quello di begin e end\n",idRoot->line,nomeRoot);
                    exit(0);
                }
                *tipoRitornato = exprBody(nodoCorrente->child->brother);
                break;
          }
        nodoCorrente = nodoCorrente->brother;
    }
   
    printf("\t \tSYMBTAB DI %s\n",nomeRoot);
    stampa(stab->tab);//stampa la hash table
    stampa2(stab->tab);//stampa la symbol tabel
    
    if(tipoRitornato!=NULL && *tipoRitornato != NULL){
        printf("Tipo ritornato da %s\n",nomeRoot);
        printType(*tipoRitornato);
    }
}

void pulisciSymbTab(pST s){//settiamo tutti i campi della hash table a NULL per sicurezza
    //printf("\npulisciSymbTab\n");
    int j;
    for(j=0;j<TOT;j++)
        s->tab[j]=NULL;
}

/*MANCA LA  CONDEXPR,
 * funzione che si occupa di gestire i casi compresi dalla clausola EXPR della BNF astratta
 */
ptypeS exprBody(pnode ex){
    //printf("exprBody\n");
    
    ptypeS tipoRitornato = NULL;
    
    switch(ex->type){
        case T_LOGICEXPR:tipoRitornato=expr(ex);
        break;
        case T_COMPEXPR:tipoRitornato=expr(ex);
        break;
        case T_MATHEXPR:tipoRitornato=expr(ex);
        break;
        case T_NEGEXPR:tipoRitornato=expr(ex);
        break;
        case T_MODCALL:tipoRitornato=modCall(ex);
        break;
        case T_NONTERM:
            
            switch(ex->val.ival){
                case N_LHS:
                    
                    tipoRitornato=lhs(ex);
                break;
                case N_CONST:
                    switch(ex->child->type){
                        case T_BOOLCONST:
                            tipoRitornato = tipoBoolean;
                        break;
                        case T_INTCONST:
                            tipoRitornato = tipoIntero;
                        break;
                        case T_STRCONST:
                            tipoRitornato = tipoString;
                        break;
                        //se non è nessuno di questi sopra è un arrayconst
                        default:tipoRitornato=nArrayConst(ex->child);
                                //printType(tipoRitornato);
                                break;
                    };
                break;
                case N_CONDEXPR:;
                break;
            };
        break;
    }
    
    if(tipoRitornato==NULL){
        printf("ERRORE #%d:tipi dell'expr non compatibili\n",line);
        printSemanticError();
        exit(0);
    }
    
    //printType(tipoRitornato);
    return tipoRitornato;
    
}

/*
 * funzione che crea un tipo fittizio per rappresentare una costante array;
 */
ptypeS nArrayConst(pnode nAC){
    //printf("nArrayConst\n");
    
    ptypeS tipoRitornato;
    ptypeS tipoParziale;
    
    int contatore=1;
    
    pnode nconst = nAC->child;
    
    idErr = "una costante array";
    line = nconst->line;
    
    if(nconst->child->type!=T_NONTERM){
        //entro se trovo una int,str,bool const
        printf("nArrayConst IF\n");
        switch(nconst->child->type){
            case T_INTCONST:tipoParziale=tipoIntero;
            break;
            case T_STRCONST:tipoParziale=tipoString;
            break;
            case T_BOOLCONST:tipoParziale=tipoBoolean;
            break;
        }
        
        while(nconst->brother!=NULL){
            printf("nArrayConstWHILE\n");
            /*
             * una volta che ho trovato una costante, anche tutti i fratelli devono essere costanti dello stesso tipo
             */
            ptypeS tipoParziale2;
            nconst=nconst->brother;
            
            if(nconst->child->type==T_NONTERM){
                //vuol dire che è un N_ARRAYCONST
                printf("ERRORE #%d: non sono ammessi array composti (es. [3,[]])\n",line);
                printSemanticError();
                exit(0);
            }
            
            switch(nconst->child->type){
                case T_INTCONST:tipoParziale2=tipoIntero;
                break;
                case T_STRCONST:tipoParziale2=tipoString;
                break;
                case T_BOOLCONST:tipoParziale2=tipoBoolean;
                break;
            }
            
            if(controllaCompatibilitaTipi(tipoParziale,tipoParziale2)==0){
                printf("ERRORE #%d: non sono ammessi array con tipi eterogenei (es. [3,\"ciao\"])\n",line);
                printSemanticError();
                exit(0);
            }
            
            contatore++;
            
        }
          
    }else{        
        //entro se ho un altro array innestato
        printf("nArrayConstELSE\n");
        tipoParziale = nArrayConst(nconst->child);
        ptypeS tipoParziale2;
        
        //ora tutti i fratelli devono essere array con la stessa struttura di tipoParziale
        while(nconst->brother!=NULL){
            tipoParziale2 = nArrayConst(nconst->brother->child);
            
            if(controllaCompatibilitaTipi(tipoParziale,tipoParziale2)==0){
                printf("ERRORE #%d: non sono ammessi array eterogenei (es. [[1],[2,3]])\n",line);
                printSemanticError();
                exit(0);
            }
            
            contatore++;
            nconst=nconst->brother;
        }
               
    }
    printf("nArrayConstRETURN\n");
    tipoRitornato=createType(S_ARRAY,tipoParziale,contatore);
    
    return tipoRitornato;
        
}

//funzione che si occupa di: opt-type-sect, opt-var-sect, opt-const-sect
void optTypeSect_var_const(pnode opttypesect_var,int classe){
    printf("opttypesect\n");
    pnode n_decl = opttypesect_var->child;//optypesect può essere opttype optvar o optconst
    
    while(n_decl){
       ptypeS type=NULL;
       char *idDecl = n_decl->child->child->val.sval;
       decl(stab,n_decl,classe,&type);//recupero il tipo della decl per fare type check nel caso di costanti
        n_decl = n_decl->brother;
        
        if(classe==2){//se ho classe=2 sono costanti;
             if(controlConstType(type,n_decl)){//se è una costante non è n_decl ma n_const
               n_decl = n_decl->brother;//devo fare cosi perchè nell'albero le costanti hanno un fratello in più
             }else{
                 printf("ERRORE #%d: l'inizializzazione della costante %s non corrisponde al tipo",n_decl->child->child->line,idDecl);
                 exit(0);
             }
        }
       
    }
      
}

void optModuleList(pnode optModuleList){
    printf("\noptmodulelist\n");
    
    pnode procFuncDecl = optModuleList->child; //nodo n_procdecl o n_funcdecl
    while(procFuncDecl){//finchè ci sono fratelli ossia nodi n_procdecl o n_funcdecl
        
        ptypeS tipoRitornato = NULL;
        
        pnode nID = procFuncDecl->child;//nodo id
        char *idFD = nID->val.sval;//id del proc/func
        ptypeS tipoTornatoFunc = NULL;//tipo tornato: sarà diverso da NULL solo se è una funzione
        
        if(findInSt(stab->tab,idFD)==NULL){//se l'id non è già stato preso
            /*
             * Nel caso di una funzione dobbiamo assicurarci che il tipo di ritorno esista
             */
            //di base settiamo i parametri come se fosse una proc, se si entra nell'if li si aggiorna per una func
            int classe=4;
            int type=2;
            if(procFuncDecl->val.ival == N_FUNCDECL){//entriamo solo se è una func
                pnode n_domain = nID->brother->brother;
                pnode nOptFormalList = nID->brother;
                pnode nFormalDecl = nOptFormalList->child;
                
                //tipoRitornato = (ptypeS)malloc(sizeof(TypeStruct));
                
                //una funzione può avere solo parametri passati come IN
                while(nFormalDecl!=NULL){
                    pnode tMode = nFormalDecl->child;
                    if(tMode->val.ival!=M_IN){
                        printf("ERRORE %d: la funzione %s può avere solo parametri IN\n",nID->line,idFD);
                        exit(0);
                    }
                    
                    nFormalDecl = nFormalDecl->brother;
                }
                
                
                //recuperiamo la struttura del tipo che deve tornare la func
                nDomain(n_domain,&tipoTornatoFunc);
                              
                //se controllaEsistenza restituisce NULL vuol dire che il tipo ritornato dalla func non è stato definito
                //(nDomain->child->type==T_ID) && (controllaEsistenzaTipo(stab,nDomain)==NULL)
                if(tipoTornatoFunc==NULL){
                   printf("\nERRORE #%d: il tipo %s restituito dalla func %s non esiste\n",n_domain->child->line,n_domain->child->val.sval,idFD);
                    exit(0);
                }
                
                //stabiliamo la classe e il tipo (da passare a start)
                classe = type = 3;
            }
            
            stab->oidC = stab->oidC+1;//incrementiamo il contatore degli oid            
            pST stabLocal = createSymbTab(stab);//creiamo la symbol table locale            
            int formals1 = optFormalList(stabLocal,procFuncDecl->child->brother);//recuperiamo il numero di parametri
            pstLine *formals2 = (pstLine*)malloc(sizeof(pstLine)*formals1);
            formals2 = recuperaFormali(stabLocal,formals1);//recuperiamo l'array di puntatori ai parametri
            printf("ID: %s\n",idFD);
            insertFindLine(stab->tab,hash(idFD),idFD,stab->oidC,classe,tipoTornatoFunc,stabLocal,formals1,formals2);
            start(procFuncDecl,stabLocal, &tipoRitornato);
            
            printf("RITORNO\n");
                       
            if(tipoRitornato!=NULL){
                printType(tipoRitornato);
                /*
                 * se tipoRitornato è diverso da NULL vuol dire che è una func
                 * e devo controllare che il tipo sia compatibile caon la expr nel corpo
                 */
                if(controllaCompatibilitaTipi(tipoRitornato,tipoTornatoFunc)==0){
                    printf("ERRORE #%d: l'expr nel corpo di %s non è compatibile con il tipo tornato\n",nID->line,idFD);
                    exit(0);
                }
            }else{
                printf("RITORNO NULL\n");
            }
        }else{//se l'id è già stato preso è errore
            printf("ERRORE #%d: id func/proc %s -> esiste già una var con quell'id\n",procFuncDecl->child->line,procFuncDecl->child->val.sval);
            exit(0);
        }
        procFuncDecl = procFuncDecl->brother;
        
        if(stab->back!=NULL){
            stab = stab->back;//devo fare cosi per rimettere nella var globale stab la symbtab corretta
        }
            
    }   
    
}

/*  
 * I parametri formali di una func o di una proc sono i primi a essere inseriti nella symb tab locale
 *  quindi per recuperarli mi basta scorrere la symb tab e prendere i puntatori degli unici
 * parametri inseriti
 */
pstLine* recuperaFormali(pST localStab,int formals1){
    //printf("\nrecupera formali\n");
    pstLine *arrFormals = (pstLine*)malloc(sizeof(pstLine)*(formals1));
    int i;
    for(i =0; i<TOT;i++){
        if(localStab->tab[i]!=NULL){
            
            arrFormals[(localStab->tab[i]->oid)-1]=localStab->tab[i];
            pstLine parente = localStab->tab[i]->next;
            while(parente!=NULL){      
                arrFormals[(localStab->tab[i]->oid)-1]=parente;
                parente = parente->next;
            }
        }
    }
   
    return arrFormals;
}

int optFormalList(pST localStab,pnode nOptFormalList){//restituisce il numero dei formali
    printf("optformallist\n");
    pnode nFormalDecl = nOptFormalList->child;
    
    while(nFormalDecl!=NULL){
        pnode tMode = nFormalDecl->child;
        int classe;  
        if(tMode->val.ival == M_IN){
            classe = 5;
        }else if(tMode->val.ival == M_OUT){
            classe = 6;
        }else{
            classe = 7;
        }
        ptypeS nullo;//puntatore fittizio
        decl(localStab,tMode->brother,classe,&nullo);        
        
        nFormalDecl = nFormalDecl->brother;
    }
    
    return localStab->oidC;
}

/*
 * funzione che controlla che il valore assegnato alla costante sia compatibile con il suo tipo
 * return 1 = OK
 * return 0 = errore
 */
int controlConstType(ptypeS type,pnode n_const){
    //printf("controlConstType\n");
    int risultato=1;
    int dimConstArray=0;
    int i=0;
    switch(type->domain){
        case S_INTEGER:
            risultato = n_const->child->type == T_INTCONST ? 1:0;
        break;
        case S_STRING: risultato = n_const->child->type == T_STRCONST ? 1:0;
        break;
        case S_BOOLEAN: risultato = n_const->child->type == T_BOOLCONST ? 1:0;
        break;
        case S_ARRAY: 
            
            risultato = controllaCompatibilitaTipi(type,nArrayConst(n_const->child));
            
            /*if(n_const->child->type == T_NONTERM){//se type è non term vuol dire che è un N_ARRAYCONST
                pnode n_const_intern = n_const->child->child;
                while(n_const_intern){
                    dimConstArray++;
                    n_const_intern = n_const_intern->brother;
                }
                
                if(dimConstArray == type->dim){//controllo che la dim della constArray sia uguale a quella del tipo
                    pnode n_const_intern = n_const->child->child;
                    for(i;i<dimConstArray;i++){                       
                        risultato = risultato && controlConstType(type->child,n_const_intern);
                        n_const_intern = n_const_intern->brother;
                    }
                }else{
                    
                    risultato = 0;
                }
            }else{//se il type non è non_term allora è sbagliato
                risultato = 0;
            };*/
        break;
    }
    
    return risultato;
}

/*
 *a decl passo stab invece di prenderlo dalla var globale perchè quando inserisco i parametri formali
 * di una func/dec devo metterli nella symbTab della proc/func, che non è quella che ho in questo 
 * momento nella var globale ( quella è il padre)
 */
void decl(pST stab, pnode n_decl,int classe,ptypeS* dom){
    printf("decl OID %d:\n",stab->oidC);
    nDomain(n_decl->child->brother,dom); 
    
    pnode t_id = n_decl->child->child;
    
    while(t_id){
        
        if(findInSt(stab->tab,t_id->val.sval)==NULL){//vuol dire che non è già stata definito un tipo con quell'id
            stab->oidC=stab->oidC+1;
            insertFindLine(stab->tab,hash(t_id->val.sval),t_id->val.sval,stab->oidC,classe,*dom,NULL,0,NULL);
            t_id = t_id->brother;
        }else{//altrimenti si sta sovrascrivendo=>ERRORE
            printf("ERRORE #%d: esiste già una var con l'id %s\n",t_id->line,t_id->val.sval);
            exit(0);
        }
               
    }
}

/*
 * funzione che crea un tipo, o ritorna errore se il dominio sfrutta un tipo che non è stato 
 * precedentemente definito
 */
void nDomain(pnode n_domain, ptypeS* dom){
    printf("ndomain\n");
    //ptypeS dom=NULL;
    
    if(n_domain->child->type == T_ATOMICDOMAIN){
        
        switch(n_domain->child->val.ival){
            case D_INTEGER: *dom = tipoIntero;
            break;
            case D_STRING: *dom = tipoString;
            break;
            case D_BOOLEAN: *dom = tipoBoolean;
            break;
        }
        //dom = createType(n_domain->child->val.ival,NULL,0);
    
    }else if(n_domain->child->type == T_NONTERM){//se è non term vuol dire che è un array domain
        ptypeS dom2 = NULL; 
        nDomain(n_domain->child->child->brother,&dom2);
         
         *dom = createType(3,dom2,n_domain->child->child->val.ival);//il 3 come primo parametro indica all'enum che è un array
    }else{//vuol dire che è un T_ID
        //se è un ID dobbiamo controllare che sia stato definito in precedenza
        *dom = controllaEsistenzaTipo(n_domain);
               
    }
     
    if(*dom == NULL){//se non ho trovato nessuna corrispondenza ho un errore
        printf("ERRORE #%d: il tipo %s non esiste\n",n_domain->child->line,n_domain->child->val.sval);
        exit(0);
    }
    printf("RITORNO NDOMAIN\n");
    printType(*dom);
    
    //return dom;
    
}

void nStatBody(pnode n_stat_body){
    //printf("nstatbody\n");
    pnode nStatList = n_stat_body->child->brother;
    pnode nStat = nStatList->child;
       
    int risultato;
    
    while(nStat!=NULL){
        
        switch(nStat->child->val.ival){
            case N_ASSIGNSTAT://il figlio di un assign è un lhs, il fratello della lhs è una expr
                risultato = assignStat(nStat);
                if(risultato==0){
                    printf("ERRORE: tipi dell'assegnamento non compatibili\n");
                    printSemanticError();
                    exit(0);
                }
                break;
            case N_IFSTAT:
                break;
            case N_WHILESTAT:
                break;
            case N_REPEATSTAT:
                break;
            case N_FORSTAT:
                break;
            case N_INPUTSTAT:
                break;
            case N_OUTPUTSTAT:
                break;
            case E_PROC:
                modCall(nStat->child);
                break;
            /*default:
                printf("ERRORE: nella stat-list\n");*/
            
          }
        
        
        nStat = nStat->brother;
    }
}

/*
 * funzione che gestisce la chiamata a una func o proc;
 * se è una func, l'int ritornato identifica il tipo ritornato dalla func;
 */
ptypeS modCall(pnode nodoModcall){
    printf("modCall\n");
    
    ptypeS tipoRitornato;
    pnode nodoIdMod = nodoModcall->child;
    
    idErr = nodoIdMod->val.sval;
    line = nodoIdMod->line;
    
    //controlliamo che l'id della func/proc esista
    pstLine p = controllaEsistenzaId(nodoIdMod);
    if(p==NULL){
        printf("ERRORE #%d: la func/proc %s non esiste\n",line,idErr);
        exit(0);
    }
    /*
     * bisogna anche controllare che:
     * se nodoModcall->val.ival = E_PROC allora p->class=S_PROC
     * se nodoModcall->val.ival = E_FUNC allora p->class=S_FUNC
     * perchè questo errore non può essere visto a livello sintattico
     * es. che in una stat sia fatta una modcall ad una func, 
     * o che n una expr sia fatta una modccal ad una proc
     */
    else if(!((nodoModcall->val.ival==E_PROC && p->classe==S_PROC) || (nodoModcall->val.ival==E_FUNC && p->classe==S_FUNC))){
        printf("ERRORE #%d: la func/proc %s non può essere chiamata li\n",line,idErr);
        exit(0);
    }
    else{
        
        tipoRitornato = p->root;
        
        //ora bisogna controllare i parametri passati 
        // che devono essere giusti sia in numero, che in tipo, che in modalità di passaggio
        //es. un parametro out o inout non può essere una costante
        pstLine *formali = (pstLine*)malloc(sizeof(pstLine)*p->formals1);
        printf("NUMER FOR %d\n",p->formals1);
        formali = p->formals2;
        pnode nodoParamAttuale = nodoIdMod->brother;
        int i;
        
        for(i=0;i<p->formals1;i++){
            printf("SENTRO FOR %d\n",i);
            printf("%d***************NOME %s\n",i,formali[i]->name);
            controllaParametroChiamata(formali[i],nodoParamAttuale);
            nodoParamAttuale = nodoParamAttuale->brother;
        }
        
        if(nodoParamAttuale != NULL){
            printf("ERRORE #%d: numero eccessivo di parametri attuali per la func/proc %s \n",line,idErr);
            exit(0);
        }
               
    }
    
    printf("exit modcall\n");
    
    //risetto questi perchè se sono passato da altre funzioni li ho modificati, ma se arrivo qui vuol dire che
    //errori nelle funzioni chiamate non ne ho trovati
    idErr = nodoIdMod->val.sval;
    line = nodoIdMod->line;
    
    return tipoRitornato;
    
}

/*
 * MANCA CONDEXPR 
 * funzione che controlla che il parametro attuale e formale passati abbiano stesso tipo
 */
void controllaParametroChiamata(pstLine formale, pnode attuale){
    printf("controllaParametroChiamata\n");
    
    //id della proc/func 
    char *idProcFunc = idErr;
    
    if(attuale == NULL){
            printf("ERRORE #%d: numero non sufficiente di parametri attuali per la func/proc %s \n",line,idErr);
            exit(0);
        }
    
    char *nomeFormale = formale->name;
   
    ptypeS typeAttuale = exprBody(attuale);
   
    //printf("ATTUALE\n");
    //printType(typeAttuale);
    
    //printf("FORMALE\n");
    //printType(formale->root);

    /*
     * A questo punto in typeAttuale dovremmo avere (qualsiasi cosa fosse il param attuale) un tipo
     * fittizio che rappresenta il tipo del parametro
     */
    
    /*
     * a un parametro tipo out o inout pui passare solo una var (niente expr costanti ecc)
     */
    if((formale->classe == S_OUT || formale->classe == S_INOUT) && (attuale->val.ival!=N_LHS || typeAttuale->costante==1)){
        printf("ERRORE #%d: al formale %s di tipo out/inout si può passare solo una var\n",line,nomeFormale);
        exit(0);
    }
    
    if(controllaCompatibilitaTipi(typeAttuale,formale->root)!=1){
        printf("ERRORE #%d: tipo attuale della proc/func %s non compatibile con quello del formale %s\n",line,idProcFunc,nomeFormale);
        exit(0);
    }
    
}

/*
 * A sx dell'uguale ho perforza un lhs, quindi chiamo lhs()
     *A dx posso avere:
     *      una costante-> chiamo il metodo già usato per controllare la compatibilità nella definizione delle costanti
     *      una lhs->richiamo lhs e poi chiamo il metodo per il controllo della compatibilità tra due tipi di variabili
     *      una expr->in questo caso devo calcolare il tipo della expr e in base a quello creare un tipo fittizio con 
     *                il quale chiamare il metodo per il controllo tra tipi di variabile
  */
int assignStat(pnode nStat){
    //printf("assignStat\n");
    int risultato;
    
    pnode ex = nStat->child->child->brother;
    
    ptypeS typeLhs = lhs(nStat->child->child);
    ptypeS typeExpr = exprBody(ex);
    /*
    if(nStat->child->child->brother->val.ival == N_CONST){//se a dx dell'uguale ho una costante
        risultato = controlConstType(typeLhs,nStat->child->child->brother);
        return risultato;//0=errore 1=OK
    }else if(nStat->child->child->brother->val.ival == N_LHS){//se a dx dell'uguale ho un lhs
        typeExpr = lhs(nStat->child->child->brother);
    }else if(nStat->child->child->brother->type == T_MODCALL){//se a dx dell'uguale ho una modcall
        typeExpr = modCall(nStat->child->child->brother);
    }else{//se a dx dell'= ho una logic/math/comp/neg expr 
        printf("EXPR\n");
        typeExpr = expr(nStat->child->child->brother);
        if(typeExpr==NULL){
                printf("ERRORE: tipi non compatibili nell'assegnamento\n");
                printSemanticError();
                exit(0);
        }
    }*/
    
    
    
    risultato = controllaCompatibilitaTipi(typeLhs,typeExpr);//recuperati i due tipi controllo che coincidano
    
    return risultato;            
    
}

/*
 *lhs torna il tipo della lhs 
 */
ptypeS lhs(pnode nLhs){
    //printf("lhs\n");
    ptypeS tipoLhs = NULL;
    pnode figlio = nLhs->child;
    
    if(figlio->type == T_ID){//se il figlio del lhs è un id
        
        char *id = figlio->val.sval;
        pstLine p = controllaEsistenzaId(figlio);
        
        idErr = figlio->val.sval;
        line = figlio->line;
        
        if(!p || (p->classe != S_VAR && p->classe != S_CONST)){
            printf("ERRORE #%d: %s usato come lhs non è una variabile\n",figlio->line,figlio->val.sval);
            exit(0);
        }else{
            tipoLhs = p->root;
             
            /*
             * per sapere se l'id trovato è quello di una costante
             */
            if(p->classe==S_CONST){
                tipoLhs->costante=1;
            }            
            //return tipoLhs;
        }
        
    }
    else{//il figlio è un indexing
        //printf("lhs INDEXING\n");
        pnode nLhs2 = figlio->child;
        pnode expr2 = figlio->child->brother;
        
        //parte per cercare di aggiustare l'eventule errore presentato a video
        if(nLhs2->child->type==T_ID){
            idErr = nLhs2->child->val.ival;
            line = nLhs2->child->line;
        }
        
        //la expr che forma un indexing deve essere per forza di tipo matematico, o lhs, o const, o mod call 
        //perchè la si deve usare per restituire un numero da usare come indicizzatore dell'array
        switch(expr2->type){
            case T_MATHEXPR://calcoliamo il tipo ritornato dalla expr 
                if(controllaCompatibilitaTipi(expr(expr2),tipoIntero)!=1){//vuol dire che si sta provando ad indicizzare un array con un expr che non ritorna un intero 
                printf("ERRORE: l'expr usata per l'indexing non restituisce un intero\n");
                printSemanticError();
                exit(0);
                }
            break;
            case T_MODCALL:
                if(controllaCompatibilitaTipi(modCall(expr2),tipoIntero)==0){
                   printf("ERRORE: la modcall usata per l'indexing non restituisce un intero\n");
                    printSemanticError();
                    exit(0); 
                };
            break;
            case T_NONTERM:      
                switch(expr2->val.ival){
                    case N_LHS:
                            
                            /*
                             * Se ho un lhs qui vuol dire che ho una roba tiopo arr1[arr2[3]]
                             * Quindi a me importa solo controllare che arr2[3] torni un int
                            */
                            if(controllaCompatibilitaTipi(lhs(expr2),tipoIntero) != 1){
                                printf("ERRORE: l'array interno non torna un intero\n");
                                printSemanticError();
                                exit(0);
                            }

                    break;
                    case N_CONST:
                            if(expr2->child->type != T_INTCONST){//se ho una costante non numerica
                                printf("ERRORE: non si può indicizzare un array con una costante non numerica\n");
                                printSemanticError();
                                exit(0);
                            };
                    break;
                }
                
            break;                
            default:
                printf("ERRORE: non si può indicizzare un array con una expr che non restituisce un integer\n");
                printSemanticError();
                exit(0);
        }
                
        ptypeS parziale = lhs(nLhs2);
        if(parziale->child!=NULL){
            tipoLhs = parziale->child;
        }
        else{
            printf("ERRORE: l'array non è cosy grande\n");
            printSemanticError();
            exit(0);
        }
        
    }
    
    return tipoLhs;
    
}


/*
 *Funzione che controlla la compatibilità di due tipi
 * 1=OK
 * 0=errore
 */
int controllaCompatibilitaTipi(ptypeS t1,ptypeS t2){
    //printf("controllaCompatibiliàtipi\n");
    int risultato=1;
    
    if(t1->domain == t2->domain && t1->dim == t2->dim){
            
        if(t1->domain == S_ARRAY){
            
            risultato = risultato && controllaCompatibilitaTipi(t1->child,t2->child);
            
        }else{
            risultato = 1;
        }
            
    }else{
        risultato = 0;
    }
    //printf("controllaCompatibiliàtipi RETURN %d\n",risultato);
    return risultato;
}


/*
 * logic-expr, comp-expr,math-expr,neg-expr;
 */
ptypeS expr(pnode nExpr){
    //printf("expr\n");
    ptypeS tipoRitornato;//tipo ritornato dall'expr
    
    int tipoExpr;
    
    //stabilisco il tipo della expr
    switch(nExpr->type){
            case T_LOGICEXPR: 
                tipoExpr= T_LOGICEXPR;
                tipoRitornato=tipoBoolean;//una logic expr deve tornare un bool 
                break;              
            case T_MATHEXPR: 
                tipoExpr= T_MATHEXPR;
                tipoRitornato=tipoIntero;//una math expr deve tornare un integer
                break;   
            case T_COMPEXPR: 
                tipoExpr= T_COMPEXPR;
                tipoRitornato=tipoBoolean;//una comp expr deve tornare un bool ;
                break;
            case T_NEGEXPR:
                tipoExpr= T_NEGEXPR;
                tipoRitornato=tipoBoolean;//una neg expr deve tornare un bool ;
            break;
          }
    
    
    pnode f1 = nExpr->child;
    pnode f2 = nExpr->child->brother;
    
    //stabilisco il tipo del primo figlio
    ptypeS tr1 = figliExpr(f1);
    //stabilisco iltipo del secondo figlio (fratello del primo figlio)
    ptypeS tr2 = figliExpr(f2);
    
    //printType(tr1);
    //printType(tr2);
    
    if(tr1==NULL || tr2==NULL || controllaCompatibilitaTipi(tr1,tr2)==0){
        printf("ERRORE #%d: tipi incompatibili nell'espressione\n",line);
        printSemanticError();
        exit(0);
    }else{
        
        //se ho una comp expr i figli possono avere tipo diverso da booleano
        //es. 3<4
        if(tipoExpr == T_COMPEXPR){
            
            int tipoComp = nExpr->val.ival;
            printf("%d\n",tipoComp);
            if(tipoComp != E_EQ && tipoComp != E_NE){
                // <,<=,>,>= non possono essere applicati ai booleani 
                
                printType(tipoBoolean);
                if(controllaCompatibilitaTipi(tr1,tipoBoolean)==1){

                    //ad due booleani non puoi applicare niente che non sia == o !=
                    printf("ERRORE: non puoi applicare == o != ad un booleano\n");
                    printSemanticError();
                    exit(0);               
                }else{

                    return tipoRitornato;
                }

            }
            return tipoRitornato;
           
        }
        else{
            /*
             *Se ho una math o un logic expr deve essere che
             * tipoRitornato == tipoRitornato1 == tipoRitornato2
             * altrimenti ho errore
             */
            if(controllaCompatibilitaTipi(tr1,tipoRitornato)==1 && controllaCompatibilitaTipi(tr1,tr2)==1){
                
                return tipoRitornato;
            }else{
                printf("ERRORE: non puoi applicare quell'operatore a quel tipo di figli\n");
                printSemanticError();
                exit(0); 
            }

        }        
    }    
}

/*
 * una expr ha sempre due figli (un figlio e suo fratello) e bisogna assicurarsi 
 * che i tipi di tutti e tre siano "compatibili"
*/
ptypeS figliExpr(pnode figlioExpr){
    //printf("figli expr\n");
    ptypeS tipoRitornato;
    
    if(figlioExpr->val.ival==N_CONST){
        
        switch(figlioExpr->child->type){
            case T_INTCONST:tipoRitornato=tipoIntero;
            break;
            case T_BOOLCONST:tipoRitornato=tipoBoolean;
            break;
            case T_STRCONST:tipoRitornato=tipoString;
            break;
            //se non è nessuno di questi sopra è un arrayconst
            default:tipoRitornato=nArrayConst(figlioExpr->child);
                   //printType(tipoRitornato);
            break;
        }
    }else if(figlioExpr->val.ival==N_LHS){
        
        tipoRitornato = lhs(figlioExpr);
       
    }else if(figlioExpr->type==T_MODCALL){
        tipoRitornato = modCall(figlioExpr);
        
    }else{
        tipoRitornato=expr(figlioExpr);
    }
    printType(tipoRitornato);
    return tipoRitornato;
    
}

/*
 * funzione per controllare l'esistenza di tipi definiti dall'utente
 */
ptypeS controllaEsistenzaTipo(pnode n_domain){
    
    ptypeS dom = NULL;
    
    pST s = stab;
    
    while(s){//oltre che nella stab locale devo anche controllare in quelle dei genitori
            
            pstLine p = findInSt(s->tab,n_domain->child->val.sval);
         
            if(p && p->classe == S_TYPE){//se trovo una precedente dichirazione del tipo
                
                dom = p->root;
                break; //saltimao fuori dal while se abbiamo trovato una precedente dichiarazione
            }else{
                s = s->back;
            }
            
        }
    
    return dom;
       
}

/*
 * funzione che controlla la presenza di un elemento nella symbtab, anche ai livelli precedenti
 */
pstLine controllaEsistenzaId(pnode t_id){
    //printf("controllaEsistenzaId\n");
    
    pST s = stab;
    
    pstLine p = NULL;
    
    while(s){//oltre che nella stab locale devo anche controllare in quelle dei genitori
            
            p = findInSt(s->tab,t_id->val.sval);
         
            if(p){//se trovo una corrispondenza
                
                break; //saltimao fuori dal while se abbiamo trovato una precedente dichiarazione
            }else{
                s = s->back;
            }
            
        }
    
    return p;
    
}


/*
 * funzione che crea un tipo definito dall'utente e ritorna il corrispondente ptypeS
 */
ptypeS createType(int ival,ptypeS child,int dim){
    //printf("createType\n");
    ptypeS p = malloc(sizeof(TypeStruct));
    p->domain = ival;
    p->child =  child;
    p->dim = dim;
 
    return (p);
    
}

/*
 * funzione che controlla la presenza di un elemento nella symbtab (solo quella locale, non nei genitori)
 * in caso positivo torna il pstLine 
 * in caso negativo un NULL
 */
pstLine findInSt(pstLine stab[],char *id){
    //printf("findInSt\n");
    
    pstLine p=NULL,parente=NULL;
    
    int h = hash(id);
    
    if(stab[h]){
        int trovato = 0;
        int nullo = 0;
        parente = stab[h];
        while(!nullo && !trovato){
            
            if((strcmp(parente->name,id)) == 0){ // controllo il valore della stringa del nodo
                //se trovo un nodo già presente con l stessa stringa
                return parente;

            }else{ //se il nodo ha stringa diversa passo oltre        
                
                    if(parente->next != 0){ // se il puntatore è assegnato passo al nodo successivo
                    
                        parente = parente->next;
                    
                    }else{//altrimenti sono arrivato in fondo senza trovare un nodo con la stringa uguale  e devo uscire dal while e crearne uno nuovo nodo
                   
                        nullo = 1;
                    }
                
            }
            
        }
        
    }
    
    return p;//se arrivo qui torno un null pointer = non c'è un nodo con quell'id
    
}

/*
 * funzione che cerca la presenza di un elemento nella symbtab
 * in caso positivo torna il pstLine
 * in caso negativo aggiunge il nuovo elemento nella tabella
 */
pstLine insertFindLine(pstLine stab[],int h, char *id, int oid,int classe,ptypeS root,pstLine local,int formals1,pstLine formals2[]){
    
    //printf("insertFindLine HASH %d\n",h);
    char *p;
    pstLine nuovoNodo, parente;
    if(!stab[h]){ // se non c'è già un nodo con quell'hash
        
        nuovoNodo = createLine(id,oid,classe,root,local,formals1,formals2,NULL);
        stab[h] = nuovoNodo;
              
        
    }else{ // se c'è già un nodo con quell'hash
        
        int trovato = 0;
        int nullo = 0;
        parente = stab[h];
        while(!nullo && !trovato){
            
            if((strcmp(parente->name,id)) == 0){ // controllo il valore della stringa del nodo
                //se trovo un nodo già presente con l stessa stringa
               
                return parente;

            }else{ //se il nodo ha stringa diversa passo oltre        
                
                    if(parente->next != 0){ // se il puntatore è assegnato passo al nodo successivo
                    
                        parente = parente->next;
                    
                    }else{//altrimenti sono arrivato in fondo senza trovare un nodo con la stringa uguale  e devo uscire dal while e crearne uno nuovo nodo
                   
                        nullo = 1;
                    }
                
            }
            
        }
        
        nuovoNodo = createLine(id,oid,classe,root,local,formals1,formals2,NULL);
        parente->next = nuovoNodo;
       
    }
    
    return nuovoNodo;
}

/*
 * funzione che crea una riga della symbtab e restituisce il corrispondente pstLine
 */
pstLine createLine(char *id,int oid,int classe,ptypeS root,pstLine local,int formals1,pstLine formals2[],pstLine next){
    
    //printf("create Line\n");
    pstLine p = malloc(sizeof(StructstLine));
    p->name = id;
    p->oid =  oid;
    p->classe = classe;
    p->root = root;
    p->local = local;
    p->formals1 = formals1;
    p->formals2 = formals2;
    p->next = next;
    return (p);
  
}


