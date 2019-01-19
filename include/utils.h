#ifndef UTILITIES
#define UTILITIES

#include <stdbool.h>
#include "structs.h"

#define bookText "\n Book number (%d):\n"        \
                 "------------------------\n"    \
                 "     _______   Title:    %s\n" \
                 "    /      /,  Author:   %s\n" \
                 "   /      //   ISBN:     %s\n" \
                 "  /______//    Amount:   %d\n" \
                 " (______(/     In stock: %d\n"

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
void printBook(book *book, int count);
void clearConsole();
void clearInput();
bool isbnValidation();
//takes user input of length 'length' and stores it into 'buffer'
bool getString(char *buffer, int length);

#endif
