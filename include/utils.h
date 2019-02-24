#ifndef UTILITIES
#define UTILITIES

#include <stdbool.h>
#include "structs.h"

#define bookText ANSI_COLOR_YELLOW"     _______   "ANSI_COLOR_RESET"Title:    %s\n" \
                 ANSI_COLOR_YELLOW"    /      /,  "ANSI_COLOR_RESET"Author:   %s\n" \
                 ANSI_COLOR_YELLOW"   /      //   "ANSI_COLOR_RESET"ISBN:     %s\n" \
                 ANSI_COLOR_YELLOW"  /______//    "ANSI_COLOR_RESET"Amount:   %d\n" \
                 ANSI_COLOR_YELLOW" (______(/     "ANSI_COLOR_RESET"In stock: %d\n"

char menu(char *text, int options);
/*
 * Function: yesno
 * ----------------------------
 *  parses single character yes or no input (Y or N)
 *  user input is not case sensitive
 *
 *  def: (0|1) default return value that is used if the user just presses enter
 *
 *  returns: 1 for 'y', 0 for 'n', <def> for 'enter'
 */
bool yesno(bool def);
void printLib();
void printBook(book *book);
void clearConsole();
void clearInput();
bool isbnValidation();
//takes user input of length 'length' and stores it into 'buffer'
bool getString(char *buffer, int length);
//converts a string to uppercase
void upperString(char *dest, char *src);

#endif
