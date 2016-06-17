/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "headerHash.h"

nodo *tabella[TOT - 1];

int hash(char *id){
    int h = 0;
    int i= 0;

    for(i = 0; id[i] != '\0'; i++){
        
        h = ((h << SHIFT)+id[i])%TOT;
        
    }
    //printf("stringa %s HASH %d\n",id,h);
    return h;
    
}

nodo* creaNodo(char *id){
    struct nodo *nuovoNodo;
    nuovoNodo = malloc(sizeof(struct nodo));
    char *p = malloc(strlen(id)+1);
    strcpy(p,id);
    nuovoNodo->stringa = p;
    return nuovoNodo;
}


char* insertFind(int h, char *id){
    char *p;
    nodo *nuovoNodo, *parente;
    if(!tabella[h]){ // se non c'è già un nodo con quell'hash
        
        nuovoNodo = creaNodo(id);
        tabella[h] = nuovoNodo;
              
        
    }else{ // se c'è già un nodo con quell'hash
        
        int trovato = 0;
        int nullo = 0;
        parente = tabella[h];
        while(!nullo && !trovato){
            
            if((strcmp(parente->stringa,id)) == 0){ // controllo il valore della stringa del nodo
                //se trovo un nodo già presente con l stessa stringa
                
                p = parente->stringa;
                return p;

            }else{ //se il nodo ha stringa diversa passo oltre        
                
                    if(parente->fratello != 0){ // se il puntatore è assegnato passo al nodo successivo
                    
                        parente = parente->fratello;
                    
                    }else{//altrimenti sono arrivato in fondo senza trovare un nodo con la stringa uguale  e devo uscire dal while e crearne uno nuovo nodo
                   
                        nullo = 1;
                    }
                
            }
            
        }
        
        nuovoNodo = creaNodo(id);
        parente->fratello = nuovoNodo;
       
    }
    p = nuovoNodo->stringa;
    return p;
}

void stampa(){
    int i;
    for(i =0; i<TOT;i++){
        if(tabella[i]){
            printf("%d stringa:%s \n",i,tabella[i]->stringa);
            nodo *parente = tabella[i]->fratello;
            while(parente){
                //printf("CREDIAMOCI");
                printf("%d stringa interna:%s \n",i,parente->stringa);
                parente = parente->fratello;
            }
        }else{
            printf("%d VUOTO\n",i);
        }
    }
}