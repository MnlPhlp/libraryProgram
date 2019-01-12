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
 * returns: pointer to the loaded Library
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

#endif