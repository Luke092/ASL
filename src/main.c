#include "def.h"
#include "def_symbtab.h"
#include "def_codegen.h"

FILE *yyin;
pnode root = NULL;

int main(int argc,char* argv[]){
    int result;
    
    yyin = fopen(argv[1],"r");
      
    if((result = yyparse()) == 0)
    {
        treeprint(root, 0);
        Code code;
        code = start(root,createSymbTab(NULL),NULL);
        print_code(stdout, code); //Stampo ACODE nello standard output
    }
    
  return(result);
    
}