#include <stdlib.h>
#include <stdio.h>

#include "garbage.h"

Garbage _garbage = {olist:NULL, slist:NULL,osize:0, ssize:0};

void Garbage_Create(){
    Garbage tmp;
    tmp.olist = (Option*)calloc(1, sizeof(Option));
    tmp.slist = (char**)calloc(1, sizeof(char*));
    tmp.osize = 0;
    tmp.ssize = 0;
    _garbage.olist = tmp.olist;
    _garbage.slist = tmp.slist;
    
    _garbage.osize = tmp.osize;
    _garbage.ssize = tmp.ssize;
}

void Garbage_OPush(Option* option){
    Garbage* garbage = &_garbage;
    if(garbage == NULL || option == NULL){
        return;
    }

    Option* tmp = realloc(garbage->olist, (garbage->osize+1)*sizeof(Option));
    if(tmp == NULL){
        return;
    }
    garbage->olist = tmp;

    // Copy the wanted pointers
    garbage->olist[garbage->osize].help = option->help;
    garbage->olist[garbage->osize].name = option->name;
    garbage->olist[garbage->osize].pos = option->pos;
    // Copy the regular datas too, used for parse
    garbage->olist[garbage->osize].count = option->count;
    garbage->olist[garbage->osize].start = option->start;
    garbage->olist[garbage->osize].trigger = option->trigger;
    garbage->olist[garbage->osize].parsed = option->parsed;
    garbage->olist[garbage->osize].valided = option->valided;

    garbage->osize++;
}

void Garbage_Dump(){
    if(_garbage.olist != NULL){

        for(size_t i=0; i< _garbage.osize; i++){
            if(_garbage.olist[i].help != NULL){
                free(_garbage.olist[i].help);
                _garbage.olist[i].help = NULL;
            }
            if(_garbage.olist[i].name != NULL){
                free(_garbage.olist[i].name);
                _garbage.olist[i].name = NULL;
            }

            _garbage.olist[i].count=0;
            _garbage.olist[i].pos=0;
            _garbage.olist[i].start = NULL;
            _garbage.olist[i].trigger = NULL;
            _garbage.olist[i].parsed = false;
            _garbage.olist[i].valided = false;
        }

        free(_garbage.olist);
        _garbage.olist = NULL;
        _garbage.osize = 0;
    }

    if(_garbage.slist != NULL){
        for(size_t i=0; i< _garbage.ssize; i++){
            free(_garbage.slist[i]);
            _garbage.slist[i] = NULL;
        }
        free(_garbage.slist);
        _garbage.slist = NULL;
        _garbage.ssize = 0;
    }
}
