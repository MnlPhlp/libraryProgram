#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "visual.h"
#include "structs.h"
#include "data.h"
#define savefile "bin/Save/test/fail"

int main()
{
  printf("\nlibrary gets loaded from file '%s' ...\n", savefile);
  //load library from savefile
  library *lib = loadData(savefile);
  if (lib == NULL)
  {
    printf(ANSI_COLOR_RED "no library loaded or created" ANSI_COLOR_RESET "\nprogram closed\n");
    return 1;
  }
  printf("%d books loaded\n", lib->count);

  //show main menu
  mainMenu(lib);

  //save library to savefile
  printf("library gets saved into file '%s' ...\n", savefile);
  if (saveData(lib, savefile))
  {
    printf(ANSI_COLOR_RED"nothing saved"ANSI_COLOR_RESET);
  }
  else
    printf("%d books saved\n", lib->count);
  return 0;
}