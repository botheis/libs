#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ini.h"
#include "../bool.h"
#include "../String/String.h"

IniSection* Ini_CreateSection(){
    IniSection* tmp = (IniSection*)malloc(sizeof(IniSection));

    if(tmp != NULL){
        strcpy(tmp->name, "");
        tmp->list = NULL;
        tmp->size = 0;
    }
    return tmp;
}

IniParser* Ini_CreateParser(){
    IniParser* tmp = (IniParser*)malloc(sizeof(IniParser));
    if(tmp != NULL){
        tmp->list = NULL;
        tmp->size = 0;
    }
    return tmp;
}

void Ini_FreeParser(IniParser* tofree){
    if(tofree->list != NULL){
        for(size_t i=0; i< tofree->size; i++){
            // for each section
            strcpy(tofree->list[i].name, "");
            if(tofree->list[i].list != NULL){
                free(tofree->list[i].list);
                tofree->list[i].list = NULL;
                tofree->list[i].size = 0;
            }
        }
        tofree->size = 0;
        free(tofree->list);
        tofree->list = NULL;
    }
    free(tofree);
}

void Ini_PushSection(IniParser* parser, const char* name){
    if(parser->list == NULL){
        parser->list = (IniSection*)malloc(sizeof(IniSection));
        if(parser->list != NULL){
            parser->size += 1;
        }
    }
    else{
        IniSection* tmp = (IniSection*)realloc(parser->list, (parser->size+1)*sizeof(IniSection));
        if(tmp != NULL){
            parser->list = tmp;
            parser->size += 1;
        }
    }

    IniSection* index = parser->list+(parser->size-1);
    index->list = NULL;
    strcpy(index->name, name);
    index->size = 0;
}


void Ini_PopSection(IniParser* parser){
    if(parser->list != NULL){
        if(parser->size-1 > 0){
            IniSection* tmp = realloc(parser->list, (parser->size-1)*sizeof(IniSection));
            if(tmp != NULL){
                parser->list = tmp;
                parser->size -= 1;
            }
        }
        else{
            free(parser->list);
            parser->list = NULL;
            parser->size = 0;
        }
    }
}

void Ini_ShowSectionNames(IniParser* parser){
    for(size_t i=0; i< parser->size; i++){
        printf("%s\n", parser->list[i].name);
    }
}

void Ini_ShowOptions(IniSection* section){
    for(size_t i=0; i<section->size; i++){
        printf("%s = %s\n", section->list[i].name, section->list[i].value);
    }
}

IniSection* Ini_GetSection(IniParser* parser, const char* name){
    for(size_t i=0; i < parser->size; i++){
        if(strcmp(parser->list[i].name, name) == 0){
            return &parser->list[i];
        }
    }
    return NULL;
}

IniSection* Ini_GetSectionFromId(IniParser* parser, int id){
    if(id >= parser->size || id < 0){
        return NULL;
    }
    return parser->list+id;
}

bool Ini_HasSection(IniParser* parser, const char* name){
    return (Ini_GetSection(parser, name) == NULL) ? FALSE : TRUE;
}

bool Ini_HasOption(IniParser* parser, const char* sectionName, const char* optionName){
    if(Ini_HasSection(parser, sectionName) == FALSE){
        return FALSE;
    }
    IniSection *section = Ini_GetSection(parser, sectionName);
    for(size_t i=0; i < section->size; i++){
        if(strcmp(section->list[i].name, optionName) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

char* Ini_GetOption(IniParser* parser, const char* sectionName, const char* optionName){
    if(Ini_HasSection(parser, sectionName) == FALSE){
        return NULL;
    }
    IniSection *section = Ini_GetSection(parser, sectionName);
    for(size_t i=0; i < section->size; i++){
        if(strcmp(section->list[i].name, optionName) == 0){
            return section->list[i].value;
        }
    }
    return NULL;
}

void Ini_PushOption(IniSection* section, const char* name, const char* value){
    
    if(section->list == NULL){
        section->list = (IniOption*)malloc(sizeof(IniOption));
        section->size = 1;
    }
    else{
        IniOption* tmp = realloc(section->list, (section->size+1)*sizeof(IniOption));
        if(tmp != NULL){
            section->list = tmp;
            section->size += 1;
        }
    }
    IniOption* index = section->list+(section->size-1);
    if(section->size > 0){
        strcpy(index->name, name);
        strcpy(index->value, value);
    }
}

bool Ini_ParseFile(const char* filename, IniParser* parser){
    FILE* config = fopen(filename, "r");
    if(config == NULL){
        fclose(config);
        return FALSE;
    }

    long size = 0;
    fseek(config, 0, SEEK_END);
    size = ftell(config)+1;
    fseek(config, 0, SEEK_SET);
    
    char* content = (char*) malloc((size)*sizeof(char));
    if(content == NULL){
        fclose(config);
        free(content);
        return FALSE;
    }
    fread(content, 1, size, config);
    fclose(config);
    content[size-1] = '\0';
    // Mode comment
    char commentMode = 0;
    char sectionMode = 0;
    char optionMode = 0;
    char valueMode = 0;

    char sectionTmp[255] = "";
    char optionTmp[255] = "";
    char valueTmp[255] = "";

    int i = 0;
    while(i < size){

        if(content[i] == '\n' || content[i] == '\0'){
            commentMode = 0;
            sectionMode = 0;
            optionMode = 0;
            valueMode = 0;

            if(strcmp(optionTmp, "") != 0 ){
                IniSection* section = Ini_GetSection(parser, sectionTmp);
                if(section != NULL){
                    #ifdef DEBUG
                        printf("s:%s\to:%s\tv:%s\n", sectionTmp, optionTmp, valueTmp);
                    #endif
                    char* opt = trim(' ', optionTmp);
                    char* val = trim(' ', valueTmp);

                    Ini_PushOption(section, opt, val);
                    free(opt);
                    free(val);
                }
            }
            
            strcpy(optionTmp, "");
            strcpy(valueTmp, "");

            i++;
            continue;
        }

        if(content[i] == ';'){
            commentMode = 1;
            sectionMode = 0;
            optionMode = 0;
            valueMode = 0;
        }

        if(content[i] == '[' && commentMode == 0){
            strcpy(sectionTmp, "");
            sectionMode = 1;
            i++;
            continue;
        }
        if(content[i] == ']' && commentMode == 0){
            sectionMode = 0;
            #ifdef DEBUG
                printf("new section : %s\n", sectionTmp);
            #endif
            Ini_PushSection(parser, sectionTmp);
            i++;
            continue;
        }

        if(sectionMode == 0 && commentMode == 0 && valueMode == 0){
            optionMode = 1;
        }

        if(optionMode){
            if(content[i] == '='){
                optionMode = 0;
                valueMode = 1;
            }
            else{
                strncat(optionTmp, content+i, 1);   
            }
            i++;
            continue;
        }

        if(commentMode){
            i++;
            continue;
        }
        if(sectionMode){
            strncat(sectionTmp, content+i,1);
        }
        if(valueMode){
            strncat(valueTmp, content+i,1);
        }
        i++;
    }
    free(content);
    return TRUE;
}

bool Ini_WriteFile(const char* filename, IniParser* parser){
    FILE* config = fopen(filename, "w");
    if(config == NULL){
        return FALSE;
    }

    for(int i=0; i< parser->size; i++){
        IniSection* SIndex = parser->list+i;

        fprintf(config, "[%s]\n", SIndex->name);
        
        for(int j=0; j<SIndex->size; j++){
            IniOption* OIndex = SIndex->list+j;
            fprintf(config, "%s=%s\n", OIndex->name, OIndex->value);
        }
    }

    fclose(config);
    return TRUE;
}