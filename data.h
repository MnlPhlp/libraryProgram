#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int yesno(int def);

unsigned long
hash(struct library *lib)
{
  unsigned long *str = (unsigned long *)lib;
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return 1234565432345;
}

struct library *loadData(char *savefile)
{
  FILE *save = fopen(savefile, "r");
  int count;
  size_t length;
  fread(&count, sizeof(int), 1, save);
  struct library *lib = malloc(sizeof(struct library) + sizeof(struct book *) * count);
  lib->count = count;
  for (int i = 0; i < lib->count; i++)
  {
    //read borrowed amount as int
    fread(&count, sizeof(int), 1, save);
    lib->books[i] = malloc(sizeof(struct book) + sizeof(char *) * count);
    lib->books[i]->borrowed = count;
    //read amount as int
    fread(&lib->books[i]->amount, sizeof(int), 1, save);
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
    printf(ANSI_COLOR_RED "Die Datei wurde verändert oder beschädigt\n" ANSI_COLOR_RESET);
  }
  fclose(save);
  return lib;
}

int saveData(struct library *lib, char *savefile)
{
  char *backup = malloc(strlen(savefile) + 8);
  size_t length;
  strcpy(backup, "backup_");
  strcat(backup, savefile);
  while (rename(savefile, backup))
  {
    printf(ANSI_COLOR_RED "backup couldn't be created" ANSI_COLOR_RESET"\ntry again?");
    if (!yesno(1))
      break;
  }
  FILE *save = fopen(savefile, "w+");
  fwrite(&lib->count, sizeof(int), 1, save);
  for (int i = 0; i < lib->count; i++)
  {
    //save borrowed amount as int
    fwrite(&lib->books[i]->borrowed, sizeof(int), 1, save);
    //save amount as int
    fwrite(&lib->books[i]->amount, sizeof(int), 1, save);
    //save isbn as long
    fwrite(&lib->books[i]->isbn, sizeof(long), 1, save);
    //save title with length-value encoding
    length = strlen(lib->books[i]->title)+1;
    fwrite(&length, sizeof(size_t), 1, save);
    fwrite(lib->books[i]->title, length, 1, save);
    //save author with length-value encoding
    length = strlen(lib->books[i]->author)+1;
    fwrite(&length, sizeof(size_t), 1, save);
    fwrite(lib->books[i]->author, length, 1, save);
    //save each element of the borrower array
    for (int j = 0; j < lib->books[i]->borrowed; j++)
    {
      //save borrower with length-value encoding
      length = strlen(lib->books[i]->borrower[j])+1;
      fwrite(&length, sizeof(size_t), 1, save);
      fwrite(lib->books[i]->borrower[j], length, 1, save);
    }
  }
  unsigned long checksum = hash(lib);
  fwrite(&checksum, sizeof(unsigned long), 1, save);
  fclose(save);
  return 0;
}

struct library *addBook(struct library *lib)
{
  lib = realloc(lib, sizeof(lib)+sizeof(struct book *));
  lib->books[lib->count+1] = malloc(sizeof(struct book));
  return lib;
}
