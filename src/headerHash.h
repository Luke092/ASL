/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functionsHash.h
 * Author: andrea
 *
 * Created on 23 maggio 2016, 18.22
 */

#ifndef FUNCTIONSHASH_H
#define FUNCTIONSHASH_H

int hash(char *id);

nodo* creaNodo(char *id);

char* insertFind(int h, char *id);

void stampa();


#endif /* FUNCTIONSHASH_H */

