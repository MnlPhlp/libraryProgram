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

#define BookText     "------------------------\n"\
                     " Title: %s\n"\
                     " Author: %s\n"\
                     " ISBN: %ld\n"\
                     " Amount: %d\n"\
                     " In stock: %d\n\n"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

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

int menu(char *text, int options);
void mainMenu();
void returnMenu();
void borrowMenu();
void deleteMenu();
void searchMenu();

//prints the whole library to the console
void printLib();
void printBook(book *book,int count);
void clearConsole();
void clearInput();


#endif
