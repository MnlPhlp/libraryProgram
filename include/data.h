#ifndef DATA
#define DATA

#include <stdbool.h>
#include "structs.h"

/*
 * Function: loadData
 * ----------------------------
 * loads library from file into memory
 *
 * saveFile: filepath to the File that should be loaded
 *
 * returns: true if an error occurred
*/
bool loadData(FILE * save);

/*
 * Function: saveData
 * ----------------------------
 * writes library from memory to file
 *
 * lib: pointer to the library that should be saved
 * saveFile: filepath to the File that should be loaded
 *
 * returns: false if successful, true if an error occurred
*/


bool saveData(FILE *save);

/*
 * Function: addBook
 * ----------------------------
 * adds a new Book to the library
 *
 * lib: pointer to the library that should be extended
 * and all parameters the book has
 *
 * returns: 0 if successful, 1 if an error occur ed
*/
bool addBook(int amount, int borrowed, char isbn[14], char *title, char *author, char **borrower);

/*
 * Function: deleteBook
 * ----------------------------
 * removes a Book from the library
 * the last Book in the array is moved to the free position
 *
 * b: pointer to the book that should be removed
 *
 * returns: 0 if successful, 1 if an error occur ed
*/
bool deleteBook(book *b);

void freeBook(book *b);

/*
 * Function: borrowBook
 * ----------------------------
 * adds a new Borrower to a Book if possible
 * checks if there is a book available or if all copies are already borrowed
 *
 * book: pointer to the book that should be borrow
 * borrower: name of the borrower
 *
 * returns: 0 if successful, 1 if there are no copies left, 2 if memory could not be allocated
*/
int borrowBook(book *book, char* borrower);
void returnBook(book *book, int returner);

library *searchBook(char mode, char*);

int sortBooksIsbn(const void *a, const void *b);
int sortBooksTitle(const void *a, const void *b);
int sortBooksAuthor(const void *a, const void *b);

FILE *openFile(char *saveFile, char *mode);
int contentSize(FILE *file);

unsigned long hashLib();

//if not on windows stricmp has to be named strcasecmp
#ifndef _WIN32
#define stricmp strcasecmp
#endif

extern library lib;


#endif
