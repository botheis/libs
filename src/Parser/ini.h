#ifndef PARSER_INI_H
#define PARSER_INI_H

#include <string.h>
#include "../bool.h"

/*
Parse an ini file and store the result in structured form

The structures are:
IniParser
    |-> n x IniSection
            |-> m x IniOption
*/
typedef struct IniOption{
    // @TODO: dynamic string
    char name[255];
    char value[255];
}IniOption;

typedef struct IniSection{
    // @TODO: dynamic string
    char name[255];
    IniOption* list;
    size_t size;
}IniSection;

typedef struct IniParser{
    IniSection* list;
    size_t size;
}IniParser;

/*
Create a new IniParser
Only the pointer on IniParser is allocated, the members are set to :
    - NULL for pointers members
    - 0 for size_t members
    - "" for string members
*/
IniParser* Ini_CreateParser();

/*
Free the specified parser and all its content (IniSections and IniOptions)
*/
void Ini_FreeParser(IniParser* tofree);

/*
Create a new IniSection
Only the pointer on IniSection is allocated, the members are set to :
    - NULL for pointers members
    - 0 for size_t members
    - "" for string members
*/
IniSection* Ini_CreateSection();

/*
Add a new section to the parser nammed <name>
*/
void Ini_PushSection(IniParser* parser, const char* name);

/*
Remove the last section stored in the parser.
The memory is cleaned
*/
void Ini_PopSection(IniParser* parser);

/*
Debug function: Show the sections names stored in the parser
*/
void Ini_ShowSectionNames(IniParser* parser);
/*
Debug function: Show the options and their values from the specified section*/
void Ini_ShowOptions(IniSection* section);

/*
Get the section named <name> if this section doesn't exist, the result is NULL
*/
IniSection* Ini_GetSection(IniParser* parser, const char* name);

/*
Get the <id>th section of the parser
If <id> is greater than the array size (or lower than 0), then the result is NULL
*/
IniSection* Ini_GetSectionFromId(IniParser* parser, int id);

/*
Lightly different from the 2 previous functions, 
this one just returns a boolean if the section named <name> exists
*/
bool Ini_HasSection(IniParser* parser, const char* name);

/*
Check if the specified option <optionName> exists in the section <sectionName>.
*/
bool Ini_HasOption(IniParser* parser, const char* sectionName, const char* optionName);

/*
If the option <optionName> exists in the section <sectionName>, then returns its value, else returns NULL
*/
char* Ini_GetOption(IniParser* parser, const char* sectionName, const char* optionName);

/*
Push an option {<name>:<value>} to the specified section <section>
*/
void Ini_PushOption(IniSection* section, const char* name, const char* value);

/*
Read the specified file and parse it as ini file.
The result may be inpredicted if the specified file is not a real ini file.
Retruns TRUE in success (of reading)
*/
bool Ini_ParseFile(const char* filename, IniParser* parser);

/*
Write the parser structure <parser> in a specified file <filename>
Returns TRUE in success 
*/
bool Ini_WriteFile(const char* filename, IniParser* parser);
#endif