#ifndef MENU
#define MENU

#include <stdbool.h>
#include "structs.h"

#define mainMenuText "\n ________________________\n"\
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
                      "|(Q) QUIT                |\n"\
                      "'------------------------'\n"

#define borrowMenuText "\n ________________________\n"\
                        "|What do you want to do?:|\n"\
                        "|------------------------|\n"\
                        "|(1) Search a book       |\n"\
                        "|(2) Borrow by ISBN      |\n"\
                        "|------------------------|\n"\
                        "|(Q) QUIT                |\n"\
                        "'------------------------'\n"

#define BookText     "------------------------\n"\
                     " Title: %s\n"\
                     " Author: %s\n"\
                     " ISBN: %ld\n"\
                     " Amount: %d\n"\
                     " In stock: %d\n"\
                     " Borrower:\n"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

#define buffSize 32


void mainMenu();
void returnMenu();
void borrowMenu();
int addMenu();
void deleteMenu();
void searchMenu();

void borrowByIsbn();

#endif
