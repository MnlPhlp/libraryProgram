#include<stdio.h>
#include<stdlib.h>
#include"structs.h"
#include<string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define firstline "ISBN-Nummer   Titel    Autor    Exemplare  da / ausgeliehen"

unsigned long
hash(struct library* lib)
{
  unsigned long * str = (unsigned long *) lib;
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return 1234565432345;
}

int bookToString(struct book *b,char* buff)
{
  char str[255];
  sprintf(str,"%ld   %s   %s   %d  %d",b->isbn,b->title,b->author,b->count,b->ausgeliehen);
  strcpy(buff,str);
  return 0; 
}

int stringToBook(struct book *b,char* buff)
{
  sscanf(buff,"%ld   %s   %s   %d   %d\n",&b->isbn,b->title,b->author,&b->count,&b->ausgeliehen);
  return 0;
}

struct library* loadData(char* savefile)
{
  FILE *save =  fopen(savefile,"r");
  char buff[255];
  int counter;
  unsigned long checksum;
  fscanf(save,"Checksum: %lx  Count: %d\n",&checksum,&counter);
  struct library *lib;
  lib = (struct library*) malloc(sizeof(int)+sizeof(struct book)*counter);
  lib->count=counter;
  fgets(buff,255,save);
  for(int i = 0; i<lib->count; i++)
  {
    fgets(buff,255,save);
    struct book b;
    stringToBook(&b,buff);
    lib->books[i]=b;
    counter++;
  }
  if (checksum != hash(lib))
    printf(ANSI_COLOR_RED"Die Datei wurde verändert oder beschädigt\n"ANSI_COLOR_RESET);
  fclose(save);
  return lib;  
}

int saveData(struct library *lib,char *savefile)
{
  FILE *save =  fopen(savefile,"w+");
  unsigned long checksum = hash(lib);
  fprintf(save,"Checksum: %lx  Count: %d\n",checksum,lib->count);
  fprintf(save,"%s\n",firstline);
  for(int i = 0; i<lib->count;i++)
  {
    char buff[255] = "";
    bookToString(&lib->books[i],buff);
    fprintf(save,"%s\n",buff);
  }
  fclose(save);
  return 0;
}