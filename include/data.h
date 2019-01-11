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
 * pointer to the extended library only differs from given pointer 
 * if there is not enough free memory available at the old location
 * 
 * lib: pointer to the library that should be extended
 * 
 * returns: pointer to the extended Library
*/
library *addBook(library *lib);

#endif