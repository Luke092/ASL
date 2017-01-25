/*
 * Author: andrea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def_symbtab.h"

char *idErr;//id della var che da errore
int line;//linea dell'errore

int mid = 0; //l'id del modulo è univoco per tutto il programma

void printSemanticError(){
    printf("ERRORE #%d: causato probabilmente da %s\n",line,idErr);
}

pST stab;//puntatore alla symbtab locale

ptypeS tipoIntero;//ptypeS che rappresenta un intero
ptypeS tipoString;//ptypeS che rappresenta una stringa
ptypeS tipoBoolean;//ptypeS che rappresenta un bool

int primoGiro = 1;

//TODO: cambiare modo di gestire l'offset, non funziona se si cercano variabili in ST superiori
int offset = 0; // offset oid per la SymbTab locale
/*
 * L'indirizzo di una variabile sullo stack degli oggetti è definito come
 * oid - offset - 1
 */

pST createSymbTab(pST back){
    printf("createSymbTab\n");
    
    if(primoGiro){
        tipoIntero=createType(0,NULL,0);
        tipoString=createType(1,NULL,0);
        tipoBoolean=createType(2,NULL,0);
        primoGiro = 0;
    }
    
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
Code start(pnode root, pST s, ptypeS* tipoRitornato){
    Code code = endcode(),
            modl_code = endcode();
    
    printf("start\n");
    
    stab = s;
    offset = 0;
    
    pnode idRoot = root->child;
    char *nomeRoot = idRoot->val.sval;
    
    idErr = nomeRoot;
    line = idRoot->line;
    
    //Definizione del modulo
    if(stab->back == NULL){
        code = makecode1(MODL, mid++);
    } else {
        code = makecode1(MODL, findInSt(stab->back->tab, nomeRoot)->mid);
    }
    
    pnode nodoCorrente = idRoot->brother;
    while(nodoCorrente){
        Code tmp = endcode();
        
        switch(nodoCorrente->val.ival){
            case N_OPTTYPESECT:
                optTypeSect_var_const(nodoCorrente,0);
                break;
            case N_OPTVARSECT: 
                tmp = optTypeSect_var_const(nodoCorrente,1);
                if(tmp.size != 0){
                    if (code.size != 0)
                        code = concode(code, tmp, endcode());
                    else
                        code = tmp;
                }
                break;
            case N_OPTCONSTSECT:
                tmp = optTypeSect_var_const(nodoCorrente,2);
                if(tmp.size != 0){
                    if (code.size != 0)
                        code = concode(code, tmp, endcode());
                    else
                        code = tmp;
                }
                break;
            case N_OPTMODULELIST:
                tmp = optModuleList(nodoCorrente);
                //TODO: generare codice per i moduli
                if(tmp.size != 0){
                    if (modl_code.size != 0)
                        modl_code = concode(code, tmp, endcode());
                    else
                        modl_code = tmp;
                }
                break;
            case N_STATBODY:
      
                //l'id usato per la root deve coincidere con quello che segue BEGIN
                if(strcmp(nomeRoot,nodoCorrente->child->val.sval)!=0){
                    printSemanticError();
                    printf("ERRORE #%d: l'id %s non coincide con quello di begin e end\n",idRoot->line,nomeRoot);
                    exit(0);
                }
                tmp = statList(nodoCorrente->child->brother);
                
                if(tmp.size != 0){
                    if (code.size != 0)
                        code = concode(code, tmp, endcode());
                    else
                        code = tmp;
                }
                break;
            case N_EXPRBODY:
                if(strcmp(nomeRoot,nodoCorrente->child->val.sval)!=0){
                    printf("ERRORE #%d: l'id %s non coincide con quello di begin e end\n",idRoot->line,nomeRoot);
                    exit(0);
                }
                //*tipoRitornato = exprBody(nodoCorrente->child->brother);
                tmp = exprBody(nodoCorrente->child->brother,tipoRitornato);
                
                if(tmp.size != 0){
                    if (code.size != 0)
                        code = concode(code, tmp, endcode());
                    else
                        code = tmp;
                }
                
                printf("Tipo ritornato da exprbody\n");
                printType(*tipoRitornato);
                break;
          }
        nodoCorrente = nodoCorrente->brother;
    }
    
    // metto un return alla fine del codice
    code = concode(code, makecode(RETN), endcode());
    
    // appendo in fondo la definizione dei moduli
    code = concode(code, modl_code, endcode());
   
    printf("\t \tSYMBTAB DI %s\n",nomeRoot);
    stampa(stab->tab);//stampa la hash table
    stampa2(stab->tab);//stampa la symbol tabel
    
    if(tipoRitornato!=NULL && *tipoRitornato != NULL){
        printf("Tipo ritornato da %s\n",nomeRoot);
        printType(*tipoRitornato);
    }
    
    if(root->val.ival == N_PROGRAM){
        int local_objs = count_local_objs(s->tab);
        /*
         * mid = 0 per main
         * num-formals-aux = num-locals in quanto non ho parametri formali per il main
         */
        Code main_call = make_call(0, local_objs,-1, 0);
        Code halt = makecode(HALT);
        int code_size = main_call.size + halt.size + code.size;
        code = concode(main_call,
                halt,
                code,
                endcode());
        code = subs_jump_address(code); // sostituisco il module id con l'address effettivo dell'inizio del modulo
        code = concode(makecode1(ACODE, code_size), code, endcode());
    }
    
    return code;
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
Code exprBody(pnode ex,ptypeS* tipoRitornato){
    Code code;
    code.size = 0;
    
    //printf("exprBody\n");
    
    ptypeS tipoRitornato2 = NULL;
    
    switch(ex->type){
        case T_LOGICEXPR:
            code = expr(ex,&tipoRitornato2);
            break;
        case T_COMPEXPR:
            code = expr(ex,&tipoRitornato2);
            break;
        case T_MATHEXPR:
            code = expr(ex,&tipoRitornato2);
            break;
        case T_NEGEXPR:
            code = expr(ex,&tipoRitornato2);
            break;
        case T_MODCALL:
            code = modCall(ex,&tipoRitornato2);
            //TODO: implement code generation
            break;
        case T_NONTERM:
            
            switch(ex->val.ival){
                case N_LHS:
                    code = lhs(ex,&tipoRitornato2);
                    
                    pnode pt = ex->child;
                    if(pt->type == T_ID){
                        
                        int env_distance;
                        pstLine line = controllaEsistenzaId(pt->val.sval, &env_distance);
                        int addr = line->oid - offset - 1;
                        
                        if(tipoRitornato2 == tipoBoolean ||
                                tipoRitornato2 == tipoIntero ||
                                tipoRitornato2 == tipoString){
                            code = makecode2(LOAD, env_distance, addr);
                        } else {
                            int size = 1;
                            ptypeS t = tipoRitornato2;
                            while(t->child != NULL){
                                size *= t->dim;
                                t = t->child;
                            }
                            if(t == tipoIntero || t == tipoBoolean){
                                size *= sizeof(int);
                            } else if (t == tipoString){
                                size *= sizeof(void*);
                            }
                            code = concode(
                                    makecode2(LODA, env_distance, addr),
                                    makecode1(SIND, size),
                                    endcode()
                                    );
                        }
                    } else {
                        int size;
                        ptypeS t = tipoRitornato2;
                        if(t == tipoBoolean || t == tipoIntero){
                            size = sizeof(int);
                            code = concode(code,
                                makecode1(AIND, size),
                                endcode());
                        } else if (t == tipoString){
                            size = sizeof(void*);
                            code = concode(code,
                                makecode1(AIND, size),
                                endcode());
                        } else {
                            /* 
                             * Il tipo dell'espressione non è atomico, quindi
                             * devo fare un caricamento indiretto del tipo strutturato
                             * corrispondente
                             */
                            size = 1;
                            while(t->child != NULL){
                                size *= t->dim;
                                t = t->child;
                            }
                            if(t == tipoIntero || t == tipoBoolean){
                                size *= sizeof(int);
                            } else if (t == tipoString){
                                size *= sizeof(void*);
                            }
                            code = concode(code,
                                makecode1(SIND, size),
                                endcode());
                        }
                        
                        
                    }
                break;
                case N_CONST:
                    switch(ex->child->type){
                        case T_BOOLCONST:
                            idErr = "una costante booleana";
                            tipoRitornato2 = tipoBoolean;
                            
                            int bval = (ex->child->val.bval == 0)? 1 : 0;
                            code = make_loci(bval);
                            break;
                        case T_INTCONST:
                            idErr = "una costante intera";
                            tipoRitornato2 = tipoIntero;
                            
                            code = make_loci(ex->child->val.ival);
                            break;
                        case T_STRCONST:
                            idErr = "una costante stringa";
                            tipoRitornato2 = tipoString;
                            
                            code = make_locs(ex->child->val.sval);
                            break;
                        //se non è nessuno di questi sopra è un arrayconst
                        default:
                            nArrayConst(ex->child,&tipoRitornato2);
                            
                            code = cg_array_const(ex->child);
                            break;
                    };
                    break;
                case N_CONDEXPR:
                    code = condExpr(ex,&tipoRitornato2);
                    break;
            };
        break;
    }
    
    if(tipoRitornato2==NULL){
        printf("ERRORE #%d:tipi dell'expr non compatibili\n",line);
        printSemanticError();
        exit(0);
    }
    
    
    
    *tipoRitornato = tipoRitornato2;
    printf("Tipo tornato dentro exprbody aster\n");
    printType(*tipoRitornato);
    
    printf("Tipo tornato dentro exprbody normale\n");
    printType(tipoRitornato2);
    
    //TODO: change STAB
    if(code.size == 0)
        code = makecode(NOOP);
    
    return code;
}

/*
 * funzione che gestisce le cond expr
 * 
 * Ragiona esattamente come la funzione ifStat
 */
Code condExpr(pnode nCond,ptypeS* tipoRitornato){
    Code res_code = endcode(),
            if_code = endcode(),
            elseif_code = endcode(),
            else_code = endcode();
    //printf("condexpr\n");
    
    line = nCond->child->line;
    
    //exprIf= la condizione dell'if
    ptypeS exprIf = NULL;
    if_code = exprBody(nCond->child,&exprIf);
    
    if(controllaCompatibilitaTipi(exprIf,tipoBoolean)==0){
        //l'exprIf deve essere per forza un booleano, se no è errore
        printf("ERRORE #%d: l'expr di un if/elseif deve tornare un booleano\n",line);
        printSemanticError();
        exit(0);
    }
    
    //expr1= expr dopo l'if
    ptypeS expr1 = NULL;
    Code cond_code = exprBody(nCond->child->brother,&expr1);
    if_code = concode(if_code,
            makecode1(SKPF, cond_code.size + 1),
            cond_code,
            endcode());
    
    //ora inizia la serie dei possibili fratelli optelsifexprlist
    pnode nElseIf = nCond->child->brother->brother;
    pnode nExprElseIf = nElseIf->child;
    
    //expr3 è l'expr dopo l'else finale
    ptypeS expr3 = NULL;
    else_code = exprBody(nElseIf->brother, &expr3);
    
    int else_if_count = 0;
    
    pnode tmp_node = nExprElseIf;
    while(tmp_node != NULL){
        else_if_count++;
        tmp_node = tmp_node->brother->brother;
    }
    
    for(int i = else_if_count - 1; i >= 0; i--){
        Code elseif_cond_code = endcode(),
                elseif_then_code = endcode();
        
        tmp_node = nExprElseIf;
        
        for(int j = 0; j < i; j++){
            tmp_node = tmp_node->brother->brother;
        }
        
        line = tmp_node->child->line;
        
        //exprElseIf espressione (che deve tornare un bool) dell'elsif
        ptypeS exprElseIf = NULL;
        elseif_cond_code = exprBody(tmp_node, &exprElseIf);
        
        if(controllaCompatibilitaTipi(exprElseIf, tipoBoolean)==0){
            //l'exprIf deve essere per forza un booleano, se no è errore
            printf("ERRORE #%d: l'expr di un if/elseif deve tornare un booleano\n",line);
            printSemanticError();
            exit(0);
        }
        
        //expr2 = espressione dopo elsif
        ptypeS expr2 = NULL;
        elseif_then_code = exprBody(tmp_node->brother,&expr2);
        
        if(controllaCompatibilitaTipi(expr2, expr1)==0){
            //l'expr2 deve essere dello stesso tipo di expr1, se no è errore
            printf("ERRORE #%d: il tipo dell'expr di un elseif non coincide con quella dell'if\n",line);
            printSemanticError();
            exit(0);
        }
        
        elseif_code = concode(
                elseif_cond_code,
                makecode1(SKPF, elseif_then_code.size + 1),
                elseif_then_code,
                makecode1(SKIP, else_code.size + elseif_code.size),
                elseif_code,
                endcode());
    }
    
    if_code = concode(if_code, makecode1(SKIP, else_code.size + elseif_code.size), endcode());
    
    if(controllaCompatibilitaTipi(expr3,expr1)==0){
        //l'expr2 deve essere dello stesso tipo di expr1, se no è errore
        line = nElseIf->brother->child->line;
        printf("ERRORE #%d: il tipo dell'expr dell'else non coincide con quella dell'if\n",line);
        printSemanticError();
        exit(0);
    }
    
    *tipoRitornato = expr1;
    printf("tipo tornato COND_EXPR\n");
    printType(*tipoRitornato);
    
    res_code = concode(if_code, elseif_code, else_code, endcode());
    return res_code;
}

/*
 * funzione che crea un tipo fittizio per rappresentare una costante array;
 */
void nArrayConst(pnode nAC,ptypeS* tipoRitornato){
    //printf("nArrayConst\n");
    
    ptypeS tipoRitornato2;
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
        nArrayConst(nconst->child,&tipoParziale);
        
        //ora tutti i fratelli devono essere array con la stessa struttura di tipoParziale
        while(nconst->brother!=NULL){
            ptypeS tipoParziale2 = NULL;
            nArrayConst(nconst->brother->child,&tipoParziale2);
            
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
    tipoRitornato2=createType(S_ARRAY,tipoParziale,contatore);
    
    *tipoRitornato = tipoRitornato2;
    
    printf("Tipo tornato array const\n");
    printType(*tipoRitornato);
        
}

//funzione che si occupa di: opt-type-sect, opt-var-sect, opt-const-sect
Code optTypeSect_var_const(pnode opttypesect_var,int classe){
    Code d_code, c_code;
    d_code.size = 0;
    c_code.size = 0;
    
    printf("opttypesect\n");
    pnode n_decl = opttypesect_var->child;//optypesect può essere opttype optvar o optconst
    
    while(n_decl){
        
        if(classe == 0){
            offset++;
        }
        
       ptypeS type=NULL;
       char *idDecl = n_decl->child->child->val.sval;
       
       Code decl_code;
       
       decl_code = decl(stab,n_decl,classe,&type);//recupero il tipo della decl per fare type check nel caso di costanti
        n_decl = n_decl->brother;
        
        if(classe==2){//se ho classe=2 sono costanti;
             if(controlConstType(type,n_decl)){//se è una costante non è n_decl ma n_const
                // genero codice per la costante
                 Code const_code;
                 
                 int env_distance;
                 pstLine line = controllaEsistenzaId(idDecl, &env_distance);
                 int addr = line->oid - offset - 1;
                 
                 if(type == tipoIntero){
                     const_code = make_loci(n_decl->child->val.ival);
                     const_code = concode(const_code,
                             makecode2(STOR, env_distance, addr),
                             endcode()
                             );
                 } else if (type == tipoBoolean){
                     int bool = (n_decl->child->val.ival == TRUE) ? 1 : 0; 
                     const_code = make_loci(bool);
                     const_code = concode(const_code,
                             makecode2(STOR, env_distance, addr),
                             endcode()
                             );
                 } else if (type == tipoString){
                     const_code = make_locs(n_decl->child->val.sval);
                     const_code = concode(const_code,
                             makecode2(STOR, env_distance, addr),
                             endcode()
                             );
                 } else {
                     const_code = cg_array_const(n_decl->child);
                     ptypeS tmp = type;
                     int array_dim = 1;
                     while(tmp->child != NULL){
                         array_dim *= tmp->dim;
                         tmp = tmp->child;
                     }
                     int size;
                     if(tmp == tipoIntero || tmp == tipoBoolean)
                         size = sizeof(int);
                     else if(tmp == tipoString)
                         size = sizeof(void*);
                     const_code = concode(const_code,
                             makecode2(PACK, array_dim, size),
                             makecode2(STOR, env_distance, addr),
                             endcode());
                 }
                
                 if(c_code.size == 0){
                     c_code = const_code;
                 } else {
                     c_code = concode(c_code, const_code, endcode());
                 }
                 
                n_decl = n_decl->brother;//devo fare cosi perchè nell'albero le costanti hanno un fratello in più
             }else{
                 printf("ERRORE #%d: l'inizializzazione della costante %s non corrisponde al tipo",n_decl->child->child->line,idDecl);
                 exit(0);
             }
        }
       
        if(d_code.size != 0)
            d_code = concode(d_code, decl_code, endcode());
        else
            d_code = decl_code;;
        
    }
    
    if(c_code.size != 0)
        return concode(d_code, c_code, endcode());
    else
        return d_code;
}

Code optModuleList(pnode optModuleList){
    Code code = endcode();
    printf("\noptmodulelist\n");
    
    pnode procFuncDecl = optModuleList->child; //nodo n_procdecl o n_funcdecl
    while(procFuncDecl){//finchè ci sono fratelli ossia nodi n_procdecl o n_funcdecl
        int old_offset = offset; // salvo l'offset delle variabili locale
        Code tmp = endcode();
        
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
            pstLine newLine = insertFindLine(stab->tab,hash(idFD),idFD,stab->oidC,classe,tipoTornatoFunc,stabLocal,formals1,formals2);
            newLine->mid = mid++;
            tmp = start(procFuncDecl,stabLocal, &tipoRitornato);
            if(code.size != 0){
                code = concode(code, tmp, endcode());
            } else {
                code = tmp;
            }
            
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
        
        offset = old_offset; // ripristino l'offset locale
    }   
    
    return code;
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
    printf("controlConstType\n");
    int risultato=1;
    int dimConstArray=0;
    int i=0;
    ptypeS typeArray = NULL;
    switch(type->domain){
        case S_INTEGER:
            risultato = n_const->child->type == T_INTCONST ? 1:0;
        break;
        case S_STRING: risultato = n_const->child->type == T_STRCONST ? 1:0;
        break;
        case S_BOOLEAN: risultato = n_const->child->type == T_BOOLCONST ? 1:0;
        break;
        case S_ARRAY:           
            nArrayConst(n_const->child,&typeArray);
            risultato = controllaCompatibilitaTipi(type,typeArray);
            
        break;
    }
    
    return risultato;
}

/*
 *a decl passo stab invece di prenderlo dalla var globale perchè quando inserisco i parametri formali
 * di una func/dec devo metterli nella symbTab della proc/func, che non è quella che ho in questo 
 * momento nella var globale ( quella è il padre)
 */
Code decl(pST stab, pnode n_decl,int classe,ptypeS* dom){
    Code code;
    code.size = 0;
    
    printf("decl OID %d:\n",stab->oidC);
    nDomain(n_decl->child->brother,dom);
    
    int var_size;
    int structured = 0;
    if(*dom == tipoIntero || *dom == tipoBoolean){
        var_size = sizeof(int);
    }else if(*dom == tipoString){
        var_size = sizeof(void*);
    } else {
        //In questo caso il tipo è strutturato
        structured = 1;
        var_size = (*dom)->dim;
        ptypeS pt = (*dom)->child;
        while(pt != NULL){
            if(pt == tipoIntero || pt == tipoBoolean){
                var_size *= sizeof(int);
            }else if(pt == tipoString){
                var_size *= sizeof(void*);
            } else {
                var_size *= pt->dim;
            }
            pt = pt->child;
        }
    }
    
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
        
        if(structured){
            // Tipo strutturato
            if (code.size != 0)
                code = concode(code, makecode1(SDEF, var_size), endcode());
            else
                code = makecode1(SDEF, var_size);
        } else {
            // Tipo semplice
            if (code.size != 0)
                code = concode(code, makecode1(ADEF, var_size), endcode());
            else
                code = makecode1(ADEF, var_size);
        }
    }
    
    return code;
}

/*
 * funzione che crea un tipo, o ritorna errore se il dominio sfrutta un tipo che non è stato 
 * precedentemente definito
 */
void nDomain(pnode n_domain, ptypeS* dom){
    printf("ndomain\n");
    
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

/*
 * funzione che gestisce le stat list
 */
Code statList(pnode nStatList){
    Code code;
    code.size = 0;
    
    //printf("nstatbody\n");
    pnode nStat = nStatList->child;
    ptypeS exType=NULL;
    pstLine p=NULL;
 
    while(nStat!=NULL){
        Code tmp = endcode();
        
        switch(nStat->child->val.ival){
            case N_ASSIGNSTAT://il figlio di un assign è un lhs, il fratello della lhs è una expr
                tmp = assignStat(nStat);
                if(code.size == 0){
                    code = tmp;
                } else {
                    code = concode(code, tmp, endcode());
                }
                break;
            case N_IFSTAT:
                tmp = ifStat(nStat->child);
                
                if(code.size == 0){
                    code = tmp;
                } else {
                    code = concode(code, tmp, endcode());
                }
                break;
            case N_WHILESTAT:
                tmp = whileStat(nStat->child);
                
                if(code.size == 0){
                    code = tmp;
                } else {
                    code = concode(code, tmp, endcode());
                }
                break;
            case N_REPEATSTAT:
                tmp = repeatStat(nStat->child);
                
                if(code.size == 0){
                    code = tmp;
                } else {
                    code = concode(code, tmp, endcode());
                }
                break;
            case N_FORSTAT:
                tmp = forStat(nStat->child);
                
                if(code.size == 0){
                    code = tmp;
                } else {
                    code = concode(code, tmp, endcode());
                }
                break;
            case N_INPUTSTAT:
                p = controllaEsistenzaId(nStat->child->child->val.sval, NULL);
                if(p==NULL || (p->classe != S_VAR && p->classe != S_IN && p->classe != S_OUT && p->classe != S_INOUT)){
                    printf("ERRORE #%d: l'id %s non è quello di una variabile\n",nStat->child->child->line,nStat->child->child->val.sval);
                    exit(0);
                }
                
                tmp = makecode2(READ, 0, p->oid);
                
                if(p->root == tipoIntero){
                    tmp.head->args[2].sval = "i";
                } else if (p->root == tipoBoolean){
                    tmp.head->args[2].sval = "b";
                } else if (p->root == tipoString){
                    tmp.head->args[2].sval = "s";
                } else {
                    char* sep = " "; // separatore
                    char* start = "a"; // è un tipo strutturato, la prima lettera del formato è una "a"
                    
                    char* res = string_cat(start, sep);
                    char* dimensions = "";
                    
                    ptypeS pt = exType;
                    while(pt->child != NULL){
                        dimensions = string_cat(dimensions,
                                string_cat(sep, itoa(pt->dim))
                                );
                        pt = pt->child;
                    }
                    
                    char* t;
                    if(pt == tipoBoolean){
                        t = "b";
                    } else if(pt == tipoIntero){
                        t = "i";
                    } else if(pt == tipoString){
                        t = "s";
                    } else {
                        fprintf(stderr, "ERRORE!"); // qualcosa non va
                        exit(-1);
                    }
                    res = string_cat(
                            res,
                            string_cat(
                            t,
                            dimensions
                            )
                            );
                    tmp.head->args[2].sval = res;
                }
                
                if(code.size == 0){
                    code = tmp;
                } else {
                    code = concode(code, tmp, endcode());
                }
                break;
            case N_OUTPUTSTAT:
                tmp = exprBody(nStat->child->child,&exType);
                Code write_stmn = makecode(WRIT);;
                if(exType == tipoIntero){
                    write_stmn.head->args[0].sval = "i";
                } else if (exType == tipoBoolean){
                    write_stmn.head->args[0].sval = "b";
                } else if (exType == tipoString){
                    write_stmn.head->args[0].sval = "s";
                } else {
                    char* sep = " "; // separatore
                    char* start = "a"; // è un tipo strutturato, la prima lettera del formato è una "a"
                    
                    char* res = string_cat(start, sep);
                    char* dimensions = "";
                    
                    ptypeS pt = exType;
                    while(pt->child != NULL){
                        dimensions = string_cat(dimensions,
                                string_cat(sep, itoa(pt->dim))
                                );
                        pt = pt->child;
                    }
                    
                    char* t;
                    if(pt == tipoBoolean){
                        t = "b";
                    } else if(pt == tipoIntero){
                        t = "i";
                    } else if(pt == tipoString){
                        t = "s";
                    } else {
                        fprintf(stderr, "ERRORE!"); // qualcosa non va
                        exit(-1);
                    }
                    res = string_cat(
                            res,
                            string_cat(
                            t,
                            dimensions
                            )
                            );
                    write_stmn.head->args[0].sval = res;
                }
                
                tmp = concode(tmp, write_stmn, endcode());
                
                if(code.size == 0){
                    code = tmp;
                } else {
                    code = concode(code, tmp, endcode());
                }
                break;
            case E_PROC:
                //TODO: write code for procedure call
                tmp = modCall(nStat->child,NULL);
                
                if(code.size == 0){
                    code = tmp;
                } else {
                    code = concode(code, tmp, endcode());
                }
                break;
          }
        
        
        nStat = nStat->brother;
    }

    return code;
}

/*
 * funzione che gestisce una if-stat
 * 
 * Essendo che la generazione del codice di tale controllo di flusso necessita
 * di sapere di quanto saltare tra una condizione ed un altra il codice è generato
 * in maniera inversa rispetto agli altri, partendo quindi con la generazione
 * dell'eventuale clausola else per poi tornare indietro e infine collegare i vari
 * pezzi di codice generato.
 * 
 * Dato che il codice per l'analisi semantica è stato pensato in maniera iterativa
 * la parte di generazione di codice è stata pensata per aderire a questa filosofia.
 */
Code ifStat(pnode nIfStat){
    Code res_code = endcode(),
            if_code = endcode(),
            elseif_code = endcode(),
            else_code = endcode();
    //printf("nIfStat\n");
    
    line = nIfStat->child->line;
    
    //exprIf deve tornare un bool se no è errore
    ptypeS exprIf = NULL;
    if_code = exprBody(nIfStat->child,&exprIf); // Genero codice per la condizione dell'IF
    
    if(controllaCompatibilitaTipi(exprIf,tipoBoolean)==0){
        //l'exprIf deve essere per forza un booleano, se no è errore
        printf("ERRORE #%d: l'expr di un if/elseif deve tornare un booleano\n",line);
        printSemanticError();
        exit(0);
    }
    
    Code cond_code = endcode();
    pnode nStatList = nIfStat->child->brother;
    cond_code = statList(nStatList); // Genero codice per la statList del THEN
    
    if_code = concode(if_code,
            makecode1(SKPF, cond_code.size + 1 + 1), // Salto all'else o all'else-if successivo
            cond_code,
            endcode()
            );
    
    pnode nOptElsif = nStatList->brother;
    pnode nOptExpr = nOptElsif->child;
    
    pnode nElseStatList = nOptElsif->brother;
    
    //se nElseStatList è != NULL svuol dire che c'è l'else finale
    if(nElseStatList!=NULL){
        else_code = statList(nElseStatList); // Genero il codice per l'else
    }
    
    // Conto il numero di else-if presenti
    int else_if_count = 0;
    
    pnode tmp_node = nOptExpr;
    while(tmp_node != NULL){
        else_if_count++;
        /* 
         * Ogni else-if è composto da una coppia di nodi quindi mi devo ogni
         * volta spostare di 2 elementi.
         */
        tmp_node = tmp_node->brother->brother;
    }
    
    /*
     * Ora devo costruire il codice dei vari else-if in maniera inversa rispetto
     * alla navigazione iterativa dell'albero.
     * Per fare ciò parto dall'ultimo else-if, spostando il puntatore di un numero
     * di passi che parte dal massimo numero di else-if a 0.
     * Ogni volta che sposto il puntatore genero il codice per l'else-if attualmente
     * puntato.
     */
    for(int i = else_if_count - 1; i >= 0; i--){
        Code elseif_cond_code = endcode(),
                elseif_then_code = endcode();
        
        tmp_node = nOptElsif;
        
        for(int j = 0; j < i; j++){
            tmp_node = tmp_node->brother->brother;
        }
        
        ptypeS exprElsif = NULL;
        elseif_cond_code = exprBody(nOptExpr, &exprElsif);
        
        if(controllaCompatibilitaTipi(exprElsif,tipoBoolean)==0){
            line = nOptExpr->child->line;
            //l'exprElsif deve essere per forza un booleano, se no è errore
            printf("ERRORE #%d: l'expr di un if/elseif deve tornare un booleano\n",line);
            printSemanticError();
            exit(0);
        }
        
        elseif_then_code = statList(nOptExpr->brother);
        
        elseif_code = concode(
                elseif_cond_code,
                makecode1(SKPF, elseif_then_code.size + 1), // Vado al prossimo else-if o all'else
                elseif_then_code,
                makecode1(SKIP, else_code.size + elseif_code.size), // Salto fuori dall'if
                elseif_code,
                endcode());
    }
    
    /*
     * Ora che ho generato il codice per tutti gli elementi posso sapere di quanto
     * saltare per uscire dopo l'esecuzione del codice per il THEN
     */
    if_code = concode(if_code, makecode1(SKIP, else_code.size + elseif_code.size), endcode());
    
    // Infine ritorno il codice così generato
    if(elseif_code.size != 0){
        res_code = concode(if_code, elseif_code, else_code, endcode());
    } else {
        res_code = concode(if_code, else_code, endcode());
    }
    return res_code;
}

/*
 * funzione che gestisce i while 
 */
Code whileStat(pnode nWhileStat){
    Code res_code = endcode(),
            cond_code = endcode(),
            while_code = endcode();
    //printf("whilestat\n");
    
    //exprWhile deve tornare un bool se no è errore
    ptypeS exprWhile = NULL;
    cond_code = exprBody(nWhileStat->child,&exprWhile);
    if(controllaCompatibilitaTipi(exprWhile,tipoBoolean)==0){
        line = nWhileStat->child->line;
        printf("ERRORE #%d: l'expr di un while deve tornare un booleano\n",line);
        printSemanticError();
        exit(0);
    }
    
    while_code = statList(nWhileStat->child->brother);
    
    res_code = concode(
            cond_code,
            makecode1(SKPF, while_code.size + 1),
            while_code,
            makecode1(SKIP, -(cond_code.size + 1 + while_code.size)),
            endcode()
            );
    
    return res_code;
    
}

/*
 * funzione che gestisce i repeat
 */
Code repeatStat(pnode nRepeatStat){
    Code res_code = endcode(),
            cond_code = endcode(),
            repeat_code = endcode();
    //printf("repeatstat\n");
    
    repeat_code = statList(nRepeatStat->child);
    
    //exprRep deve tornare un bool se no è errore
    ptypeS exprRep = NULL;
    cond_code = exprBody(nRepeatStat->child->brother,&exprRep);
    if(controllaCompatibilitaTipi(exprRep,tipoBoolean)==0){
        line = nRepeatStat->child->line;
        printf("ERRORE #%d: l'expr di un repeat deve tornare un booleano\n",line);
        printSemanticError();
        exit(0);
    }
    
    res_code = concode(
            repeat_code,
            cond_code,
            makecode1(SKPF, -(repeat_code.size + cond_code.size)),
            endcode()
            );
    
    return res_code;
}

/*
 *
 */
Code forStat(pnode nodoFor){
    //TODO: migliorare gestione temporaneo del ciclio for
    Code res_code = endcode(),
            start_value_code = endcode(),
            end_value_code = endcode(),
            for_code = endcode();
    
    //printf("forstat\n");
    pnode nId = nodoFor->child;
    pstLine p = controllaEsistenzaId(nId->val.sval, NULL);
    if(p==NULL || (p->classe != S_VAR && p->classe != S_IN && p->classe != S_OUT && p->classe != S_INOUT)){
        printf("ERRORE #%d: l'id %s della var del for non è quello di una variabile intera\n",nId->line,nId->val.sval);
        exit(0);
    }
    
    if(controllaCompatibilitaTipi(tipoIntero,p->root)==0){
        printf("ERRORE #%d: l'id %s della var del for non è quello di una variabile intera\n",nId->line,nId->val.sval);
        exit(0);
    }
    
    ptypeS expr1 = NULL;
    ptypeS expr2 = NULL;
    
    start_value_code = exprBody(nId->brother,&expr1);
    end_value_code = exprBody(nId->brother->brother,&expr2);
    
    if(controllaCompatibilitaTipi(tipoIntero,expr1)==0 || controllaCompatibilitaTipi(tipoIntero,expr2)==0){
        printf("ERRORE #%d: gli estremi della var %s nel for devono essere interi\n",nId->line,nId->val.sval);
        exit(0);
    }
    
    for_code = statList(nId->brother->brother->brother);
    
    int addr_tmp = stab->oidC + 1;
    res_code = concode(
            start_value_code,
            makecode2(STOR, 0, p->oid), //TODO: generalizzare
            end_value_code,
            //TODO: store nella stab locale
            makecode2(STOR, 0, addr_tmp), //Store del temporaneo
            makecode2(LOAD, 0, p->oid), //TODO: generalizzare
            makecode2(LOAD, 0, addr_tmp),
            makecode(ILEQ),
            makecode1(SKPF, for_code.size + 5),
            for_code,
            makecode2(LOAD, 0, p->oid), //TODO: generalizzare
            make_loci(1),
            makecode(ADDI),
            makecode2(STOR, 0, p->oid), //TODO: generalizzare
            makecode1(SKIP, -(for_code.size + 7)),
            endcode()
            );
    
    return res_code;
    
}

/*
 * funzione che gestisce la chiamata a una func o proc;
 * se è una func, viene settato il tipo ritornato;
 */
Code modCall(pnode nodoModcall,ptypeS* tipoRitornato){
    Code code = endcode();
    printf("modCall\n");
    
    //if da levare è solo per controllo
    if(tipoRitornato==NULL){
        printf("SIAMO in una proc\n");
    }
    
    ptypeS tipoRitornato2=NULL;
    pnode nodoIdMod = nodoModcall->child;
    
    idErr = nodoIdMod->val.sval;
    line = nodoIdMod->line;
    
    //controlliamo che l'id della func/proc esista
    pstLine p = controllaEsistenzaId(nodoIdMod->val.sval, NULL);
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
        
        tipoRitornato2 = p->root;
        
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
    
    if(tipoRitornato!=NULL){
        *tipoRitornato = tipoRitornato2;
        printf("Tipo ritornato dentro modcall\n");
        printType(*tipoRitornato);
    }
    
    pstLine modLine = findInSt(stab, nodoIdMod->val.sval);
    int objs = count_local_objs(modLine->local);
    code = make_call(modLine->formals1 + objs, objs, 0, modLine->mid); //TODO: static chain more general   
//    print_code(stdout, code);
//    exit(0);
    return code;
}

/*
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
   
    ptypeS typeAttuale = NULL;
    exprBody(attuale,&typeAttuale);

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
Code assignStat(pnode nStat){
    Code code,
            ex_code,
            lhs_code;
    //printf("assignStat\n");
    int risultato;
    
    pnode ex = nStat->child->child->brother;
  
    ptypeS typeExpr = NULL;
    ex_code = exprBody(ex,&typeExpr);
    if(typeExpr != tipoBoolean &&
                typeExpr != tipoIntero &&
                typeExpr != tipoString){
        Code pack = endcode();
        int atomic_elems = 1;
        ptypeS t = typeExpr;
        while(t->child != NULL){
            atomic_elems *= t->dim;
            t = t->child;
        }
        if(t == tipoIntero || t == tipoBoolean){
            pack = makecode2(PACK, atomic_elems, sizeof(int));
        } else if(t == tipoString) {
            pack = makecode2(PACK, atomic_elems, sizeof(void*));
        }
        ex_code = concode(ex_code, 
                pack,
                endcode());
    }
    
    ptypeS typeLhs = NULL;
    lhs_code = lhs(nStat->child->child,&typeLhs);
    
    pnode pt = nStat->child->child->child;
    
    if(pt->type == T_ID){
        
        int env_distance;
        pstLine line = controllaEsistenzaId(pt->val.sval, &env_distance);
        int addr = line->oid - offset - 1;
        
        if(typeLhs != tipoBoolean &&
                typeLhs != tipoIntero &&
                typeLhs != tipoString){
            code = concode(
                    //makecode2(LODA, env_distance, addr),
                    ex_code,
                    makecode2(STOR, env_distance, addr),
                    endcode()
                    );
        } else {
            code = concode(
                    ex_code,
                    makecode2(STOR, env_distance, addr),
                    endcode()
                    );
        }
    } else {
        code = concode(
                lhs_code,
                ex_code,
                makecode(ISTO),
                endcode()
                );
    }
    
    risultato = controllaCompatibilitaTipi(typeLhs,typeExpr);//recuperati i due tipi controllo che coincidano
    
    if(risultato==0){
        printf("ERRORE #%d: tipi dell'assegnamento non compatibili\n",line);
        printSemanticError();
        exit(0);
    }
    return code;
}

/*
 *lhs torna il tipo della lhs 
 */
Code lhs(pnode nLhs,ptypeS* tipoRitornato){
    Code code;
    
    printf("lhs\n");
    ptypeS tipoLhs = NULL;
    pnode figlio = nLhs->child;
    
    if(figlio->type == T_ID){//se il figlio del lhs è un id
        
        char *id = figlio->val.sval;
        pstLine p = controllaEsistenzaId(figlio->val.sval, NULL);
        
        idErr = figlio->val.sval;
        line = figlio->line;
        
        //TODO: errore semantico!
        if(!p || (p->classe != S_VAR &&
                p->classe != S_CONST &&
                p->classe != S_IN &&
                p->classe != S_INOUT)){
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
        }
        
        if(tipoLhs != tipoIntero &&
                tipoLhs != tipoBoolean &&
                tipoLhs != tipoString) {
            int env_distanve;
            pstLine line = controllaEsistenzaId(id, &env_distanve);
            int addr = line->oid - offset - 1;
            code = makecode2(LODA, env_distanve, addr);
        } else {
            code = endcode();
        }
    }
    else{//il figlio è un indexing
        
        Code lhs_code, ex_code;
        
        //printf("lhs INDEXING\n");
        pnode nLhs2 = figlio->child;
        pnode expr2 = figlio->child->brother;
        
        //parte per cercare di aggiustare l'eventule errore presentato a video
        if(nLhs2->child->type==T_ID){
            idErr = nLhs2->child->val.sval;
            line = nLhs2->child->line;
        }
        
        //la expr che forma un indexing deve essere per forza di tipo matematico, o lhs, o const, o mod call 
        //perchè la si deve usare per restituire un numero da usare come indicizzatore dell'array
        
        ptypeS tipoExpr2 = NULL;
        ex_code = exprBody(expr2,&tipoExpr2);
        if(controllaCompatibilitaTipi(tipoExpr2, tipoIntero)==0){
            printf("ERRORE: l'expr usata per l'indexing non restituisce un intero\n");
            printSemanticError();
            exit(0);
        }
           
        ptypeS parziale = NULL;
        lhs_code = lhs(nLhs2,&parziale);
        if(parziale->child!=NULL){
            tipoLhs = parziale->child;
        }
        else{
            printf("ERRORE: l'array non è cosy grande\n");
            printSemanticError();
            exit(0);
        }
        
        //generazione codice per indexing
        Code ixad;
        if(parziale == tipoIntero || parziale == tipoBoolean){
            ixad = makecode1(IXAD, sizeof(int));
        } else if (parziale == tipoString){
            ixad = makecode1(IXAD, sizeof(void*));
        } else {            
            ptypeS pt = parziale->child;
            
            if(pt == tipoIntero || pt == tipoBoolean){
                ixad = makecode1(IXAD, sizeof(int));
            } else if (pt == tipoString){
                ixad = makecode1(IXAD, sizeof(void*));
            } else {
                int size = 1;
                while(pt->child != NULL){
                    size *= pt->dim;
                    pt = pt->child;
                }
                
                if(pt == tipoIntero || pt == tipoBoolean){
                    ixad = makecode1(IXAD, size * sizeof(int));
                } else if (pt == tipoString){
                    ixad = makecode1(IXAD, size * sizeof(void*));
                }
            }
        }
        
        code=concode(
        lhs_code,
        ex_code,
        ixad,
        endcode()
        );
         
    }
    
    *tipoRitornato = tipoLhs;
    
    return code;
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
Code expr(pnode nExpr,ptypeS* tipoRitornato){
    Code ex_code = endcode(),
            f1_code = endcode(),
            f2_code = endcode(),
            res_code = endcode();
    
    printf("expr\n");
    ptypeS tipoRitornato2;//tipo ritornato dall'expr
    
    line = nExpr->line;
    
    int tipoExpr; 
    
    //stabilisco il tipo della expr
    switch(nExpr->type){
            case T_LOGICEXPR: 
                tipoExpr= T_LOGICEXPR;
                tipoRitornato2=tipoBoolean;//una logic expr deve tornare un bool 
                break;              
            case T_MATHEXPR: 
                tipoExpr= T_MATHEXPR;
                tipoRitornato2=tipoIntero;//una math expr deve tornare un integer
                break;   
            case T_COMPEXPR: 
                tipoExpr= T_COMPEXPR;
                tipoRitornato2=tipoBoolean;//una comp expr deve tornare un bool ;
                break;
            case T_NEGEXPR:
                tipoExpr= T_NEGEXPR;
                //una neg expr può tornare un bool o un int ;
                if(nExpr->val.ival==E_UMINUS){
                    tipoRitornato2=tipoIntero;
                }else{
                    tipoRitornato2=tipoBoolean;
                }
                
            break;
          }
    
    pnode f1 = nExpr->child;
    pnode f2 = nExpr->child->brother;
    
    //stabilisco il tipo del primo figlio
    ptypeS tr1 = NULL;
    f1_code = exprBody(f1,&tr1);   
    printf("TIPO FIGLIO 1\n");
    printType(tr1);   
    //stabilisco iltipo del secondo figlio (fratello del primo figlio)
    //di default lo metto uguale a tr1 e se sono nel caso di una neg expr lo lascio cosi (non entro nell'if)
    //altrimenti richiamo exprBody 
    ptypeS tr2 = tr1;
    if(!(tipoExpr==T_NEGEXPR)){
        f2_code = exprBody(f2,&tr2);
    }
    
     printf("TIPO FIGLIO 2\n");
    printType(tr2);
    
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
                    printf("ERRORE #%d: non puoi applicare == o != ad un booleano\n",line);
                    //printSemanticError();
                    exit(0);               
                }

            }
            *tipoRitornato = tipoRitornato2;
           
        }
        else{
            /*
             *Se ho una math una logic o una neg expr deve essere che
             * tipoRitornato == tipoRitornato1 == tipoRitornato2
             * altrimenti ho errore
             */
            if(controllaCompatibilitaTipi(tr1,tipoRitornato2)==1 && controllaCompatibilitaTipi(tr1,tr2)==1){
                
                *tipoRitornato = tipoRitornato2;
            }else{
                printf("ERRORE #%d: non puoi applicare quell'operatore a quel tipo di figli\n",line);
                //printSemanticError();
                exit(0); 
            }

        }        
    }
    
    //stabilisco il tipo della expr per la generazione del codice
    switch(nExpr->type){
            case T_LOGICEXPR: 
                switch(nExpr->val.ival){
                    case E_AND:
                        res_code = concode(f1_code,
                                makecode1(SKPF, f2_code.size + 2),
                                f2_code,
                                makecode1(SKIP, 2),
                                make_loci(0),
                                endcode()
                                );
                        break;
                    case E_OR:
                        res_code = concode(f1_code,
                                makecode1(SKPF, 3),
                                make_loci(1),
                                makecode1(SKIP, f2_code.size + 1),
                                endcode()
                                );
                        break;
                    default:
                        //Albero generato male!
                        fprintf(stderr, "MATHEXPR not found!");
                        exit(-1);
                        break;
                }
                break;              
            case T_MATHEXPR: 
                switch(nExpr->val.ival){
                    case E_PLUS:
                        ex_code = makecode(ADDI);
                        break;
                    case E_MINUS:
                        ex_code = makecode(SUBI);
                        break;
                    case E_MUL:
                        ex_code = makecode(MULI);
                        break;
                    case E_DIV:
                        ex_code = makecode(DIVI);
                        break;
                    default:
                        //Albero generato male!
                        fprintf(stderr, "MATHEXPR not found!");
                        exit(-1);
                        break;
                }
                res_code = concode(f1_code,
                        f2_code,
                        ex_code,
                        endcode());
                break;   
            case T_COMPEXPR: 
                switch(nExpr->val.ival){
                    case E_EQ:
                        ex_code = makecode(EQUA);
                        break;
                    case E_NE:
                        ex_code = makecode(NEQU);
                        break;
                    case E_GT:
                        if(tr1 == tipoIntero){
                            ex_code = makecode(IGRT);
                        } else if(tr1 == tipoString){
                            ex_code = makecode(SGRT);
                        }
                        break;
                    case E_GE:
                        if(tr1 == tipoIntero){
                            ex_code = makecode(IGEQ);
                        } else if(tr1 == tipoString){
                            ex_code = makecode(SGEQ);
                        }
                        break;
                    case E_LT:
                        if(tr1 == tipoIntero){
                            ex_code = makecode(ILET);
                        } else if(tr1 == tipoString){
                            ex_code = makecode(SLET);
                        }
                        break;
                    case E_LE:
                        if(tr1 == tipoIntero){
                            ex_code = makecode(ILEQ);
                        } else if(tr1 == tipoString){
                            ex_code = makecode(SLEQ);
                        }
                        break;
                    default:
                        //Albero generato male!
                        fprintf(stderr, "MATHEXPR not found!");
                        exit(-1);
                        break;
                }
                
                res_code = concode(f1_code,
                        f2_code,
                        ex_code,
                        endcode());
                
                break;
            case T_NEGEXPR:
                switch(nExpr->val.ival){
                    case E_NOT:
                        ex_code = makecode(NEGA);
                        break;
                    case E_UMINUS:
                        ex_code = makecode(UMIN);
                        break;
                    default:
                        //Albero generato male!
                        fprintf(stderr, "MATHEXPR not found!");
                        exit(-1);
                        break;
                }
                res_code = concode(f1_code,
                        ex_code,
                        endcode()
                        );
            break;
          }
    
    return res_code;
    
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
pstLine controllaEsistenzaId(char* id, int* env_distance){
    //printf("controllaEsistenzaId\n");
    int distance = 0;
    
    pST s = stab;
    
    pstLine p = NULL;
    
    while(s){//oltre che nella stab locale devo anche controllare in quelle dei genitori
            
            p = findInSt(s->tab, id);
         
            if(p){//se trovo una corrispondenza
                
                break; //saltimao fuori dal while se abbiamo trovato una precedente dichiarazione
            }else{
                s = s->back;
                distance++;
            }
            
        }
    if(env_distance != NULL){
        *env_distance = distance;
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


int count_local_objs(pstLine s[]){
    int objs = 0;
    for (int i = 0; i < TOT; i++){
        pstLine l = s[i];
        while(l != NULL){
            if(l->classe == S_VAR || l->classe == S_CONST){
                objs++;
            }
            l = l->next;
        }
    }
    return objs;
}