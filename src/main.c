#include "def.h"
#include "def_symbtab.h"
#include <stdio.h>
#include <stdlib.h>

FILE *yyin;
pnode root = NULL;

int stampaSymbtab=2;
FILE *sp;
FILE *file;
FILE *fileCode;

int main(int argc,char* argv[]){
    int result;
    
    yyin = fopen(argv[1],"r");
      
    if((result = yyparse()) == 0)
    {
        
        int i = 3;
        
        while(i<=argc){
                     
            if(strcmp("-tree",argv[i-1])==0){
             
                file = fopen("tree.txt", "w");
                if (file == NULL) {
                    printf("qwertyu\n");
                }
                treeprint(root, 0, file);
                
                fclose(file);
            }else if(strcmp("-symb",argv[i-1])==0){
                stampaSymbtab = 1;
                sp = fopen("symb.txt", "w");
            }else{
                printf("Parametro errato %s\n",argv[i-1]);
            }
            
            i++;
        }
        
        Code code;
        code = start(root,createSymbTab(NULL),NULL);
        if(sp!=NULL){
            fclose(sp);
        }
        //print_code(stdout, code); //Stampo ACODE nello standard output
        char *nomeProg = strcat(argv[1],".code");
        fileCode = fopen(nomeProg,"w");
        print_code(fileCode, code);
    }
    
  return result;
    
}