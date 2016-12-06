/* 
 * File:   def_codegen.h
 * Author: Luca
 *
 * Created on December 6, 2016, 11:28 AM
 */

#ifndef DEF_CODEGEN_H
#define DEF_CODEGEN_H

enum Operator{
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
    RETN
};

char* s_op_code[]{
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
    "RETN"
};

typedef struct{
    int address;
    Operator op;
    int args[3];
    Stat* next;
} Stat;

typedef struct{
    Stat* head;
    int size;
    Stat* tail;
} Code;

Code    relocate(Code code, int offset),
        appcode(Code code1, Code code2),
        endcode(),
        concode(Code code1, Code code2, ...),
        makecode(Operator op),
        makecode1(Operator op, int arg),
        makecode2(Operator op, int arg1, int arg2),
        make_call(int nobj, int chain, int entry),
        make_loci(int i),
        make_locs(char* s);

Stat* newstat(Operator op);

#endif /* DEF_CODEGEN_H */

