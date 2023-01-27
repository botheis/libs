#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "Parser/ini.h"

int main(int argc, char** argv){

    /*
    =============
    CONFIG PARSER
    =============
    */

    IniParser* config = Ini_CreateParser();
    char* inifile = "assets/etc/mylib.ini";

    Ini_ParseFile(inifile, config);

    for(size_t i=0; i < config->size; i++){
        IniSection *section = config->list+i;
        printf("%s\n", section->name);
        for(size_t j=0; j< section->size; j++){
            printf("\t%s = %s\n", section->list[j].name, section->list[j].value);
        }
    }
    // Uncomment this line to test the creation of ini file from IniParser object
    // Ini_WriteFile("assets/etc/mylib_save.ini", config);
    Ini_FreeParser(config);

    return 0;
}