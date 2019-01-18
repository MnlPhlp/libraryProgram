#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/data.h"
#include "../include/menu.h"
#include "../include/utils.h"

library lib;

unsigned long hashLib() {return 23;}

FILE *openFile(char *saveFile, char *mode)
{
  FILE *save = fopen(saveFile, mode);
  while (save == NULL)
  {
    printf(ANSI_COLOR_RED "standard save file could not be opened\n" ANSI_COLOR_RESET
                          "Error message: " ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
           strerror(errno));
    printf("try again? ");
    if (!yesno(true))
      break;
  }
  return save;
}

int loadData(char *saveFile)
{
  FILE *save = openFile(saveFile, "r");
  unsigned long length;
  //if the file couldn't be loaded create a new empty library
  if (save == NULL)
  {
    printf("new empty library will be used\n");
    lib.count = 0;
    lib.books = NULL;
    return 0;
  }
  fread(&lib.count, sizeof(int), 1, save);
  lib.books = calloc(lib.count, sizeof(book *));
  if (lib.books == NULL)
  {
    printf("memory could not be allocated\n");
    return 0;
  }
  for (int i = 0; i < lib.count; i++)
  {
    lib.books[i] = malloc(sizeof(book));
    if (lib.books[i] == NULL)
    {
      printf("memory could not be allocated\n");
      return 0;
    }
    //read amount as int
    fread(&lib.books[i]->amount, sizeof(int), 1, save);
    //read borrowed amount as int
    fread(&lib.books[i]->borrowed, sizeof(int), 1, save);
    //read isbn as char
    fread(&lib.books[i]->isbn, 11*sizeof(char), 1, save);
    //read title with length-value encoding
    fread(&length, sizeof(size_t), 1, save);
    lib.books[i]->title = malloc(length);
    if (lib.books[i]->title == NULL)
    {
      printf("memory could not be allocated\n");
      return 0;
    }
    fread(lib.books[i]->title, length, 1, save);
    //read author with length-value encoding
    fread(&length, sizeof(size_t), 1, save);
    lib.books[i]->author = malloc(length);
    if (lib.books[i]->author == NULL)
    {
      printf("memory could not be allocated\n");
      return 0;
    }
    fread(lib.books[i]->author, length, 1, save);
    //read each element of the borrower array
    lib.books[i]->borrower = malloc(sizeof(char *) * lib.books[i]->borrowed);
    if (lib.books[i]->borrower == NULL)
    {
      printf("memory could not be allocated\n");
      return 0;
    }
    for (int j = 0; j < lib.books[i]->borrowed; j++)
    {
      //read borrower with length-value encoding
      fread(&length, sizeof(size_t), 1, save);
      lib.books[i]->borrower[j] = malloc(length);
      if (lib.books[i]->borrower[j] == NULL)
      {
        printf("memory could not be allocated\n");
        return 0;
      }
      fread(lib.books[i]->borrower[j], length, 1, save);
    }
  }
  unsigned long checksum_test = hashLib();
  unsigned long checksum_file;
  fread(&checksum_file, sizeof(unsigned long), 1, save);
  if (checksum_test != checksum_file)
  {
    printf(ANSI_COLOR_RED "the file was changed or damaged\n" ANSI_COLOR_RESET);
  }
  fclose(save);
  return 0;
}

bool saveData(char *saveFile)
{
  char *backup = malloc(strlen(saveFile) + 8);
  size_t length;
  strcpy(backup, saveFile);
  strcat(backup, "_backup");
  while (rename(saveFile, backup))
  {
    printf(ANSI_COLOR_RED "backup couldn't be created" ANSI_COLOR_RESET "\ntry again?\n");
    if (!yesno(false))
      break;
  }
  FILE *save = openFile(saveFile, "w");
  if (save == NULL)
    return true;
  fwrite(&lib.count, sizeof(int), 1, save);
  for (int i = 0; i < lib.count; i++)
  {
    //save amount as int
    fwrite(&lib.books[i]->amount, sizeof(int), 1, save);
    //save borrowed amount as int
    fwrite(&lib.books[i]->borrowed, sizeof(int), 1, save);
    //save isbn as char
    fwrite(&lib.books[i]->isbn, 11*sizeof(char), 1, save);
    //save title with length-value encoding
    length = strlen(lib.books[i]->title) + 1;
    fwrite(&length, sizeof(size_t), 1, save);
    fwrite(lib.books[i]->title, length, 1, save);
    //save author with length-value encoding
    length = strlen(lib.books[i]->author) + 1;
    fwrite(&length, sizeof(size_t), 1, save);
    fwrite(lib.books[i]->author, length, 1, save);
    //save each element of the borrower array
    for (int j = 0; j < lib.books[i]->borrowed; j++)
    {
      //save borrower with length-value encoding
      length = strlen(lib.books[i]->borrower[j]) + 1;
      fwrite(&length, sizeof(size_t), 1, save);
      fwrite(lib.books[i]->borrower[j], length, 1, save);
    }
  }
  unsigned long checksum = hashLib();
  fwrite(&checksum, sizeof(unsigned long), 1, save);
  fclose(save);
  return false;
}

book *newBook(int amount, int borrowed, char isbn[11], char *title, char *author, char **borrower)
{
  book *newBook = malloc(sizeof(book));
  newBook->amount = amount;
  newBook->borrowed = borrowed;
  strcpy(newBook->isbn,isbn);
  newBook->title = malloc(strlen(title) + 1);
  strcpy(newBook->title, title);
  newBook->author = malloc(strlen(author) + 1);
  strcpy(newBook->author, author);
  newBook->borrower = malloc(sizeof(char *) * borrowed);

  for (int i = 0; i < newBook->borrowed; i++)
  {
    newBook->borrower[i] = malloc(strlen(borrower[i]));
    strcpy(newBook->borrower[i], borrower[i]);
  }

  return newBook;
}

bool addBook(int amount, int borrowed, char isbn[11], char *title, char *author, char **borrower)
{
  lib.count += 1;
  lib.books = realloc(lib.books, lib.count * sizeof(book *));
  lib.books[lib.count - 1] = newBook(amount, borrowed, isbn, title, author, borrower);
  return false;
}

bool deleteBook(book *book)
{
  free(book);  
  for(int i = 0; i < lib.count; i++)
  {
    //if the deleted book was not at the last position of books array
    if(lib.books[i] == book)
    {
      //move last element to the position of the deleted book
      lib.books[i] = lib.books[lib.count-1];
    }
  }
  lib.count -= 1;
  return false;
}

int borrowBook(book *book, char *borrower)
{
  //return 1 if there are no books available
  if (book->amount == book->borrowed)
    return 1;

  book->borrowed += 1;
  book->borrower = realloc(book->borrower, sizeof(char *) * book->borrowed);
  book->borrower[book->borrowed - 1] = malloc(strlen(borrower));
  if (book->borrower[book->borrowed - 1] == NULL)
    return 2;
  strcpy(book->borrower[book->borrowed - 1], borrower);
  return 0;
}

library *searchISBN(char *isbn) {
  library *results = malloc(sizeof(library));
  results->count = 0;
  results->books = NULL;
  for(int i = 0,j=0;i<lib.count;i++) {
    if(strstr(lib.books[i]->isbn,isbn)){
      j++;
      results->books = realloc(results->books,j*sizeof(book*));
      results->books[j-1] = lib.books[i];
      results->count = j;
    }
  }
  return results;
}

bool returnBook(book *book, char *borrower)
{

  for(int i = 0; i < book->borrowed; i++)
  {
    if (strcmp(book->borrower[i],borrower)){
      book->borrowed -= 1;
      free(book->borrower[i]);
      //if the deleted borrower was in middle of the array fill the empty space with last element
      if (i < book->borrowed){
        book->borrower[i] = book->borrower[book->borrowed];
      }
      book->borrower=realloc(book->borrower,book->borrowed*sizeof(*book));
      return true;
    }
  }
  
  //return false if there are no books borrowed from the given borrower
  return false;
}
