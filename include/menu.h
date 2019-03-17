// use include guard
#ifndef MENU
#define MENU

#include <stdbool.h>
#include "structs.h"

//define the texts used in the menus
#define mainMenuText "  _______________________\n"  \
                     " |       Main Menu       |\n" \
                     " |-----------------------|\n" \
                     " | (1) Borrow a book     |\n" \
                     " | (2) Return a book     |\n" \
                     " | (3) Search a book     |\n" \
                     " | (4) Add a book        |\n" \
                     " | (5) Remove a book     |\n" \
                     " | (6) Show all books    |\n" \
                     " |-----------------------|\n" \
                     " | (Q) QUIT              |\n" \
                     " '-----------------------'\n"

#define borrowMenuText "  _______________________\n"  \
                       " |      Borrow Menu      |\n" \
                       " |-----------------------|\n" \
                       " | (1) Search a book     |\n" \
                       " | (2) Borrow by ISBN    |\n" \
                       " |-----------------------|\n" \
                       " | (Q) QUIT              |\n" \
                       " '-----------------------'\n"

#define returnMenuText "  _______________________\n"  \
                       " |      Return Menu      |\n" \
                       " |-----------------------|\n" \
                       " | (1) Search a book     |\n" \
                       " | (2) Return by ISBN    |\n" \
                       " |-----------------------|\n" \
                       " | (Q) QUIT              |\n" \
                       " '-----------------------'\n"                       

#define deleteMenuText "  _______________________\n"  \
                       " |      Remove Menu      |\n" \
                       " |-----------------------|\n" \
                       " | (1) Search a book     |\n" \
                       " | (2) Remove by ISBN    |\n" \
                       " |-----------------------|\n" \
                       " | (Q) QUIT              |\n" \
                       " '-----------------------'\n"

#define loadMenuText "  _______________________\n"  \
                     " |       Load Menu       |\n" \
                     " | Choose your save-file |\n" \
                     " |-----------------------|\n" \
                     " | (1) Standard (./Save) |\n" \
                     " | (2) Enter save path   |\n" \
                     " |-----------------------|\n" \
                     " | (Q) QUIT              |\n" \
                     " '-----------------------'\n"

#define searchMenuText "  _______________________\n"  \
                       " |      Search Menu      |\n" \
                       " |-----------------------|\n" \
                       " | Search by...          |\n" \
                       " | (1) ISBN              |\n" \
                       " | (2) Title             |\n" \
                       " | (3) Author            |\n" \
		               " | (4) Borrower          |\n" \
                       " |-----------------------|\n" \
                       " | (Q) QUIT              |\n" \
                       " '-----------------------'\n"

//define ANSI escape sequences used for colors in output
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW "\x1b[33m"

//define buffer size for input
#define buffSize 255

/*
 * Function: ...Menu
 * ----------------------------
 * top level menu functions 
 * allow the user to select a specific action
 */ 
void mainMenu();
void returnMenu();
void borrowMenu();
void addMenu();
void search();
bool loadMenu();
void deleteMenu();
void bookMenu();

/*
 * Function: deleteBookMenu
 * ----------------------------
 * lets the user choose how many copies of a book he wants to remove
 * if all copies are removed the book is completely deleted
 * 
 * b: pointer to the book of wich copies are removed
 */ 
void deleteBookMenu(book* b);

/*
 * Function: search
 * ----------------------------
 * lets the user search for a book
 * by Title, Author, Borrower or ISBN
 * 
 * returns: library struct containing all the results
 */ 
library* searchMenu();

/*
 * Function: selectBook
 * ----------------------------
 * lets the user select a book from a library
 * 
 * results: library containing the books to select from
 * 
 * returns: pointer to the selected book
 */
book* selectBook(library *results);

/*
 * Function: searchSelect
 * ----------------------------
 * takes search results as input and handels if NULL is given
 * calls selectBook and frees the results after a book is selected
 * 
 * results: library containing the books to select from
 * 
 * returns: pointer to the selected book
 */
book *searchSelect(library *results);

/*
 * Function: searchResults
 * ----------------------------
 * prints a library in an order selected by the user
 * can be ordered by title, author of ISBN
 * 
 * results: library containing the books to print
 * 
 */
void searchResults( library *results);

/*
 * Function: searchResults
 * ----------------------------
 * selects a book by ISBN from the global library
 * can only be used with the complete ISBN
 * calls the search but with valid ISBN so there can be only one or no result
 * 
 * 
 * returns: the selected book or NULL if there is no matching book
 */
book *selectByIsbn();

#endif
