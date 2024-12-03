#ifndef SYSTEM_OPTION_H
#define SYSTEM_OPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int (*OptionAction)(int count, char** vector);

typedef struct Option{
    int count;
    int pos;
    char* name;
    char** start;
    char* help;
    OptionAction trigger;
    bool parsed;
    bool valided;
}Option;


Option Option_Create(const char* name, int count, const char* help, OptionAction trigger);
void Option_Parse(int count, char** vector);
Option* Option_Has(const char* name);
int Option_Launch(const char* name);
int Option_Run(Option* option);



#endif