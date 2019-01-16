#ifndef DATA
#define DATA

#include "structs.h"

/*
 * Function: loadData
 * ----------------------------
 * loads library from file into memory
 *
 * saveFile: filepath to the File that should be loaded
 *
 * returns: pointer to the loaded Library, NULL if an error occured
*/
int loadData(char * saveFile);

/*
 * Function: saveData
 * ----------------------------
 * writes library from memory to file
 *
 * lib: pointer to the library that should be safed
 * saveFile: filepath to the File that should be loaded
 *
 * returns: 0 if succesfull, 1 if an error occured
*/


int saveData(char *saveFile);

/*
 * Function: addBook
 * ----------------------------
 * adds a new Book to the library
 *
 * lib: pointer to the library that should be extended
 * and all parameters the book has
 *
 * returns: 0 if succesfull, 1 if an error occured
*/
int addBook(int amount, int borrowed, char isbn[11], char *title, char *author, char **borrower);

/*
 * Function: deleteBook
 * ----------------------------
 * removes a Book from the library
 * the last Book in the array is moved to the free position
 *
 * index: index of the book that should be deleted
 *
 * returns: 0 if succesfull, 1 if an error occured
*/
int deleteBook(int index);


/*
 * Function: borrowBook
 * ----------------------------
 * adds a new Borrower to a Book if possible
 * checks if there is a book available or if all copies are already borrowed
 *
 * book: pointer to the book that should be borrow
 * borrower: name of the borrower
 *
 * returns: 0 if succesfull, 1 if there are no copies left, 2 if memmory could not be allocated
*/
int borrowBook(book *book, char* borrower);

extern library lib;


#endif
