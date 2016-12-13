/* 
 * File:   def_codegen.h
 * Author: Luca
 *
 * Created on December 6, 2016, 11:28 AM
 */

#ifndef DEF_CODEGEN_H
#define DEF_CODEGEN_H

#include "def.h"

typedef enum {
    ACODE,
    PUSH,
    JUMP,
    APOP,
    HALT,
    ADEF,
    SDEF,
    LOAD,
    PACK,
    LODA,
    IXAD,
    AIND,
    SIND,
    STOR,
    ISTO,
    SKIP,
    SKPF,
    EQUA,
    NEQU,
    IGRT,
    IGEQ,
    ILET,
    ILEQ,
    SGRT,
    SGEQ,
    SLET,
    SLEQ,
    ADDI,
    SUBI,
    MULI,
    DIVI,
    UMIN,
    NEGA,
    READ,
    WRIT,
    MODL,
    RETN,
    LOCS,
    LOCI,
    NOOP
} Operator;

typedef struct stat{
    int address;
    Operator op;
    Value args[3];
    struct stat* next;
} Stat;

typedef struct{
    Stat* head;
    int size;
    Stat* tail;
} Code;

void    relocate(Code code, int offset);

Code    appcode(Code code1, Code code2),
        endcode(),
        concode(Code code1, Code code2, ...),
        makecode(Operator op),
        makecode1(Operator op, int arg),
        makecode2(Operator op, int arg1, int arg2),
        makecode3(Operator op, int arg1, int arg2, int arg3),
        make_call(int nformals_aux, int nlocals, int chain, int entry),
        make_loci(int i),
        make_locs(char* s),
        cg_array_const(pnode node);

Stat* newstat(Operator op);

void    print_code(FILE* file, Code code),
        print_stat(FILE* file, Stat* stat);

#endif /* DEF_CODEGEN_H */

