#ifndef STRUCTURES
#define STRUCTURES

typedef unsigned char uint8;

typedef struct book
{
  uint8 amount;
  uint8 borrowed;
  char isbn[14];
  char *title;
  char *author;
  char **borrower;
}book;

typedef struct library
{
  int count;
  book **books;
}library;

#endif
