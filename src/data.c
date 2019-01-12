#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "data.h"
#include "visual.h"
#include "menu.h"

unsigned long
hash(library *lib)
{
  unsigned long *str = (unsigned long *)lib;
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return 1234565432345;
}

FILE *openFile(char *saveFile, char *mode)
{
  FILE *save = fopen(saveFile, mode);
  while (save == NULL)
  {
    printf(ANSI_COLOR_RED "standard save file could not be opened\n" ANSI_COLOR_RESET
          "Error message: " ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET, strerror(errno));
    printf("try again? ");
    if (!yesno(1))
      break;
  }
  return save;
}

library *loadData(char *saveFile)
{
  FILE *save = openFile(saveFile,"r");
  if (save == NULL)
    return NULL;
  size_t length;
  library *lib = malloc(sizeof(library));
  if (lib == NULL)
  {
     printf("memory could not be allocated\n");
    return NULL;
  }
  fread(&lib->count, sizeof(int), 1, save);
  lib->books = calloc(lib->count, sizeof(book *));
  if (lib->books == NULL)
  {
    printf("memory could not be allocated\n");
    return NULL;
  }
  for (int i = 0; i < lib->count; i++)
  {
    lib->books[i] = malloc(sizeof(book));
    //read amount as int
    fread(&lib->books[i]->amount, sizeof(int), 1, save);
    //read borrowed amount as int
    fread(&lib->books[i]->borrowed, sizeof(int), 1, save);
    //read isbn as long
    fread(&lib->books[i]->isbn, sizeof(long), 1, save);
    //read title with length-value encoding
    fread(&length, sizeof(size_t), 1, save);
    lib->books[i]->title = malloc(length);
    fread(lib->books[i]->title, length, 1, save);
    //read author with length-value encoding
    fread(&length, sizeof(size_t), 1, save);
    lib->books[i]->author = malloc(length);
    fread(lib->books[i]->author, length, 1, save);
    //read each element of the borrower array
    lib->books[i]->borrower = malloc(sizeof(char *) * lib->books[i]->borrowed);
    for (int j = 0; j < lib->books[i]->borrowed; j++)
    {
      //read borrower with length-value encoding
      fread(&length, sizeof(size_t), 1, save);
      lib->books[i]->borrower[j] = malloc(length);
      fread(lib->books[i]->borrower[j], length, 1, save);
    }
  }
  unsigned long checksum_test = hash(lib);
  unsigned long checksum_file;
  fread(&checksum_file, sizeof(unsigned long), 1, save);
  if (checksum_test != checksum_file)
  {
    printf(ANSI_COLOR_RED "the file was changed or damaged\n" ANSI_COLOR_RESET);
  }
  fclose(save);
  return lib;
}

int saveData(library *lib, char *saveFile)
{
  char *backup = malloc(strlen(saveFile) + 8);
  size_t length;
  strcpy(backup, saveFile);
  strcat(backup, "_backup");
  while (rename(saveFile, backup))
  {
    printf(ANSI_COLOR_RED "backup couldn't be created" ANSI_COLOR_RESET "\ntry again?\n");
    if (!yesno(1))
      break;
  }
  FILE *save = openFile(saveFile,"w+");
  if (save == NULL)
    return 1;
  fwrite(&lib->count, sizeof(int), 1, save);
  for (int i = 0; i < lib->count; i++)
  {
    //save amount as int
    fwrite(&lib->books[i]->amount, sizeof(int), 1, save);
    //save borrowed amount as int
    fwrite(&lib->books[i]->borrowed, sizeof(int), 1, save);
    //save isbn as long
    fwrite(&lib->books[i]->isbn, sizeof(long), 1, save);
    //save title with length-value encoding
    length = strlen(lib->books[i]->title) + 1;
    fwrite(&length, sizeof(size_t), 1, save);
    fwrite(lib->books[i]->title, length, 1, save);
    //save author with length-value encoding
    length = strlen(lib->books[i]->author) + 1;
    fwrite(&length, sizeof(size_t), 1, save);
    fwrite(lib->books[i]->author, length, 1, save);
    //save each element of the borrower array
    for (int j = 0; j < lib->books[i]->borrowed; j++)
    {
      //save borrower with length-value encoding
      length = strlen(lib->books[i]->borrower[j]) + 1;
      fwrite(&length, sizeof(size_t), 1, save);
      fwrite(lib->books[i]->borrower[j], length, 1, save);
    }
  }
  unsigned long checksum = hash(lib);
  fwrite(&checksum, sizeof(unsigned long), 1, save);
  fclose(save);
  return 0;
}

book *newBook(int amount, int borrowed, long isbn, char *title, char *author, char **borrower)
{
  book *newBook = malloc(sizeof(book));
  newBook->amount = amount;
  newBook->borrowed = borrowed;
  newBook->isbn = isbn;
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

int addBook(library *lib, int amount, int borrowed, long isbn, char *title, char *author, char **borrower)
{
  lib->count += 1;
  lib->books = realloc(lib->books, lib->count * sizeof(book *));
  lib->books[lib->count - 1] = newBook(amount, borrowed, isbn, title, author, borrower);
  return 0;
}

int deleteBook(library *lib, int index)
{
  free(lib->books[index]);
  lib->count -= 1;
  lib->books[index] = lib->books[lib->count];
  return 0;
}
