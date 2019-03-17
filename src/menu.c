#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "menu.h"
#include "utils.h"


void mainMenu()
{
  while (true)
  {
    switch (menu(mainMenuText, 6))
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
      if (lib.count > 0){
        // print the whole library
        searchResults(&lib);
        printf("Enter to continue..");
        // clear input buffer
        clearInput();
        // clear output
        clearConsole();
      }
      else
      {
        clearConsole();
        printf("library contains no Books\nhit enter to continue..");
        clearInput();
      }

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

void borrowInput(book* b){
  char borrower[buffSize];
  //show book which will be borrowed
  printf("Borrowing book:\n");
  printBook(b);
  do{
    printf("Name of borrower: ");
  } while (getString(borrower, buffSize - 1));
  // clear output for the next menu
  clearConsole();
  switch(borrowBook(b,borrower))
  {
    case 0:
      printf("book '%s' was successfully borrowed by '%s'\n",b->title,borrower);
      break;
    case 1:
      printf("the book '%s' is currently not in stock\n",b->title);
      break;
    case 2:
      printf("book could not be borrowed because memory could not be allocated\n");
      break;
  }
}

void returnInput(book* b){
  //calculate how much characters are needed to input the highest number shown as a borrower
  int count = 1;
  while (b->borrowed / (10 * count) != 0)
  {
    count++;
  }
  char input[count+1];
  int selection = 0;
  bool firstTry = true;
  printBook(b);
  printf("choose the borrower who is returning the book (Q to quit)\n");
  while (selection > b->borrowed || selection < 1)
  {
    if (!firstTry)
      printf("Selection was invalid\n");
    do
    {
      printf("Selection: ");
    } while (getString(input, count));
    if (toupper(input[0]) == 'Q')
    {
      clearConsole();
      printf("no book returned\n");
      // clear output
      clearConsole();
      return;
    }
    selection = atoi(input);
    // set firstTry false to give error message if user entered invalid input
    firstTry = false;
  }
  // clear output
  clearConsole();
  returnBook(b,selection-1);
  printf("book '%s' returned by '%s'",b->title,b->borrower[selection-1]);
}

void borrowMenu()
{
  // clear output of the main menu
  clearConsole();
  book *b = NULL;
  while (true)
  {
    switch (menu(borrowMenuText, 2))
    {
    case '1':
      b = searchSelect(search());
      break;

    case '2':
      b = selectByIsbn();
      break;

    case 'Q':
      // clear the output for the next menu
      clearConsole();
      // return to main menu
      return;
      break;
    }
    // clear the output for the next menu
    clearConsole();
    if (b != NULL){
      // check if book is in stock before asking borrower for his name
      if (b->amount > b ->borrowed){
        // ask the user to input his name and borrow the book
        borrowInput(b);
      }
      else{
        printf("the book '%s' is currently not in stock\n",b->title);
      }
    }
  }
}

void returnMenu()
{
  // clear output of the main menu
  clearConsole();
  book *b = NULL;
  while (true)
  {
    switch (menu(returnMenuText, 2))
    {
    case '1':
      b = searchSelect(search());
      break;

    case '2':
      b = selectByIsbn();
      break;

    case 'Q':
      // clear the output for the next menu
      clearConsole();
      // return to the main menu
      return;
      break;
    }
    if (b != NULL){
      returnInput(b);
    }
  }
}

library *search(){
  // clear output of the last program
  clearConsole();
  char keyword[buffSize + 1];
  // create library pointer to store results
  library *results = NULL;
    switch (menu(searchMenuText, 4))
    {
    case '1':
      do
      {
        printf("ISBN: ");
      } while (getString(keyword, 13));
      results = searchBook('i', keyword);
      break;

    case '2':
      do
      {
        printf("Title: ");
      } while (getString(keyword, buffSize));
      results = searchBook('t', keyword);
      break;

    case '3':
      do
      {
        printf("Author: ");
      } while (getString(keyword, buffSize));
      results = searchBook('a', keyword);
      break;

    case '4':
      do
      {
        printf("Borrower: ");
      } while (getString(keyword, buffSize));
      results = searchBook('b', keyword);
      break;

    case 'Q':
      clearConsole();
      break;
    default:
      printf("Invalid input\n");
      break;
    }
  return results;
}

book* searchSelect(library *results){
  // clear the output of the search menu
  clearConsole();
  book *b = NULL;
  //if there are results show them
  if (results !=NULL && results->count > 0){
    searchResults(results);
    printf("select a book to continue with (Q to quit)\n");
    b = selectBook(results);
  }
  else
  {
    clearConsole();
    printf("no Books found\n");
  }
  // free the memory allocated for the results
  if (results != NULL){
    free(results->books);
    free(results);
  }
  return b;
}

void addMenu()
{
  // clear ouput of main menu
  clearConsole();
  printf("Enter the data of the new book.\n");
  // enter ISBN first to detect if book is already stored
  char isbn[14] = "";
  do
  {
    printf("ISBN (Q to quit): ");
  } while (isbnValidation(isbn));
  if (isbn[0] == 'Q'){
    // quit the add menu
    clearConsole();
    printf("adding was cancled\n");
    // return to main menu
    return;
  }
  int i = 0;
  while (i < lib.count && !strstr(lib.books[i]->isbn, isbn))
  {
    i++;
  }

  if(i < lib.count){
    //save addres of the found book
    book *b=lib.books[i];
    // if ISBN is already stored just increase the count
    printf("A Book with the entered ISBN already exists\n\n");
    printBook(b);
    printf("how many copies do you want to add (max. %d)\n",255 - b->amount);
    int amount;
    // ask for the added amount
    printf("Amount: ");
    // check if input was successful
    while (scanf("%d", &amount) != 1 || amount + b->amount > 255 || amount + b->amount < 0)
    {
      clearInput();
      printf("Invalid input\nAmount:");
    }
    clearInput();
    b->amount += amount;
    // in this case we don't need more user input
    //clear output for main menu
    clearConsole();
    printf("added %d cop%s to the book '%s'\n"
    , amount, b->amount == 1 ? "y" : "ies", b->title);
    return;
  }

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
  printf("Amount (max. 255): ");
  while (scanf("%d", &amount) != 1 || amount > 255)
  {
    clearInput();
    printf("Invalid input\nAmount:");
  }
  // add the book with entered data
  addBook(amount, isbn, title, author);
  // clear input buffer
  clearInput();
  // clear output
  clearConsole();
  printf("Book '%s' added\n",title);
}

void deleteMenu()
{
  // clear the output of the main menu
  clearConsole();
  book *b = NULL;
  while (true)
  {
    switch (menu(deleteMenuText, 2))
    {
    case '1':
      b = searchSelect(search());
      break;

    case '2':
      b = selectByIsbn();
      break;

    case 'Q':
      // clear the output for the next menu
      clearConsole();
      // return to main menu
      return;
      break;
    }
    if (b != NULL){
      deleteBookMenu(b);
    }
  }
}

book *selectByIsbn()
{
  char isbn[14];
  library *results;
  book *b = NULL;
  //get a valid ISBN from user to clearly identify book
  do
  {
    printf("enter ISBN (Q to quit): ");
  } while (isbnValidation(isbn));
  if (isbn[0] == 'Q'){
    clearConsole();
    printf("no ISBN entered\n");
  }
  // search for the entered isbn
  results = searchBook('i', isbn);
  //because only a valid ISBN can be entered there can only be one search result or none
  if (results->count==0){
    clearConsole();
    printf("the library contains no book with ISBN '%s'\n",isbn);
  }
  else{
    b = results->books[0];
  }
  //free memory allocated for the search results
  free(results->books);
  free(results);
  return b;
}

void deleteBookMenu(book* b){
  int amount;
  // clear output of menu
  clearConsole();
  // show which book will be deleted
  printf("removing book:\n");
  printBook(b);
  // ask the user how many copies he wants to remove
  printf("enter the amount of copies you want to remove\n"
         "you can only remove the %d in stock (%d borrowed)\n"
         "Amount: ", b->amount - b->borrowed, b->borrowed);

  // accept only a number between 0 and the amount of copies in stock
  while (scanf("%d", &amount) != 1 || amount > b->amount-b->borrowed || amount < 0)
  {
    printf("Invalid Input\nAmount: ");
    // clear Input buffer
    clearInput();
  }
  // clear Input buffer
  clearInput();
  // clear output
  clearConsole();
  if (amount == b->amount){
    // delete the book completely from the library
    printf("the book '%s' was deleted from the library\n", b->title);
    deleteBook(b);
  }
  else{
    // remove given amount of copies
    b->amount -= amount;
    // inform the user
    if (amount == 1){
      printf("%d copy of the book '%s' was removed.\n%d cop%s remaining (%d in stock)\n"
      ,amount, b->title, b->amount, b->amount == 1 ? "y" : "ies", b->amount - b->borrowed);
    }
    else{
      printf("%d copies of the book '%s' were removed.\n%d cop%s remaining (%d in stock)\n"
      ,amount, b->title, b->amount, b->amount == 1 ? "y" : "ies", b->amount - b->borrowed);
    }
  }
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

void searchResults(library *results)
{
  // only sort if there is more than one result
  if (results->count > 1)
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
  }
  printLib(results);
}

book* selectBook(library *results){
  //calculate how much characters are needed to input the highest number shown as a result
  int count = 1;
  while (results->count / (10 * count) != 0)
  {
    count++;
  }

  char input[count + 1];
  int selection = 0;
  bool firstTry = true;
  while (selection > results->count || selection < 1)
  {
    if (!firstTry)
      printf("Selection was invalid\n");
    do
    {
      printf("Selection: ");
    } while (getString(input, count));
    if (toupper(input[0]) == 'Q')
    {
      clearConsole();
      printf("no book selected\n");
      return NULL;
    }
    selection = atoi(input);
    // set firstTry false to give error message if user entered invalid input
    firstTry = false;
  }
  // clear output for the next menu
  clearConsole();
  return results->books[selection-1];
}

void bookMenu(book *b)
{
  printBook(b);
  switch (menu("1) Borrow  2) Return  3) Delete\n",3))
  {
    case '1':
      borrowInput(b);
      break;

    case '2':
      returnInput(b);
      break;

    case '3':
      deleteBookMenu(b);
      break;

    default:
      break;
  }
}

void searchMenu(){
  library *results;
  while(true){
    results = search();
    if (results == NULL){
      break;
    }
    book *b = NULL;
    b = searchSelect(results);
    if (b != NULL){
      bookMenu(b);
    }
  }
}
