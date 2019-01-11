#include <stdio.h>
#include <string.h>
#include "menu.h"
#define savefile "Save"

int main(int argc, char const *argv[])
{ 
  printf("\nlibrary gets loaded from file '%s' ...\n",savefile);
  //load library from savefile
  struct library *lib;
  while((lib = loadData(savefile)) == NULL)
  {
    printf(ANSI_COLOR_RED"File could not be loaded succesfully"ANSI_COLOR_RESET
          "\ntry again [Y/n]: ");
    //checks user input with true as default
    if (!yesno(1))
      //end program with exit code 1
      return 1;
  }/*
  struct library *lib = malloc(50);
  lib->count=1;
  lib->books[0] = malloc(500);
  lib->books[0]->isbn=3564354324;
  lib->books[0]->amount=2;
  lib->books[0]->borrowed=2;
  lib->books[0]->title="titel1";
  lib->books[0]->author="autor1";
  lib->books[0]->borrower[0]="manuel";
  lib->books[0]->borrower[1]="Philipp";*/
  printf("%d books loaded\n", lib->count);
  //show main menu
  mainMenu(lib);
  printf("library gets saved into file '%s' ...\n",savefile);
  //save library to savefile
  saveData(lib, savefile);
  printf("%d books saved\n", lib->count);
  return 0;
}