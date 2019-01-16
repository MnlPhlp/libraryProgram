#include <stdio.h>
#include <string.h>
#include "../include/menu.h"
#include "../include/structs.h"
#include "../include/data.h"
#define savefile "bin/Save"

int main()
{
  printf("\nlibrary gets loaded from file '%s' ...\n", savefile);
  //load library from savefile
  if (loadData(savefile))
  {
    printf(ANSI_COLOR_RED "no library loaded or created" ANSI_COLOR_RESET "\nprogram closed\n");
    return 1;
  }
  printf("%d books loaded\n", lib.count);

  //show main menu
  mainMenu();

  //save library to savefile
  printf("library gets saved into file '%s' ...\n", savefile);
  if (saveData(savefile))
  {
    printf(ANSI_COLOR_RED"nothing saved"ANSI_COLOR_RESET);
  }
  else
    printf("%d books saved\n", lib.count);
  return 0;
}
