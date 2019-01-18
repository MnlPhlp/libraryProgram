#ifndef MENU
#define MENU

#include <stdbool.h>
#include "structs.h"

#define mainMenuText "  _______________________\n" \
                     " |       Main Menu       |\n"\
                     " |-----------------------|\n"\
                     " | (1) Borrow a book     |\n"\
                     " | (2) Return a book     |\n"\
                     " | (3) Search a book     |\n"\
                     " | (4) Add a book        |\n"\
                     " | (5) Remove a book     |\n"\
                     " | (6) Show all books    |\n"\
                     " | (7) Tests r/woosh     |\n"\
                     " |-----------------------|\n"\
                     " | (Q) QUIT              |\n"\
                     " '-----------------------'\n"

#define borrowMenuText "  _______________________\n" \
                       " |      Borrow Menu      |\n"  \
                       " |-----------------------|\n"  \
                       " | (1) Search a book     |\n"  \
                       " | (2) Borrow by ISBN    |\n"  \
                       " |-----------------------|\n"  \
                       " | (Q) QUIT              |\n"  \
                       " '-----------------------'\n"

#define deleteMenuText "  _______________________\n" \
                       " |      Remove Menu      |\n"  \
                       " |-----------------------|\n"  \
                       " | (1) Search a book     |\n"  \
                       " | (2) Remove by ISBN    |\n"  \
                       " |-----------------------|\n"  \
                       " | (Q) QUIT              |\n"  \
                       " '-----------------------'\n"

#define loadMenuText "  _______________________\n"  \
                     " |       Load Menu       |\n" \
                     " |-----------------------|\n" \
                     " | (1) Standard (./Save) |\n" \
                     " | (2) Enter save path   |\n" \
                     " |-----------------------|\n" \
                     " | (Q) QUIT              |\n" \
                     " '-----------------------'\n"                       

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW "\x1b[33m"

#define buffSize 32

void mainMenu();
void returnMenu();
void borrowMenu();
int addMenu();
void deleteMenu();
void searchMenu();
bool loadMenu();

void borrowByIsbn();
void deleteByIsbn();

#endif
