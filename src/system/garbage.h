#ifndef SYSTEM_GARBAGE_H
#define SYSTEM_GARBAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "option.h"

/**
 * \author Noël-Antoine Kneib (botheis)
 * \date 03/11/2024
 * 
 * \brief garbage collector structure
 */
typedef struct Garbage{
    Option* olist;
    char** slist;

    size_t osize;
    size_t ssize;
}Garbage;

extern Garbage _garbage;

/**
 * \author Noël-Antoine Kneib (botheis)
 * \date 03/11/2024
 * 
 * \brief create the garbage collector
 */
void Garbage_Create();

/*
 * \author Noël-Antoine Kneib (botheis)
 * \date 03/11/2024
 * 
 * \brief push an option into the garbage used when an option has been created
 * \param option is the option we want to be destroy automatically.
 */
void Garbage_OPush(Option* option);

/**
 * \author Noël-Antoine Kneib (botheis)
 * \date 03/11/2024
 * 
 * \params Option
 */
void Garbage_SPush(char* str);

/*
 * \author Noël-Antoine Kneib (botheis)
 * \date 03/11/2024
 * 
 * \brief dump all the datas from the garbage. Used only at the end of the program
 */
void Garbage_Dump();
#endif