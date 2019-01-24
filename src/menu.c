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
      searchResultMenu(&lib);
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
  clearConsole();
  char keyword[buffSize];
  library *results;
  while (true)
  {
    switch (menu(searchMenuText, 3))
    {
    case '1':
      do
      {
        printf("ISBN: ");
      } while (getString(keyword, 10));
      results = searchISBN(keyword);
      break;

    case '2':
      break;

    case '3':
      break;

    case 'Q':
      return;
      break;
    default:
      printf("Invalid input\n");
      break;
    }
    //if there are results show them
    if (results->count > 0)
      searchResultMenu(results);
    else
    {
      clearConsole();
      printf("no Books found\n");
    }
    for (int i = 0; i < results->count; i++)
    {
      freeBook(results->books[i]);
    }
    free(results->books);
  }
}

int addMenu()
{
  char title[buffSize] = "";
  do
  {
    printf("Title: ");
  } while (getString(title, buffSize - 1));

  char author[buffSize] = "";
  do
  {
    printf("Author: ");
  } while (getString(author, buffSize - 1));

  int amount;
  printf("Amount: ");
  while (scanf("%d", &amount) != 1 || amount <= 0)
  {
    clearInput();
    printf("Invalid input\nAmount:");
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
  //if isbn is already stored increase count of the stored book by the entered amount
  i < lib.count ? lib.books[i]->amount += amount : addBook(amount, 0, isbn, title, author, NULL);
  clearConsole();
  printf("Book added\n");
  return 0;
}

void deleteMenu()
{
  while (true)
  {
    switch (menu(deleteMenuText, 2))
    {
    case '1':
      break;

    case '2':
      deleteByIsbn();
      break;

    case 'Q':
      return;
      break;
    }
  }
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
  } while (getString(borrower, buffSize - 1));
  clearConsole();
  //check if book could be borrowed and inform the user
  if (borrowBook(book, borrower) == 1)
    printf("book '%s' is not in stock at the moment\n", book->title);
  else
    printf("book '%s' was succesfully borrowed by '%s'\n", book->title, borrower);
}

void deleteByIsbn()
{
  char isbn[11];
  int amount;
  book *book;
  library *results;
  //get a valid isbn from user to clearly identify book to delete
  do
  {
    printf("ISBN: ");
  } while (isbnValidation(isbn));

  //because only a valid isbn can be entered there can only be one or none search result
  results = searchISBN(isbn);
  if (results->count == 0)
  {
    printf("no book with the isbn '%s' was found\n", isbn);
    return;
  }
  book = results->books[0];
  printf("Amount of copies you want to delete (%d available): ", book->amount);
  while (scanf("%d", &amount) != 1 || amount > book->amount || amount <= 0)
  {
    printf("Invalid Input\nAmount: ");
    clearInput();
  }
  clearInput();
  if (amount == book->amount)
    deleteBook(book);
  else
    book->amount -= amount;
}

bool loadMenu(char *saveFile, int bufferSize)
{
  switch (menu(loadMenuText, 2))
  {
  case '1':
    strcpy(saveFile, "Save");
    break;

  case '2':
    do
    {
      printf("Path: ");
    } while (getString(saveFile, bufferSize - 1));
    break;

  case 'Q':
    return true;
    break;
  }
  clearConsole();
  return false;
}

void searchResultMenu(library *results)
{
  char *sortMenuText = "Sort by (1)ISBN (2)Title (3)Author\n";
  //print results sorted by given parameter
  switch (menu(sortMenuText, 3))
  {
  case '1':
    qsort(results->books, results->count, sizeof(book *), sortBooksIsbn);
    break;
  case '2':
    qsort(results->books, results->count, sizeof(book *), sortBooksTitle);
    break;
  case '3':
    qsort(results->books, results->count, sizeof(book *), sortBooksAuthor);
    break;
  default:
    break;
  }

  printLib(results);

  //calculate how much characters are needed to input the highest number shown as a result
  int count = 1;
  while (results->count / (10 * count) != 0)
  {
    count++;
  }

  char input[count + 1];
  int selection;
  printf("select a book to borrow, return or delete it (Q to quit)\n");
  do
  {
    printf("Selection: ");
  } while (getString(input, count));
  if (toupper(input[0]) == 'Q')
  {
    clearConsole();
    printf("no book selected\n");
    return;
  }
  selection = atoi(input);
  while (selection > results->count || selection < 1)
  {
    printf("Selected number was invalid\nSelection: ");
    do
    {
      printf("Selection: ");
    } while (getString(input, count));
    if (toupper(input[0]) == 'Q')
    {
      clearConsole();
      printf("no books selected\n");
      return;
    }
    selection = atoi(input);
  }
  clearConsole();
  printf("selected Book %d\n", selection);
  printBook(results->books[selection - 1]);
}

//void bookMenu(book* b){
//
//}
