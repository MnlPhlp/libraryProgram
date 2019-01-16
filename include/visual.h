#ifndef VISUAL
#define VISUAL

#include "structs.h"

#define LibText "\nThe library contains %d Books\n"\
                     "-----------------------------------\n"

#define BookText     "------------------------\n"\
                     " Title: %s\n"\
                     " Author: %s\n"\
                     " ISBN: %ld\n"\
                     " Amount: %d\n"\
                     " In stock: %d\n\n"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

//prints the whole library to the console
// void printLib();

#endif
