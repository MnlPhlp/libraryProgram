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
  while (true)
  {
    switch (menu(mainMenuText, 7))
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
    case '6':
      printLib(&lib);
      break;
    case '7':
      runTests();
      break;
    case 'Q':
      return;
      break;
    default:
      printf("Invalid input");
      break;
    }
  }
}

void borrowMenu()
{
  while (true)
  {
    switch (menu(borrowMenuText, 2))
    {
    case '1':
      break;

    case '2':
      borrowByIsbn();
      break;

    case 'Q':
      return;
      break;
    }
  }
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
                         "Q) quit\n\n";
  switch (menu(searchMenuText, 3))
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

  case 'Q':
  default:
    break;
  }
}

int addMenu()
{
  char title[buffSize] = "";
  do
  {
    printf("Title: ");
  } while (getString(title, buffSize-1));

  char author[buffSize] = "";
  do
  {
    printf("Author: ");
  } while (getString(author, buffSize-1));

  int amount;
  printf("Amount: ");
  while (scanf("%d", &amount) == 0)
  {
    clearInput();
    printf("Invalid Character \n\nAmount:");
  }
  clearInput();

  char isbn[11] = "";
  do
  {
    printf("ISBN: ");
  } while (isbnValidation(isbn));
  int i = 0;
  while (i < lib.count && !strstr(lib.books[i]->isbn, isbn))
  {
    i++;
  }
  i < lib.count ? lib.books[i]->amount++ : addBook(amount, 0, isbn, title, author, NULL);
  printf("Book added\n");
  return 0;
}

void deleteMenu()
{
}

void borrowByIsbn()
{
  char isbn[11];
  char borrower[buffSize];
  book *book;
  //get a valid isbn from user to clearly identify book to borrow
  do
  {
    printf("ISBN: ");
  } while (isbnValidation(isbn));

  //because only a valid isbn can be entered there can only be one search result
  book = searchISBN(isbn)->books[0];
  //get name of borrower
  do
  {
    printf("Name of borrower: ");
  } while (getString(borrower, buffSize-1));
  //check if book could be borrowed and inform the user
  if (borrowBook(book, borrower) == 1)
    printf("all copys of this book are borrowed at the moment");
  else
    printf("book %s was succesfully borrowed by %s", book->title, borrower);
}
