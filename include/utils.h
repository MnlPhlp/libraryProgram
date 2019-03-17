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
 * the promt shows the default option in upper case
 *
 *  def: (true|false) default return value that is used if the user just presses enter
 *
 *  returns: true for 'y', false for 'n', <def> for 'enter'
 */
bool yesno(bool def);

/*
 * Function: printlib
 * ----------------------------
 *  prints the given library to the console
 * 
 *  plib: pointer to the library that should be printed
 */
void printLib(library *pLib);

/*
 * Function: printBook
 * ----------------------------
 *  prints a single book
 */
void printBook(book *book);

/*
 * Function: clearConsole
 * ----------------------------
 *  clears any ramining output from the console
 */
void clearConsole();

/*
 * Function: clearInput
 * ----------------------------
 *  clears the input buffer
 */
void clearInput();

bool isbnValidation();

/*
 * Function: getString
 * ----------------------------
 * takes user input of length 'length' and stores it into 'buffer'
 * 
 * buffer: pointer to the area where the input should be stored
 * length: max length that the user input can have
 * 
 * returns: false if succesfull, true if input was to long
 */
bool getString(char *buffer, int length);


/*
 * Function: upperString
 * ----------------------------
 * takes a string an stores it as upper case
 * source and destination can savely be the same 
 * 
 * dest: pointer to the location where the upper case string is stored
 * src: pointer to the given string
 */
void upperString(char *dest, char *src);

#endif
