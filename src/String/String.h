#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>

/*
Not used yet
------------

typedef struct String{
    char* content;
    size_t size;
}String;

String* new_String(const char* content);
void free_String(String* tofree);

int cmp_String(String* a, String* b);
void affect_String(String* ref, const char* content);
*/

/*
Trim char <rem> to the string <str> from the left.
Rreturns allocated string which need to be free manually
*/
char* ltrim(char rem, const char* str);

/*
Trim char <rem> to the string <str> from the right.
Rreturns allocated string which need to be free manually
*/
char* rtrim(char rem, const char* str);

/*
Trim char <rem> to the string <str> from both sides.
Rreturns allocated string which need to be free manually
*/
char* trim(char rem, const char* str);
#endif