#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "structs.h"
#include "data.h"
#include "utils.h"

int main()
{
  char savefile[50];
  FILE *save = NULL;
  clearConsole();
  while (save == NULL)
  {
    if (loadMenu(savefile, 50))
    {
      printf(ANSI_COLOR_RED "no library loaded or created" ANSI_COLOR_RESET "\nprogram closed\n");
      return 0;
    }
    save = openFile(savefile,"rb");
  }

  if(contentSize(save) == 0){
    printf("new empty library will be used\n");
  }

  else{
    printf("\nlibrary gets loaded from file '%s' ...\n", savefile);
    //load library from save-file
    if (loadData(save))
    {
      printf(ANSI_COLOR_RED "no library loaded or created" ANSI_COLOR_RESET "\nprogram closed\n");
      return 1;
    }
    printf("%d book%s loaded\n", lib.count, lib.count == 1 ? "" : "s");
  }
  fclose(save);

  //show main menu
  mainMenu();

  save = openFile(savefile, "wb");
  //save library to save-file
  clearConsole();
  printf("library gets saved into file '%s' ...\n", savefile);
  if (saveData(save))
  {
    printf(ANSI_COLOR_RED "nothing saved\n" ANSI_COLOR_RESET);
  }
  else{
    printf("%d book%s saved\n", lib.count, lib.count == 1 ? "" : "s");
  }
  fclose(save);
  return 0;

}
