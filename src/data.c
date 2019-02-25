#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/data.h"
#include "../include/menu.h"
#include "../include/utils.h"

library lib = {0, NULL};

unsigned long hashStr(char * str){
  unsigned long hash = *str;
  int count = 0;
  while (*str != '\00'){
    hash += *str * count  ;
    count ++;
    str ++;
  }
  return hash;
}

unsigned long hashLib() 
{ 
  unsigned long hash = lib.count;
  for(int i = 0; i < lib.count; i++)
  {
    hash += lib.books[i]->amount;
    hash += lib.books[i]->borrowed;
    hash += hashStr(lib.books[i]->author);
    hash += hashStr(lib.books[i]->isbn);
    hash += hashStr(lib.books[i]->title);
    for (int j = 0; j<lib.books[i]->borrowed; j++){
      hash += hashStr(lib.books[i]->borrower[j]);
    }
  }
  return hash; 
}

int contentSize(FILE *file)
{
  // move file pointer to end of File
  fseek(file, 0, SEEK_END);
  // store position of file pointer to size
  int size = ftell(file);
  // move file pointer back to the start of the file
  rewind(file);
  return size;
}

FILE *openFile(char *saveFile, char *mode)
{
  FILE *save = fopen(saveFile, mode);
  while (save == NULL)
  {
    switch (errno)
    {
    case 2:
      // 2 means file/folder does not exist
      printf("file '%s' does not exist. Do you want to create it?\n"
       ANSI_COLOR_YELLOW "This only works if the folder already exists\n" ANSI_COLOR_RESET, saveFile);
      //try to create the file. This only works if the folder already exists
      if (yesno(true))
      {
        // use fopen with mode w to create the file
        save = fopen(saveFile, "wb");
        if (save != NULL)
        {
          clearConsole();
          printf("created file '%s'\n", saveFile);
        }
        else
        {
          clearConsole();
          printf("failed to create file '%s'\n", saveFile);
          return NULL;
        }
      }
      else
        return NULL;
      break;

    default:
      printf("try again?");
      printf(ANSI_COLOR_RED "Save file could not be opened\n" ANSI_COLOR_RESET
             "Error message: " ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
             strerror(errno));
      printf("try again? ");
      if (!yesno(false))
        return NULL;
      break;
    }
  }
  return save;
}

bool loadData(FILE *save)
{
  unsigned long length;
  fread(&lib.count, sizeof(int), 1, save);
  lib.books = calloc(lib.count, sizeof(book *));
  if (lib.books == NULL)
  {
    printf("memory could not be allocated\n");
    return true;
  }
  for (int i = 0; i < lib.count; i++)
  {
    lib.books[i] = malloc(sizeof(book));
    if (lib.books[i] == NULL)
    {
      printf("memory could not be allocated\n");
      return true;
    }
    //read amount as int
    fread(&lib.books[i]->amount, sizeof(uint8), 1, save);
    //read borrowed amount as int
    fread(&lib.books[i]->borrowed, sizeof(uint8), 1, save);
    //read isbn as char
    fread(&lib.books[i]->isbn, 11, 1, save);
    //read title with length-value encoding
    fread(&length, sizeof(size_t), 1, save);
    lib.books[i]->title = malloc(length);
    if (lib.books[i]->title == NULL)
    {
      printf("memory could not be allocated\n");
      return true;
    }
    fread(lib.books[i]->title, length, 1, save);
    //read author with length-value encoding
    fread(&length, sizeof(size_t), 1, save);
    lib.books[i]->author = malloc(length);
    if (lib.books[i]->author == NULL)
    {
      printf("memory could not be allocated\n");
      return true;
    }
    fread(lib.books[i]->author, length, 1, save);
    //read each element of the borrower array
    lib.books[i]->borrower = malloc(sizeof(char *) * lib.books[i]->borrowed);
    if (lib.books[i]->borrower == NULL)
    {
      printf("memory could not be allocated\n");
      return true;
    }
    for (int j = 0; j < lib.books[i]->borrowed; j++)
    {
      //read borrower with length-value encoding
      fread(&length, sizeof(size_t), 1, save);
      lib.books[i]->borrower[j] = malloc(length);
      if (lib.books[i]->borrower[j] == NULL)
      {
        printf("memory could not be allocated\n");
        return true;
      }
      fread(lib.books[i]->borrower[j], length, 1, save);
    }
  }
  unsigned long checksum_test = hashLib();
  unsigned long checksum_file;
  fread(&checksum_file, sizeof(unsigned long), 1, save);
  fclose(save);
  if (checksum_test != checksum_file)
  {
    printf(ANSI_COLOR_RED "The loaded library does not match the one saved to the file (checksum is invalid)\n" ANSI_COLOR_RESET
                          "Do you want to continue anyway?\n");
    if (!yesno(false))
    {
      return true;
    }
  }
  return false;
}

bool saveData(FILE *save)
{
  size_t length;
  if (save == NULL)
    return true;
  fwrite(&lib.count, sizeof(int), 1, save);
  for (int i = 0; i < lib.count; i++)
  {
    //save amount as int
    fwrite(&lib.books[i]->amount, sizeof(uint8), 1, save);
    //save borrowed amount as int
    fwrite(&lib.books[i]->borrowed, sizeof(uint8), 1, save);
    //save isbn as char
    fwrite(&lib.books[i]->isbn, 11, 1, save);
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
  return false;
}

book *newBook(int amount, int borrowed, char *isbn, char *title, char *author, char **borrower)
{
  book *newBook = malloc(sizeof(book));
  newBook->amount = amount;
  newBook->borrowed = borrowed;
  strcpy(newBook->isbn, isbn);
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

bool addBook(int amount, int borrowed, char *isbn, char *title, char *author, char **borrower)
{
  // increase count of books in library
  lib.count += 1;
  // allocate more space in book array
  lib.books = realloc(lib.books, lib.count * sizeof(book *));
  // store pointer to the new book at last position of book array
  lib.books[lib.count - 1] = newBook(amount, borrowed, isbn, title, author, borrower);
  return false;
}

void freeBook(book *b)
{
  //free all the memory allocated for the book
  free(b->title);
  free(b->author);
  for (int i = 0; i < b->borrowed; i++)
  {
    free(b->borrower[i]);
  }
  free(b->borrower);
  free(b);
}

bool deleteBook(book *b)
{
  freeBook(b);
  // if the deleted book was not at the last position of books array
  // move last element to the position of the deleted book
  for (int i = 0; i < lib.count; i++)
  {
    if (lib.books[i] == b)
    {
      lib.books[i] = lib.books[lib.count - 1];
    }
  }
  // lower the lib count and free the empty space on the books array
  lib.count -= 1;
  lib.books = realloc(lib.books, lib.count * sizeof(book *));
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

bool cmpIsbn(book *b, char * keyword){
  char buffer[strlen(b->isbn)+1];
  upperString(buffer, b->isbn);
  return strstr(buffer,keyword) != NULL;
}

bool cmpTitle(book *b, char * keyword){
  char buffer[strlen(b->title)+1];
  upperString(buffer, b->title);
  return strstr(buffer,keyword) != NULL;
}

bool cmpAuthor(book *b, char * keyword){
  char buffer[strlen(b->author)+1];
  upperString(buffer, b->author);
  return strstr(buffer,keyword) != NULL;
}

bool cmpBorrower(book *b, char *keyword){
  bool result = false;
  for (int j = 0; j < b->borrowed; j++){
    char buffer[strlen(b->borrower[j])+1];
    upperString(buffer,b->borrower[j]);
    if(strstr(buffer,keyword) != 0){
      result = true;
      break;
    };
  }
  return result;
}

library *searchBook(char mode, char *keyword)
{
  // create empty library
  library *results = calloc(1,sizeof(library));
  // create function pointer
  bool (*compare)(book *,char*);
  // store upper version of keyword to make search case insensitive
  upperString(keyword,keyword);
  // select the compare function according to search mode
  switch (mode)
  {
    case 'i':
      compare = cmpIsbn;
      break;
    case 't':
      compare = cmpTitle;
      break;
    case 'a':
      compare = cmpAuthor;
      break;
    case 'b':
      compare = cmpBorrower;
      break;
    default:
      printf("%c is no valid mode",mode);
      return NULL;
      break;
  }
  for (int i = 0, j = 0; i < lib.count; i++)
  {
    // check if the choosen parameter contains the keyword
    if (compare(lib.books[i],keyword))
    {
      j++;
      results->books = realloc(results->books, j * sizeof(book *));
      results->books[j - 1] = lib.books[i];
      results->count = j;
    }
  }
  return results;
}
 
void returnBook(book *b, int selection)
{
  // decrease number of borrowers
  b->borrowed--;
  // free space used to store the name of the borrower
  free(b->borrower[selection]);
  // if the borrower was not last element of the array move last element to free space
  if (selection != b->borrowed){
    b->borrower[selection]=b->borrower[b->borrowed];
  }
  b->borrower = realloc(b->borrower,b->borrowed*sizeof(book*));
}

int sortBooksIsbn(const void *a, const void *b)
{
  //stricmp already returns the value expected from qsort
  char *isbn1 = (*(book **)a)->isbn;
  char *isbn2 = (*(book **)b)->isbn;
  return stricmp(isbn1, isbn2);
}

int sortBooksTitle(const void *a, const void *b)
{
  //stricmp already returns the value expected from qsort
  char *title1 = (*(book **)a)->title;
  char *title2 = (*(book **)b)->title;
  return stricmp(title1, title2);
}

int sortBooksAuthor(const void *a, const void *b)
{
  //stricmp already returns the value expected from qsort
  char *author1 = (*(book **)a)->author;
  char *author2 = (*(book **)b)->author;
  return stricmp(author1, author2);
}
