#ifndef VISUAL
#define VISUAL

#include "structs.h"

#define LibText "\nThe library contains %d Books\n"\
                     "-----------------------------------\n"

#define BookText "\nThis is Book number %d\n"\
                      "------------------------\n"\
                      " title: %s\n"\
                      " author: %s\n"\
                      " isbn: %ld\n"\
                      " amount: %d\n"\
                      " borrowed: %d\n"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

//prints the whole library to the console
void printLib(library *lib);

#endif
