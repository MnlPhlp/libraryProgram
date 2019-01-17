#ifndef UTILITIES
#define UTILITIES

#include <stdbool.h>
#include "structs.h"

//prints the whole library to the console
int menu(char *text, int options);
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
int yesno(bool def);
void printLib();
void printBook(book *book,int count);
void clearConsole();
void clearInput();
bool isbnValidation();
//takes user input of length 'length' and stores it into 'buffer'
bool getString(char *buffer, int length);

#endif
