/* 
 * File:   CodeGen_Utility.c
 * Author: Luca
 *
 * Created on December 6, 2016, 11:28 AM
 */

#include <stdlib.h>
#include "def_codegen.h"

char* s_op_code[] = 
{
    "ACODE",
    "PUSH",
    "JUMP",
    "APOP",
    "HALT",
    "ADEF",
    "SDEF",
    "LOAD",
    "PACK",
    "LODA",
    "IXAD",
    "AIND",
    "SIND",
    "STOR",
    "ISTO",
    "SKIP",
    "SKPF",
    "EQUA",
    "NEQU",
    "IGRT",
    "IGEQ",
    "ILET",
    "ILEQ",
    "SGRT",
    "SGEQ",
    "SLET",
    "SLEQ",
    "ADDI",
    "SUBI",
    "MULI",
    "DIVI",
    "UMIN",
    "NEGA",
    "READ",
    "WRIT",
    "MODL",
    "RETN",
    "LOCS",
    "LOCI",
    "NOOP"
};

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

Code makecode3(Operator op, int arg1, int arg2, int arg3){
    Code code;
    
    code = makecode(op);
    code.head->args[0].ival = arg1;
    code.head->args[1].ival = arg2;
    code.head->args[2].ival = arg3;
    
    return code;
}

Code make_call(int nformals_aux, int nlocals, int chain, int entry){
    return concode(
            makecode3(PUSH, nformals_aux, nlocals, chain),
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

void print_code(FILE* file, Code code){
    Stat* pt = code.head;
    for(int i = 0; i < code.size; i++){
        print_stat(file, pt);
        pt = pt->next;
    }
}

void print_stat(FILE* file, Stat* stat){
    fprintf(file, "%s ", s_op_code[stat->op]);
    switch(stat->op){
        case ACODE:
            fprintf(file, "%d\n", stat->args[0]);
            break;
        case PUSH:
            fprintf(file, "%d %d %d\n", stat->args[0].ival,
                    stat->args[1].ival,
                    stat->args[2].ival);
            break;
        case JUMP:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        case APOP:
            fprintf(file, "\n");
            break;
        case HALT:
            fprintf(file, "\n");
            break;
        case ADEF:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        case SDEF:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        case LOAD:
            fprintf(file, "%d %d\n", stat->args[0].ival,
                    stat->args[1].ival);
            break;
        case PACK:
            fprintf(file, "%d %d\n", stat->args[0].ival,
                    stat->args[1].ival);
            break;
        case LODA:
            fprintf(file, "%d %d\n", stat->args[0].ival,
                    stat->args[1].ival);
            break;
        case IXAD:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        case AIND:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        case SIND:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        case STOR:
            fprintf(file, "%d %d\n", stat->args[0].ival,
                    stat->args[1].ival);
            break;
        case ISTO:
            fprintf(file, "\n");
            break;
        case SKIP:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        case SKPF:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        case EQUA:
            fprintf(file, "\n");
            break;
        case NEQU:
            fprintf(file, "\n");
            break;
        case IGRT:
            fprintf(file, "\n");
            break;
        case IGEQ:
            fprintf(file, "\n");
            break;
        case ILET:
            fprintf(file, "\n");
            break;
        case ILEQ:
            fprintf(file, "\n");
            break;
        case SGRT:
            fprintf(file, "\n");
            break;
        case SGEQ:
            fprintf(file, "\n");
            break;
        case SLET:
            fprintf(file, "\n");
            break;
        case SLEQ:
            fprintf(file, "\n");
            break;
        case ADDI:
            fprintf(file, "\n");
            break;
        case SUBI:
            fprintf(file, "\n");
            break;
        case MULI:
            fprintf(file, "\n");
            break;
        case DIVI:
            fprintf(file, "\n");
            break;
        case UMIN:
            fprintf(file, "\n");
            break;
        case NEGA:
            fprintf(file, "\n");
            break;
        case READ:
            fprintf(file, "%d %d \"%s\"\n", stat->args[0].ival,
                    stat->args[1].ival,
                    stat->args[2].sval);
            break;
        case WRIT:
            fprintf(file, "\"%s\"\n", stat->args[0].sval);
            break;
        case MODL:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        case RETN:
            fprintf(file, "\n");
            break;
        case LOCS:
            fprintf(file, "%s\n", stat->args[0].sval);
            break;
        case LOCI:
            fprintf(file, "%d\n", stat->args[0].ival);
            break;
        default:
            fprintf(file, "OPERATORE NON RICONOSCIUTO!\n");
            break;
    }
}