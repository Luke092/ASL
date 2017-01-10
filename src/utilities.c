#include "utilities.h"

char* string_cat(char* s1, char* s2){
    int size1 = strlen(s1);
    int size2 = strlen(s2);
    char* res = (char*) malloc(sizeof(char) * size1 + size2 + 1);
    
    char* pt_r = res;
    
    char* pt_s = s1;
    for(int i = 0; i < size1; i++){
        *pt_r = *pt_s;
        pt_r++;
        pt_s++;
    }
    pt_s = s2;
    for(int i = 0; i < size2; i++){
        *pt_r = *pt_s;
        pt_r++;
        pt_s++;
    }
    *pt_r = '\0';
    
    return res;
}

char* itoa(int i){    
    int size = 0;
    int tmp = i;
    while(tmp != 0){
        tmp = (int)(tmp / 10);
        size++;
    }
    int strsize;
    if(i < 0){
        strsize = size + 1 + 1;
    } else {
        strsize = size + 1;
    }
    
    char* num = (char*) malloc(sizeof(char) * strsize);
    
    snprintf(num, strsize, "%d", i);
    
    return num;
}