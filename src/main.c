#include <stdio.h>
#include <string.h>
#include "../include/menu.h"
#include "../include/structs.h"
#include "../include/data.h"
#include "../include/utils.h"

int main()
{
  char savefile[50];
  loadMenu(savefile, 50);
  printf("\nlibrary gets loaded from file '%s' ...\n", savefile);
  //load library from savefile
  if (loadData(savefile))
  {
    printf(ANSI_COLOR_RED "no library loaded or created" ANSI_COLOR_RESET "\nprogram closed\n");
    return 1;
  }
  printf("%d book%s loaded\n", lib.count,lib.count == 1 ? "":"s");

  //show main menu
  mainMenu();

  //save library to savefile
  printf("library gets saved into file '%s' ...\n", savefile);
  if (saveData(savefile))
  {
    printf(ANSI_COLOR_RED"nothing saved"ANSI_COLOR_RESET);
  }
  else
    printf("%d book%s saved\n", lib.count,lib.count == 1 ? "":"s");
  return 0;
}
