#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "String.h"

/*
Not used yet
------------

String* new_String(const char* content){
    String* tmp = (String*)malloc(sizeof(String));
    if(tmp == NULL){
        return NULL;
    }
    tmp->size = strlen(content);
    tmp->content = (char*) malloc(tmp->size+1);
    strcpy(tmp->content, content);

    return tmp;
}

void free_String(String* tofree){
    if(tofree != NULL){
        if(tofree->content != NULL){
            free(tofree->content);
            tofree->content = NULL;
            tofree->size = 0;
        }
        free(tofree);
    }
}

int cmp_String(String* a, String* b){
    return strcmp(a->content, b->content);
}


void affect_String(String* ref, const char* content){
    if(ref != NULL){
        if(ref->content != NULL){
            free(ref->content);
            ref->size = strlen(content);
            ref->content = (char*)malloc(ref->size+1);
            strcpy(ref->content, content);
        }
    }
}
*/

char* ltrim(char rem, const char* str){
    size_t size = strlen(str)+1;
    
    int start=0;
    for(int i=0; i< size; i++){
        if(str[i] == rem){
            start += 1;
        }
        else{
            break;
        }
    }

    char* result = (char*)malloc(size-start);
    strcpy(result, str+start);
    return result;
}

char* rtrim(char rem, const char* str){
    size_t end=strlen(str);

    for(int i=end-1; i>=0; i--){
        // printf("rtrim #%d: %c(%d) ?=? %c\n", i, str[i], str[i], rem);
        if(str[i] == rem){
            end -= 1;
        }
        else{
            break;
        }
    }

    char* result = (char*)malloc(end+1);

    strcpy(result, "");
    strncat(result, str, end);
    return result;
}

char* trim(char rem, const char* str){
    char* ltrimed = ltrim(rem, str);
    char* trimed = rtrim(rem, ltrimed);
    free(ltrimed);
    return trimed;
}