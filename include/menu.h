#ifndef MENU
#define MENU

#include "structs.h"

#define mainMenuText  "\n ________________________\n"\
                    "|What do you want to do?:|\n"\
                    "|------------------------|\n"\
                    "|(1) Borrow a book       |\n"\
                    "|(2) Return a book       |\n"\
                    "|(3) Search a book       |\n"\
                    "|(4) Add a book          |\n"\
                    "|(5) Delete a book       |\n"\
                    "|(6) Show all books      |\n"\
                    "|(7) Tests r/woosh       |\n"\
                    "|------------------------|\n"\
                    "|(5) QUIT                |\n"\
                    "'------------------------'\n"

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
int addMenu();

void mainMenu();
void printBook(book *book,int count);
void clearConsole();
void clearInput();

#endif
