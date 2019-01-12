#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "visual.h"
#include "structs.h"
#include "data.h"
#define savefile "bin/Save"

int main()
{
  printf("\nlibrary gets loaded from file '%s' ...\n", savefile);
  //load library from savefile
  library *lib;
  while ((lib = loadData(savefile)) == NULL)
  {
    printf(ANSI_COLOR_RED "File could not be loaded succesfully" ANSI_COLOR_RESET
                          "\ntry again [Y/n]: ");
    //checks user input with true as default
    if (!yesno(1))
      //end program with exit code 1
      return 1;
  }
  printf("%d books loaded\n", lib->count);
  //show main menu
  mainMenu(lib);
  //save library to savefile
  printf("library gets saved into file '%s' ...\n", savefile);
  saveData(lib, savefile);
  printf("%d books saved\n", lib->count);
  return 0;
}