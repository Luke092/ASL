/* 
 * File:   CodeGen_Utility.c
 * Author: Luca
 *
 * Created on December 6, 2016, 11:28 AM
 */

#include <stdlib.h>
#include "def_codegen.h"

void relocate(Code code, int offset){
    Stat* pt = code.head;
    int i;
    
    for (i=0; i < code.size; i ++){
        pt->address += offset;
        pt = pt->next;
    }
}

Code appcode(Code code1, Code code2){
    Code rescode;
    
    relocate(code2, code1.size);
    rescode.head = code1.head;
    rescode.tail = code2.tail;
    code1.tail->next = code2.head;
    rescode.size = code1.size + code2.size;
    
    return rescode;
}

Code endcode(){
    static Code code = {NULL, 0, NULL};
    return code;
}

Code concode(Code code1, Code code2, ...){
    Code rescode = code1;
    Code* pcode = &code2;
    
    while(pcode->head != NULL)
    {
        rescode = appcode(rescode, *pcode);
        pcode++;
    }
    
    return rescode;
}

Code makecode(Operator op){
    Code code;
    
    code.head = code.tail = newstat(op);
    code.size = 1;
    
    return code;
}

Code makecode1(Operator op, int arg){
    Code code;
    
    code = makecode(op);
    code.head->args[0].ival = arg;
    
    return code;
}

Code makecode2(Operator op, int arg1, int arg2){
    Code code;
    
    code = makecode(op);
    code.head->args[0].ival = arg1;
    code.head->args[1].ival = arg2;
    
    return code;
}

Code make_call(int nobj, int chain, int entry){
    return concode(
            makecode2(PUSH, nobj, chain),
            makecode1(JUMP, entry),
            makecode(APOP),
            endcode()
            );
}
Code make_loci(int i){
    Code code;
    code = makecode(LOCI);
    code.head->args[0].ival = i;
    return code;
}

Code make_locs(char* s){
    Code code;
    code = makecode(LOCS);
    code.head->args[0].sval = s;
    return code;
}

Stat* newstat(Operator op){
    Stat *pstat;
    pstat = (Stat*)malloc(sizeof(Stat));
    pstat->address = 0;
    pstat->op = op;
    pstat->next = NULL;
    return pstat;
}