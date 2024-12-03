#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "option.h"
#include "../system/garbage.h"

Option Option_Create(const char* name, int count, const char* help, OptionAction trigger){
    Option tmp;
    if(name == NULL || strcmp(name, "") == 0){
        tmp.count = 0;
        tmp.pos = 0;
        tmp.help = NULL;
        tmp.name = NULL;
        tmp.start = NULL;
        tmp.trigger = NULL;
        tmp.parsed = false;
        tmp.valided = false;
        return tmp;
    }
    if(help != NULL){
        tmp.help = (char*)calloc(strlen(help)+1, sizeof(char));
        if(tmp.help != NULL){
            strcpy(tmp.help, help);
        }
    }
    else{
        tmp.help = NULL;
    }
    tmp.count = count;
    tmp.parsed = false;
    tmp.valided = false;
    tmp.name = (char*) calloc(strlen(name)+1, sizeof(char));
    if(tmp.name != NULL){
        strcpy(tmp.name, name);
    }
    tmp.start = NULL;
    tmp.trigger = trigger;

    Garbage_OPush(&tmp);
    return tmp;
}

void Option_Parse(int count, char** vector){
    Option* list = _garbage.olist;

    // Set the Options args and positions
    for(size_t i=0; i< _garbage.osize; i++){
        // Test if we find the option by its name
        for(int j=0; j< count; j++){
            // Option found in the list, need to check the number of params
            if(strcmp(list[i].name, vector[j]) == 0){
                list[i].pos = j;
                list[i].start = vector+j;
                list[i].parsed = true;
                break;
            }
        }
    }

    // Test if the options are contigus
    for(size_t i=0; i< _garbage.osize; i++){

        // Ignore not parsed values
        if(_garbage.olist[i].parsed == false){
            continue;
        }

        int iStart = _garbage.olist[i].pos;
        int iEnd = _garbage.olist[i].pos + _garbage.olist[i].count;
        if (iEnd > count){
            // tag the option as not parsed
            _garbage.olist[i].parsed = false;
            continue;
        }

        for(size_t j=0; j< _garbage.osize; j++){
            if(i==j || _garbage.olist[j].parsed == false){
                continue;
            }

            int jStart = _garbage.olist[j].pos;
            int jEnd = _garbage.olist[j].pos + _garbage.olist[j].count;

            if(jEnd > count){
                _garbage.olist[j].parsed = false;
                break;
            }
            if((iStart < jStart && iEnd <= jStart) || (jStart < iStart && jEnd <= iStart)){
                // No crossing, parsed and validated
                _garbage.olist[i].valided = true;
                
                break;
            }
            else{
                _garbage.olist[i].parsed = false;
                _garbage.olist[i].valided = false;
                break;
            }
        }
        _garbage.olist[i].valided = _garbage.olist[i].parsed == true ? true : false;
    }
}

Option* Option_Has(const char* name){
    Option* opt = NULL;
    for(size_t i=0; i < _garbage.osize; i++){
        opt = _garbage.olist+i;
        if(opt->parsed == false || opt->valided == false){
            continue;
        }
        if(strcmp(opt->name, name) == 0){
            return opt;
        }
    }
    return NULL;
}

int Option_Launch(const char* name){
    Option* option = Option_Has(name);
    if(option == NULL){
        return 0;
    }
    if(option->trigger != NULL){
        return option->trigger(option->count, option->start);
    }

    return 0;
}

int Option_Run(Option* option){
    if(option == NULL){
        return 0;
    }
    if(option->trigger != NULL){
        return option->trigger(option->count, option->start);
    }

    return 0;
}
