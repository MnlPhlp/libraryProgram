#include <stdio.h>
#include <ctype.h>
#include "data.h"
#include "visual.h"

int menu(char *text, int options)
{
  int input = 0;
  char buff;
  //print specific menu text
  printf(text);

  while (input == 0)
  {
    printf("choose option: ");
    buff = getchar();
    if (buff >= '1' && buff <= '0' + options)
      //save choosen option if in valid range
      input = buff - '0';
    else if (buff == 'm')
      //print specific menu text again
      //useful after many invalid inputs to see the valid options again
      printf(text);
    else
      printf("invalid input, try again (enter 'm' to show menu again)\n");
    while (buff != '\n')
      buff = getchar();
  }
  return input;
}

void borrowMenu()
{
}

void returnMenu()
{
}

void searchMenu()
{
  long isbn;
  char *searchMenuText = "1) serch by ISBN\n"
                         "2) search by title\n"
                         "3) search by author\n"
                         "4) quit\n\n";
  switch (menu(searchMenuText, 4))
  {
  case 1:
    printf("enter ISBN: ");
    scanf("%ld", &isbn);
    //searchBookIsbn(isbn);
    break;

  case 2:
    break;

  case 3:
    break;

  case 4:
  default:
    break;
  }
}

void addMenu()
{
}

void deleteMenu()
{
}

void mainMenu(struct library *lib)
{
  char *mainMenuText = "\n    main menu\n"
                       "------------------\n"
                       "1) borrow a book\n"
                       "2) return a book\n"
                       "3) search a book\n"
                       "4) add a book\n"
                       "5) delete a book\n"
                       "6) show all books\n"
                       "7) quit\n\n";
  while (1)
  {
    switch (menu(mainMenuText, 7))
    {
    case 1:
      borrowMenu();
      break;
    case 2:
      returnMenu();
      break;
    case 3:
      searchMenu();
      break;
    case 4:
      addMenu();
      break;
    case 5:
      deleteMenu();
      break;
    case 6:
      printLib(lib);
      break;
    case 7:
    default:
      return;
    }
  }
}

/*
 * Function: yesno
 * ----------------------------
 *  parses single character yes or no input (Y or N) 
 *  user input is not case sensitive
 *  
 *  def: default answer that is used if the user just presses enter 
 *
 *  returns: 1 for 'y', 0 for 'n', value of def for 'enter'
 */
int yesno(int def)
{
  char buff = getchar();
  char *options = "[Y/n]";
  int input = -1;
  while (input == -1)
  {
    switch (toupper(buff))
    {
    case 'Y':
      input = 1;
      break;
    case 'N':
      input = 0;
      break;
    case '\n':
      input = def;
      break;
    default:
      if (def == 0)
        options = "[y/N]";
      printf("invalid input, try again\n%s: ", options);
      break;
    }
  }
  return input;
}