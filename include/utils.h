#ifndef UTILITIES
#define UTILITIES

#include <stdbool.h>
#include "structs.h"

//prints the whole library to the console
int menu(char *text, int options);
int yesno(int def);
void printLib();
void printBook(book *book,int count);
void clearConsole();
void clearInput();
bool isbnValidation();
//takes user input of length 'length' and stores it into 'buffer'
bool getString(char *buffer, int length);

#endif
