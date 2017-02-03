#include "def.h"
#include "def_symbtab.h"
//#include "def_codegen.h"

FILE *yyin;
pnode root = NULL;

int stampaSymbtab=3;
FILE *sp;

int main(int argc,char* argv[]){
    int result;
    
    yyin = fopen(argv[1],"r");
      
    if((result = yyparse()) == 0)
    {
        
        int i = 3;
        
        while(i<=argc){
            
            
            if(strcmp("-tree",argv[i-1])==0){
                FILE *fp;
                fp = fopen("tree.txt", "w");
                treeprint(root, 0,fp);
                fclose(fp);
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
        print_code(stdout, code); //Stampo ACODE nello standard output
    }
    
  return(result);
    
}