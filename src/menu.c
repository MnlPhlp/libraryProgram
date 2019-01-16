#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "data.h"
#include "visual.h"
#include "menu.h"

void runTests();

int menu(char *text, int options)
{
  int input = 0;
  char buff;
  //print specific menu text
  printf("%s",text);

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
      printf("%s",text);
    else
      printf("invalid input, try again (enter 'm' to show menu again)\n");
  }
  clearConsole();
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

int addMenu()
{
  char title[32] = "";
  printf("Title: ");
  char c;
  int i = 0;
  while ((c = getchar()) != '\n' && c != EOF) {
    title[i] = c;
    i++;
  }

  char author[32] = "";
  printf("Author: ");
  i = 0;
  while ((c = getchar()) != '\n' && c != EOF) {
    author[i]=c;
    i++;
  }

  int amount;
  printf("Amount: ");
  while(scanf("%d",&amount) == 0) {
    clearInput();
    printf("Invalid Character \n\nAmount:");
  }
  clearInput();

  long isbn;
  printf("ISBN: ");
  while(scanf("%ld",&isbn) == 0) {
    clearInput();
    printf("Invalid Character \n\nISBN:");
  }

  addBook(amount,0,isbn,title,author,NULL);

  clearConsole();
  printf("Book added\n");
  return 0;
}

void deleteMenu()
{
}

void mainMenu()
{
  while (1)
  {
    switch (menu(mainMenuText, 8))
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
      printf("Amount of Books is %d: \n",lib.count);
      for(int i = 0;i<lib.count;i++){
        printBook(lib.books[i],i+1);
      }
      printf("Hit ENTER to continue...");
      clearConsole();
      break;
    case 7:
      saveData("bin/Save");
      lib.count=0;
      lib.books = NULL;
      runTests();
      loadData("bin/Save");
      break;
    case 8:
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
  char buff;
  char *options;
  if (def == 1)
    options = "[Y/n]";
  else
    options = "[y/N]";

  int input = -1;
  while (input == -1)
  {
    printf("%s: ", options);
    buff = getchar();
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
      printf("invalid input, try again\n");
      break;
    clearInput();
    }
  }
  return input;
}

void clearConsole() {
  clearInput();
  for(int i = 0;i<10;i++) {
    printf("\n\n\n\n\n");
  }
}

void clearInput() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) { }
}

void printBook(book *book,int count) {
  printf("\n Book number (%d):\n"
         "------------------------\n"
         " Title: %s\n"
         " Author: %s\n"
         " ISBN: %ld\n"
         " Amount: %d\n"
         " In stock: %d\n\n",
         count,book->title,book->author,book->isbn,book->amount,book->amount-book->borrowed);
}
