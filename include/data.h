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
library *loadData(char * saveFile);

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
int saveData(library *lib,char *saveFile);

/*
 * Function: addBook
 * ----------------------------
 * adds a new Book to the library
 * 
 * lib: pointer to the library that should be extended
 * 
 * returns: 0 if succesfull, 1 if an error occured
*/
int addBook(library *lib, int amount, int borrowed, long isbn, char *title, char *author, char **borrower);

/*
 * Function: addBook
 * ----------------------------
 * removes a Book from the library
 * the last Book in the array is moved to the free position
 * 
 * lib: pointer to the library 
 * index: index of the book that should be deleted
 * 
 * returns: 0 if succesfull, 1 if an error occured
*/
int deleteBook(library *lib, int index);


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


#endif