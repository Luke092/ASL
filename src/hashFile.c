/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "def.h"
#include <stdio.h>
#include <stdlib.h>

int hash(char *id){
    int h = 0;
    int i= 0;

    for(i = 0; id[i] != '\0'; i++){
        
        h = ((h << SHIFT)+id[i])%TOT;
        
    }
    printf("stringa %s HASH %d\n",id,h);
    return h;
    
}

nodo* creaNodo(int h, char *id){
    struct nodo *nuovoNodo;
    nuovoNodo = malloc(sizeof(struct nodo));
    //tabella[h] = nuovoNodo;
    nuovoNodo->stringa = id;
    return nuovoNodo;
}


char* insertFind(int h, char *id){
    char *p;
    nodo *nuovoNodo, *parente;
    if(!tabella[h]){ // se non c'è già un nodo con quell'hash
        
        nuovoNodo = creaNodo(h,id);
        tabella[h] = nuovoNodo;
        
    }else{ // se c'è già un nodo con quell'hash
        //printf("dentro primo else\n");
        int trovato = 0;
        int nullo = 0;
        parente = tabella[h];
        while(!nullo && !trovato){
            /*printf("dentro while\n");
            printf("stringa nodo %s\n",parente->stringa);
            printf("CAZZO1\n");
            printf("ID:%s",id);
            printf("CAZZO2\n");*/
            //int a;
            //printf("stringhe da confrontare %s %s\n",parente->stringa,id);
            if((strcmp(parente->stringa,id)) == 0){ // controllo il valore della stringa del nodo
                //printf("dentro if a:%d\n",a);
                //printf("TROVATO str1: %s str2:%s\n",parente->stringa,id);
                trovato = 1;
                p = parente->stringa;
                return p;
            }else{ //se il nodo ha stringa diversa passo oltre        
                if(parente->fratello != 0){ // se il puntatore è assegnato passo al nodo successivo
                    //printf("dentro if\n");
                    parente = parente->fratello;
                    //printf("puntiamo a %s\n",parente->stringa);
                }else{
                   // printf("nullo\n");
                    nullo = 1;
                }
                
            }
            
        }
        //printf("fuori dal while\n");
        nuovoNodo = creaNodo(h,id);
        parente->fratello = nuovoNodo;
       // printf("stringa aggiunta %s\n",parente->fratello->stringa);
    }
    p = nuovoNodo->stringa;
    return p;
}

//funzione ausiliaria

void stampa(){
    int i;
    for(i =0; i<TOT;i++){
        if(tabella[i]){
            printf("%d stringa:%s \n",i,tabella[i]->stringa);
            nodo *parente = tabella[i]->fratello;
            while(parente){
                printf("CREDIAMOCI");
                printf("%d stringa interna:%s \n",i,parente->stringa);
                parente = parente->fratello;
            }
        }else{
            printf("%d UN CAZZO\n",i);
        }
    }
}