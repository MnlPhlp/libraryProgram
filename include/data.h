//use include guard
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
 * returns: false if successful, true if an error occurred
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
 * returns: false if successful, true if an error occur ed
*/
bool addBook(uint8 amount, char isbn[14], char *title, char *author);

/*
 * Function: deleteBook
 * ----------------------------
 * removes a Book from the library
 * the last Book in the array is moved to the free position
 *
 * b: pointer to the book that should be removed
 *
 * returns: false if successful, true if an error occured
*/
bool deleteBook(book *b);

/*
 * Function: freeBook
 * ----------------------------
 * frees all the memory used by a book
 *
 * b: pointer to the book that should be removed
 *
*/
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

/*
 * Function: returnBook
 * ----------------------------
 * removes a borrower from a book and decreases the borrowed value
 *
 * b: pointer to the book that should be returned
 * returner: position of returner in 'borrower' array
 *
 * returns: 0 if successful, 1 if an error occur ed
*/
void returnBook(book *book, int returner);

/*
 * Function: searchBook
 * ----------------------------
 * searches the library for a given keyword
 * also finds fragments like 'arr' for 'Harry'
 * 
 * possible serch modes are:
 * i: ISBN
 * a: author
 * t: title
 * b: borrowr
 * 
 * mode: one of 'i','a','t' and 'b'
 * keyword: word or part of a word to search
 * 
 * returns: library struct containing all the results
*/
library *searchBook(char mode, char* keyword);

/*
 * Function: sortBooksIsbn
 * ----------------------------
 * callback function used with qsort to sort books by ISBN
 *
 * a: pointer to a book
 * b: pointer to another book
 *
 * returns: value returned by stricmp between the ISBNs
*/
int sortBooksIsbn(const void *a, const void *b);

/*
 * Function: sortBooksTitle
 * ----------------------------
 * callback function used with qsort to sort books by title
 *
 * a: pointer to a book
 * b: pointer to another book
 *
 * returns: value returned by stricmp between the titles
*/
int sortBooksTitle(const void *a, const void *b);

/*
 * Function: sortBooksIsbn
 * ----------------------------
 * callback function used with qsort to sort books by author
 *
 * a: pointer to a book
 * b: pointer to another book
 *
 * returns: value returned by stricmp between the authors
*/
int sortBooksAuthor(const void *a, const void *b);

/*
 * Function: openFile
 * ----------------------------
 * fopen wrapper providing error management
 * prints out error messages (errno)
 * asks the user to retry when a file could not be opened
 *
 * saveFile: filepath to the savefile or a path to create a new file
 * mode: mode in wich the file should be opened (gets passed to fopen)
 *
 * returns: File pointer to the opened file
 */ 
FILE *openFile(char *saveFile, char *mode);

/*
 * Function: contentSize
 * ----------------------------
 * calculates the size of an opened file in bytes
 *
 * file: File pointer
 *
 * returns: size of file in bytes
 */
int contentSize(FILE *file);

unsigned long hashLib();

//if not on windows stricmp has to be named strcasecmp
#ifndef _WIN32
#define stricmp strcasecmp
#endif

//declare global library lib (initialized in data.c)
extern library lib;


#endif
