#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data.h"
#include "../include/menu.h"
#include "../include/utils.h"

void runTests(); //Was das? :D

void mainMenu()
{
  bool status = true;
  while (status)
  {
    switch (menu(mainMenuText, 8))
    {
    case '1':
      borrowMenu();
      break;
    case '2':
      returnMenu();
      break;
    case '3':
      searchMenu();
      break;
    case '4':
      addMenu();
      break;
    case '5':
      deleteMenu();
      break;
<<<<<<< HEAD
    case '6':
      printLib();
=======
    case 6:
      printLib(&lib);
>>>>>>> master
      break;
    case '7':
      saveData("bin/Save");
      lib.count = 0;
      lib.books = NULL;
      runTests();
      loadData("bin/Save");
      break;
    case '8':
      status = false;
      break;
    default:
      printf("Invalid input");
      break;
    }
  }
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
  case '1':
    printf("enter ISBN: ");
    scanf("%ld", &isbn);
    //searchBookIsbn(isbn);
    break;

  case '2':
    break;

  case '3':
    break;

  case '4':
  default:
    break;
  }
}

int addMenu()
{
  char title[buffSize] = "";
  do{
    printf("Title: ");
  }while(getString(title, buffSize));

  char author[buffSize] = "";
  do{
    printf("Author: ");
  }while(getString(author, buffSize));

  int amount;
  printf("Amount: ");
  while (scanf("%d", &amount) == 0)
  {
    clearInput();
    printf("Invalid Character \n\nAmount:");
  }
  clearInput();

  char isbn[11] = "";
  printf("ISBN: ");
  while (isbnValidation(isbn))
  {
    printf("ISBN: ");
  }
  int i = 0;
  while(i < lib.count && !strstr(lib.books[i]->isbn,isbn)){
    i++;
  }
  i < lib.count ? lib.books[i]->amount++ : addBook(amount,0,isbn,title,author,NULL);
  printf("Book added\n");
  return 0;
}



void deleteMenu()
{
}
