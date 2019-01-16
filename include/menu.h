#ifndef MENU
#define MENU

#include "structs.h"

#define mainMenuText "\n    main menu\n"\
                     "------------------\n"\
                     "1) borrow a book\n"\
                     "2) return a book\n"\
                     "3) search a book\n"\
                     "4) add a book\n"\
                     "5) delete a book\n"\
                     "6) show all books\n"\
                     "7) tests\n"\
                     "8) quit\n\n"

#define buffSize 32                     

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
int yesno(int def);

void mainMenu();

int addMenu();

void clearConsole();

void clearInput();

#endif
