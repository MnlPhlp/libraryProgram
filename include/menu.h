#ifndef MENU
#define MENU

#include <stdbool.h>
#include "structs.h"

#define mainMenuText "  _______________________\n"  \
                     " |       Main Menu       |\n" \
                     " |-----------------------|\n" \
                     " | (1) Borrow a book     |\n" \
                     " | (2) Return a book     |\n" \
                     " | (3) Search a book     |\n" \
                     " | (4) Add a book        |\n" \
                     " | (5) Remove a book     |\n" \
                     " | (6) Show all books    |\n" \
                     " | (7) Tests r/woosh     |\n" \
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
                     " | Choose your savefile  |\n" \
                     " |-----------------------|\n" \
                     " | (1) Standard (./Save) |\n" \
                     " | (2) Enter save path   |\n" \
                     " |-----------------------|\n" \
                     " | (Q) QUIT              |\n" \
                     " '-----------------------'\n"

#define searchSelectText "  _______________________\n"  \
                       " |      Search Menu      |\n" \
                       " |-----------------------|\n" \
                       " | Search by...          |\n" \
                       " | (1) ISBN              |\n" \
                       " | (2) Title             |\n" \
                       " | (3) Author            |\n" \
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
void deleteBookMenu(book* b);
library* search();
book *searchSelect(library *results);
void searchMenu();
bool loadMenu();
void searchResults( library *results);
void bookMenu();

book *selectByIsbn();
void deleteByIsbn();

book* selectBook(library *results);

#endif
